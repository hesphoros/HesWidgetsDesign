#include "HesApplication.h"

#include "HesTheme.h"
#include "HesWinShadowHelper.h"
#include "private/HesApplicationPrivate.h"

#include <QApplication>
#include <QCursor>
#include <QFontDatabase>
#include <QWidget>
#include <utility>

HES_SINGLETON_CREATE_CPP(HesApplication)

HesApplication::HesApplication(QObject* parent)
    : QObject{parent}, d_ptr(new HesApplicationPrivate())
{
    Q_D(HesApplication);
    d->q_ptr = this;
    d->_pHesMicaImagePath = ":/include/Image/MicaBase.png";
    d->_pWindowDisplayMode = HesApplicationType::Normal;
    d->_themeMode = hesTheme->getThemeMode();
    connect(hesTheme, &HesTheme::themeModeChanged, d, &HesApplicationPrivate::onThemeModeChanged);
}

HesApplication::~HesApplication()
{
}


void HesApplication::setWindowDisplayMode(HesApplicationType::WindowDisplayMode windowDisplayType)
{
    Q_D(HesApplication);
    auto lastDisplayMode = d->_pWindowDisplayMode;
    if (lastDisplayMode == windowDisplayType)
    {
        return;
    }
    switch (windowDisplayType)
    {
    case HesApplicationType::Normal:
    {
        break;
    }
    case HesApplicationType::HesMica:
    {
        d->_pWindowDisplayMode = windowDisplayType;
        d->_initMicaBaseImage(QImage(d->_pHesMicaImagePath));
        break;
    }
    default:
    {
        break;
    }
    }
#ifdef Q_OS_WIN
    for (auto widget: d->_micaWidgetList)
    {
        HesWinShadowHelper::getInstance()->setWindowDisplayMode(widget, windowDisplayType, lastDisplayMode);
        HesWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), d->_themeMode == HesThemeType::Light);
    }
#endif
    if (windowDisplayType != HesApplicationType::HesMica)
    {
        d->_pWindowDisplayMode = windowDisplayType;
        Q_EMIT pWindowDisplayModeChanged();
    }
}


HesApplicationType::WindowDisplayMode HesApplication::getWindowDisplayMode() const
{
    Q_D(const HesApplication);
    return d->_pWindowDisplayMode;
}


void HesApplication::setHesMicaImagePath(QString micaImagePath)
{
    Q_D(HesApplication);
    d->_pHesMicaImagePath = std::move(micaImagePath);
    d->_initMicaBaseImage(QImage(d->_pHesMicaImagePath));
    Q_EMIT pHesMicaImagePathChanged();
}


QString HesApplication::getHesMicaImagePath() const
{
    Q_D(const HesApplication);
    return d->_pHesMicaImagePath;
}

void HesApplication::init()
{
    Q_INIT_RESOURCE(HesWidgetTools);
    QApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    QFontDatabase::addApplicationFont(":/include/Font/HesAwesome.ttf");
    //默认字体
    QFont font = qApp->font();
    font.setPixelSize(13);
    font.setFamily("Microsoft YaHei");
    font.setHintingPreference(QFont::PreferNoHinting);
    qApp->setFont(font);
}

void HesApplication::syncWindowDisplayMode(QWidget* widget, bool isSync)
{
    Q_D(HesApplication);
    if (!widget)
    {
        return;
    }
    if (isSync)
    {
        d->_micaWidgetList.append(widget);
        widget->installEventFilter(d);
    }
    else
    {
        d->_micaWidgetList.removeOne(widget);
        widget->removeEventFilter(d);
    }
    switch (d->_pWindowDisplayMode)
    {
    case HesApplicationType::Normal:
    case HesApplicationType::HesMica:
    {
        if (isSync)
        {
            if (d->_pWindowDisplayMode == HesApplicationType::WindowDisplayMode::HesMica)
            {
                d->_updateMica(widget, false);
            }
        }
        else
        {
        }
        break;
    }
    default:
    {
#ifdef Q_OS_WIN
        if (isSync)
        {
            HesWinShadowHelper::getInstance()->setWindowDisplayMode(widget, d->_pWindowDisplayMode, HesApplicationType::Normal);
            HesWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), d->_themeMode == HesThemeType::Light);
        }
        else
        {
            HesWinShadowHelper::getInstance()->setWindowDisplayMode(widget, HesApplicationType::Normal, d->_pWindowDisplayMode);
            HesWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), true);
        }
#endif
        break;
    }
    }
}

bool HesApplication::containsCursorToItem(QWidget* item)
{
    if (!item || !item->isVisible())
    {
        return false;
    }
    auto point = item->window()->mapFromGlobal(QCursor::pos());
    QRectF rect = QRectF(item->mapTo(item->window(), QPoint(0, 0)), item->size());
    if (rect.contains(point))
    {
        return true;
    }
    return false;
}
