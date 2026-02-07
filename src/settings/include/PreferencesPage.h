/**
 * @file PreferencesPage.h
 * @brief 首选项/设置页面 - 应用配置中心
 */

#ifndef PREFERENCESPAGE_H
#define PREFERENCESPAGE_H

#include <QWidget>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class PreferencesPage; }
QT_END_NAMESPACE

/**
 * 首选项页面
 * 提供主题、语言、自动保存等设置
 */
class PreferencesPage : public QWidget
{
    Q_OBJECT

public:
    explicit PreferencesPage(QWidget *parent = nullptr);
    ~PreferencesPage();

    static QString pageName() { return QObject::tr("首选项"); }

private slots:
    // 外观设置
    void onThemeChanged(int index);
    void onLanguageChanged(int index);
    void onFontSizeChanged(int size);
    
    // 行为设置
    void onAutoSaveToggled(bool checked);
    void onAutoSaveIntervalChanged(int minutes);
    void onMinimizeToTrayToggled(bool checked);
    void onStartupToggled(bool checked);
    
    // 操作按钮
    void onApplyClicked();
    void onResetClicked();
    void onRestoreDefaultsClicked();

private:
    void loadSettings();
    void saveSettings();
    void setupConnections();
    void applyTheme(int themeIndex);
    void updateStatusLabel();

private:
    Ui::PreferencesPage *ui;
    QSettings *m_settings;
    bool m_settingsChanged;
};

#endif // PREFERENCESPAGE_H
