#include "mythtvinterface.h"

MythTVInterface::MythTVInterface(QString name, QSettings *settings, QObject *parent) :
    DeviceInterface(name, settings, parent)
{
    qDebug() << "creating MythTV interface" << name;

    //load settings
    getSettings();

    mythSocket = new QTcpSocket(this);
    mythSocket->connectToHost(host,6546);
    connect(mythSocket, SIGNAL(readyRead()), this, SLOT(getMessage()));

    wol.setIP(host);
    wol.setMAC(mac.toLatin1());
    wol.setPort(7);
}

void MythTVInterface::messageSend(QString message)
{
    if(message == "power_on") //power on handed by wake on lan
        wol.send();
    else if(message == "power_off")
    {
        mythSocket->write(QString("key " + offKey).toLatin1());
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

void MythTVInterface::getSettings()
{
    settings->beginGroup(name);
    host = settings->value("host", "localhost").toString();
    mac = settings->value("mac", "00:00:00:00:00:00").toString();
    offKey = settings->value("offKey").toString();
    settings->endGroup();
}
