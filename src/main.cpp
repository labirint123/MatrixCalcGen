#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

#include "themes.h"
#include "MainWindow.h"
#include "Controller.h"
#include "SettingsDialog.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    #ifdef __EMSCRIPTEN__
    setNordPalette(app);   
    #endif

    QString theme;
    
    QFile file("settings.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonObject jsonObj = doc.object();

        theme = jsonObj["theme"].toString();
    }
    if (theme == "nord")
        setNordPalette(app);
    
    MainWindow mWinObj;
    return app.exec();
}
