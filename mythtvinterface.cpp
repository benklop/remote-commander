#include "mythtvinterface.h"

MythTVInterface::MythTVInterface(QString name, QString mythTvHost, QObject *parent) :
    DeviceInterface(name, parent)
{
    mythSocket = new QTcpSocket(this);
    mythSocket->connectToHost(mythTvHost,6546);
}

void MythTVInterface::messageSend(QString message)
{
}

void MythTVInterface::getMessage()
{
}
