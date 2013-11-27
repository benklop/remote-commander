#ifndef IRDEVICE_H
#define IRDEVICE_H

#include <QObject>
#include "deviceinterface.h"
#include "lircinterface.h"

class IrDevice : public DeviceInterface
{
    Q_OBJECT
public:
    explicit IrDevice(QString remoteName, Commander *commander, QObject *parent = 0);
    QString getRemoteName();

signals:
    void messageReceive(QString message);
public slots:
    void messageSend(QString message);
private:
    QString remoteName;
    LircInterface *interface;

};

#endif // IRDEVICE_H
