#ifndef HESMENU_H
#define HESMENU_H


#include <QMenu>
#include <QWidget>

#include "common/common_defs.h"
#include "stdafx.h"
class HesMenuPrivate;
class HES_EXPORT HesMenu : public QMenu
{
    Q_OBJECT
    Q_DECLARE_PIMPL(HesMenu)

public:
    explicit HesMenu(QWidget* parent = nullptr);
    explicit HesMenu(const QString& title, QWidget* parent = nullptr);
    ~HesMenu();
    void setMenuItemHeight(int menuItemHeight);
    int getMenuItemHeight() const;

    QAction* addMenu(QMenu* menu);
    HesMenu* addMenu(const QString& title);
    HesMenu* addMenu(const QIcon& icon, const QString& title);
    HesMenu* addMenu(HesIconType::IconName icon, const QString& title);

    QAction* addHesIconAction(HesIconType::IconName icon, const QString& text);
    QAction* addHesIconAction(HesIconType::IconName icon, const QString& text, const QKeySequence& shortcut);

    bool isHasChildMenu() const;
    bool isHasIcon() const;
Q_SIGNALS:
    Q_SIGNAL void menuShow();

protected:
    virtual void showEvent(QShowEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // HESMENU_H