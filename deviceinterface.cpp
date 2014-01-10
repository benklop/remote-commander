#include "deviceinterface.h"
#include <QDebug>

DeviceInterface::DeviceInterface(QString name, QSettings *settings, QObject *parent) :
    QObject(parent), name(name), settings(settings)
{

}

QString DeviceInterface::getName()
{
    return name;
}
