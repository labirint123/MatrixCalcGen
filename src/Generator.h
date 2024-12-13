#pragma once
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

class Generator
{
public:
    Matrix FirstM;
    Matrix SecondM;
private:
    QHBoxLayout ButtonsLayout;    
    QHBoxLayout MatrixLayout;
    QGridLayout GridButtonsLayout;
    QPushButton GenerateBt;      
    QSpinBox ResultSizeSb;

    QSpinBox DiapasoneFromSb;
    QSpinBox DiapasoneToSb;
    QLabel DiapasoneFromLb;
    QLabel DiapasoneToLb;

    
    QLabel SizeLb;
    QLabel Instruction;    

    void InitHeap();
    void InitLayout();
    void InitConnections();
    void GenBtIsPressed();
public:
    QVBoxLayout *MainLayout;
    void show();
    void hide();
    Generator(/* args */);
    ~Generator();
};