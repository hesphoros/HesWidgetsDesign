#include "HesLog.h"

#include <QDir>
#include "HesLogPrivate.h"


HES_SINGLETON_CREATE_CPP(HesLog)
Q_PROPERTY_DEFINE_MEMBER_CPP(HesLog, QString, LogSavePath)
Q_PROPERTY_DEFINE_MEMBER_CPP(HesLog, QString, LogFileName)
Q_PROPERTY_DEFINE_MEMBER_CPP(HesLog, bool, IsLogFileNameWithTime)


HesLog::HesLog(QObject *parent)
    : QObject(parent), d_ptr(new HesLogPrivate(this))
{
    Q_D(HesLog);
    d->q_ptr = this;
    d->_pLogFileName = "HesLog";
    d->_pLogSavePath = QDir::currentPath();
    d->_pIsLogFileNameWithTime = false;
    d->_clearLogFile();
    connect(this, &HesLog::pLogSavePathChanged, d, &HesLogPrivate::_clearLogFile);
    connect(this, &HesLog::pLogFileNameChanged, d, &HesLogPrivate::_clearLogFile);
    connect(this, &HesLog::pIsLogFileNameWithTimeChanged, d, &HesLogPrivate::_clearLogFile);
}

HesLog::~HesLog()
{

}

void HesLog::initMessageLog(bool isEnable) {
    Q_D(HesLog);
    qInstallMessageHandler(isEnable ? d->_messageLogHander : 0);
}