/**
 * @file FileManagerPage.h
 * @brief 文件管理器页面 - 实用的文件浏览器
 */

#ifndef FILEMANAGERPAGE_H
#define FILEMANAGERPAGE_H

#include <QWidget>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class FileManagerPage; }
QT_END_NAMESPACE

/**
 * 文件管理器页面
 * 提供文件浏览、搜索、基本信息显示功能
 */
class FileManagerPage : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerPage(QWidget *parent = nullptr);
    ~FileManagerPage();

    static QString pageName() { return QObject::tr("文件管理"); }

private slots:
    void onTreeClicked(const QModelIndex &index);
    void onListClicked(const QModelIndex &index);
    void onPathEditReturn();
    void onUpButtonClicked();
    void onHomeButtonClicked();
    void onRefreshButtonClicked();
    void onSearchTextChanged(const QString &text);
    void onFilterChanged(int index);

private:
    void setupFileSystem();
    void updateCurrentPath(const QString &path);
    QString getSelectedFilePath() const;
    QString formatFileSize(qint64 size) const;

private:
    Ui::FileManagerPage *ui;
    QFileSystemModel *m_fileModel;
    QSortFilterProxyModel *m_proxyModel;
    QString m_currentPath;
};

#endif // FILEMANAGERPAGE_H
