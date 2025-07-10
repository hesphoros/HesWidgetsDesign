#include "HesApplicationPrivate.h"

#include <QApplication>
#include <QEvent>
#include <QImage>
#include <QPalette>
#include <QScreen>
#include <QThread>
#include <QWidget>
#include <QtMath>


// #include "ElaApplication.h"
// #include "ElaMicaBaseInitObject.h"
// #include "ElaWinShadowHelper.h"

HesApplicationPrivate::HesApplicationPrivate(QObject* parent): QObject{parent} { }

HesApplicationPrivate::~HesApplicationPrivate() { }

void HesApplicationPrivate::onThemeModeChanged(HesThemeType::ThemeMode themeMode)
{
    _themeMode = themeMode;
    switch (_pWindowDisplayMode)
    {
        case HesApplicationType::Normal:
        {
            break;
        }
        case HesApplicationType::HesMica:
        {
            _updateAllMicaWidget();
            break;
        }
        default:
        {
            #ifdef Q_OS_WIN
                for (auto widget: _micaWidgetList)
                {
                    HesWinShadowHelper::getInstance()->setWindowThemeMode(widget->winId(), _themeMode == HesThemeType::Light);
                }
            #endif
            break;
        }
    }
}



bool HesApplicationPrivate::eventFilter(QObject* watched, QEvent* event)
{
    switch (event->type())
    {
        case QEvent::Show:
        {
            if (_pWindowDisplayMode == HesApplicationType::WindowDisplayMode::HesMica) {
                QWidget* widget = qobject_cast<QWidget*>(watched);
                if (widget) {
                    _updateMica(widget);
                }
            }
            else if (_pWindowDisplayMode != HesApplicationType::WindowDisplayMode::Normal) {
            #ifdef Q_OS_WIN
                QWidget* widget = qobject_cast<QWidget*>(watched);
                if (widget) {
                    HesWinShadowHelper::getInstance()->setWindowDisplayMode(widget, _pWindowDisplayMode, _pWindowDisplayMode);
                }
            #endif
            }
            break;
        }

        case QEvent::Move:
        
        case QEvent::Resize:
        {
            if (_pWindowDisplayMode == ElaApplicationType::WindowDisplayMode::ElaMica) {
                QWidget* widget = qobject_cast<QWidget*>(watched);
                if (widget) {
                    _updateMica(widget);
                }
            }
            break;
        }
        
        case QEvent::Destroy:
        {
            QWidget* widget = qobject_cast<QWidget*>(watched);
            if (widget) {
                _micaWidgetList.removeOne(widget);
            }
            break;
        }

        default:
        {
            break;
        }
    }
    return QObject::eventFilter(watched, event);
}


void HesApplicationPrivate::_initMicaBaseImage(QImage img)
{
    Q_Q(HesApplication);
    if (img.isNull())
    {
        return;
    }
    QThread* initThread = new QThread();
    HesMicaBaseInitObject* initObject = new HesMicaBaseInitObject(this);
    connect(initThread, &QThread::finished, initObject, &HesMicaBaseInitObject::deleteLater);
    connect(initObject, &HesMicaBaseInitObject::initFinished, initThread, [=]() {
        Q_EMIT q->pWindowDisplayModeChanged();
        _updateAllMicaWidget();
        initThread->quit();
        initThread->wait();
        initThread->deleteLater();
    });
    initObject->moveToThread(initThread);
    initThread->start();
    connect(this, &HesApplicationPrivate::initMicaBase, initObject, &HesMicaBaseInitObject::onInitMicaBase);
    Q_EMIT initMicaBase(img);
}


QRect HesApplicationPrivate::_calculateWindowVirtualGeometry(QWidget* widget)
{
    QRect geometry = widget->geometry();
    qreal xImageRatio = 1, yImageRatio = 1;
    QRect relativeGeometry;
    if (HesApp->screens().count() > 1)
    {
        QScreen* currentScreen = HesApp->screenAt(geometry.topLeft());
        if (currentScreen)
        {
            QRect screenGeometry = currentScreen->availableGeometry();
            xImageRatio = (qreal)_lightBaseImage.width() / screenGeometry.width();
            yImageRatio = (qreal)_lightBaseImage.height() / screenGeometry.height();
            relativeGeometry = QRect((geometry.x() - screenGeometry.x()) * xImageRatio, (geometry.y() - screenGeometry.y()) * yImageRatio, geometry.width() * xImageRatio, geometry.height() * yImageRatio);
            return relativeGeometry;
        }
    }
    QRect primaryScreenGeometry = HesApp->primaryScreen()->availableGeometry();
    xImageRatio = (qreal)_lightBaseImage.width() / primaryScreenGeometry.width();
    yImageRatio = (qreal)_lightBaseImage.height() / primaryScreenGeometry.height();
    relativeGeometry = QRect((geometry.x() - primaryScreenGeometry.x()) * xImageRatio, (geometry.y() - primaryScreenGeometry.y()) * yImageRatio, geometry.width() * xImageRatio, geometry.height() * yImageRatio);
    return relativeGeometry;
}

void HesApplicationPrivate::_updateMica(QWidget* widget, bool isProcessEvent)
{
    if (widget->isVisible())
    {
        QPalette palette = widget->palette();
        if (_themeMode == HesThemeType::Light)
        {
            palette.setBrush(QPalette::Window, _lightBaseImage.copy(_calculateWindowVirtualGeometry(widget)).scaled(widget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            palette.setBrush(QPalette::Window, _darkBaseImage.copy(_calculateWindowVirtualGeometry(widget)).scaled(widget->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        }
        widget->setPalette(palette);
        if (isProcessEvent)
        {
            QApplication::processEvents();
        }
    }
}

void HesApplicationPrivate::_updateAllMicaWidget()
{
    if (_pWindowDisplayMode == HesApplicationType::WindowDisplayMode::ElaMica)
    {
        for (auto widget: _micaWidgetList)
        {
            _updateMica(widget, false);
        }
    }
}