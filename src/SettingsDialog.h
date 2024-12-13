#pragma once
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QApplication>
#include <QStyle>
#include <QOperatingSystemVersion>
#include "themes.h"
class SettingsDialog : public QDialog
{
    Q_OBJECT
private:
    QPushButton *themeDefault;
    QPushButton *themeNord;
public:
    explicit SettingsDialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        setWindowTitle("Настройки");
        setFixedSize(300, 200);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QHBoxLayout *row1 = new QHBoxLayout;
        QLabel *label1 = new QLabel("размер шрифта матриц:");
        fontSizeSpinBox = new QSpinBox;
        fontSizeSpinBox->setMinimum(1);
        fontSizeSpinBox->setMaximum(1000);
        row1->addWidget(label1);
        row1->addWidget(fontSizeSpinBox);
        mainLayout->addLayout(row1);

        QHBoxLayout *row2 = new QHBoxLayout;
        themeDefault = new QPushButton("Стандартная тема");
        themeNord = new QPushButton("Nord тема");
        row2->addWidget(themeDefault);
        row2->addWidget(themeNord);
        mainLayout->addLayout(row2);

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        QPushButton *saveButton = new QPushButton("Сохранить");
        QPushButton *cancelButton = new QPushButton("Отмена");
        buttonLayout->addStretch();
        buttonLayout->addWidget(saveButton);
        buttonLayout->addWidget(cancelButton);
        mainLayout->addLayout(buttonLayout);

        connect(fontSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
                this, &SettingsDialog::onFontSizeChanged);
        connect(themeDefault, &QPushButton::clicked, this, &SettingsDialog::onThemeDefaultClicked);
        connect(themeNord, &QPushButton::clicked, this, &SettingsDialog::onThemeNordClicked);
        connect(saveButton, &QPushButton::clicked, this, &SettingsDialog::saveSettings);
        connect(cancelButton, &QPushButton::clicked, this, &SettingsDialog::reject);

        loadSettings(); // Загрузка настроек при открытии окна
    }

private slots:
    void onFontSizeChanged(int value)
    {
        qDebug() << "Font size changed to:" << value;
        settings["font_size"] = value; // Сохраняем в JSON
    }

    void onThemeDefaultClicked()
    {               
        themeDefault->setEnabled(0);
        themeNord->setEnabled(1);
        qDebug() << "Default theme selected.";
        settings["theme"] = "default";
    }

    void onThemeNordClicked()
    {
        themeDefault->setEnabled(1);
        themeNord->setEnabled(0);
        qDebug() << "Nord theme selected.";
        settings["theme"] = "nord";
    }

    void saveSettings()
    {       
        
        QFile file("settings.json");
        if (!file.open(QIODevice::WriteOnly))
        {
            qWarning() << "Не удалось открыть файл для записи.";
            return;
        }

        QJsonDocument doc(settings);
        if (QOperatingSystemVersion::currentType() != QOperatingSystemVersion::Windows)
        {
            if (settings["theme"] == "default"){
                qobject_cast<QApplication *>(QCoreApplication::instance())->setStyleSheet("");
                qobject_cast<QApplication *>(QCoreApplication::instance())->setPalette(qobject_cast<QApplication *>(QCoreApplication::instance())->style()->standardPalette()); 
            }
            else if (settings["theme"] == "nord")
            {
                setNordPalette(*qobject_cast<QApplication *>(QCoreApplication::instance()));
            }
        }
        
        file.write(doc.toJson());
        file.close();

        qDebug() << "Settings saved to JSON.";
        accept();               
    }

    void loadSettings()
    {
        QFile file("settings.json");
        if (file.open(QIODevice::ReadOnly))
        {
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            settings = doc.object();
            file.close();
        }

      
        fontSizeSpinBox->setValue(settings.value("font_size").toInt(12));
        QString theme = settings.value("theme").toString("default");
        if (theme == "default")
        {
            themeDefault->setEnabled(0);
            themeNord->setEnabled(1);
            qDebug() << "Default theme loaded.";
        }
        else if (theme == "nord")
        {
            themeDefault->setEnabled(1);
            themeNord->setEnabled(0);
            qDebug() << "Nord theme loaded.";
        }
    }

private:
    QSpinBox *fontSizeSpinBox;
    QJsonObject settings;
};
