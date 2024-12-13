#pragma once
#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QPalette>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayout>

inline void setNordPalette(QApplication &app) {
    QPalette nordPalette;

    // Цвета Nord (Hex значения)
    const QString nord0 = "#4c566a";  // фоновый цвет
    const QString nord1 = "#434c5e";  // цвет окон
    const QString nord2 = "#3b4252";  // светлые акценты
    const QString nord3 = "#2e3440";  // более темные элементы
    const QString textColor = "#d8dee9";  // основной цвет текста
    const QString disabledTextColor = "#a0a0a0";  // цвет текста для заблокированных элементов
    const QString sliderColor = "#88c0d0";  // цвет ползунков

    // Применение цветов к палитре
    nordPalette.setColor(QPalette::Window, QColor(nord1));

    // Строка стилей с использованием переменных
    QString styleSheet = QString(
        // QPushButton
        "QPushButton {"
        "   outline: none;"
        "   border: 1px solid %1;"         // Граница кнопки
        "   background-color: %4;"         // Фон кнопки
        "   color: %5;"                    // Цвет текста кнопки
        "   padding: 5px;"
        "   border-radius: 5px;"
        "}"
        "QPushButton:pressed {"
        "   background-color: %1;"         // Цвет при нажатии
        "}"
        "QPushButton:disabled {"
        "   background-color: %3;"         // Фон заблокированной кнопки
        "   color: %6;"                    // Цвет текста заблокированной кнопки
        "   border: 1px solid %3;"         // Граница заблокированной кнопки
        "}"

        // QLineEdit
        "QLineEdit {"
        "   background-color: %3;"         // Фон поля ввода
        "   color: %5;"                    // Цвет текста
        "   border: 1px solid %1;"         // Граница
        "   padding: 5px;"
        "}"

        // QLabel
        "QLabel {"
        "   color: %5;"                    // Цвет текста
        "}"

        // QComboBox
        "QComboBox {"
        "   background-color: %3;"         // Фон выпадающего списка
        "   color: %5;"                    // Цвет текста
        "   border: 1px solid %1;"         // Граница
        "   padding: 5px;"
        "}"

        // QCheckBox и QRadioButton
        "QCheckBox, QRadioButton {"
        "   color: %5;"                    // Цвет текста
        "}"

        // QSlider
        "QSlider::groove:horizontal {"
        "   background-color: %3;"         // Фон для слайдера
        "   height: 8px;"
        "}"
        "QSlider::handle:horizontal {"
        "   background-color: %7;"         // Ползунок
        "   width: 20px;"
        "   margin: -5px 0;"
        "}"

        // QSpinBox
        "QSpinBox {"
        "   background-color: %3;"         // Фон
        "   color: %5;"                    // Цвет текста
       // "   border: 1px solid %1;"         // Граница
       // "   padding: 5px;"
        "}"

        // QTextEdit
        "QTextEdit {"
        "   background-color: %3;"         // Фон текстового поля
        "   color: %5;"                    // Цвет текста
        "   border: 1px solid %1;"         // Граница
        "   padding: 5px;"
        "}"

        // QTableWidget
        "QTableWidget {"
        "   background-color: %3;"         // Фон таблицы
        "   color: %5;"                    // Цвет текста в таблице
        "   gridline-color: %1;"           // Цвет линий сетки
        "   selection-background-color: %1;"  // Фон при выделении
        "}"
        "QHeaderView::section {"
        "   background-color: %2;"         // Фон заголовков
        "   color: %5;"                    // Цвет текста заголовков
        "   border: 1px solid %1;"         // Граница заголовков
        "}"
        "QTableCornerButton::section {"
        "   background-color: %2;"         // Фон верхнего левого угла
        "   border: 1px solid %1;"         // Граница аналогичная заголовкам
        "}"
        "QTableWidget::item:selected {"
        "   background-color: transparent;"  
        "   color: white;"                   
        "}"

        // Горизонтальный ползунок
        "QScrollBar:horizontal {"
        "   border: none;"
        "   background-color: %3;"
        "   height: 12px;"
        "   margin: 0px;"  
        "}"
        "QScrollBar::handle:horizontal {"
        "   background-color: %7;"
        "   min-width: 20px;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "   width: 0px;"
        "   background: none;"
        "}"

        // Вертикальный ползунок
        "QScrollBar:vertical {"
        "   border: none;"
        "   background-color: %3;"
        "   width: 12px;"
        "   margin: 0px;"  
        "}"
        "QScrollBar::handle:vertical {"
        "   background-color: %7;"
        "   min-height: 20px;"
        "   border-radius: 6px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   height: 0px;"
        "   background: none;"
        "}"
    ).arg(nord0, nord1, nord2, nord3, textColor, disabledTextColor, sliderColor);

    // Применение стилей и палитры
    app.setStyleSheet(styleSheet);
    app.setPalette(nordPalette);
}

