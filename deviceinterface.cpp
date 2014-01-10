#include "deviceinterface.h"
#include <QDebug>

DeviceInterface::DeviceInterface(QString name, QSettings *settings, QObject *parent) :
    QObject(parent)
{
    this->name = name;
    this->settings = settings;

    //load settings as defined in subclass
    getSettings();
}

void DeviceInterface::messageSend(QString message)
{
}

QString DeviceInterface::getName()
{
    return name;
}
