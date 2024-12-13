#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
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
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) {
    std::cout << "MainWindow()\n";
    setWindowTitle("Matrix");
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    cont = new Controller;
    layout->addLayout(cont->MainLayout);
    
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    //resize(800, 500);
    QFile file("settings.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject jsonObj = doc.object();

        int fontsize = jsonObj["font_size"].toInt();
        cont->firstM->SetFontSize(fontsize);
        cont->secondM->SetFontSize(fontsize);
        cont->resultM->SetFontSize(fontsize);
        cont->gen->FirstM.SetFontSize(fontsize);
        cont->gen->SecondM.SetFontSize(fontsize);
    }
    show();
    
}


MainWindow::~MainWindow()
{
    qDebug() << "MainWindow::~MainWindow()";
    
    delete this->cont;
}
