/**
 * @file SecondController.h
 * @brief 次级窗口业务逻辑控制器
 */

#ifndef SECONDCONTROLLER_H
#define SECONDCONTROLLER_H

#include <QString>

namespace secondui {

enum class OperatorType {
    None,
    Add,
    Subtract,
    Multiply,
    Divide
};

class SecondController
{
public:
    SecondController();
    ~SecondController();

    QString inputDigit(const QString &current, const QString &digit);
    QString inputOperator(const QString &current, OperatorType op);
    QString calculateEqual(const QString &current);
    void clear();
    QString backspace(const QString &current);
    QString percent(const QString &current);
    QString plusMinus(const QString &current);
    OperatorType getCurrentOperator() const;
    QString getOperatorText(OperatorType op) const;
    QString formatNumber(double number) const;

private:
    double performCalculation(double left, double right, OperatorType op) const;
    bool isValidNumber(double number) const;

private:
    double m_firstOperand;
    double m_secondOperand;
    OperatorType m_currentOperator;
    bool m_waitingForSecondOperand;
};

} // namespace secondui

#endif // SECONDCONTROLLER_H
