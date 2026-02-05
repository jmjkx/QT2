/**
 * @file SecondController.cpp
 */

#include "SecondController.h"
#include <QDebug>
#include <cmath>

namespace secondui {

SecondController::SecondController()
    : m_firstOperand(0.0)
    , m_secondOperand(0.0)
    , m_currentOperator(OperatorType::None)
    , m_waitingForSecondOperand(false)
{
}

SecondController::~SecondController()
{
}

QString SecondController::inputDigit(const QString &current, const QString &digit)
{
    QString result = current;

    if (m_waitingForSecondOperand) {
        result = digit;
        m_waitingForSecondOperand = false;
    } else {
        if (result == "0" && digit != ".") {
            result = digit;
        } else {
            if (digit == "." && result.contains(".")) {
                return result;
            }
            result += digit;
        }
    }

    return result;
}

QString SecondController::inputOperator(const QString &current, OperatorType op)
{
    double currentValue = current.toDouble();

    if (m_currentOperator != OperatorType::None && !m_waitingForSecondOperand) {
        double result = performCalculation(m_firstOperand, currentValue, m_currentOperator);
        m_firstOperand = result;
        return formatNumber(result);
    }

    m_firstOperand = currentValue;
    m_currentOperator = op;
    m_waitingForSecondOperand = true;

    return formatNumber(m_firstOperand);
}

QString SecondController::calculateEqual(const QString &current)
{
    if (m_currentOperator == OperatorType::None) {
        return current;
    }

    double currentValue = current.toDouble();
    double result = performCalculation(m_firstOperand, currentValue, m_currentOperator);

    m_firstOperand = result;
    m_currentOperator = OperatorType::None;
    m_waitingForSecondOperand = true;

    return formatNumber(result);
}

void SecondController::clear()
{
    m_firstOperand = 0.0;
    m_secondOperand = 0.0;
    m_currentOperator = OperatorType::None;
    m_waitingForSecondOperand = false;
}

QString SecondController::backspace(const QString &current)
{
    if (current.length() <= 1) {
        return "0";
    }

    QString result = current;
    result.remove(result.length() - 1, 1);

    if (result.isEmpty() || result == "-") {
        return "0";
    }

    return result;
}

QString SecondController::percent(const QString &current)
{
    double value = current.toDouble();
    return formatNumber(value / 100.0);
}

QString SecondController::plusMinus(const QString &current)
{
    if (current == "0") {
        return current;
    }

    double value = current.toDouble();
    return formatNumber(-value);
}

OperatorType SecondController::getCurrentOperator() const
{
    return m_currentOperator;
}

QString SecondController::getOperatorText(OperatorType op) const
{
    switch (op) {
        case OperatorType::Add:
            return "+";
        case OperatorType::Subtract:
            return "-";
        case OperatorType::Multiply:
            return "×";
        case OperatorType::Divide:
            return "÷";
        default:
            return "";
    }
}

QString SecondController::formatNumber(double number) const
{
    if (!isValidNumber(number)) {
        return "Error";
    }

    if (number == qFloor(number)) {
        return QString::number(static_cast<qint64>(number));
    }

    QString result = QString::number(number, 'f', 10);

    while (result.endsWith("0")) {
        result.remove(result.length() - 1, 1);
    }

    if (result.endsWith(".")) {
        result.remove(result.length() - 1, 1);
    }

    return result;
}

double SecondController::performCalculation(double left, double right, OperatorType op) const
{
    switch (op) {
        case OperatorType::Add:
            return left + right;
        case OperatorType::Subtract:
            return left - right;
        case OperatorType::Multiply:
            return left * right;
        case OperatorType::Divide:
            if (right == 0.0) {
                qWarning() << "[SecondController] 除零错误";
                return NAN;
            }
            return left / right;
        default:
            return right;
    }
}

bool SecondController::isValidNumber(double number) const
{
    return !std::isnan(number) && !std::isinf(number);
}

} // namespace secondui
