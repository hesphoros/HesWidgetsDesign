#ifndef HESTEXT_H
#define HESTEXT_H

#include <QLabel>
#include "common/common_defs.h"
#include "stdafx.h"

class HesTextPrivate;

class HES_EXPORT HesText : public QLabel
{
    Q_OBJECT
    Q_DECLARE_PIMPL(HesText)
    Q_PROPERTY_DEFINE_MEMBER_H(bool, IsWrapAnywhere)                /*!< 是否允许任意位置换行 */
    Q_PROPERTY_DEFINE_MEMBER_H(int, TextPixelSize)                  /*!< 文本像素大小 */
    Q_PROPERTY_DEFINE_MEMBER_H(int, TextPointSize)                  /*!< 文本点大小 */
    Q_PROPERTY_DEFINE_MEMBER_H(HesTextType::TextStyle, TextStyle)   /*!< 文本样式 */
    Q_PROPERTY_DEFINE_MEMBER_H(HesIconType::IconName,  HesIcon)     /*!< HesIconType 图标名称 */
public:
    explicit HesText(QWidget *parent = nullptr);
    explicit HesText(QString text, QWidget *parent = nullptr);
    explicit HesText(QString text, int pixelSize, QWidget *parent = nullptr);
    ~HesText() override;
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};


#endif // HESTEXT_H