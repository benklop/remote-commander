#include "mythtvinterface.h"

MythTVInterface::MythTVInterface(QString name, QString mythTvHost, QString mythTvMac, QObject *parent) :
    DeviceInterface(name, parent)
{
    mythSocket = new QTcpSocket(this);
    mythSocket->connectToHost(mythTvHost,6546);
    connect(mythSocket, SIGNAL(readyRead()), this, SLOT(getMessage()));

    wol.setIP(mythTvHost);
    wol.setMAC(mythTvMac.toLatin1());
    wol.setPort(7);
}

void MythTVInterface::messageSend(QString message)
{
    if(message == "power_on") //power on handed by wake on lan
        wol.send();
    else
    {
        mythSocket->write(message.toLatin1());
    }
}

//retrieve a message from the socket
void MythTVInterface::getMessage()
{
    QString message = mythSocket->readAll();
    emit messageReceive(name,message);
}
