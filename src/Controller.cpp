#include "Controller.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QSlider>
#include <QSpinBox>
#include <QString>
#include <QTextEdit>
#include <QGroupBox>
#include <QWidget>
#include <QDebug>
#include <iostream>
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QRegularExpression>
#include <QObject>
#include <QRandomGenerator>
#include <string>
#include <vector>
#include <QMessageBox>
#include <QApplication>
#include "Matrix.h"
#include "SettingsDialog.h"

Controller::Controller()
{
    this->InitHeap();
    this->InitLayout();
    this->InitConnections();
    ModeGenIsPressed();

    for (int row = 0; row < firstM->matrixTable->rowCount(); ++row)
    {
        for (int col = 0; col < firstM->matrixTable->columnCount(); ++col)
        {
            if (QTableWidgetItem *item = firstM->matrixTable->item(row, col))
            {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

Controller::~Controller()
{
    qDebug() << "Controller::~Controller()";
    delete gen;

}

void Controller::firstBtIsPressed()
{
    this->firstM->ResizeMatrix(this->frist1SP->value(), this->frist2SP->value());    
    UpdateButtons();
}

void Controller::secondBtIsPressed()
{
    this->secondM->ResizeMatrix(this->second1SP->value(), this->second2SP->value());    
    UpdateButtons();
}

void Controller::firstGenBtIsPressed()
{
    for (size_t r = 0; r < this->firstM->matrixTable->rowCount(); r++)
    {
        for (size_t c = 0; c < this->firstM->matrixTable->columnCount(); c++)
        {
            QTableWidgetItem *item = this->firstM->matrixTable->item(r, c);
            if (item) {
            item->setText(std::to_string(QRandomGenerator::global()->bounded(41) - 20).c_str());  
            } else {
                qDebug() << "Элемент не существует!";
            }
            
        }
    }
    for (int row = 0; row < firstM->matrixTable->rowCount(); ++row)
    {
        for (int col = 0; col < firstM->matrixTable->columnCount(); ++col)
        {
            if (QTableWidgetItem *item = firstM->matrixTable->item(row, col))
            {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void Controller::seconGenBtIsPressed()
{
    for (size_t r = 0; r < this->secondM->matrixTable->rowCount(); r++)
    {
        for (size_t c = 0; c < this->secondM->matrixTable->columnCount(); c++)
        {
            QTableWidgetItem *item = this->secondM->matrixTable->item(r, c);
            if (item) {
            item->setText(std::to_string(QRandomGenerator::global()->bounded(41) - 20).c_str());  
            } else {
                qDebug() << "Элемент не существует!";
            }
            
        }
    }
    for (int row = 0; row < secondM->matrixTable->rowCount(); ++row)
    {
        for (int col = 0; col < secondM->matrixTable->columnCount(); ++col)
        {
            if (QTableWidgetItem *item = secondM->matrixTable->item(row, col))
            {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void Controller::foldIsPressed()
{
    QRegularExpression invalidCharPattern("[^0-9+-]");
    for (size_t row = 0; row < this->firstM->matrixTable->rowCount(); row++)
    {
        for (size_t collumn = 0; collumn < this->firstM->matrixTable->columnCount(); collumn++)
        {
            if (invalidCharPattern.match(this->firstM->matrixTable->item(row,collumn)->text()).hasMatch()){
                firstM->matrixTable->item(row,collumn)->setText("0");
            }
            if (invalidCharPattern.match(this->secondM->matrixTable->item(row,collumn)->text()).hasMatch()){
                secondM->matrixTable->item(row,collumn)->setText("0");
            }
        }
    }
    
    this->resultM->ResizeMatrix(this->firstM->matrixTable->columnCount(), this->firstM->matrixTable->rowCount());
    for (size_t row = 0; row < this->firstM->matrixTable->rowCount(); row++)
    {
        for (size_t collumn = 0; collumn < this->firstM->matrixTable->columnCount(); collumn++)
        {
            this->resultM->matrixTable->item(row,collumn)->setText(std::to_string(
                this->firstM->matrixTable->item(row,collumn)->text().toInt() +
                this->secondM->matrixTable->item(row,collumn)->text().toInt()
                ).c_str());
        }
    }
    
}

void Controller::subtractIsPressed()
{
    QRegularExpression invalidCharPattern("[^0-9+-]");
    for (size_t row = 0; row < this->firstM->matrixTable->rowCount(); row++)
    {
        for (size_t collumn = 0; collumn < this->firstM->matrixTable->columnCount(); collumn++)
        {
            if (invalidCharPattern.match(this->firstM->matrixTable->item(row,collumn)->text()).hasMatch()){
                firstM->matrixTable->item(row,collumn)->setText("0");
            }
            if (invalidCharPattern.match(this->secondM->matrixTable->item(row,collumn)->text()).hasMatch()){
                secondM->matrixTable->item(row,collumn)->setText("0");
            }
        }
    }
    

    this->resultM->ResizeMatrix(this->firstM->matrixTable->columnCount(), this->firstM->matrixTable->rowCount());
    for (size_t row = 0; row < this->firstM->matrixTable->rowCount(); row++)
    {
        for (size_t collumn = 0; collumn < this->firstM->matrixTable->columnCount(); collumn++)
        {
            this->resultM->matrixTable->item(row,collumn)->setText(std::to_string(
                this->firstM->matrixTable->item(row,collumn)->text().toInt() -
                this->secondM->matrixTable->item(row,collumn)->text().toInt()
                ).c_str());
        }
    }
}

bool Controller::multiplyIsPressed()
{
    if (firstM->matrixTable->columnCount() != secondM->matrixTable->rowCount()) return 1;
    
    QRegularExpression invalidCharPattern("[^0-9+-]");
    for (size_t row = 0; row < this->firstM->matrixTable->rowCount(); row++)
    {
        for (size_t collumn = 0; collumn < this->firstM->matrixTable->columnCount(); collumn++)
        {
            if (invalidCharPattern.match(this->firstM->matrixTable->item(row,collumn)->text()).hasMatch()){
                firstM->matrixTable->item(row,collumn)->setText("0");
            }
        }
    }
    for (size_t row = 0; row < this->secondM->matrixTable->rowCount(); row++)
    {
        for (size_t collumn = 0; collumn < this->secondM->matrixTable->columnCount(); collumn++)
        {
            if (invalidCharPattern.match(this->secondM->matrixTable->item(row,collumn)->text()).hasMatch()){
                secondM->matrixTable->item(row,collumn)->setText("0");
            }
        }
    }
    
    std::vector<std::vector<int>> First(firstM->matrixTable->rowCount(), std::vector<int>(firstM->matrixTable->columnCount(), 0));
    std::vector<std::vector<int>> Second(secondM->matrixTable->rowCount(), std::vector<int>(secondM->matrixTable->columnCount(), 0));
    
    

    for (size_t y = 0; y < firstM->matrixTable->rowCount(); y++)
    {
        for (size_t x = 0; x < firstM->matrixTable->columnCount(); x++)
        {
            First[y][x] = firstM->matrixTable->item(y,x)->text().toInt();
        }
        
    }
    for (size_t y = 0; y < secondM->matrixTable->rowCount(); y++)
    {
        for (size_t x = 0; x < secondM->matrixTable->columnCount(); x++)
        {
            Second[y][x] = secondM->matrixTable->item(y,x)->text().toInt();
        }
        
    }

    int rx, ry;
    ry = firstM->matrixTable->rowCount();
    rx = secondM->matrixTable->columnCount();
    std::vector<std::vector<int>> Result(ry,std::vector<int>(rx, 0));

    for (size_t x = 0; x < rx; x++)
    {
        for (size_t y = 0; y < ry; y++)
        {
            //Result[y][x] = x;
            int res = 0;
            for (size_t i = 0; i < rx; i++)
            {
                if (i >= ry || i >= firstM->matrixTable->columnCount() ||i >= secondM->matrixTable->rowCount())   break;                    
                res+=First[y][i] * Second[i][x];                
            }
            Result[y][x] = res;
        }
        
    }
    resultM->ResizeMatrix(rx,ry);
    
    for (size_t x = 0; x < rx; x++)
    {
        for (size_t y = 0; y < ry; y++)
        {
            resultM->matrixTable->item(y,x)->setText(std::to_string(Result[y][x]).c_str());            
        }
    }
    return 0;
}

void Controller::UpdateButtons()
{
    if (this->firstM->matrixTable->rowCount()    == this->secondM->matrixTable->rowCount()
    &&  this->firstM->matrixTable->columnCount() == this->secondM->matrixTable->columnCount())
    {
        this->fold->setEnabled(true);
        this->subtract->setEnabled(true);        
    }
    else
    {
        this->fold->setEnabled(false);
        this->subtract->setEnabled(false);
    }
    if (firstM->matrixTable->columnCount() != secondM->matrixTable->rowCount()) this->multiply->setEnabled(false);
    else    this->multiply->setEnabled(true);
    if (this->firstM->matrixTable->rowCount() == this->firstM->matrixTable->columnCount())
    {
        this->CalcDeterminant->setEnabled(true);
        this->CalcInverseM->setEnabled(true);
    }
    else{
        this->CalcDeterminant->setEnabled(false);
        this->CalcInverseM->setEnabled(false);
    }
}

void Controller::Mode1BIsPressed()
{
    secondM->matrixTable->hide();
    secondBt->hide();
    secondGenBt->hide();
    second1SP->hide();
    second2SP->hide();
    secondLb->hide();
    fold->hide();
    subtract->hide();
    multiply->hide();

    
    indexLb->show();
    Transpose->show();
    Multiplication->show();
    index->show();
    CalcInverseM->show();
    CalcDeterminant->show();
    Determinant->show();

    resultLb->show();
    resultM->matrixTable->show();
    firstLb->show();
    frist1SP->show();
    frist2SP->show();
    firstGenBt->show();
    firstBt->show();
    firstM->matrixTable->show();

    gen->hide();
}

void Controller::Mode2BIsPressed()
{
    secondM->matrixTable->show();
    secondBt->show();
    secondGenBt->show();
    second1SP->show();
    second2SP->show();
    secondLb->show();
    fold->show();
    subtract->show();
    multiply->show();

    indexLb->hide();
    Transpose->hide();
    Multiplication->hide();
    index->hide();
    CalcInverseM->hide();
    CalcDeterminant->hide();
    Determinant->hide();

    resultLb->show();
    resultM->matrixTable->show();
    firstLb->show();
    frist1SP->show();
    frist2SP->show();
    firstGenBt->show();
    firstBt->show();
    firstM->matrixTable->show();

    gen->hide();
}

void Controller::ModeGenIsPressed()
{
    secondM->matrixTable->hide();
    secondBt->hide();
    secondGenBt->hide();
    second1SP->hide();
    second2SP->hide();
    secondLb->hide();
    fold->hide();
    subtract->hide();
    multiply->hide();

    indexLb->hide();
    Transpose->hide();
    Multiplication->hide();
    index->hide();
    CalcInverseM->hide();
    CalcDeterminant->hide();
    Determinant->hide();

    resultLb->hide();
    resultM->matrixTable->hide();
    firstLb->hide();
    frist1SP->hide();
    frist2SP->hide();
    firstGenBt->hide();
    firstBt->hide();
    firstM->matrixTable->hide();
    gen->show();
}

void Controller::TransposeIsPressed()
{
    resultM->ResizeMatrix(firstM->matrixTable->rowCount(),firstM->matrixTable->columnCount());
    for (size_t y = 0; y < firstM->matrixTable->rowCount(); y++)
    {
        for (size_t x = 0; x < firstM->matrixTable->columnCount(); x++)
        {
            resultM->matrixTable->item(x,y)->setText(firstM->matrixTable->item(y,x)->text());
        }
    }
    for (int row = 0; row < resultM->matrixTable->rowCount(); ++row)
    {
        for (int col = 0; col < resultM->matrixTable->columnCount(); ++col)
        {
            if (QTableWidgetItem *item = resultM->matrixTable->item(row, col))
            {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
    
}

void Controller::MultiplicationIsPressed()
{
    resultM->ResizeMatrix(firstM->matrixTable->columnCount(),firstM->matrixTable->rowCount());
    for (size_t y = 0; y < this->firstM->matrixTable->rowCount(); y++)
    {
        for (size_t x = 0; x < this->firstM->matrixTable->columnCount(); x++)
        {
            resultM->matrixTable->item(y,x)->setText(std::to_string(firstM->matrixTable->item(y,x)->text().toInt() * index->value()).c_str());
        }
    }
    
}

void Controller::CalcDeterminantIsPressed()
{
    std::string s;
    s = "Детерминант = ";
    s += std::to_string(firstM->CalcDet());
    Determinant->setText(s.c_str());
    

}

void Controller::CalcInverseMIsPressed()
{
    if (resultM == nullptr)
    {
        QMessageBox::warning(nullptr, "Error", "Result matrix is not initialized.");
        return;
    }

    Matrix inv = firstM->Inverted();

    if (resultM->matrixTable == nullptr)
    {
        QMessageBox::warning(nullptr, "Error", "Matrix table for result is not initialized.");
        return;
    }

    int rows = inv.matrixTable->rowCount();
    int cols = inv.matrixTable->columnCount();

    if (resultM->matrixTable->rowCount() != rows || resultM->matrixTable->columnCount() != cols)
    {
        resultM->ResizeMatrix(cols, rows);
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            QTableWidgetItem* item = inv.matrixTable->item(i, j);
            if (item)
            {
                resultM->matrixTable->setItem(i, j, new QTableWidgetItem(item->text()));
            }
            else
            {
                resultM->matrixTable->setItem(i, j, new QTableWidgetItem("0"));
            }
        }
    }
}

void Controller::InitHeap()
{
    gen = new Generator;
    firstM = new Matrix;
    for (size_t r = 0; r < this->firstM->matrixTable->rowCount(); r++)
    {
        for (size_t c = 0; c < this->firstM->matrixTable->columnCount(); c++)
        {
            firstM->matrixTable->setItem(r,c,new QTableWidgetItem("0"));            
        }
    }
    secondM = new Matrix;
    resultM = new Matrix;
    resultM->SetIsChangable(0);
    firstL = new QVBoxLayout;
    secondL = new QVBoxLayout;
    firstLH = new QHBoxLayout;
    secondLH = new QHBoxLayout;
    resultLH = new QHBoxLayout;
    resultLHFB = new QHBoxLayout;
    resultLV = new QVBoxLayout;
    ModsLH = new QHBoxLayout;
    indexLH = new QHBoxLayout;

    Transpose = new QPushButton("Транспонирование");
    Multiplication = new QPushButton("Скалярно умножить на index");
    index = new QSpinBox;

    firstBt = new QPushButton("Применить");
    secondBt = new QPushButton("Применить");

    firstGenBt = new QPushButton("Сгенерировать");
    secondGenBt = new QPushButton("Сгенерировать");
    setts = new QPushButton("setts");    
    Mode1B = new QPushButton("Действия над одной матрицей");
    Mode2B = new QPushButton("Действия над двумя матрицами");
    ModeGen = new QPushButton("Генератор");
    fold = new QPushButton("Сложить");
    subtract = new QPushButton("Вычесть");
    multiply =  new QPushButton("Умножить");
    
    indexLb = new QLabel("index:");

    MainLayout = new QVBoxLayout;
    MatrixLayout = new QHBoxLayout;
    ActionsLayout = new QVBoxLayout;

    frist1SP = new QSpinBox;
    frist1SP->setValue(3);
    frist2SP = new QSpinBox;
    frist2SP->setValue(3);
    second1SP = new QSpinBox;
    second1SP->setValue(3);
    second2SP = new QSpinBox;
    second2SP->setValue(3);

    frist1SP->setMinimum(1);
    frist2SP->setMinimum(1);
    second1SP->setMinimum(1);
    second2SP->setMinimum(1);

    frist1SP->setMaximum(2000000000);
    frist2SP->setMaximum(2000000000);
    second1SP->setMaximum(2000000000);
    second2SP->setMaximum(2000000000);
    
    index->setMaximum(2000000000);
    index->setMinimum(-2000000000);

    CalcDeterminant = new QPushButton("Детерминант");
    CalcInverseM = new QPushButton("Обратная матрица");
    Determinant = new QLineEdit("Детерминант = ?");
    Determinant->setReadOnly(true);
}

void Controller::InitLayout()
{
    resultLb = new QLabel("Результат");
    resultLb->setAlignment(Qt::AlignCenter);

    firstLb = new QLabel("Матрица 1");
    firstLb->setAlignment(Qt::AlignCenter);

    secondLb = new QLabel("Матрица 2");
    secondLb->setAlignment(Qt::AlignCenter);
    
    ModsLH->addWidget(setts);
    ModsLH->addWidget(Mode1B);
    ModsLH->addWidget(Mode2B);
    ModsLH->addWidget(ModeGen);
    
    
    firstL->addWidget(firstLb);
    firstL->addLayout(firstLH);
    firstLH->addWidget(frist1SP);
    firstLH->addWidget(frist2SP);
    firstLH->addWidget(firstBt);
    firstLH->addWidget(firstGenBt);
    
    secondL->addWidget(secondLb);
    secondL->addLayout(secondLH);
    secondLH->addWidget(second1SP);
    secondLH->addWidget(second2SP);
    secondLH->addWidget(secondBt);
    secondLH->addWidget(secondGenBt);

    firstL->addWidget(firstM->matrixTable);

    secondL->addWidget(secondM->matrixTable);

    //resultLH->addLayout(ActionsLayout);
    resultLHFB ->addLayout(ActionsLayout);
    resultLHFB ->addLayout(resultLV);
    resultLV->addWidget(resultLb);
    resultLV->addWidget(resultM->matrixTable);
    // resultLH->addLayout(resultLV);

    ActionsLayout->addWidget(fold);
    ActionsLayout->addWidget(subtract);
    ActionsLayout->addWidget(multiply);

    MainLayout->addLayout(gen->MainLayout);
    MainLayout->addLayout(MatrixLayout);
    MainLayout->addLayout(resultLHFB);
    MatrixLayout->addLayout(firstL);
    MatrixLayout->addLayout(secondL);
    MainLayout->addLayout(ModsLH);

    Transpose->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    Multiplication->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    CalcDeterminant->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    CalcInverseM->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    secondL->addWidget(Transpose);
    secondL->addWidget(Multiplication);
    secondL->addWidget(CalcDeterminant);
    secondL->addWidget(CalcInverseM);
    secondL->addLayout(indexLH);    
    indexLH->addWidget(indexLb);
    indexLH->addWidget(index);
    indexLH->addWidget(Determinant);
    indexLH->setStretch(1, 1);

    CalcInverseM->hide();
    CalcDeterminant->hide();
    index->hide();
    indexLb->hide();
    Transpose->hide();
    Multiplication->hide();
    Determinant->hide();
    
}

void Controller::InitConnections()
{
    QObject::connect(this->firstBt, &QPushButton::clicked, [this]() {
    this->firstBtIsPressed();
    });
    QObject::connect(this->secondBt, &QPushButton::clicked, [this]() {
    this->secondBtIsPressed();
    });

    QObject::connect(this->firstGenBt, &QPushButton::clicked, [this]() {
    this->firstGenBtIsPressed();
    });
    QObject::connect(this->secondGenBt, &QPushButton::clicked, [this]() {
    this->seconGenBtIsPressed();
    });

    QObject::connect(this->fold, &QPushButton::clicked, [this]() {
    this->foldIsPressed();
    });
    QObject::connect(this->subtract, &QPushButton::clicked, [this]() {
    this->subtractIsPressed();
    });
    QObject::connect(this->multiply, &QPushButton::clicked, [this]() {
    this->multiplyIsPressed();
    });

    QObject::connect(this->Mode1B, &QPushButton::clicked, [this]() {
    this->Mode1BIsPressed();
    });
    QObject::connect(this->Mode2B, &QPushButton::clicked, [this]() {
    this->Mode2BIsPressed();
    });
    QObject::connect(this->ModeGen, &QPushButton::clicked, [this]() {
    this->ModeGenIsPressed();
    });

    QObject::connect(this->Transpose, &QPushButton::clicked, [this]() {
    this->TransposeIsPressed();
    });

    QObject::connect(this->Multiplication, &QPushButton::clicked, [this]() {
    this->MultiplicationIsPressed();
    });

    QObject::connect(this->CalcDeterminant, &QPushButton::clicked, [this]() {
    this->CalcDeterminantIsPressed();
    });

    QObject::connect(this->CalcInverseM, &QPushButton::clicked, [this]() {
    this->CalcInverseMIsPressed();
    });

    QObject::connect(setts, &QPushButton::clicked, [this]() {
    SettingsDialog settingsDialog(nullptr);
    if (settingsDialog.exec() == QDialog::Accepted)
    {        
        QFile file("settings.json");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            QJsonObject jsonObj = doc.object();

            int fontsize = jsonObj["font_size"].toInt();
            this->firstM->SetFontSize(fontsize);
            this->secondM->SetFontSize(fontsize);
            this->resultM->SetFontSize(fontsize);
            this->gen->FirstM.SetFontSize(fontsize);
            this->gen->SecondM.SetFontSize(fontsize);
        }
        qDebug() << "Настройки сохранены.";
    }
    else
    {
        qDebug() << "Настройки отменены.";
    }
    });

}  
