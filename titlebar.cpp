// TitleBar.cpp
#include "TitleBar.h"
#include <QSpacerItem>
#include <QStyle>
#include <QApplication>

TitleBar::TitleBar(const QString& title, QWidget* parent)
        : QWidget(parent)
        , m_isMaximized(false)
{
    m_titleLabel = new QLabel(title, this);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_minBtn = new QToolButton(this);
    m_minBtn->setText(QStringLiteral("🗕"));
    m_minBtn->setToolTip(tr("最小化"));
    connect(m_minBtn, &QToolButton::clicked, this, &TitleBar::onMinimize);

    m_maxBtn = new QToolButton(this);
    m_maxBtn->setText(QStringLiteral("🗖"));
    m_maxBtn->setToolTip(tr("最大化"));
    connect(m_maxBtn, &QToolButton::clicked, this, &TitleBar::onMaximizeRestore);

    m_closeBtn = new QToolButton(this);
    m_closeBtn->setText(QStringLiteral("🗙"));
    m_closeBtn->setToolTip(tr("关闭"));
    connect(m_closeBtn, &QToolButton::clicked, this, &TitleBar::onClose);

    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 0, 5, 0);
    layout->addWidget(m_titleLabel);
    layout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layout->addWidget(m_minBtn);
    layout->addWidget(m_maxBtn);
    layout->addWidget(m_closeBtn);
    setLayout(layout);

    setFixedHeight(30);
    setStyleSheet(R"(
        TitleBar {
            background-color: #2b2b2b;
        }
        QLabel {
            color: #ffffff;
        }
        QToolButton {
            background: transparent;
            border: none;
            color: #ffffff;
            font-size: 14px;
            padding: 0 6px;
        }
        QToolButton:hover {
            background-color: #3c3c3c;
        }
    )");
}

void TitleBar::onMinimize()
{
    emit minimizeClicked();
}

void TitleBar::onMaximizeRestore()
{
    m_isMaximized = !m_isMaximized;
    m_maxBtn->setText(m_isMaximized ? QStringLiteral("🗗") : QStringLiteral("🗖"));
    emit m_isMaximized ? maximizeClicked() : restoreClicked();
}

void TitleBar::onClose()
{
    emit closeClicked();
}
