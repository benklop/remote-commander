#include "deviceinterface.h"

DeviceInterface::DeviceInterface(Commander *commander, QObject *parent) :
    QObject(parent)
{
    this->commander = commander;
}

QStringList * DeviceInterface::getPossibleMessages()
{
    return &possibleMessages;
}


void DeviceInterface::messageSend(QString message)
{
}
