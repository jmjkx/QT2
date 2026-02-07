/**
 * @file MainWindow.cpp
 * @brief 主窗口实现 - Widget提升版
 * @description 
 *   子页面在MainWindow.ui中通过Widget提升直接嵌入
 *   代码中只需要处理页面切换逻辑
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

namespace mainui {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    
    setWindowTitle(tr("多页面示例 - Widget提升版"));
    resize(1200, 800);
    
    // 设置导航菜单
    setupNavigation();
    
    // 连接导航信号
    connect(ui->navList, &QListWidget::currentRowChanged,
            this, &MainWindow::onNavChanged);
    
    // 默认选中第一个
    ui->navList->setCurrentRow(0);
    
    qDebug() << "主窗口创建完成";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupNavigation()
{
    // ============================================
    // 添加导航菜单项（与UI文件中的页面顺序对应）
    // ============================================
    ui->navList->addItem(tr("📁 文件管理"));    // 对应 stackedWidget 第0页
    ui->navList->addItem(tr("⚙️ 首选项"));      // 对应 stackedWidget 第1页
    ui->navList->addItem(tr("🧮 计算器"));      // 对应 stackedWidget 第2页
    
    // 添加新页面时，在这里添加对应的导航项
    // ui->navList->addItem(tr("新页面"));
}

void MainWindow::onNavChanged(int index)
{
    if (index < 0 || index >= ui->stackedWidget->count())
        return;
    
    // 切换到对应页面
    ui->stackedWidget->setCurrentIndex(index);
    
    qDebug() << "切换到页面:" << index;
}

} // namespace mainui
