#include "Generator.h"
#include <vector>
#include <QRandomGenerator>
#include <QMessageBox>
void Generator::InitHeap()
{
    this->MainLayout = new QVBoxLayout;
    GenerateBt.setText("Сгенерировать");
    
    SizeLb.setText("Строки");

    Instruction.setText("Генерирует случайную матрицу и проверяет обратную на целочисленность, возвращает две целочисленные обратные матрицы.");
    SizeLb.setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    DiapasoneFromLb.setText("Минимум");
    DiapasoneToLb.setText("Максимум");  
    DiapasoneFromLb.setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    DiapasoneToLb.setAlignment(Qt::AlignRight | Qt::AlignVCenter);
}
void Generator::InitLayout()
{
    MainLayout->addLayout(&GridButtonsLayout);
    MainLayout->addLayout(&MatrixLayout);
    MainLayout->addWidget(&Instruction);
    Instruction.setWordWrap(true);
    
    GridButtonsLayout.addWidget(&GenerateBt,0,0);
    //GenerateBt.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    GridButtonsLayout.addWidget(&DiapasoneFromLb,0,1);
    GridButtonsLayout.addWidget(&DiapasoneFromSb,0,2);
    GridButtonsLayout.addWidget(&DiapasoneToLb,0,3);
    GridButtonsLayout.addWidget(&DiapasoneToSb,0,4);


    
    GridButtonsLayout.addWidget(&SizeLb,0,5);
    

    GridButtonsLayout.addWidget(&ResultSizeSb,0,6);
    
    
    MatrixLayout.addWidget(FirstM.matrixTable);
    MatrixLayout.addWidget(SecondM.matrixTable);

    ResultSizeSb.setMinimum(1);
    DiapasoneToSb.setMinimum(-1000000);
    DiapasoneFromSb.setMinimum(-1000000);
    DiapasoneFromSb.setMaximum(10000000);
    DiapasoneToSb.setMaximum(10000000);

    ResultSizeSb.setValue(3);
    DiapasoneFromSb.setValue(-9);
    DiapasoneToSb.setValue(9);

    FirstM.SetIsChangable(0);
    SecondM.SetIsChangable(0);
}

void Generator::InitConnections()
{
    QObject::connect(&this->GenerateBt, &QPushButton::clicked, [this]() {
    this->GenBtIsPressed();
    });
}

void Generator::GenBtIsPressed()
{    
    int Size, RandFrom, RandTo;
    Size = this->ResultSizeSb.value();
    RandFrom = this->DiapasoneFromSb.value();
    RandTo = this->DiapasoneToSb.value();

    if (RandFrom >= RandTo || Size == 1)
    {
        QMessageBox::warning(nullptr, "Ошибка", "Некорректные значения.");

        return;
    }
    SecondM.ResizeMatrix(Size, Size);
    FirstM.ResizeMatrix(Size, Size);    
    
    std::vector<std::vector<double>> mat(Size, std::vector<double>(Size));
    std::vector<std::vector<double>> revmat(Size, std::vector<double>(Size));
    bool IsGenerationComplited = 0;
    bool ContainNonInt = 0;
    bool IsErr = 0;
    while (!IsGenerationComplited)
    {
        ContainNonInt = 0;
        IsErr = 0;
        for (size_t i = 0; i < Size; i++)
        {
            for (size_t j = 0; j < Size; j++)
            {
                mat[i][j] = QRandomGenerator::global()->bounded(RandFrom, RandTo);
            }
        }        
        try
        {
            revmat = Matrix::GetInverted(mat);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            IsErr = 1;
        }        
        if (IsErr)  
        {
            ContainNonInt = 1;
            IsGenerationComplited = 0;
            continue;            
        }
        for (size_t i = 0; i < Size; i++)
        {
            for (size_t j = 0; j < Size; j++)
            {
                if (std::abs(revmat[i][j] - std::round(revmat[i][j])) > 1e-9)
                {
                    ContainNonInt = 1;
                }
            }
        }  
        if (!ContainNonInt)
        {
            IsGenerationComplited = 1;
        }
    }
    for (size_t i = 0; i < Size; i++)
    {
        for (size_t j = 0; j < Size; j++)
        {
            std::string temp = std::to_string(mat[i][j]);
            int tint = temp.find(",");
            if (tint == -1 || tint > temp.size())   tint = temp.find(".");
            temp = temp.substr(0,tint);
            this->FirstM.matrixTable->item(i,j)->setText(temp.c_str());
            temp = std::to_string(revmat[i][j]);
            tint = temp.find(",");
            if (tint == -1 || tint > temp.size())   tint = temp.find(".");
            temp = temp.substr(0,tint);
            this->SecondM.matrixTable->item(i,j)->setText(temp.c_str());
        }       
    }
    
}

void Generator::show()
{
    FirstM.matrixTable->show();
    SecondM.matrixTable->show();
    GenerateBt.show();
    ResultSizeSb.show();

    DiapasoneFromLb.show();
    DiapasoneFromSb.show();
    DiapasoneToLb.show();
    DiapasoneToSb.show();
    Instruction.show();
    
    SizeLb.show();

}

void Generator::hide()
{
    FirstM.matrixTable->hide();
    SecondM.matrixTable->hide();
    GenerateBt.hide();
    ResultSizeSb.hide();  

    DiapasoneFromLb.hide();
    DiapasoneFromSb.hide();
    DiapasoneToLb.hide();
    DiapasoneToSb.hide();
    Instruction.hide();
    
    SizeLb.hide();
}

Generator::Generator()
{
    this->InitHeap();
    this->InitLayout();
    this->InitConnections();
}

Generator::~Generator()
{
    qDebug() << "Generator::~Generator()";
}
