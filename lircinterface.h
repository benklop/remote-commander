#ifndef LIRCINTERFACE_H
#define LIRCINTERFACE_H

#include <QObject>
#include <QLocalSocket>
#include "deviceinterface.h"

class LircInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit LircInterface(QString remote, QObject *parent = 0);
    
signals:


public slots:
    void commandReceived();
    void messageSend(QString message);

private:
    QLocalSocket *socket;
    QString remote;
};

#endif // LIRCINTERFACE_H
