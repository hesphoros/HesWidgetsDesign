#ifndef HESEVENTBUS_H
#define HESEVENTBUS_H

#include <QObject>
#include <QVariantMap>

#include "common/common_defs.h"
#include "Singleton.h"
#include "stdafx.h"
class HesEventPrivate;
class HES_EXPORT HesEvent : public QObject
{
    Q_OBJECT
    Q_DECLARE_PIMPL(HesEvent)
    Q_PROPERTY_DEFINE_MEMBER_H(QString, EventName);
    Q_PROPERTY_DEFINE_MEMBER_H(QString, FunctionName);
    Q_PROPERTY_DEFINE_MEMBER_H(Qt::ConnectionType, ConnectionType);

public:
    explicit HesEvent(QObject* parent = nullptr);
    explicit HesEvent(QString eventName, QString functionName, QObject* parent = nullptr);
    ~HesEvent();
    HesEventBusType::EventBusReturnType registerAndInit();
};

class HesEventBusPrivate;
class HES_EXPORT HesEventBus : public QObject
{
    Q_OBJECT
    Q_DECLARE_PIMPL(HesEventBus)
    HES_SINGLETON_CREATE_H(HesEventBus);

private:
    explicit HesEventBus(QObject* parent = nullptr);
    ~HesEventBus();

public:
    HesEventBusType::EventBusReturnType post(const QString& eventName, const QVariantMap& data = {});
    QStringList getRegisteredEventsName() const;

private:
    friend class HesEvent;
};

#endif // HESEVENTBUS_H
