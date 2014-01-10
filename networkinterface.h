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
    void messageReceived();
    void acceptConnection();
    void destroySocket();
public:
    QTcpServer *server;
    QList<QTcpSocket*> socketList;

private:
    QString address;

    void messageSend(QString message);
    void getSettings();
};

#endif // NETWORKINTERFACE_H
