#ifndef LIRCINTERFACE_H
#define LIRCINTERFACE_H

#include <QObject>
#include <QLocalSocket>
#include "deviceinterface.h"

class LircInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit LircInterface(QString name, QSettings *settings, QObject *parent = 0);
    
signals:


public slots:
    void commandReceived();
    void receiveMessage(QString message);

private:
    QLocalSocket *socket;
    QString buf;
};

#endif // LIRCINTERFACE_H
