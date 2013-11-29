#include "mythtvinterface.h"

MythtvInterface::MythtvInterface(Commander *commander, QString mythTvHost, QObject *parent) :
    DeviceInterface(commander, parent)
{
    mythSocket = new QTcpSocket(this);
    mythSocket->connectToHost(mythTvHost,6546);
}

void MythtvInterface::messageSend(QString message)
{
}

void MythtvInterface::getMessage()
{
}
