/**
 * @file SecondWindow.cpp
 */

#include "SecondWindow.h"
#include <QDebug>

namespace secondui {

SecondWindow::SecondWindow(QWidget *parent)
    : QWidget(parent)
    , m_displayEdit(nullptr)
    , m_operationLabel(nullptr)
    , m_statusLabel(nullptr)
    , m_buttonLayout(nullptr)
    , m_clearButton(nullptr)
    , m_backspaceButton(nullptr)
    , m_percentButton(nullptr)
    , m_plusMinusButton(nullptr)
    , m_equalButton(nullptr)
    , m_controller(new SecondController())
{
    setupUi();
    setupConnections();
}

SecondWindow::~SecondWindow()
{
    delete m_controller;
    m_controller = nullptr;
}

void SecondWindow::setupUi()
{
    setFixedSize(350, 480);
    setStyleSheet("background-color: #2c3e50;");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    m_displayEdit = new QLineEdit(this);
    m_displayEdit->setReadOnly(true);
    m_displayEdit->setAlignment(Qt::AlignRight);
    m_displayEdit->setMinimumHeight(60);
    m_displayEdit->setStyleSheet(
        "QLineEdit {"
        "    border: none;"
        "    border-radius: 8px;"
        "    background-color: #1abc9c;"
        "    color: white;"
        "    font-size: 28px;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "}"
    );
    m_displayEdit->setText("0");
    mainLayout->addWidget(m_displayEdit);

    m_operationLabel = new QLabel(this);
    m_operationLabel->setAlignment(Qt::AlignRight);
    m_operationLabel->setStyleSheet(
        "QLabel {"
        "    color: #95a5a6;"
        "    font-size: 14px;"
        "    padding: 5px;"
        "}"
    );
    mainLayout->addWidget(m_operationLabel);

    m_statusLabel = new QLabel(this);
    m_statusLabel->setAlignment(Qt::AlignLeft);
    m_statusLabel->setStyleSheet(
        "QLabel {"
        "    color: #7f8c8d;"
        "    font-size: 11px;"
        "}"
    );
    mainLayout->addWidget(m_statusLabel);

    m_buttonLayout = new QGridLayout();
    m_buttonLayout->setSpacing(8);

    m_clearButton = createButton("C");
    m_clearButton->setStyleSheet("background-color: #e74c3c;");
    m_buttonLayout->addWidget(m_clearButton, 0, 0);

    m_backspaceButton = createButton("⌫");
    m_backspaceButton->setStyleSheet("background-color: #e67e22;");
    m_buttonLayout->addWidget(m_backspaceButton, 0, 1);

    m_percentButton = createButton("%");
    m_percentButton->setStyleSheet("background-color: #e67e22;");
    m_buttonLayout->addWidget(m_percentButton, 0, 2);

    auto *divideButton = createButton("÷");
    divideButton->setStyleSheet("background-color: #3498db;");
    m_operatorButtons.append(divideButton);
    m_buttonLayout->addWidget(divideButton, 0, 3);

    for (int i = 7; i <= 9; ++i) {
        auto *btn = createButton(QString::number(i));
        m_digitButtons.append(btn);
        m_buttonLayout->addWidget(btn, 1, i - 7);
    }

    auto *multiplyButton = createButton("×");
    multiplyButton->setStyleSheet("background-color: #3498db;");
    m_operatorButtons.append(multiplyButton);
    m_buttonLayout->addWidget(multiplyButton, 1, 3);

    for (int i = 4; i <= 6; ++i) {
        auto *btn = createButton(QString::number(i));
        m_digitButtons.append(btn);
        m_buttonLayout->addWidget(btn, 2, i - 4);
    }

    auto *subtractButton = createButton("-");
    subtractButton->setStyleSheet("background-color: #3498db;");
    m_operatorButtons.append(subtractButton);
    m_buttonLayout->addWidget(subtractButton, 2, 3);

    for (int i = 1; i <= 3; ++i) {
        auto *btn = createButton(QString::number(i));
        m_digitButtons.append(btn);
        m_buttonLayout->addWidget(btn, 3, i - 1);
    }

    auto *addButton = createButton("+");
    addButton->setStyleSheet("background-color: #3498db;");
    m_operatorButtons.append(addButton);
    m_buttonLayout->addWidget(addButton, 3, 3);

    m_plusMinusButton = createButton("±");
    m_plusMinusButton->setStyleSheet("background-color: #95a5a6;");
    m_buttonLayout->addWidget(m_plusMinusButton, 4, 0);

    auto *zeroButton = createButton("0");
    m_digitButtons.append(zeroButton);
    m_buttonLayout->addWidget(zeroButton, 4, 1);

    auto *dotButton = createButton(".");
    m_digitButtons.append(dotButton);
    m_buttonLayout->addWidget(dotButton, 4, 2);

    m_equalButton = createButton("=");
    m_equalButton->setStyleSheet("background-color: #27ae60;");
    m_buttonLayout->addWidget(m_equalButton, 4, 3);

    mainLayout->addLayout(m_buttonLayout);
}

void SecondWindow::setupConnections()
{
    for (auto *btn : m_digitButtons) {
        connect(btn, &QPushButton::clicked, this, &SecondWindow::onDigitClicked);
    }

    for (auto *btn : m_operatorButtons) {
        connect(btn, &QPushButton::clicked, this, &SecondWindow::onOperatorClicked);
    }

    connect(m_clearButton, &QPushButton::clicked, this, &SecondWindow::onClearClicked);
    connect(m_backspaceButton, &QPushButton::clicked, this, &SecondWindow::onBackspaceClicked);
    connect(m_percentButton, &QPushButton::clicked, this, &SecondWindow::onPercentClicked);
    connect(m_plusMinusButton, &QPushButton::clicked, this, &SecondWindow::onPlusMinusClicked);
    connect(m_equalButton, &QPushButton::clicked, this, &SecondWindow::onEqualClicked);
}

QPushButton *SecondWindow::createButton(const QString &text, int size)
{
    auto *button = new QPushButton(text, this);
    button->setFixedSize(size, size);
    button->setStyleSheet(
        "QPushButton {"
        "    border: none;"
        "    border-radius: 8px;"
        "    background-color: #34495e;"
        "    color: white;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #455d75; }"
        "QPushButton:pressed { background-color: #2c3e50; }"
    );
    return button;
}

void SecondWindow::updateStatusBar(const QString &message)
{
    m_statusLabel->setText(message);
}

void SecondWindow::onDigitClicked()
{
    auto *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString current = m_displayEdit->text();
    QString newText = m_controller->inputDigit(current, btn->text());
    m_displayEdit->setText(newText);
    updateStatusBar("输入数字: " + btn->text());
}

void SecondWindow::onOperatorClicked()
{
    auto *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString current = m_displayEdit->text();

    OperatorType op = OperatorType::None;
    QString opText = btn->text();
    if (opText == "+") op = OperatorType::Add;
    else if (opText == "-") op = OperatorType::Subtract;
    else if (opText == "×") op = OperatorType::Multiply;
    else if (opText == "÷") op = OperatorType::Divide;

    QString result = m_controller->inputOperator(current, op);
    m_displayEdit->setText(result);
    m_operationLabel->setText("运算符: " + m_controller->getOperatorText(op));
    updateStatusBar("选择运算符: " + opText);
}

void SecondWindow::onEqualClicked()
{
    QString current = m_displayEdit->text();
    QString result = m_controller->calculateEqual(current);
    m_displayEdit->setText(result);
    m_operationLabel->clear();
    updateStatusBar("计算完成");
}

void SecondWindow::onClearClicked()
{
    m_controller->clear();
    m_displayEdit->setText("0");
    m_operationLabel->clear();
    updateStatusBar("已清空");
}

void SecondWindow::onBackspaceClicked()
{
    QString current = m_displayEdit->text();
    QString newText = m_controller->backspace(current);
    m_displayEdit->setText(newText);
    updateStatusBar("退格");
}

void SecondWindow::onPercentClicked()
{
    QString current = m_displayEdit->text();
    QString result = m_controller->percent(current);
    m_displayEdit->setText(result);
    updateStatusBar("百分比计算");
}

void SecondWindow::onPlusMinusClicked()
{
    QString current = m_displayEdit->text();
    QString result = m_controller->plusMinus(current);
    m_displayEdit->setText(result);
    updateStatusBar("切换正负号");
}

} // namespace secondui
