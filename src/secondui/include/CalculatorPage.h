/**
 * @file CalculatorPage.h
 * @brief 计算器页面 - 作为主界面的子页面
 * @description 
 *   通过Widget提升方式嵌入主窗口的QStackedWidget中
 */

#ifndef CALCULATORPAGE_H
#define CALCULATORPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SecondWindow; }  // 使用现有的SecondWindow.ui
QT_END_NAMESPACE

/**
 * 计算器页面类
 * 包装SecondWindow.ui作为主界面的子页面
 */
class CalculatorPage : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorPage(QWidget *parent = nullptr);
    ~CalculatorPage();

    // 获取页面名称（用于导航显示）
    static QString pageName() { return QObject::tr("计算器"); }

private slots:
    // 数字按钮点击
    void onDigitClicked();
    // 运算符按钮点击
    void onOperatorClicked();
    // 等号按钮点击
    void onEqualClicked();
    // 清除按钮点击
    void onClearClicked();
    // 退格按钮点击
    void onBackspaceClicked();
    // 小数点按钮点击
    void onDotClicked();
    // 正负号按钮点击
    void onPlusMinusClicked();
    // 百分号按钮点击
    void onPercentClicked();

private:
    void setupConnections();  // 设置信号连接
    void updateDisplay();     // 更新显示
    void calculate();         // 执行计算

private:
    Ui::SecondWindow *ui;  // 复用SecondWindow的UI
    
    // 计算器状态
    QString currentInput;      // 当前输入
    QString pendingOperator;   // 待执行的运算符
    double leftOperand;        // 左操作数
    bool waitingForOperand;    // 是否在等待新操作数
};

#endif // CALCULATORPAGE_H
