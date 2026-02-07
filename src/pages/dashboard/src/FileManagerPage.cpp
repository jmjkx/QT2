/**
 * @file FileManagerPage.cpp
 * @brief 文件管理器页面实现
 */

#include "FileManagerPage.h"
#include "ui_FileManagerPage.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>
#include <QMessageBox>

FileManagerPage::FileManagerPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileManagerPage())
    , m_fileModel(new QFileSystemModel(this))
    , m_proxyModel(new QSortFilterProxyModel(this))
    , m_currentPath(QDir::homePath())
{
    ui->setupUi(this);
    
    setupFileSystem();
    
    // 连接信号槽
    connect(ui->treeView, &QTreeView::clicked, this, &FileManagerPage::onTreeClicked);
    connect(ui->listView, &QListView::clicked, this, &FileManagerPage::onListClicked);
    connect(ui->pathEdit, &QLineEdit::returnPressed, this, &FileManagerPage::onPathEditReturn);
    connect(ui->upButton, &QPushButton::clicked, this, &FileManagerPage::onUpButtonClicked);
    connect(ui->homeButton, &QPushButton::clicked, this, &FileManagerPage::onHomeButtonClicked);
    connect(ui->refreshButton, &QPushButton::clicked, this, &FileManagerPage::onRefreshButtonClicked);
    connect(ui->searchEdit, &QLineEdit::textChanged, this, &FileManagerPage::onSearchTextChanged);
    connect(ui->filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &FileManagerPage::onFilterChanged);
    
    // 初始化显示
    updateCurrentPath(m_currentPath);
    
    qDebug() << "文件管理器页面创建完成";
}

FileManagerPage::~FileManagerPage()
{
    delete ui;
}

void FileManagerPage::setupFileSystem()
{
    // 设置文件模型
    m_fileModel->setRootPath("");
    m_fileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);
    
    // 设置代理模型用于过滤
    m_proxyModel->setSourceModel(m_fileModel);
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    
    // 配置树形视图（左侧导航）
    ui->treeView->setModel(m_fileModel);
    ui->treeView->setRootIndex(m_fileModel->index(QDir::rootPath()));
    ui->treeView->setColumnWidth(0, 200);
    ui->treeView->hideColumn(1);  // 隐藏大小列
    ui->treeView->hideColumn(2);  // 隐藏类型列
    ui->treeView->hideColumn(3);  // 隐藏日期列
    
    // 配置列表视图（右侧内容）
    ui->listView->setModel(m_proxyModel);
    ui->listView->setViewMode(QListView::ListMode);
    ui->listView->setGridSize(QSize(80, 70));
    
    // 设置过滤器选项
    ui->filterCombo->addItem(tr("全部文件 (*.*)"), QString());
    ui->filterCombo->addItem(tr("文本文件 (*.txt)"), QString("*.txt"));
    ui->filterCombo->addItem(tr("图片文件 (*.png *.jpg *.bmp)"), QString("*.png *.jpg *.bmp"));
    ui->filterCombo->addItem(tr("文档 (*.pdf *.doc *.docx)"), QString("*.pdf *.doc *.docx"));
}

void FileManagerPage::onTreeClicked(const QModelIndex &index)
{
    QString path = m_fileModel->filePath(index);
    if (QFileInfo(path).isDir()) {
        updateCurrentPath(path);
    }
}

void FileManagerPage::onListClicked(const QModelIndex &index)
{
    QModelIndex sourceIndex = m_proxyModel->mapToSource(index);
    QString path = m_fileModel->filePath(sourceIndex);
    QFileInfo info(path);
    
    if (info.isDir()) {
        updateCurrentPath(path);
    } else {
        // 显示文件信息
        ui->fileNameLabel->setText(info.fileName());
        ui->fileSizeLabel->setText(tr("大小: %1").arg(formatFileSize(info.size())));
        ui->fileTypeLabel->setText(tr("类型: %1").arg(info.suffix().toUpper()));
        ui->fileDateLabel->setText(tr("修改: %1").arg(info.lastModified().toString("yyyy-MM-dd hh:mm")));
        
        // 尝试打开文件
        // QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
}

void FileManagerPage::onPathEditReturn()
{
    QString path = ui->pathEdit->text();
    if (QDir(path).exists()) {
        updateCurrentPath(path);
    } else {
        QMessageBox::warning(this, tr("路径错误"), tr("路径不存在: %1").arg(path));
    }
}

void FileManagerPage::onUpButtonClicked()
{
    QDir dir(m_currentPath);
    if (dir.cdUp()) {
        updateCurrentPath(dir.absolutePath());
    }
}

void FileManagerPage::onHomeButtonClicked()
{
    updateCurrentPath(QDir::homePath());
}

void FileManagerPage::onRefreshButtonClicked()
{
    // 重新设置根路径来刷新
    m_fileModel->setRootPath("");
    m_fileModel->setRootPath(QDir::rootPath());
    updateCurrentPath(m_currentPath);
}

void FileManagerPage::onSearchTextChanged(const QString &text)
{
    m_proxyModel->setFilterWildcard(text.isEmpty() ? QString() : "*" + text + "*");
}

void FileManagerPage::onFilterChanged(int index)
{
    QString filter = ui->filterCombo->currentData().toString();
    if (filter.isEmpty()) {
        m_fileModel->setNameFilters(QStringList());
        m_fileModel->setNameFilterDisables(false);
    } else {
        m_fileModel->setNameFilters(filter.split(' '));
        m_fileModel->setNameFilterDisables(false);
    }
}

void FileManagerPage::updateCurrentPath(const QString &path)
{
    m_currentPath = path;
    ui->pathEdit->setText(path);
    
    // 更新列表视图根索引
    QModelIndex index = m_fileModel->index(path);
    QModelIndex proxyIndex = m_proxyModel->mapFromSource(index);
    ui->listView->setRootIndex(proxyIndex);
    
    // 更新状态栏
    QDir dir(path);
    int fileCount = dir.entryList(QDir::Files).count();
    int dirCount = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).count();
    ui->statusLabel->setText(tr("文件夹: %1 | 文件: %2").arg(dirCount).arg(fileCount));
}

QString FileManagerPage::getSelectedFilePath() const
{
    QModelIndex index = ui->listView->currentIndex();
    if (!index.isValid()) return QString();
    
    QModelIndex sourceIndex = m_proxyModel->mapToSource(index);
    return m_fileModel->filePath(sourceIndex);
}

QString FileManagerPage::formatFileSize(qint64 size) const
{
    const QStringList units = {"B", "KB", "MB", "GB", "TB"};
    int unitIndex = 0;
    double fileSize = size;
    
    while (fileSize >= 1024.0 && unitIndex < units.size() - 1) {
        fileSize /= 1024.0;
        unitIndex++;
    }
    
    return QString("%1 %2").arg(fileSize, 0, 'f', 2).arg(units[unitIndex]);
}
