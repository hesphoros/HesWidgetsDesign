#include "HesTextPrivate.h"
#include "HesText.h"
#include <QTimer>

HesTextPrivate::HesTextPrivate(QObject *parent)
    : QObject(parent)
{
}

HesTextPrivate::~HesTextPrivate() {

}

void HesTextPrivate::onThemeChanged(HesThemeType::ThemeMode themeMode)
{
    Q_Q(HesText);
    _themeMode = themeMode;
    if ( q->isVisible() ) {
        _changeTheme();    
    }
    else {
        QTimer::singleShot(1,this,[=]
        {
            _changeTheme();
        });
    }
}

void HesTextPrivate::HesTextPrivate::_changeTheme()
{
    Q_Q(HesText);
    QPalette palette = q->palette();
    palette.setColor(QPalette::WindowText, _themeMode == HesThemeType::Light ? Qt::black : Qt::white);
    q->setPalette(palette);
}