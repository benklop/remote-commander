#include "networkinterface.h"

//listening address and port are specified as address:port, or default to 0.0.0.0:51328
NetworkInterface::NetworkInterface(QString name, QString address, QObject *parent) :
    DeviceInterface(name, parent)
{
    qDebug() << "creating Network interface" << name;

    server = new QTcpServer(this);
    QStringList addr = address.split(":");
    if(addr.at(0) == "0.0.0.0")
        server->listen(QHostAddress::Any,addr.at(1).toInt());
    else
        server->listen(QHostAddress(addr.at(0)),addr.at(1).toInt());

}
