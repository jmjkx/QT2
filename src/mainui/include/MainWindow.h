/**
 * @file MainWindow.h
 * @brief 主窗口 - Widget提升版
 * @description 
 *   子页面通过UI文件中的Widget提升直接嵌入
 *   无需在代码中手动创建子页面
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace mainui {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNavChanged(int index);

private:
    void setupNavigation();  // 设置导航菜单

private:
    Ui::MainWindow *ui;
};

} // namespace mainui

#endif // MAINWINDOW_H
