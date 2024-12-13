#pragma once
#include <QTableWidget>
#include <QHeaderView>
#include <vector>
class Matrix;


class Matrix
{
private:
    
public:
    QTableWidget *matrixTable;
    Matrix(/* args */);
    Matrix(int collons, int rows);
    Matrix(const Matrix& other); 
    Matrix& operator=(const Matrix& other); 
    Matrix Inverted();
    static std::vector<std::vector<double>> GetInverted(std::vector<std::vector<double>> mat);
    bool ResizeMatrix(int collons, int rows);
    void SetIsChangable(bool IsChangable);
    int CalcDet();
    int CalcDet(std::vector<std::vector<int>> m);
    void SetFontSize(int FontSize);
    ~Matrix();
};
