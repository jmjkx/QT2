/**
 * @file SecondWindow.h
 * @brief 次级窗口类
 */

#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QVector>
#include "SecondController.h"

namespace secondui {

class SecondWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow() override;

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onEqualClicked();
    void onClearClicked();
    void onBackspaceClicked();
    void onPercentClicked();
    void onPlusMinusClicked();

private:
    void setupUi();
    void setupConnections();
    QPushButton *createButton(const QString &text, int size = 60);
    void updateStatusBar(const QString &message);

private:
    QLineEdit *m_displayEdit;
    QLabel *m_operationLabel;
    QLabel *m_statusLabel;
    QGridLayout *m_buttonLayout;
    QVector<QPushButton*> m_digitButtons;
    QVector<QPushButton*> m_operatorButtons;
    QPushButton *m_clearButton;
    QPushButton *m_backspaceButton;
    QPushButton *m_percentButton;
    QPushButton *m_plusMinusButton;
    QPushButton *m_equalButton;
    SecondController *m_controller;
};

} // namespace secondui

#endif // SECONDWINDOW_H
