#include <math.h>
#include "Matrix.h"
#include <vector>
#include <QMessageBox>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include <QTime>
#include <QtDebug>
#include <QRandomGenerator>


Matrix::Matrix()
{
    matrixTable = new QTableWidget(3, 3);
    this->ResizeMatrix(3,3);
    //matrixTable->setMaximumSize(300, 300);
    matrixTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Отключаем возможность выбора ячеек
    matrixTable->setSelectionMode(QAbstractItemView::NoSelection);

    // Отключаем фокусировку на ячейках
    matrixTable->setFocusPolicy(Qt::NoFocus);
    matrixTable->setSelectionMode(QAbstractItemView::SingleSelection);
    matrixTable->setEditTriggers(QAbstractItemView::AllEditTriggers);

}
Matrix::Matrix(const Matrix& other)
{
    if (other.matrixTable)
    {
        matrixTable = new QTableWidget(other.matrixTable->rowCount(), other.matrixTable->columnCount());
        for (int i = 0; i < other.matrixTable->rowCount(); ++i)
        {
            for (int j = 0; j < other.matrixTable->columnCount(); ++j)
            {
                QTableWidgetItem* item = other.matrixTable->item(i, j);
                if (item)
                {
                    matrixTable->setItem(i, j, new QTableWidgetItem(*item));
                }
            }
        }
    }
    else
    {
        matrixTable = nullptr;
    }
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other)
        return *this;

    delete matrixTable;

    if (other.matrixTable)
    {
        matrixTable = new QTableWidget(other.matrixTable->rowCount(), other.matrixTable->columnCount());
        for (int i = 0; i < other.matrixTable->rowCount(); ++i)
        {
            for (int j = 0; j < other.matrixTable->columnCount(); ++j)
            {
                QTableWidgetItem* item = other.matrixTable->item(i, j);
                if (item)
                {
                    matrixTable->setItem(i, j, new QTableWidgetItem(*item));
                }
            }
        }
    }
    else
    {
        matrixTable = nullptr;
    }

    return *this;
}

Matrix::Matrix(int collons, int rows)
{
    matrixTable = new QTableWidget(collons, rows);
    this->ResizeMatrix(collons,rows);
    matrixTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixTable->setSelectionMode(QAbstractItemView::NoSelection);

    matrixTable->setFocusPolicy(Qt::NoFocus);
    matrixTable->setSelectionMode(QAbstractItemView::SingleSelection);
    matrixTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    for (int row = 0; row < this->matrixTable->rowCount(); ++row)
    {
        for (int col = 0; col < this->matrixTable->columnCount(); ++col)
        {
            if (QTableWidgetItem *item = this->matrixTable->item(row, col))
            {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }

}

Matrix Matrix::Inverted()
{
    int n = matrixTable->rowCount();
    if (n != matrixTable->columnCount())
    {
        QMessageBox::warning(nullptr, "Ошибка", "Для нахождения обратной матрицы она должна быть квадратной.");
        return *this;
    }

    std::vector<std::vector<double>> mat(n, std::vector<double>(2 * n));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            mat[i][j] = matrixTable->item(i, j)->text().toDouble();
        }
        for (int j = n; j < 2 * n; ++j)
        {
            mat[i][j] = (i == (j - n)) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (mat[i][i] == 0)
        {
            bool swapped = false;
            for (int k = i + 1; k < n; ++k)
            {
                if (mat[k][i] != 0)
                {
                    std::swap(mat[i], mat[k]);
                    swapped = true;
                    break;
                }
            }
            if (!swapped)
            {
                QMessageBox::warning(nullptr, "Ошибка", "Матрица является единственной и не может быть Инвертирована.");
                return *this;
            }
        }

        double diagElement = mat[i][i];
        for (int j = 0; j < 2 * n; ++j)
        {
            mat[i][j] /= diagElement;
        }

        for (int k = 0; k < n; ++k)
        {
            if (k != i)
            {
                double factor = mat[k][i];
                for (int j = 0; j < 2 * n; ++j)
                {
                    mat[k][j] -= factor * mat[i][j];
                }
            }
        }
    }

    Matrix invertedMatrix(n, n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            invertedMatrix.matrixTable->setItem(i, j, new QTableWidgetItem(QString::number(mat[i][j + n])));
        }
    }

    return invertedMatrix;
}

std::vector<std::vector<double>> Matrix::GetInverted(std::vector<std::vector<double>> mat)
{
    int n = mat.size();
    if (n == 0 || mat[0].size() != n)
    {
        throw std::invalid_argument("Матрица должна быть квадратной.");
    }
    std::vector<std::vector<double>> extendedMat(n, std::vector<double>(2 * n, 0.0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            extendedMat[i][j] = mat[i][j];
        }
        for (int j = n; j < 2 * n; ++j)
        {
            extendedMat[i][j] = (i == (j - n)) ? 1.0 : 0.0;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        if (extendedMat[i][i] == 0)
        {
            bool swapped = false;
            for (int k = i + 1; k < n; ++k)
            {
                if (extendedMat[k][i] != 0)
                {
                    std::swap(extendedMat[i], extendedMat[k]);
                    swapped = true;
                    break;
                }
            }
            if (!swapped)
            {
                throw std::runtime_error("Матрица является вырожденной и не может быть обращена.");
            }
        }
        double diagElement = extendedMat[i][i];
        for (int j = 0; j < 2 * n; ++j)
        {
            extendedMat[i][j] /= diagElement;
        }
        for (int k = 0; k < n; ++k)
        {
            if (k != i)
            {
                double factor = extendedMat[k][i];
                for (int j = 0; j < 2 * n; ++j)
                {
                    extendedMat[k][j] -= factor * extendedMat[i][j];
                }
            }
        }
    }
    std::vector<std::vector<double>> invertedMat(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            invertedMat[i][j] = extendedMat[i][j + n];
        }
    }

    return invertedMat;
}

std::vector<std::vector<double>> Matrix::GetInvertedFORSPECIALUSE(std::vector<std::vector<double>> mat, bool &isError)
{
int n = mat.size();
    isError = false;

    if (n == 0 || mat[0].size() != n) {
        isError = true; // Матрица не квадратная
        return std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
    }

    std::vector<std::vector<double>> extendedMat(n, std::vector<double>(2 * n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            extendedMat[i][j] = mat[i][j];
        }
        for (int j = n; j < 2 * n; ++j) {
            extendedMat[i][j] = (i == (j - n)) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (extendedMat[i][i] == 0) {
            bool swapped = false;
            for (int k = i + 1; k < n; ++k) {
                if (extendedMat[k][i] != 0) {
                    std::swap(extendedMat[i], extendedMat[k]);
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                isError = true; // Матрица вырожденная
                return std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
            }
        }

        double diagElement = extendedMat[i][i];
        for (int j = 0; j < 2 * n; ++j) {
            extendedMat[i][j] /= diagElement;
        }
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = extendedMat[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    extendedMat[k][j] -= factor * extendedMat[i][j];
                }
            }
        }
    }

    std::vector<std::vector<double>> invertedMat(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            invertedMat[i][j] = extendedMat[i][j + n];
        }
    }

    return invertedMat;
}

#include <QRandomGenerator>
#include <QDebug>
#include <vector>
#include <cmath>


bool Matrix::ResizeMatrix(int collons, int rows)
{
    if (collons < 1 ||rows < 1) return true;
    matrixTable->clearContents();

    matrixTable->setRowCount(rows);
    matrixTable->setColumnCount(collons);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < collons; ++col) {
            matrixTable->setItem(row, col, new QTableWidgetItem(QString("0")));
        }
    }
    for (int row = 0; row < this->matrixTable->rowCount(); ++row)
    {
        for (int col = 0; col < this->matrixTable->columnCount(); ++col)
        {
            if (QTableWidgetItem *item = this->matrixTable->item(row, col))
            {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
    return false;
}

void Matrix::SetIsChangable(bool IsChangable)
{
    if (IsChangable){
        matrixTable->setFocusPolicy(Qt::StrongFocus);
        matrixTable->setSelectionMode(QAbstractItemView::SingleSelection);
        matrixTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    }
    else{
        matrixTable->setFocusPolicy(Qt::NoFocus);
        matrixTable->setSelectionMode(QAbstractItemView::NoSelection);
        matrixTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        
    }                
}

int Matrix::CalcDet()
{
    QRegularExpression invalidCharPattern("[^0-9+-]");
    for (size_t row = 0; row < this->matrixTable->rowCount(); row++)
    {
        for (size_t collumn = 0; collumn < this->matrixTable->columnCount(); collumn++)
        {
            if (invalidCharPattern.match(this->matrixTable->item(row,collumn)->text()).hasMatch()){
                matrixTable->item(row,collumn)->setText("0");
            }
        }
    }
    std::vector<std::vector<int>> Fir(matrixTable->rowCount(), std::vector<int>(matrixTable->columnCount(), 0));
    int Res = 0;
    for (size_t y = 0; y < matrixTable->rowCount(); y++)
    {
        for (size_t x = 0; x < matrixTable->columnCount(); x++)
        {
            Fir[y][x] = matrixTable->item(y,x)->text().toInt();
        }
        
    }
    if (Fir.size() == 2)
    {
        Res = Fir[0][0] * Fir[1][1] - Fir[0][1] * Fir[1][0];
    }
    else if (Fir.size() == 1) return Fir[0][0];
    else    return this->CalcDet(Fir);
    return Res;
}

int Matrix::CalcDet(std::vector<std::vector<int>> m)
{
    int Res = 0;
    if (m.size() == 2)
    {
        Res = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }
    else
    {
        for (size_t i = 0; i < m.size(); i++)
        {
            std::vector<std::vector<int>> lm;
            lm.resize(m.size() - 1);
            for (size_t j = 0; j < lm.size(); j++)
            {
                lm[j].resize(m.size() - 1);
            }
            for (size_t y = 0; y < lm.size(); y++)
            {
                for (size_t x = 0; x < lm.size(); x++)
                {
                    int rX = (x >= i) ? x + 1 : x;
                    lm[y][x] = m[y + 1][rX];
                }
            }

            Res += m[0][i] * std::pow(-1, i) * CalcDet(lm);
        }
    }
    return Res;
}

void Matrix::SetFontSize(int FontSize)
{
    QFont font = matrixTable->font();
    font.setPointSize(FontSize);
    matrixTable->setFont(font);
}

Matrix::~Matrix()
{
    delete matrixTable;
}
