#include "mythtvinterface.h"

MythTVInterface::MythTVInterface(QString name, QSettings *settings, QObject *parent) :
    DeviceInterface(name, settings, parent)
{
    qDebug() << "creating MythTV interface" << name;

    //load settings
    QStringList settingNames;
    settingNames << "host" << "mac" << "offKey";
    loadSettings(settingNames);

    mythSocket = new QTcpSocket(this);
    mythSocket->connectToHost(loadedSettings.value("host"),6546);
    connect(mythSocket, SIGNAL(readyRead()), this, SLOT(getMessage()));

    wol.setIP(loadedSettings.value("host"));
    wol.setMAC(loadedSettings.value("mac").toLatin1());
    wol.setPort(7);
}

void MythTVInterface::receiveMessage(QString message)
{
    if(message == "power_on") //power on handed by wake on lan
        wol.send();
    else if(message == "power_off")
    {
        mythSocket->write(QString("key " + loadedSettings.value("offKey")).toLatin1());
    }
    else
    {
        mythSocket->write(message.toLatin1());
    }
}

//retrieve a message from the socket
void MythTVInterface::getMessage()
{
    QString message = mythSocket->readAll();
    if(message != "OK")
        processMessage(message);
}
