#ifndef HESLOG_H
#define HESLOG_H

#include <QObject>

#include "Singleton.h"
#include "stdafx.h"

class HesLogPrivate;

class HES_EXPORT HesLog : public QObject 
{
    Q_OBJECT
    Q_DECLARE_PIMPL(HesLog)
    Q_PROPERTY_DEFINE_MEMBER_H(QString, LogSavePath)
    Q_PROPERTY_DEFINE_MEMBER_H(QString, LogFileName)
    Q_PROPERTY_DEFINE_MEMBER_H(bool, IsLogFileNameWithTime)
    HES_SINGLETON_CREATE_H(HesLog);

private:
    explicit HesLog(QObject *parent = nullptr);
    ~HesLog();
public:
    void initMessageLog(bool isEnable);
Q_SIGNALS:
    void logMessage(QString log);
};

#endif // HESLOG_H