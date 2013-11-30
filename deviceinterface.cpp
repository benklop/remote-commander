#include "deviceinterface.h"

DeviceInterface::DeviceInterface(QString name, QObject *parent) :
    QObject(parent)
{
    this->name = name;
}

void DeviceInterface::messageSend(QString message)
{
}

QString DeviceInterface::getName()
{
    return name;
}
