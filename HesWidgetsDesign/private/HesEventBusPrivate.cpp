#include "HesEventBusPrivate.h"
#include "HesEventBus.h"
HesEventPrivate::HesEventPrivate(QObject* parent)
    : QObject{parent}
{
}

HesEventPrivate::~HesEventPrivate()
{
}

HesEventBusPrivate::HesEventBusPrivate(QObject* parent)
    : QObject{parent}
{
}

HesEventBusPrivate::~HesEventBusPrivate()
{
}


HesEventBusType::EventBusReturnType HesEventBusPrivate::registerEvent(HesEvent* event)
{
    if (!event)
    {
        return HesEventBusType::EventBusReturnType::EventInvalid;
    }
    if (event->getEventName().isEmpty())
    {
        return HesEventBusType::EventBusReturnType::EventNameInvalid;
    }
    if (_eventMap.contains(event->getEventName()))
    {
        QList<HesEvent*> eventList = _eventMap.value(event->getEventName());
        if (eventList.contains(event))
        {
            return HesEventBusType::EventBusReturnType::EventInvalid;
        }
        eventList.append(event);
        _eventMap[event->getEventName()] = eventList;
    }
    else
    {
        QList<HesEvent*> eventList;
        eventList.append(event);
        _eventMap.insert(event->getEventName(), eventList);
    }
    return HesEventBusType::EventBusReturnType::Success;
}

void HesEventBusPrivate::unRegisterEvent(HesEvent* event)
{
    if (!event)
    {
        return;
    }
    if (event->getEventName().isEmpty())
    {
        return;
    }
    if (_eventMap.contains(event->getEventName()))
    {
        if (_eventMap[event->getEventName()].count() == 1)
        {
            _eventMap.remove(event->getEventName());
        }
        else
        {
            QList<HesEvent*> eventList = _eventMap.value(event->getEventName());
            eventList.removeOne(event);
            _eventMap[event->getEventName()] = eventList;
        }
    }
}
