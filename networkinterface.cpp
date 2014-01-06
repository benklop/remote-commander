#include "networkinterface.h"
#include <QTcpSocket>

//network interface is special because it allows doing anything, not just wht is in the config file.

//listening address and port are specified as address:port, or default to 0.0.0.0:51328
NetworkInterface::NetworkInterface(QString name, QString address, QObject *parent) :
    DeviceInterface(name, parent)
{
    qDebug() << "creating Network interface List" << name;

    server = new QTcpServer(this);
    QStringList addr = address.split(":");
    if(addr.at(0) == "0.0.0.0")
        server->listen(QHostAddress::Any,addr.at(1).toInt());
    else
        server->listen(QHostAddress(addr.at(0)),addr.at(1).toInt());

    connect(server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));

}

void NetworkInterface::messageReceived()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(this->sender());
    QByteArray message = socket->readAll();
    emit messageSend(message);
    socket->write("OK\n"
                  "RC:\\ >");

}

void NetworkInterface::acceptConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    socketList.append(socket);
    connect(socket, SIGNAL(readyRead()), this, SLOT(messageReceived()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(destroySocket()));
    socket->write("Remote Commander Network Interface\n"
                  "----------------------------------\n"
                  "RC:\\ >");

}

void NetworkInterface::destroySocket()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(this->sender());
    socketList.removeAll(socket);
    socket->close();
    socket->deleteLater();
}
