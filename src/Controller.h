#pragma once
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
#include <QHeaderView>
#include <vector>
#include <QObject>
#include "Matrix.h"

#include "Generator.h"

class MainWindow;

class Controller : public QObject
{
    //Q_OBJECT
private:
    Generator* gen;

    Matrix *firstM;
    Matrix *secondM;
    Matrix *resultM;
    
    QVBoxLayout *firstL;
    QVBoxLayout *secondL;

    QHBoxLayout *firstLH;
    QHBoxLayout *secondLH;

    QHBoxLayout *resultLH;
    QHBoxLayout *resultLHFB;
    QVBoxLayout *resultLV;

    QHBoxLayout *ModsLH;

    QPushButton *firstBt;
    QPushButton *secondBt;

    QPushButton *firstGenBt;
    QPushButton *secondGenBt;

    QPushButton *Mode1B;
    QPushButton *Mode2B;
    QPushButton *ModeGen;
    QPushButton *setts;

    QPushButton *fold;
    QPushButton *subtract;
    QPushButton *multiply;

    QSpinBox *frist1SP;
    QSpinBox *frist2SP;

    QSpinBox *second1SP;
    QSpinBox *second2SP;

    QVBoxLayout *ActionsLayout;
    QHBoxLayout *MatrixLayout;

    QLabel *firstLb;
    QLabel *secondLb;
    QLabel *resultLb;

    QHBoxLayout *indexLH;
    QLabel *indexLb;
    QSpinBox *index;
    QPushButton *Transpose;
    QPushButton *Multiplication;

    QPushButton *CalcDeterminant;
    QPushButton *CalcInverseM;
    QLineEdit *Determinant;

public:
    QVBoxLayout *MainLayout;   
    Controller(/* args */);
    ~Controller();

    

private:
    void firstBtIsPressed();
    void secondBtIsPressed();

    void firstGenBtIsPressed();
    void seconGenBtIsPressed();

    void foldIsPressed();
    void subtractIsPressed();
    bool multiplyIsPressed();
    void UpdateButtons();

    void Mode1BIsPressed();
    void Mode2BIsPressed();
    void ModeGenIsPressed();
    void TransposeIsPressed();
    void MultiplicationIsPressed();

    void CalcDeterminantIsPressed();
    void CalcInverseMIsPressed();

    void InitHeap();
    void InitLayout();
    void InitConnections();
    friend MainWindow;
};
