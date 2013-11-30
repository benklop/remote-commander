#include "deviceinterface.h"

DeviceInterface::DeviceInterface(QObject *parent) :
    QObject(parent)
{
}

QStringList * DeviceInterface::getPossibleMessages()
{
    return &possibleMessages;
}


void DeviceInterface::messageSend(QString message)
{
}
