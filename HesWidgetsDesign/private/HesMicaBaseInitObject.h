#ifndef HESMICABASEINITOBJECT_H
#define HESMICABASEINITOBJECT_H


#include <QObject>

class HesApplicationPrivate;

class HesMicaBaseInitObject : public QObject
{
    Q_OBJECT
public:
    explicit HesMicaBaseInitObject(HesApplicationPrivate* appPrivate, QObject* parent = nullptr);
    ~HesMicaBaseInitObject();
    Q_SLOT void onInitMicaBase(QImage img);
Q_SIGNALS:
    Q_SIGNAL void initFinished();
private:
    HesApplicationPrivate* _appPrivate{nullptr};
};




#endif // HESMICABASEINITOBJECT_H