#include "lircinterface.h"
#include <QStringList>

//i'm assuming that when i open multiple connections to a socket,
//i can read the same data from the socket on each connection. this might not be true.

LircInterface::LircInterface(QString name, QSettings *settings, QObject *parent) :
    DeviceInterface(name, settings, parent)
{
    qDebug() << "creating LIRC interface" << name;

    //load settings
    loadSettings("remote");

    //init lirc socket connection
    socket = new QLocalSocket(this);
    socket->connectToServer("/var/run/lirc/lircd");//i think this is the only location this ever happens at. could be wrong.
    connect(socket,SIGNAL(readyRead()),this,SLOT(commandReceived()));


}

void LircInterface::commandReceived()
{
    QString command;
    if(buf.isEmpty())
    {
        //get the command(s) from the socket
        command = socket->readAll();
    }
    else
    {
        command = buf;
        command.append(socket->readAll());
        buf = QString();
    }

    if(command.contains(loadedSettings.value("remote"))) //try to constrain debug output to the right interface...
        qDebug() << "got command" << command << "from LIRC";

    if(command.startsWith("BEGIN")&&command.endsWith("END\n"))//grab reply packets for this interface
    {
        QStringList commandParts = command.split('\n');
        QString origCommand = commandParts.at(1);
        QString errState = commandParts.at(2);
        if(origCommand.startsWith("SEND") && origCommand.split(" ").at(1) == loadedSettings.value("remote")) //got a success / fail for  command we sent
        {
            if(errState == "SUCCESS")
                emit success();
            else
                emit error();
        }
        else if(origCommand.startsWith("LIST") && origCommand.endsWith(loadedSettings.value("remote"))) //got a list we requested
        {
            qDebug() << "list of commands for" << name;
            //for now just qdebug the list
            for(int i = 3; i > commandParts.count() - 1; i++)
            {
                qDebug() << commandParts.at(i);
            }
        }
    }
    else if(command.endsWith(loadedSettings.value("remote")))
    {
        //process command, split into its components.
        QStringList components = command.split(' ');
        //QString code = components.at(0);
        int repeatCount = components.at(1).toInt();
        QString buttonName = components.at(2);
        QString remoteName = components.at(3);

        if(remoteName == loadedSettings.value("remote")) //we've got a command from this remote
        {

            //for the moment let's only worry about the first press, not a button that's been held down
            if(repeatCount == 0)
            {
                processMessage(buttonName);
            }
        }
    }
    else
    {
        buf.append(command);
    }
}

void LircInterface::receiveMessage(QString message)
{
    if(message == "LIST")
    {
        socket->write(QString("LIST " + loadedSettings.value("remote")).toLatin1() + '\n');
    }
    else
    {
        QString sendString = "SEND_ONCE " + loadedSettings.value("remote") + " " + message + '\n';
        socket->write(sendString.toLatin1());
    }
}
