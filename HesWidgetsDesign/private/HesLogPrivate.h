#ifndef HESLOGPRIVATE_H
#define HESLOGPRIVATE_H

#include <QObject>
#include "stdafx.h"


class HesLog;

class HesLogPrivate : public QObject {
    Q_OBJECT

    Q_PROPERTY_CREATE_PRIVATE(QString, LogSavePath)
    Q_PROPERTY_CREATE_PRIVATE(QString, LogFileName)
    Q_PROPERTY_CREATE_PRIVATE(bool, IsLogFileNameWithTime)
    Q_D_DECLARE_POINTER(HesLog)
public:
    explicit HesLogPrivate(QObject *parent = nullptr);
    ~HesLogPrivate();
private:
    static void _messageLogHander(QtMsgType type, const QMessageLogContext& ctx, const QString& msg);
    void _clearLogFile();
};

#endif // HESLOGPRIVATE_H