/**
 * @file MainController.h
 * @brief 主窗口业务逻辑控制器
 */

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QString>
#include <QDateTime>
#include <QSysInfo>

namespace mainui {

class MainController
{
public:
    MainController();
    ~MainController();

    QString getWelcomeMessage() const;
    QString getSystemInformation() const;
    QString getCurrentTimestamp() const;
    QString processUserInput(const QString &input) const;
    QString getApplicationStats() const;
    QString createSeparator(int length = 40, QChar character = '=') const;

private:
    QString formatDateTime(const QDateTime &dateTime) const;
};

} // namespace mainui

#endif // MAINCONTROLLER_H
