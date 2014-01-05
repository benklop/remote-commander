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



bool Commander::readConfig(QString configFile)
{
    QFile config(configFile);
    if(!config.exists())
    {
        qWarning() << "Config file '" + configFile + "' does not exist.";
        return false;
    }
    qDebug() << "reading config file";
    settings = new QSettings(configFile, QSettings::IniFormat, this);
    bool retVal = true;
    //first set up remotes
    settings->beginGroup("Devices");
    foreach(const QString deviceName, settings->childKeys())
    {
        //deviceName contains the device's name, which will be the group name containing that device's settings. The value is that device's type.
        //currently there are 'lirc', 'samsung', 'mythtv', and 'network'.

        QString currentDevice = settings->value(deviceName).toString();

        if(currentDevice == "lirc")
        {
            //init an LIRC device
            settings->endGroup();
            settings->beginGroup(deviceName);
            devices.insert(deviceName, new LircInterface(deviceName, settings->value("remote").toString(), this));

            settings->endGroup();
            settings->beginGroup("Devices");

        }
        else if(currentDevice == "samsung")
        {
            //get parameters for and init a samsung TV
            settings->endGroup();
            settings->beginGroup(deviceName);
            devices.insert(deviceName, new SamsungInterface(deviceName, settings->value("port", "/dev/ttyAMA0").toString(), this));
            settings->endGroup();
            settings->beginGroup("Devices");
        }
        else if(currentDevice == "mythtv")
        {
            //get parameters for and init a mythTV frontend
            settings->endGroup();
            settings->beginGroup(deviceName);
            devices.insert(deviceName, new MythTVInterface(deviceName, settings->value("host", "localhost").toString(), settings->value("mac", "00:00:00:00:00:00").toString(), this));
            settings->endGroup();
            settings->beginGroup("Devices");
        }
        else if(currentDevice == "network")
        {
            //get parameters for and init a network listening socket
            settings->endGroup();
            settings->beginGroup(deviceName);
            devices.insert(deviceName, new NetworkInterface(deviceName, settings->value("address", "0.0.0.0:51328").toString(), this));
            settings->endGroup();
            settings->beginGroup("Devices");
        }
        else
        {
            //specified invalid device type
            qWarning() << "Remote type \"" << currentDevice << "\" is not a valid remote type";
            retVal = false;
        }
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
