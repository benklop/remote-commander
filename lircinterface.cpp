#include "lircinterface.h"
#include <QStringList>

LircInterface::LircInterface(QString name, QString remote, QObject *parent) :
    DeviceInterface(name, parent)
{
    qDebug() << "creating LIRC interface" << name;

    this->remote = remote;

    //init lirc socket connection
    socket = new QLocalSocket(this);
    socket->connectToServer("/var/run/lirc/lircd");
    connect(socket,SIGNAL(readyRead()),this,SLOT(commandReceived()));


}

void LircInterface::commandReceived()
{
    //get the command(s) from the socket
    QString command = socket->readAll();

    //split the command(s) in case there are multiple lines
    QStringList commands = command.split('\n');
    foreach(QString command, commands)
    {

        //process each command, split into its components.
        QStringList components = command.split(' ');
        int repeatCount = components.at(1).toInt();
        QString buttonName = components.at(2);
        QString remoteName = components.at(3);

        if(remoteName == remote) //we've got a command from the right remote
        {

            //for the moment let's only worry about the first press, no a button that's been held down
            if(repeatCount == 0)
            {
                emit messageReceive(name, buttonName);
            }
        }
    }
}

void LircInterface::messageSend(QString message)
{
    QString sendString = "SEND_ONCE " + remote + message + '\n';
    socket->write(sendString.toLatin1());
}
