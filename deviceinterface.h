#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H

#include <QObject>
#include <QStringList>
#include "commander.h"

class DeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInterface(Commander *commander, QObject *parent = 0);
    QStringList * getPossibleMessages();
signals:
    void messageReceive(QString message);
public slots:
    virtual void messageSend(QString message);
protected:
    QStringList possibleMessages;
    Commander *commander;
};

#endif // DEVICEINTERFACE_H
