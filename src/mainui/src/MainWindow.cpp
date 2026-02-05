/**
 * @file MainWindow.cpp
 */

#include "MainWindow.h"
#include "SecondWindow.h"
#include <QDebug>
#include <QTextCursor>

namespace mainui {

const QString MainWindow::COLOR_BLUE = "#3498db";
const QString MainWindow::COLOR_BLUE_HOVER = "#2980b9";
const QString MainWindow::COLOR_BLUE_PRESS = "#21618c";
const QString MainWindow::COLOR_RED = "#e74c3c";
const QString MainWindow::COLOR_RED_HOVER = "#c0392b";
const QString MainWindow::COLOR_RED_PRESS = "#922b21";
const QString MainWindow::COLOR_GREEN = "#27ae60";
const QString MainWindow::COLOR_GREEN_HOVER = "#229954";
const QString MainWindow::COLOR_GREEN_PRESS = "#1e8449";
const QString MainWindow::COLOR_PURPLE = "#9b59b6";
const QString MainWindow::COLOR_PURPLE_HOVER = "#8e44ad";
const QString MainWindow::COLOR_PURPLE_PRESS = "#71368a";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_buttonLayout(nullptr)
    , m_titleLabel(nullptr)
    , m_infoLabel(nullptr)
    , m_textEdit(nullptr)
    , m_showInfoButton(nullptr)
    , m_clearButton(nullptr)
    , m_systemInfoButton(nullptr)
    , m_calculatorButton(nullptr)
    , m_calculatorWindow(nullptr)
    , m_controller(new MainController())
{
    setupUi();
    setupConnections();
    setupWindowStyle();
    m_textEdit->append(m_controller->getWelcomeMessage());
}

MainWindow::~MainWindow()
{
    delete m_controller;
    m_controller = nullptr;
}

void MainWindow::setupUi()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    m_mainLayout = new QVBoxLayout(m_centralWidget);
    m_mainLayout->setSpacing(LAYOUT_SPACING);
    m_mainLayout->setContentsMargins(LAYOUT_MARGIN, LAYOUT_MARGIN,
                                      LAYOUT_MARGIN, LAYOUT_MARGIN);

    m_titleLabel = new QLabel("欢迎使用 LiquidCam", m_centralWidget);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50;");
    m_mainLayout->addWidget(m_titleLabel);

    m_infoLabel = new QLabel("这是一个基于Qt5和CMake的多模块项目模板", m_centralWidget);
    m_infoLabel->setAlignment(Qt::AlignCenter);
    m_infoLabel->setStyleSheet("font-size: 14px; color: #7f8c8d;");
    m_mainLayout->addWidget(m_infoLabel);

    m_textEdit = new QTextEdit(m_centralWidget);
    m_textEdit->setReadOnly(false);
    m_textEdit->setMinimumHeight(TEXT_EDIT_MIN_HEIGHT);
    m_textEdit->setPlaceholderText("操作日志将显示在这里...");
    m_textEdit->setStyleSheet(
        "QTextEdit {"
        "    border: 2px solid #bdc3c7;"
        "    border-radius: 5px;"
        "    padding: 10px;"
        "    font-family: 'Consolas', 'Monaco', monospace;"
        "    font-size: 12px;"
        "    color: #000000;"
        "    background-color: #f8f9fa;"
        "}"
    );
    m_mainLayout->addWidget(m_textEdit);

    m_buttonLayout = new QHBoxLayout();
    m_buttonLayout->setSpacing(10);

    m_showInfoButton = new QPushButton("显示信息", m_centralWidget);
    m_showInfoButton->setMinimumHeight(BUTTON_MIN_HEIGHT);
    m_showInfoButton->setStyleSheet(createButtonStyle(COLOR_BLUE,
                                                       COLOR_BLUE_HOVER,
                                                       COLOR_BLUE_PRESS));
    m_buttonLayout->addWidget(m_showInfoButton);

    m_clearButton = new QPushButton("清空", m_centralWidget);
    m_clearButton->setMinimumHeight(BUTTON_MIN_HEIGHT);
    m_clearButton->setStyleSheet(createButtonStyle(COLOR_RED,
                                                    COLOR_RED_HOVER,
                                                    COLOR_RED_PRESS));
    m_buttonLayout->addWidget(m_clearButton);

    m_systemInfoButton = new QPushButton("获取系统信息", m_centralWidget);
    m_systemInfoButton->setMinimumHeight(BUTTON_MIN_HEIGHT);
    m_systemInfoButton->setStyleSheet(createButtonStyle(COLOR_GREEN,
                                                         COLOR_GREEN_HOVER,
                                                         COLOR_GREEN_PRESS));
    m_buttonLayout->addWidget(m_systemInfoButton);

    m_calculatorButton = new QPushButton("打开计算器", m_centralWidget);
    m_calculatorButton->setMinimumHeight(BUTTON_MIN_HEIGHT);
    m_calculatorButton->setStyleSheet(createButtonStyle(COLOR_PURPLE,
                                                         COLOR_PURPLE_HOVER,
                                                         COLOR_PURPLE_PRESS));
    m_buttonLayout->addWidget(m_calculatorButton);

    m_mainLayout->addLayout(m_buttonLayout);
    m_mainLayout->addStretch();
}

void MainWindow::setupConnections()
{
    connect(m_showInfoButton, &QPushButton::clicked,
            this, &MainWindow::onShowInfoClicked);
    connect(m_clearButton, &QPushButton::clicked,
            this, &MainWindow::onClearClicked);
    connect(m_systemInfoButton, &QPushButton::clicked,
            this, &MainWindow::onGetSystemInfoClicked);
    connect(m_calculatorButton, &QPushButton::clicked,
            this, &MainWindow::onOpenCalculatorClicked);
}

void MainWindow::setupWindowStyle()
{
    setWindowTitle("LiquidCam - Main Window");
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setMinimumSize(WINDOW_MIN_WIDTH, WINDOW_MIN_HEIGHT);
    setStyleSheet("QMainWindow { background-color: #ecf0f1; }");
    setAttribute(Qt::WA_StyledBackground, true);
}

QString MainWindow::createButtonStyle(const QString &baseColor,
                                       const QString &hoverColor,
                                       const QString &pressedColor) const
{
    return QString(
        "QPushButton {"
        "    border: none;"
        "    border-radius: 5px;"
        "    color: white;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    background-color: %1;"
        "}"
        "QPushButton:hover { background-color: %2; }"
        "QPushButton:pressed { background-color: %3; }"
    ).arg(baseColor, hoverColor, pressedColor);
}

void MainWindow::onShowInfoClicked()
{
    m_textEdit->append(m_controller->createSeparator());
    m_textEdit->append(m_controller->processUserInput("用户点击了'显示信息'按钮"));
    m_textEdit->append(m_controller->getApplicationStats());
    m_textEdit->append(m_controller->createSeparator());
    m_textEdit->moveCursor(QTextCursor::End);
}

void MainWindow::onClearClicked()
{
    m_textEdit->clear();
    m_textEdit->append(m_controller->getWelcomeMessage());
}

void MainWindow::onGetSystemInfoClicked()
{
    m_textEdit->append(m_controller->createSeparator());
    m_textEdit->append(m_controller->processUserInput("用户点击了'获取系统信息'按钮"));
    m_textEdit->append(m_controller->getSystemInformation());
    m_textEdit->append(m_controller->createSeparator());
    m_textEdit->moveCursor(QTextCursor::End);
}

void MainWindow::onOpenCalculatorClicked()
{
    m_textEdit->append(m_controller->createSeparator());
    m_textEdit->append(m_controller->processUserInput("用户点击了'打开计算器'按钮"));

    if (!m_calculatorWindow) {
        m_calculatorWindow = new secondui::SecondWindow(nullptr);
        m_calculatorWindow->setWindowTitle("计算器");
        m_calculatorWindow->setAttribute(Qt::WA_DeleteOnClose, true);
        connect(m_calculatorWindow, &QMainWindow::destroyed, this, [this]() {
            m_calculatorWindow = nullptr;
        });
    }

    m_calculatorWindow->show();
    m_calculatorWindow->raise();
    m_calculatorWindow->activateWindow();

    m_textEdit->append("计算器窗口已打开");
    m_textEdit->append(m_controller->createSeparator());
    m_textEdit->moveCursor(QTextCursor::End);
}

} // namespace mainui
