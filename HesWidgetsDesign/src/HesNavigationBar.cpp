#include "HesNavigationBar.h"

#include "HesBaseListView.h"
#include "HesFooterDelegate.h"
#include "HesFooterModel.h"
#include "HesIconButton.h"
#include "HesInteractiveCard.h"
#include "HesMenu.h"
#include "HesNavigationModel.h"
#include "HesNavigationNode.h"

#include "HesNavigationView.h"
#include "HesSuggestBox.h"
#include "HesTheme.h"
#include "HesToolButton.h"
#include "HesNavigationBarPrivate.h"
#include "HesSuggestBoxPrivate.h"
#include <QEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QScroller>
#include <QVBoxLayout>
Q_PROPERTY_DEFINE_MEMBER_CPP(HesNavigationBar, bool, IsTransparent)
Q_PROPERTY_DEFINE_MEMBER_CPP(HesNavigationBar, bool, IsAllowPageOpenInNewWindow)
HesNavigationBar::HesNavigationBar(QWidget* parent)
    : QWidget{parent}, d_ptr(new HesNavigationBarPrivate())
{
    Q_D(HesNavigationBar);
    d->q_ptr = this;
    d->_pIsAllowPageOpenInNewWindow = true;
    d->_pNavigationBarWidth = 300;
    setFixedWidth(300);
    d->_pIsTransparent = true;

    //用户卡片
    d->_userCard = new ElaInteractiveCard(this);
    d->_userCard->setMinimumWidth(0);
    d->_userCard->setCardPixmap(QPixmap(":/include/Image/Cirno.jpg"));
    d->_userCard->setTitle("Ela Tool");
    d->_userCard->setSubTitle("Liniyous@gmail.com");
    connect(d->_userCard, &ElaInteractiveCard::clicked, this, &HesNavigationBar::userInfoCardClicked);
    d->_userButton = new HesIconButton(QPixmap(":/include/Image/Cirno.jpg"), this);
    d->_userButton->setFixedSize(36, 36);
    d->_userButton->setVisible(false);
    d->_userButton->setBorderRadius(8);
    d->_userButtonLayout = new QVBoxLayout();
    d->_userButtonLayout->setAlignment(Qt::AlignLeft);
    d->_userButtonLayout->setContentsMargins(0, 0, 0, 6);
    d->_userButtonLayout->setSpacing(0);
    d->_userButtonLayout->addWidget(d->_userButton);

    connect(d->_userButton, &HesIconButton::clicked, this, &HesNavigationBar::userInfoCardClicked);
    QHBoxLayout* userCardLayout = new QHBoxLayout();
    userCardLayout->setContentsMargins(0, 0, 0, 0);
    userCardLayout->addSpacing(3);
    userCardLayout->addLayout(d->_userButtonLayout);
    userCardLayout->addWidget(d->_userCard);

    // 搜索栏和按钮组
    d->_navigationButton = new ElaToolButton(this);
    d->_navigationButton->setFixedSize(40, 38);
    d->_navigationButton->setElaIcon(ElaIconType::Bars);
    d->_navigationButton->setBorderRadius(8);
    connect(d->_navigationButton, &ElaToolButton::clicked, d, &HesNavigationBarPrivate::onNavigationButtonClicked);

    d->_searchButton = new ElaToolButton(this);
    d->_searchButton->setFixedSize(40, 38);
    d->_searchButton->setElaIcon(ElaIconType::MagnifyingGlass);
    d->_searchButton->setBorderRadius(8);
    connect(d->_searchButton, &ElaToolButton::clicked, d, &HesNavigationBarPrivate::onNavigationButtonClicked);
    d->_searchButton->setVisible(false);

    d->_navigationSuggestBox = new ElaSuggestBox(this);
    d->_navigationSuggestBox->setMinimumWidth(0);
    d->_navigationButtonLayout = new QVBoxLayout();
    d->_navigationButtonLayout->setContentsMargins(0, 0, 0, 0);
    d->_navigationButtonLayout->setSpacing(0);
    d->_navigationButtonLayout->addWidget(d->_navigationButton);
    d->_navigationButtonLayout->addWidget(d->_searchButton);

    d->_navigationSuggestLayout = new QHBoxLayout();
    d->_navigationSuggestLayout->setContentsMargins(0, 0, 10, 0);
    d->_navigationSuggestLayout->setSpacing(6);
    d->_navigationSuggestLayout->addLayout(d->_navigationButtonLayout);
    d->_navigationSuggestLayout->addWidget(d->_navigationSuggestBox);

    // 搜索跳转
    connect(d->_navigationSuggestBox, &ElaSuggestBox::suggestionClicked, this, [=](QString suggestText, QVariantMap suggestData) {
        ElaNavigationNode* node = nullptr;
        if (suggestData.value("ElaNodeType").toString() == "Stacked")
        {
            node = d->_navigationModel->getNavigationNode(suggestData.value("ElaPageKey").toString());
            if (node)
            {
                d->onTreeViewClicked(node->getModelIndex());
            }
        }
        else
        {
            node = d->_footerModel->getNavigationNode(suggestData.value("ElaPageKey").toString());
            if (node)
            {
                d->onFooterViewClicked(node->getModelIndex());
            }
        }
    });

    // 导航模型
    d->_navigationModel = new ElaNavigationModel(this);
    d->_navigationView = new ElaNavigationView(this);
    d->_navigationView->setNavigationBarPrivate(d);
    d->_navigationView->setModel(d->_navigationModel);
    connect(d->_navigationView, &ElaNavigationView::navigationClicked, this, [=](const QModelIndex& index) {
        d->onTreeViewClicked(index);
    });
    connect(d->_navigationView, &ElaNavigationView::navigationOpenNewWindow, d, &HesNavigationBarPrivate::onNavigationOpenNewWindow);

    // 页脚
    d->_footerView = new ElaBaseListView(this);
    d->_footerView->setFixedHeight(0);
    d->_footerModel = new ElaFooterModel(this);
    d->_footerView->setModel(d->_footerModel);
    d->_footerDelegate = new ElaFooterDelegate(this);
    d->_footerDelegate->setElaListView(d->_footerView);
    d->_footerView->setItemDelegate(d->_footerDelegate);
    connect(d->_footerView, &ElaBaseListView::mousePress, this, [=](const QModelIndex& index) {
        d->_footerDelegate->setPressIndex(index);
        d->_footerView->viewport()->update();
    });
    connect(d->_footerView, &ElaBaseListView::mouseDoubleClick, this, [=](const QModelIndex& index) {
        d->_footerDelegate->setPressIndex(index);
        d->_footerView->viewport()->update();
    });
    connect(d->_footerView, &ElaBaseListView::mouseRelease, this, [=](const QModelIndex& index) {
        d->_footerDelegate->setPressIndex(QModelIndex());
        d->_footerView->viewport()->update();
    });
    connect(d->_footerView, &ElaBaseListView::clicked, this, [=](const QModelIndex& index) {
        d->onFooterViewClicked(index);
    });

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignLeft);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 10, 5, 0);
    mainLayout->addLayout(userCardLayout);
    mainLayout->addSpacing(4);
    mainLayout->addLayout(d->_navigationSuggestLayout);
    mainLayout->addSpacing(4);
    mainLayout->addWidget(d->_navigationView);
    mainLayout->addWidget(d->_footerView);

    // 主题设置
    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        d->_themeMode = themeMode;
    });
}

HesNavigationBar::~HesNavigationBar()
{
}

void HesNavigationBar::setNavigationBarWidth(int navigationBarWidth)
{
    Q_D(HesNavigationBar);
    if (navigationBarWidth < 180)
    {
        navigationBarWidth = 180;
    }
    if (d->_currentDisplayMode == HesNavigationType::NavigationDisplayMode::Maximal)
    {
        setFixedWidth(navigationBarWidth);
    }
    d->_pNavigationBarWidth = navigationBarWidth;
    Q_EMIT pNavigationBarWidthChanged();
}

int HesNavigationBar::getNavigationBarWidth() const
{
    Q_D(const HesNavigationBar);
    return d->_pNavigationBarWidth;
}

void HesNavigationBar::setUserInfoCardVisible(bool isVisible)
{
    Q_D(HesNavigationBar);
    d->_isShowUserCard = isVisible;
    d->_userCard->setVisible(isVisible);
    if (!isVisible)
    {
        d->_userButton->setVisible(false);
    }
}

void HesNavigationBar::setUserInfoCardPixmap(QPixmap pix)
{
    Q_D(HesNavigationBar);
    d->_userCard->setCardPixmap(pix);
    d->_userButton->setPixmap(pix);
}

void HesNavigationBar::setUserInfoCardTitle(QString title)
{
    Q_D(HesNavigationBar);
    d->_userCard->setTitle(title);
}

void HesNavigationBar::setUserInfoCardSubTitle(QString subTitle)
{
    Q_D(HesNavigationBar);
    d->_userCard->setSubTitle(subTitle);
}

HesNavigationType::NodeOperateReturnType HesNavigationBar::addExpanderNode(QString expanderTitle, QString& expanderKey, ElaIconType::IconName awesome)
{
    Q_D(HesNavigationBar);
    HesNavigationType::NodeOperateReturnType returnType = d_ptr->_navigationModel->addExpanderNode(expanderTitle, expanderKey, awesome);
    if (returnType == HesNavigationType::Success)
    {
        d->_initNodeModelIndex(QModelIndex());
        d->_resetNodeSelected();
    }
    return returnType;
}

HesNavigationType::NodeOperateReturnType HesNavigationBar::addExpanderNode(QString expanderTitle, QString& expanderKey, QString targetExpanderKey, ElaIconType::IconName awesome)
{
    Q_D(HesNavigationBar);
    HesNavigationType::NodeOperateReturnType returnType = d->_navigationModel->addExpanderNode(expanderTitle, expanderKey, targetExpanderKey, awesome);
    if (returnType == HesNavigationType::Success)
    {
        d->_initNodeModelIndex(QModelIndex());
        d->_resetNodeSelected();
    }
    return returnType;
}

HesNavigationType::NodeOperateReturnType HesNavigationBar::addPageNode(QString pageTitle, QWidget* page, ElaIconType::IconName awesome)
{
    Q_D(HesNavigationBar);
    if (!page)
    {
        return HesNavigationType::PageInvalid;
    }
    QString pageKey;
    HesNavigationType::NodeOperateReturnType returnType = d_ptr->_navigationModel->addPageNode(pageTitle, pageKey, awesome);
    if (returnType == HesNavigationType::Success)
    {
        d->_pageMetaMap.insert(pageKey, page->metaObject());
        d->_pageNewWindowCountMap.insert(pageKey, 0);
        d->_addStackedPage(page, pageKey);
        d->_initNodeModelIndex(QModelIndex());
        d->_resetNodeSelected();
    }
    return returnType;
}

HesNavigationType::NodeOperateReturnType HesNavigationBar::addPageNode(QString pageTitle, QWidget* page, QString targetExpanderKey, ElaIconType::IconName awesome)
{
    Q_D(HesNavigationBar);
    if (!page)
    {
        return HesNavigationType::PageInvalid;
    }
    if (targetExpanderKey.isEmpty())
    {
        return HesNavigationType::TargetNodeInvalid;
    }
    QString pageKey;
    HesNavigationType::NodeOperateReturnType returnType = d->_navigationModel->addPageNode(pageTitle, pageKey, targetExpanderKey, awesome);
    if (returnType == HesNavigationType::NodeOperateReturnType::Success)
    {
        d->_pageMetaMap.insert(pageKey, page->metaObject());
        d->_pageNewWindowCountMap.insert(pageKey, 0);
        ElaNavigationNode* node = d->_navigationModel->getNavigationNode(pageKey);
        ElaNavigationNode* originalNode = node->getOriginalNode();
        if (d->_compactMenuMap.contains(originalNode))
        {
            ElaMenu* menu = d->_compactMenuMap.value(originalNode);
            QAction* action = menu->addElaIconAction(node->getAwesome(), node->getNodeTitle());
            connect(action, &QAction::triggered, this, [=]() {
                d->onTreeViewClicked(node->getModelIndex());
            });
        }
        else
        {
            ElaMenu* menu = new ElaMenu(const_cast<HesNavigationBar*>(this));
            QAction* action = menu->addElaIconAction(node->getAwesome(), node->getNodeTitle());
            connect(action, &QAction::triggered, this, [=]() {
                d_ptr->onTreeViewClicked(node->getModelIndex());
            });
            d_ptr->_compactMenuMap.insert(originalNode, menu);
        }
        d_ptr->_addStackedPage(page, pageKey);
        d->_initNodeModelIndex(QModelIndex());
        d->_resetNodeSelected();
    }
    return returnType;
}

HesNavigationType::NodeOperateReturnType HesNavigationBar::addPageNode(QString pageTitle, QWidget* page, int keyPoints, ElaIconType::IconName awesome)
{
    Q_D(HesNavigationBar);
    if (!page)
    {
        return HesNavigationType::PageInvalid;
    }
    QString pageKey;
    HesNavigationType::NodeOperateReturnType returnType = d_ptr->_navigationModel->addPageNode(pageTitle, pageKey, keyPoints, awesome);
    if (returnType == HesNavigationType::Success)
    {
        d->_pageMetaMap.insert(pageKey, page->metaObject());
        d->_pageNewWindowCountMap.insert(pageKey, 0);
        d->_addStackedPage(page, pageKey);
        d->_initNodeModelIndex(QModelIndex());
        d->_resetNodeSelected();
    }
    return returnType;
}

HesNavigationType::NodeOperateReturnType HesNavigationBar::addPageNode(QString pageTitle, QWidget* page, QString targetExpanderKey, int keyPoints, ElaIconType::IconName awesome)
{
    Q_D(HesNavigationBar);
    if (!page)
    {
        return HesNavigationType::PageInvalid;
    }
    if (targetExpanderKey.isEmpty())
    {
        return HesNavigationType::TargetNodeInvalid;
    }
    QString pageKey;
    HesNavigationType::NodeOperateReturnType returnType = d_ptr->_navigationModel->addPageNode(pageTitle, pageKey, targetExpanderKey, keyPoints, awesome);
    if (returnType == HesNavigationType::Success)
    {
        d->_pageMetaMap.insert(pageKey, page->metaObject());
        d->_pageNewWindowCountMap.insert(pageKey, 0);
        ElaNavigationNode* node = d_ptr->_navigationModel->getNavigationNode(pageKey);
        ElaNavigationNode* originalNode = node->getOriginalNode();
        if (d_ptr->_compactMenuMap.contains(originalNode))
        {
            ElaMenu* menu = d_ptr->_compactMenuMap.value(originalNode);
            QAction* action = menu->addElaIconAction(node->getAwesome(), node->getNodeTitle());
            connect(action, &QAction::triggered, this, [=]() {
                d_ptr->onTreeViewClicked(node->getModelIndex());
            });
        }
        else
        {
            ElaMenu* menu = new ElaMenu(const_cast<HesNavigationBar*>(this));
            QAction* action = menu->addElaIconAction(node->getAwesome(), node->getNodeTitle());
            connect(action, &QAction::triggered, this, [=]() {
                d_ptr->onTreeViewClicked(node->getModelIndex());
            });
            d_ptr->_compactMenuMap.insert(originalNode, menu);
        }
        d_ptr->_addStackedPage(page, pageKey);
        d->_initNodeModelIndex(QModelIndex());
        d->_resetNodeSelected();
    }
    return returnType;
}

HesNavigationType::NodeOperateReturnType HesNavigationBar::addFooterNode(QString footerTitle, QString& footerKey, int keyPoints, ElaIconType::IconName awesome)
{
    return addFooterNode(footerTitle, nullptr, footerKey, keyPoints, awesome);
}

HesNavigationType::NodeOperateReturnType HesNavigationBar::addFooterNode(QString footerTitle, QWidget* page, QString& footerKey, int keyPoints, ElaIconType::IconName awesome)
{
    HesNavigationType::NodeOperateReturnType returnType = d_ptr->_footerModel->addFooterNode(footerTitle, footerKey, page ? true : false, keyPoints, awesome);
    if (returnType == HesNavigationType::Success)
    {
        d_ptr->_addFooterPage(page, footerKey);
    }
    return returnType;
}

bool HesNavigationBar::getNavigationNodeIsExpanded(QString expanderKey) const
{
    Q_D(const HesNavigationBar);
    ElaNavigationNode* node = d->_navigationModel->getNavigationNode(expanderKey);
    if (!node || !node->getIsExpanderNode())
    {
        return false;
    }
    return d->_navigationView->isExpanded(node->getModelIndex());
}

void HesNavigationBar::expandNavigationNode(QString expanderKey)
{
    Q_D(HesNavigationBar);
    ElaNavigationNode* node = d->_navigationModel->getNavigationNode(expanderKey);
    if (!node || !node->getIsExpanderNode())
    {
        return;
    }
    d->_expandOrCollpaseExpanderNode(node, true);
    d->_resetNodeSelected();
}

void HesNavigationBar::collpaseNavigationNode(QString expanderKey)
{
    Q_D(HesNavigationBar);
    ElaNavigationNode* node = d->_navigationModel->getNavigationNode(expanderKey);
    if (!node || !node->getIsExpanderNode())
    {
        return;
    }
    d->_expandOrCollpaseExpanderNode(node, false);
    d->_resetNodeSelected();
}

void HesNavigationBar::removeNavigationNode(QString nodeKey)
{
    Q_D(HesNavigationBar);
    ElaNavigationNode* node = d->_navigationModel->getNavigationNode(nodeKey);
    if (!node)
    {
        node = d->_footerModel->getNavigationNode(nodeKey);
    }
    if (!node)
    {
        return;
    }
    if (node->getIsFooterNode())
    {
        Q_EMIT navigationNodeRemoved(HesNavigationType::FooterNode, nodeKey);
        d->_footerModel->removeNavigationNode(nodeKey);
        d->_footerView->setFixedHeight(40 * d->_footerModel->getFooterNodeCount());
    }
    else
    {
        QStringList removeKeyList = d->_navigationModel->removeNavigationNode(nodeKey);
        d->_initNodeModelIndex(QModelIndex());
        for (const auto& removeKey: removeKeyList)
        {
            d->_pageMetaMap.remove(removeKey);
            d->_pageNewWindowCountMap.remove(removeKey);
            Q_EMIT navigationNodeRemoved(HesNavigationType::PageNode, removeKey);
        }
    }
    d->_navigationSuggestBox->removeSuggestion(d->_suggestKeyMap.value(nodeKey));
}

void HesNavigationBar::setNodeKeyPoints(QString nodeKey, int keyPoints)
{
    Q_D(HesNavigationBar);
    ElaNavigationNode* node = d->_navigationModel->getNavigationNode(nodeKey);
    if (!node)
    {
        node = d->_footerModel->getNavigationNode(nodeKey);
    }
    else if (node->getIsExpanderNode() || keyPoints < 0)
    {
        return;
    }
    if (!node)
    {
        return;
    }
    node->setKeyPoints(keyPoints);
    if (node->getIsFooterNode())
    {
        d->_footerView->viewport()->update();
    }
    else
    {
        d->_navigationView->viewport()->update();
    }
}

int HesNavigationBar::getNodeKeyPoints(QString nodeKey) const
{
    Q_D(const HesNavigationBar);
    ElaNavigationNode* node = d->_navigationModel->getNavigationNode(nodeKey);
    if (!node)
    {
        node = d->_footerModel->getNavigationNode(nodeKey);
    }
    else if (node->getIsExpanderNode())
    {
        return -1;
    }
    if (!node)
    {
        return -1;
    }
    return node->getKeyPoints();
}

void HesNavigationBar::navigation(QString pageKey, bool isLogClicked, bool isRouteBack)
{
    Q_D(HesNavigationBar);
    ElaNavigationNode* node = d->_navigationModel->getNavigationNode(pageKey);
    if (!node)
    {
        node = d->_footerModel->getNavigationNode(pageKey);
    }
    if (node)
    {
        if (node->getIsFooterNode())
        {
            d->onFooterViewClicked(node->getModelIndex(), isLogClicked, isRouteBack);
        }
        else
        {
            if (!node->getIsExpanderNode())
            {
                d->onTreeViewClicked(node->getModelIndex(), isLogClicked, isRouteBack);
            }
        }
    }
}

void HesNavigationBar::setDisplayMode(HesNavigationType::NavigationDisplayMode displayMode, bool isAnimation)
{
    Q_D(HesNavigationBar);
    if (d->_currentDisplayMode == displayMode || displayMode == HesNavigationType::Auto)
    {
        return;
    }
    d->_doComponentAnimation(displayMode, isAnimation);
    d->_raiseNavigationBar();
}

int HesNavigationBar::getPageOpenInNewWindowCount(QString nodeKey) const
{
    Q_D(const HesNavigationBar);
    if (!d->_pageNewWindowCountMap.contains(nodeKey))
    {
        return 0;
    }
    return d->_pageNewWindowCountMap[nodeKey];
}

void HesNavigationBar::paintEvent(QPaintEvent* event)
{
    Q_D(HesNavigationBar);
    if (!d->_pIsTransparent)
    {
        QPainter painter(this);
        painter.save();
        painter.setPen(ElaThemeColor(d->_themeMode, PopupBorder));
        painter.setBrush(ElaThemeColor(d->_themeMode, PopupBase));
        QRect baseRect = this->rect();
        baseRect.adjust(-1, 0, -1, 0);
        QPainterPath path;
        path.moveTo(baseRect.topLeft());
        path.lineTo(QPoint(baseRect.right() - 8, baseRect.y()));
        path.arcTo(QRectF(baseRect.right() - 16, baseRect.y(), 16, 16), 90, -90);
        path.lineTo(QPoint(baseRect.right(), baseRect.bottom() - 8));
        path.arcTo(QRectF(baseRect.right() - 16, baseRect.bottom() - 16, 16, 16), 0, -90);
        path.lineTo(baseRect.bottomLeft());
        path.closeSubpath();
        painter.drawPath(path);
        painter.restore();
    }
    QWidget::paintEvent(event);
}
