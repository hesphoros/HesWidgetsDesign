#include "HesApplication.h"

// #include "HesTheme.h"
// #include "HesWinShadowHelper.h"
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
    d->_themeMode = eTheme->getThemeMode();
    connect(eTheme, &HesTheme::themeModeChanged, d, &HesApplicationPrivate::onThemeModeChanged);
}

ElaApplication::~ElaApplication()
{
}
