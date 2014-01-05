#include "mythtvinterface.h"
#include <QSettings>
#include <QDebug>

MythTVInterface::MythTVInterface(QString name, QString mythTvHost, QString mythTvMac, QObject *parent) :
    DeviceInterface(name, parent)
{
    qDebug() << "creating MythTV interface";

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
    else if(message == "power_off")
    {
        QSettings settings("/etc/remote-commander.conf",QSettings::IniFormat,this);
        settings.beginGroup(name);
        mythSocket->write(QString("key " + settings.value("offKey").toString()).toLatin1());
    }
    else
    {
        mythSocket->write(message.toLatin1());
    }
}

//retrieve a message from the socket
void MythTVInterface::getMessage()
{
    QString message = mythSocket->readAll();
    if(message != "OK")
        emit messageReceive(name, message);
}
