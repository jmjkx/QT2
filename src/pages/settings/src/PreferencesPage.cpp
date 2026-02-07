/**
 * @file PreferencesPage.cpp
 * @brief 首选项页面实现
 */

#include "PreferencesPage.h"
#include "ui_PreferencesPage.h"
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QStyleFactory>

PreferencesPage::PreferencesPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PreferencesPage())
    , m_settings(new QSettings("LiquidCam", "Preferences", this))
    , m_settingsChanged(false)
{
    ui->setupUi(this);
    
    setupConnections();
    loadSettings();
    
    qDebug() << "首选项页面创建完成";
}

PreferencesPage::~PreferencesPage()
{
    delete ui;
}

void PreferencesPage::setupConnections()
{
    // 外观设置
    connect(ui->themeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &PreferencesPage::onThemeChanged);
    connect(ui->languageCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &PreferencesPage::onLanguageChanged);
    connect(ui->fontSizeSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &PreferencesPage::onFontSizeChanged);
    
    // 行为设置
    connect(ui->autoSaveCheck, &QCheckBox::toggled, this, &PreferencesPage::onAutoSaveToggled);
    connect(ui->autoSaveIntervalSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &PreferencesPage::onAutoSaveIntervalChanged);
    connect(ui->minimizeToTrayCheck, &QCheckBox::toggled, this, &PreferencesPage::onMinimizeToTrayToggled);
    connect(ui->startupCheck, &QCheckBox::toggled, this, &PreferencesPage::onStartupToggled);
    
    // 操作按钮
    connect(ui->applyButton, &QPushButton::clicked, this, &PreferencesPage::onApplyClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &PreferencesPage::onResetClicked);
    connect(ui->restoreDefaultsButton, &QPushButton::clicked, this, &PreferencesPage::onRestoreDefaultsClicked);
}

void PreferencesPage::loadSettings()
{
    // 外观
    ui->themeCombo->setCurrentIndex(m_settings->value("appearance/theme", 0).toInt());
    ui->languageCombo->setCurrentIndex(m_settings->value("appearance/language", 0).toInt());
    ui->fontSizeSpin->setValue(m_settings->value("appearance/fontSize", 12).toInt());
    
    // 行为
    ui->autoSaveCheck->setChecked(m_settings->value("behavior/autoSave", true).toBool());
    ui->autoSaveIntervalSpin->setValue(m_settings->value("behavior/autoSaveInterval", 5).toInt());
    ui->minimizeToTrayCheck->setChecked(m_settings->value("behavior/minimizeToTray", false).toBool());
    ui->startupCheck->setChecked(m_settings->value("behavior/startup", false).toBool());
    
    m_settingsChanged = false;
    updateStatusLabel();
}

void PreferencesPage::saveSettings()
{
    // 外观
    m_settings->setValue("appearance/theme", ui->themeCombo->currentIndex());
    m_settings->setValue("appearance/language", ui->languageCombo->currentIndex());
    m_settings->setValue("appearance/fontSize", ui->fontSizeSpin->value());
    
    // 行为
    m_settings->setValue("behavior/autoSave", ui->autoSaveCheck->isChecked());
    m_settings->setValue("behavior/autoSaveInterval", ui->autoSaveIntervalSpin->value());
    m_settings->setValue("behavior/minimizeToTray", ui->minimizeToTrayCheck->isChecked());
    m_settings->setValue("behavior/startup", ui->startupCheck->isChecked());
    
    m_settings->sync();
    m_settingsChanged = false;
    
    qDebug() << "设置已保存";
    updateStatusLabel();
}

void PreferencesPage::updateStatusLabel()
{
    if (m_settingsChanged) {
        ui->statusLabel->setText(tr("⚠ 有未保存的更改"));
        ui->statusLabel->setStyleSheet("color: #e67e22; padding: 5px;");
    } else {
        ui->statusLabel->setText(tr("✓ 设置已保存"));
        ui->statusLabel->setStyleSheet("color: #27ae60; padding: 5px;");
    }
}

void PreferencesPage::onThemeChanged(int index)
{
    m_settingsChanged = true;
    updateStatusLabel();
    applyTheme(index);
}

void PreferencesPage::applyTheme(int themeIndex)
{
    QString style;
    switch (themeIndex) {
        case 0: // 浅色
            qApp->setStyle(QStyleFactory::create("Fusion"));
            qApp->setPalette(qApp->style()->standardPalette());
            break;
        case 1: // 深色
            style = R"(
                QWidget { background-color: #2c3e50; color: #ecf0f1; }
                QGroupBox { border: 1px solid #34495e; margin-top: 10px; padding-top: 10px; }
                QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; }
                QPushButton { background-color: #3498db; color: white; border: none; padding: 8px 16px; }
                QPushButton:hover { background-color: #2980b9; }
                QComboBox, QSpinBox, QCheckBox { color: #ecf0f1; }
            )";
            qApp->setStyleSheet(style);
            break;
        case 2: // 跟随系统
            qApp->setStyleSheet("");
            break;
    }
}

void PreferencesPage::onLanguageChanged(int index)
{
    Q_UNUSED(index)
    m_settingsChanged = true;
    updateStatusLabel();
}

void PreferencesPage::onFontSizeChanged(int size)
{
    QFont font = qApp->font();
    font.setPointSize(size);
    qApp->setFont(font);
    
    m_settingsChanged = true;
    updateStatusLabel();
}

void PreferencesPage::onAutoSaveToggled(bool checked)
{
    ui->autoSaveIntervalSpin->setEnabled(checked);
    ui->autoSaveIntervalLabel->setEnabled(checked);
    m_settingsChanged = true;
    updateStatusLabel();
}

void PreferencesPage::onAutoSaveIntervalChanged(int minutes)
{
    Q_UNUSED(minutes)
    m_settingsChanged = true;
    updateStatusLabel();
}

void PreferencesPage::onMinimizeToTrayToggled(bool checked)
{
    Q_UNUSED(checked)
    m_settingsChanged = true;
    updateStatusLabel();
}

void PreferencesPage::onStartupToggled(bool checked)
{
    Q_UNUSED(checked)
    m_settingsChanged = true;
    updateStatusLabel();
}

void PreferencesPage::onApplyClicked()
{
    saveSettings();
    QMessageBox::information(this, tr("成功"), tr("设置已应用并保存！"));
}

void PreferencesPage::onResetClicked()
{
    loadSettings();
    QMessageBox::information(this, tr("重置"), tr("已恢复到最后保存的设置。"));
}

void PreferencesPage::onRestoreDefaultsClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, tr("恢复默认"),
        tr("确定要恢复所有设置为默认值吗？"),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        m_settings->clear();
        loadSettings();
        QMessageBox::information(this, tr("完成"), tr("已恢复默认设置。"));
    }
}
