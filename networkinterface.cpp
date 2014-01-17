#include "networkinterface.h"
#include "commander.h"
#include <QTcpSocket>

//network interface is special because it allows doing anything, not just wht is in the config file.

//listening address and port are specified as address:port
NetworkInterface::NetworkInterface(QString name, QSettings *settings, QObject *parent) :
    DeviceInterface(name, settings, parent)
{
    qDebug() << "creating Network interface List" << name;

    //load settings
    loadSettings("address");

    server = new QTcpServer(this);
    QStringList addr = loadedSettings.value("address").split(":");
    if(addr.at(0) == "0.0.0.0")
        server->listen(QHostAddress::Any,addr.at(1).toInt());
    else
        server->listen(QHostAddress(addr.at(0)),addr.at(1).toInt());

    connect(server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));

}

void NetworkInterface::dataReceived()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(this->sender());
    QByteArray message = socket->readAll();
    if((message.startsWith("do-command") || message.startsWith("dc")) && message.split(' ').length() > 1)
    {
        QByteArray command = message.split(' ').at(1).trimmed();
        socket->write("performing command " + command);
        Commander* commander = qobject_cast<Commander*>(this->parent());
        commander->doCommand(command);
    }
    else
    {
        processMessage(message);
    }
    prompt(socket);

}

void NetworkInterface::acceptConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    socketList.append(socket);
    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(destroySocket()));
    socket->write("Remote Commander Network Interface\n"
                  "----------------------------------\n");
    prompt(socket);
}

void NetworkInterface::destroySocket()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(this->sender());
    socketList.removeAll(socket);
    socket->close();
    socket->deleteLater();
}

void NetworkInterface::receiveMessage(QString message)
{
    foreach(QTcpSocket *socket, socketList)
    {

        socket->write("\n" + message.toLatin1());
        prompt(socket);

    }
}

void NetworkInterface::prompt(QTcpSocket *socket)
{
    socket->write("\n" + name.toLatin1() + ":" + QByteArray::number(socketList.indexOf(socket) + 1) + "#");
}
