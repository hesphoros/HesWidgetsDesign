#ifndef HESNAVIGATIONBAR_H
#define HESNAVIGATIONBAR_H

#include <QWidget>

#include "common/common_defs.h"
#include "stdafx.h"

class HesNavigationBarPrivate;
class HES_EXPORT HesNavigationBar : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PIMPL(HesNavigationBar)
    Q_PROPERTY_DEFINE_MEMBER_H(bool, IsTransparent)
    Q_PROPERTY_DEFINE_MEMBER_H(bool, IsAllowPageOpenInNewWindow)
    Q_PROPERTY_DEFINE_MEMBER_H(int, NavigationBarWidth)
public:
    explicit HesNavigationBar(QWidget* parent = nullptr);
    ~HesNavigationBar() override;
    void setUserInfoCardVisible(bool isVisible);
    void setUserInfoCardPixmap(QPixmap pix);
    void setUserInfoCardTitle(QString title);
    void setUserInfoCardSubTitle(QString subTitle);

    HesNavigationType::NodeOperateReturnType addExpanderNode(QString expanderTitle, QString& expanderKey, HesIconType::IconName awesome = HesIconType::None);
    HesNavigationType::NodeOperateReturnType addExpanderNode(QString expanderTitle, QString& expanderKey, QString targetExpanderKey, HesIconType::IconName awesome = HesIconType::None);
    HesNavigationType::NodeOperateReturnType addPageNode(QString pageTitle, QWidget* page, HesIconType::IconName awesome = HesIconType::None);
    HesNavigationType::NodeOperateReturnType addPageNode(QString pageTitle, QWidget* page, QString targetExpanderKey, HesIconType::IconName awesome = HesIconType::None);
    HesNavigationType::NodeOperateReturnType addPageNode(QString pageTitle, QWidget* page, int keyPoints = 0, HesIconType::IconName awesome = HesIconType::None);
    HesNavigationType::NodeOperateReturnType addPageNode(QString pageTitle, QWidget* page, QString targetExpanderKey, int keyPoints = 0, HesIconType::IconName awesome = HesIconType::None);
    HesNavigationType::NodeOperateReturnType addFooterNode(QString footerTitle, QString& footerKey, int keyPoints = 0, HesIconType::IconName awesome = HesIconType::None);
    HesNavigationType::NodeOperateReturnType addFooterNode(QString footerTitle, QWidget* page, QString& footerKey, int keyPoints = 0, HesIconType::IconName awesome = HesIconType::None);

    bool getNavigationNodeIsExpanded(QString expanderKey) const;
    void expandNavigationNode(QString expanderKey);
    void collpaseNavigationNode(QString expanderKey);
    void removeNavigationNode(QString nodeKey);

    void setNodeKeyPoints(QString nodeKey, int keyPoints);
    int getNodeKeyPoints(QString nodeKey) const;

    void navigation(QString pageKey, bool isLogClicked = true, bool isRouteBack = false);
    void setDisplayMode(HesNavigationType::NavigationDisplayMode displayMode, bool isAnimation = true);

    int getPageOpenInNewWindowCount(QString nodeKey) const;

Q_SIGNALS:
    Q_SIGNAL void pageOpenInNewWindow(QString nodeKey);
    Q_SIGNAL void userInfoCardClicked();
    Q_SIGNAL void navigationNodeClicked(HesNavigationType::NavigationNodeType nodeType, QString nodeKey, bool isRouteBack);
    Q_SIGNAL void navigationNodeAdded(HesNavigationType::NavigationNodeType nodeType, QString nodeKey, QWidget* page);
    Q_SIGNAL void navigationNodeRemoved(HesNavigationType::NavigationNodeType nodeType, QString nodeKey);

protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // HESNAVIGATIONBAR_H
