/**
 * @file CalculatorPage.cpp
 * @brief 计算器页面实现
 */

#include "CalculatorPage.h"
#include "ui_SecondWindow.h"  // 使用SecondWindow的生成头文件
#include <QDebug>
#include <cmath>

CalculatorPage::CalculatorPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SecondWindow())
    , leftOperand(0.0)
    , waitingForOperand(false)
{
    ui->setupUi(this);
    
    // 初始化显示
    currentInput = "0";
    updateDisplay();
    
    // 设置信号连接
    setupConnections();
    
    qDebug() << "计算器页面创建完成";
}

CalculatorPage::~CalculatorPage()
{
    delete ui;
}

void CalculatorPage::setupConnections()
{
    // 数字按钮 0-9
    connect(ui->digit0, &QPushButton::clicked, this, &CalculatorPage::onDigitClicked);
    connect(ui->digit1, &QPushButton::clicked, this, &CalculatorPage::onDigitClicked);
    connect(ui->digit2, &QPushButton::clicked, this, &CalculatorPage::onDigitClicked);
    connect(ui->digit3, &QPushButton::clicked, this, &CalculatorPage::onDigitClicked);
    connect(ui->digit4, &QPushButton::clicked, this, &CalculatorPage::onDigitClicked);
    connect(ui->digit5, &QPushButton::clicked, this, &CalculatorPage::onDigitClicked);
    connect(ui->digit6, &QPushButton::clicked, this, &CalculatorPage::onDigitClicked);
    connect(ui->digit7, &QPushButton::clicked, this, &CalculatorPage::onDigitClicked);
    connect(ui->digit8, &QPushButton::clicked, this, &CalculatorPage::onDigitClicked);
    connect(ui->digit9, &QPushButton::clicked, this, &CalculatorPage::onDigitClicked);
    
    // 运算符按钮
    connect(ui->addButton, &QPushButton::clicked, this, &CalculatorPage::onOperatorClicked);
    connect(ui->subtractButton, &QPushButton::clicked, this, &CalculatorPage::onOperatorClicked);
    connect(ui->multiplyButton, &QPushButton::clicked, this, &CalculatorPage::onOperatorClicked);
    connect(ui->divideButton, &QPushButton::clicked, this, &CalculatorPage::onOperatorClicked);
    
    // 功能按钮
    connect(ui->equalButton, &QPushButton::clicked, this, &CalculatorPage::onEqualClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &CalculatorPage::onClearClicked);
    connect(ui->backspaceButton, &QPushButton::clicked, this, &CalculatorPage::onBackspaceClicked);
    connect(ui->dotButton, &QPushButton::clicked, this, &CalculatorPage::onDotClicked);
    connect(ui->plusMinusButton, &QPushButton::clicked, this, &CalculatorPage::onPlusMinusClicked);
    connect(ui->percentButton, &QPushButton::clicked, this, &CalculatorPage::onPercentClicked);
}

void CalculatorPage::onDigitClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    QString digit = button->text();
    
    if (waitingForOperand) {
        currentInput = digit;
        waitingForOperand = false;
    } else {
        if (currentInput == "0") {
            currentInput = digit;
        } else {
            currentInput += digit;
        }
    }
    
    updateDisplay();
}

void CalculatorPage::onOperatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    // 如果有待执行的运算，先计算
    if (!pendingOperator.isEmpty() && !waitingForOperand) {
        calculate();
    }
    
    // 保存当前操作数和运算符
    leftOperand = currentInput.toDouble();
    pendingOperator = button->text();
    waitingForOperand = true;
    
    // 更新运算符标签
    ui->operationLabel->setText(currentInput + " " + pendingOperator);
}

void CalculatorPage::onEqualClicked()
{
    if (pendingOperator.isEmpty() || waitingForOperand) {
        return;
    }
    
    calculate();
    
    pendingOperator.clear();
    ui->operationLabel->clear();
    waitingForOperand = true;
}

void CalculatorPage::onClearClicked()
{
    currentInput = "0";
    pendingOperator.clear();
    leftOperand = 0.0;
    waitingForOperand = false;
    ui->operationLabel->clear();
    ui->statusLabel->clear();
    updateDisplay();
}

void CalculatorPage::onBackspaceClicked()
{
    if (waitingForOperand) return;
    
    if (currentInput.length() > 1) {
        currentInput.chop(1);
    } else {
        currentInput = "0";
    }
    
    updateDisplay();
}

void CalculatorPage::onDotClicked()
{
    if (waitingForOperand) {
        currentInput = "0.";
        waitingForOperand = false;
    } else if (!currentInput.contains('.')) {
        currentInput += '.';
    }
    
    updateDisplay();
}

void CalculatorPage::onPlusMinusClicked()
{
    double value = currentInput.toDouble();
    value = -value;
    currentInput = QString::number(value, 'g', 15);
    updateDisplay();
}

void CalculatorPage::onPercentClicked()
{
    double value = currentInput.toDouble();
    value = value / 100.0;
    currentInput = QString::number(value, 'g', 15);
    updateDisplay();
}

void CalculatorPage::updateDisplay()
{
    ui->displayEdit->setText(currentInput);
}

void CalculatorPage::calculate()
{
    double rightOperand = currentInput.toDouble();
    double result = 0.0;
    
    if (pendingOperator == "+") {
        result = leftOperand + rightOperand;
    } else if (pendingOperator == "-") {
        result = leftOperand - rightOperand;
    } else if (pendingOperator == "×") {
        result = leftOperand * rightOperand;
    } else if (pendingOperator == "÷") {
        if (rightOperand == 0.0) {
            ui->statusLabel->setText(tr("错误：除数不能为零"));
            return;
        }
        result = leftOperand / rightOperand;
    }
    
    currentInput = QString::number(result, 'g', 15);
    updateDisplay();
    
    // 显示计算过程
    QString operation = QString::number(leftOperand, 'g', 15) + " " + 
                       pendingOperator + " " + 
                       QString::number(rightOperand, 'g', 15) + " =";
    ui->operationLabel->setText(operation);
    ui->statusLabel->clear();
}
