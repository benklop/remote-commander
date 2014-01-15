#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H
#include "deviceinterface.h"
#include <QTcpServer>

class NetworkInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit NetworkInterface(QString name, QSettings *settings, QObject *parent = 0);
    
signals:
    
public slots:
    void dataReceived();
    void acceptConnection();
    void destroySocket();
    void receiveMessage(QString message);

public:
    QTcpServer *server;
    QList<QTcpSocket*> socketList;

private:

};

#endif // NETWORKINTERFACE_H
