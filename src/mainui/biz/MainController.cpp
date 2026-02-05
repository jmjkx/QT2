/**
 * @file MainController.cpp
 */

#include "MainController.h"
#include <QCoreApplication>

namespace mainui {

MainController::MainController()
{
}

MainController::~MainController()
{
}

QString MainController::getWelcomeMessage() const
{
    QString message;
    message += createSeparator(50, '=') + "\n";
    message += QString("    欢迎使用 LiquidCam 应用程序\n");
    message += QString("    版本: %1\n").arg(QCoreApplication::applicationVersion());
    message += QString("    启动时间: %1\n").arg(getCurrentTimestamp());
    message += createSeparator(50, '=');
    return message;
}

QString MainController::getSystemInformation() const
{
    QString info;
    info += QString("操作系统: %1\n").arg(QSysInfo::prettyProductName());
    info += QString("内核版本: %1\n").arg(QSysInfo::kernelVersion());
    info += QString("系统架构: %1\n").arg(QSysInfo::currentCpuArchitecture());
    info += QString("产品类型: %1\n").arg(QSysInfo::productType());
    info += QString("产品版本: %1\n").arg(QSysInfo::productVersion());
    info += QString("构建ABI: %1\n").arg(QSysInfo::buildAbi());
    info += QString("Qt版本: %1\n").arg(qVersion());
    return info;
}

QString MainController::getCurrentTimestamp() const
{
    return formatDateTime(QDateTime::currentDateTime());
}

QString MainController::processUserInput(const QString &input) const
{
    QString timestamp = getCurrentTimestamp();
    return QString("[%1] %2").arg(timestamp, input);
}

QString MainController::getApplicationStats() const
{
    QString stats;
    stats += QString("应用名称: %1\n").arg(QCoreApplication::applicationName());
    stats += QString("应用版本: %1\n").arg(QCoreApplication::applicationVersion());
    stats += QString("组织名称: %1\n").arg(QCoreApplication::organizationName());
    stats += QString("应用PID: %1\n").arg(QCoreApplication::applicationPid());
    stats += QString("运行目录: %1\n").arg(QCoreApplication::applicationDirPath());
    return stats;
}

QString MainController::formatDateTime(const QDateTime &dateTime) const
{
    return dateTime.toString("yyyy-MM-dd HH:mm:ss");
}

QString MainController::createSeparator(int length, QChar character) const
{
    return QString().fill(character, length);
}

} // namespace mainui
