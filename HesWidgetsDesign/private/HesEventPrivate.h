#ifndef HESEVENTBUSPRIVATE_H
#define HESEVENTBUSPRIVATE_H

#include <QMap>
#include <QObject>

#include "common/common_defs.h"
#include "stdafx.h"
class HesEvent;
class HesEventPrivate : public QObject
{
    Q_OBJECT
    Q_D_DECLARE_POINTER(HesEvent)
    Q_PROPERTY_CREATE_PRIVATE(QString, EventName);
    Q_PROPERTY_CREATE_PRIVATE(QString, FunctionName);
    Q_PROPERTY_CREATE_PRIVATE(Qt::ConnectionType, ConnectionType);

public:
    explicit HesEventPrivate(QObject* parent = nullptr);
    ~HesEventPrivate();
};

class HesEventBus;
class HesEventBusPrivate : public QObject
{
    Q_OBJECT
    Q_D_DECLARE_POINTER(HesEventBus)
public:
    explicit HesEventBusPrivate(QObject* parent = nullptr);
    ~HesEventBusPrivate();
    HesEventBusType::EventBusReturnType registerEvent(HesEvent* event);
    void unRegisterEvent(HesEvent* event);

private:
    QMap<QString, QList<HesEvent*>> _eventMap;
};

#endif // HESEVENTBUSPRIVATE_H
