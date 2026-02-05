/**
 * @file MainWindow.h
 * @brief 主窗口类
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include "MainController.h"

namespace secondui { class SecondWindow; }

namespace mainui {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onShowInfoClicked();
    void onClearClicked();
    void onGetSystemInfoClicked();
    void onOpenCalculatorClicked();

private:
    void setupUi();
    void setupConnections();
    void setupWindowStyle();
    QString createButtonStyle(const QString &baseColor,
                              const QString &hoverColor,
                              const QString &pressedColor) const;

private:
    static const int LAYOUT_SPACING = 15;
    static const int LAYOUT_MARGIN = 20;
    static const int TEXT_EDIT_MIN_HEIGHT = 300;
    static const int BUTTON_MIN_HEIGHT = 40;
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    static const int WINDOW_MIN_WIDTH = 600;
    static const int WINDOW_MIN_HEIGHT = 400;

    static const QString COLOR_BLUE;
    static const QString COLOR_BLUE_HOVER;
    static const QString COLOR_BLUE_PRESS;
    static const QString COLOR_RED;
    static const QString COLOR_RED_HOVER;
    static const QString COLOR_RED_PRESS;
    static const QString COLOR_GREEN;
    static const QString COLOR_GREEN_HOVER;
    static const QString COLOR_GREEN_PRESS;
    static const QString COLOR_PURPLE;
    static const QString COLOR_PURPLE_HOVER;
    static const QString COLOR_PURPLE_PRESS;

private:
    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_buttonLayout;
    QLabel *m_titleLabel;
    QLabel *m_infoLabel;
    QTextEdit *m_textEdit;
    QPushButton *m_showInfoButton;
    QPushButton *m_clearButton;
    QPushButton *m_systemInfoButton;
    QPushButton *m_calculatorButton;
    MainController *m_controller;
    secondui::SecondWindow *m_calculatorWindow;
};

} // namespace mainui

#endif // MAINWINDOW_H
