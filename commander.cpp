#include "commander.h"
#include "lircinterface.h"
#include "mythtvinterface.h"
#include "samsunginterface.h"

/*
 *commander object initiates the series of commands called for in the config file
 */

Commander::Commander(QObject *parent) :
    QObject(parent)
{
    readConfig();
}

void Commander::doCommand(QString commandName)
{

}

bool Commander::readConfig()
{
    settings = new QSettings("/etc/remote-commander.conf",QSettings::IniFormat,this);
    bool retVal = true;
    //first set up remotes
    settings->beginGroup("Devices");
    foreach(const QString device, settings->childKeys())
    {
        //device contains the device's name, which will be the group name containing that device's settings. The value is that device's type.
        //currently there are 'lirc', 'samsung', 'mythtv', and 'network'. 'network' listens on the port in the value.

        QString currentDevice = settings->value(device).toString();

        if(currentDevice == "lirc")
        {
            //init an LIRC device
            settings->endGroup();
            settings->beginGroup(device);
            devices.append(new LircInterface(settings->value("remote").toString(), this));
            settings->endGroup();
            settings->beginGroup("Devices");

        }
        else if(currentDevice == "samsung")
        {
            //get parameters for and init a samsung TV
            settings->endGroup();
            settings->beginGroup(device);
            devices.append(new SamsungInterface(settings->value("remote", "/dev/ttyAMA0").toString(), this));
            settings->endGroup();
            settings->beginGroup("Devices");
        }
        else if(currentDevice == "mythtv")
        {
            //get parameters for and init a mythTV frontend
            settings->endGroup();
            settings->beginGroup(device);
            devices.append(new MythTVInterface(settings->value("remote", "localhost").toString(), this));
            settings->endGroup();
            settings->beginGroup("Devices");
        }
        else if(currentDevice == "network")
        {
            //get parameters for and init a network listening socket
        }
        else
        {
            //specified invalid device type
            qWarning() << "Remote type \"" << device << "\" is not a valid remote type";
            retVal = false;
        }
    }
    return retVal;
}

bool Commander::writeConfig()
{
    return true;
}
