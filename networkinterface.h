#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H
#include "deviceinterface.h"
#include <QTcpServer>

class NetworkInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit NetworkInterface(QString name, QString address = "0.0.0.0:51328", QObject *parent = 0);
    
signals:
    
public slots:
    void messageReceived();
    void acceptConnection();
    void destroySocket();
public:
    QTcpServer *server;
    QList<QTcpSocket*> socketList;
};

#endif // NETWORKINTERFACE_H
