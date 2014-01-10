#include "commander.h"
#include "lircinterface.h"
#include "mythtvinterface.h"
#include "samsunginterface.h"
#include "networkinterface.h"
#include <QFile>

/*
 *commander object initiates the series of commands called for in the config file
 */

Commander::Commander(QString configFile, QObject *parent) :
    QObject(parent)
{
    readConfig(configFile);
}

void Commander::doCommand(QString deviceName, QString commandName)
{
    DeviceInterface *device = devices.value(deviceName);
    device->messageSend(commandName);
}

void Commander::parseMessage(QString name, QString message)
{
    qDebug() << "received message" << message << "from interface" << name;
}

bool Commander::readConfig(QString configFile)
{
    QFile config(configFile);
    if(!config.exists())
    {
        qWarning() << "Config file '" + configFile + "' does not exist.";
        return false;
    }
    qDebug() << "reading config file" << configFile;
    settings = new QSettings(configFile, QSettings::IniFormat, this);
    bool retVal = true;
    //first set up remotes
    settings->beginGroup("Devices");
    foreach(const QString deviceName, settings->childKeys())
    {
        //deviceName contains the device's name, which will be the group name containing that device's settings. The value is that device's type.
        //currently there are 'lirc', 'samsung', 'mythtv', and 'network'.

        QString currentDevice = settings->value(deviceName).toString();
        DeviceInterface* interface = 0;

        settings->endGroup();
        settings->beginGroup(deviceName);
        if(currentDevice == "lirc")
        {
            //init an LIRC device
            interface = new LircInterface(deviceName, settings->value("remote").toString(), this);
        }
        else if(currentDevice == "samsung")
        {
            //get parameters for and init a samsung TV
            interface = new SamsungInterface(deviceName, settings->value("port", "/dev/ttyAMA0").toString(), this);
        }
        else if(currentDevice == "mythtv")
        {
            //get parameters for and init a mythTV frontend
            interface = new MythTVInterface(deviceName, settings->value("host", "localhost").toString(), settings->value("mac", "00:00:00:00:00:00").toString(), settings, this);
        }
        else if(currentDevice == "network")
        {
            //get parameters for and init a network listening socket
            interface = new NetworkInterface(deviceName, settings->value("address", "0.0.0.0:51328").toString(), this);
        }
        else
        {
            //specified invalid device type
            qWarning() << "Remote type \"" << currentDevice << "\" is not a valid remote type";
            retVal = false;
        }

        if(interface != 0)
        {
            connect(interface, SIGNAL(messageReceive(QString,QString)), this, SLOT(parseMessage(QString,QString)));
            devices.insert(deviceName, interface);
        }
        settings->endGroup();
        settings->beginGroup("Devices");
    }
    settings->endGroup();

    //load up macros
    settings->beginGroup("Macros");
    foreach(QString key, settings->childKeys())
    {
        QStringList value = settings->value(key).toString().split(',');
        actions.insert(key,value);
    }
    settings->endGroup();

    //load up device sections
    foreach(DeviceInterface* device, devices)
    {
        QString deviceName = device->getName();
        settings->beginGroup(deviceName);
        foreach(QString key, settings->childKeys())
        {
            QStringList value = settings->value(key).toString().split(',');
            actions.insert(key,value);
        }
        settings->endGroup();
    }

    return retVal;
}

bool Commander::writeConfig()
{
    return true;
}
