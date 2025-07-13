#ifndef HESTOOLBUTTON_H
#define HESTOOLBUTTON_H

#include <QToolButton>

#include "common/common_defs.h"


class HesMenu;
class HesToolButtonPrivate;
class HES_EXPORT HesToolButton : public QToolButton
{
    Q_OBJECT
    Q_DECLARE_PIMPL(HesToolButton)
    Q_PROPERTY_DEFINE_MEMBER_H(int,  BorderRadius);
    Q_PROPERTY_DEFINE_MEMBER_H(bool, IsSelected);

public:
    explicit HesToolButton(QWidget* parent = nullptr);
    ~HesToolButton();

    void setIsTransparent(bool isTransparent);
    bool getIsTransparent() const;

    void setMenu(HesMenu* menu);
    void setHesIcon(HesIconType::IconName icon);

protected:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // HESTOOLBUTTON_H
