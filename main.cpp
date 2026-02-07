/**
 * @file main.cpp
 * @brief 程序入口
 */

#include <QApplication>
#include <QDebug>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("MultiPageDemo");
    
    qDebug() << "程序启动...";

    mainui::MainWindow window;
    window.show();

    return app.exec();
}
