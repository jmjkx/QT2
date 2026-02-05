/**
 * @file main.cpp
 * @brief LiquidCam主入口
 */

#include <QApplication>
#include <QDebug>
#include <QDir>
#include "MainWindow.h"

namespace mainui { class MainWindow; }

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("LiquidCam");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("LiquidCam Team");
    app.setStyle("Fusion");

    qDebug() << "LiquidCam Starting...";
    qDebug() << "Version:" << app.applicationVersion();
    qDebug() << "Working Dir:" << QDir::currentPath();

    mainui::MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
