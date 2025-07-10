#ifndef HESAPPLICATIONPRIVATE_H
#define HESAPPLICATIONPRIVATE_H

#include <QColor>
#include <QIcon>
#include <QScopedPointer>
#include <QObject>

#include "common/common_defs.h"

class HesApplication;
class HesApplicationPrivate : public QObject
{
    Q_OBJECT
    Q_D_DECLARE_POINTER(HesApplication)
    Q_PROPERTY_CREATE_PRIVATE(HesApplicationType::WindowDisplayMode, WindowDisplayMode)
    Q_PROPERTY_CREATE_PRIVATE(QString, MicaImagePath)
public:
    explicit HesApplicationPrivate(QObject* parent = nullptr);
    ~HesApplicationPrivate() override;
    Q_SLOT void onThemeModeChanged(HesThemeType::ThemeMode themeMode);
Q_SIGNALS:
    Q_SIGNAL void initMicaBase(QImage img);
protected:
    virtual bool eventFilter(QObject* watched, QEvent* event) override;

private:
   
    HesThemeType::ThemeMode _themeMode;
    QList<QWidget*>         _micaWidgetList;
    QImage                  _lightBaseImage;
    QImage                  _darkBaseImage;
    
private:    
    friend class ElaMicaBaseInitObject;
    void    _initMicaBaseImage(QImage img);
    QRect   _calculateWindowVirtualGeometry(QWidget* widget);
    void    _updateMica(QWidget* widget, bool isProcessEvent = true);
    void    _updateAllMicaWidget();
};


#endif // HESAPPLICATIONPRIVATE_H