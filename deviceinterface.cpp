#include "deviceinterface.h"
#include <QDebug>

DeviceInterface::DeviceInterface(QString name, QSettings *settings, QObject *parent) :
    QObject(parent), name(name), settings(settings)
{

}

void DeviceInterface::processMessage(QString message)
{
    message = message.trimmed();
    if(message.startsWith("setMode/"))
    {
        mode = message.remove(0,8);
    }
    else if(message.startsWith("wait/"))
    {
        //need to figure out how to do a delay without blocking the rest of the app
    }
    else if(actions.contains(message))
    {
        MacroAction *action = actions.value(message);
        if(action->getToggle())
        {
            QString command = action->getNext(mode);
            QStringList splitCommand = command.split(":");
            emit SendMessage(splitCommand.at(0),splitCommand.at(1));
        }
        else
        {
            foreach(QString command, action->getActions(mode))
            {
                QStringList splitCommand = command.split(":");
                emit SendMessage(splitCommand.at(0),splitCommand.at(1));
            }
        }
    }
    else
    {
        qDebug() << "no such action" << message << "configured!";
    }
}

void DeviceInterface::loadSettings(QString settingsNames)
{
    loadSettings(QStringList(settingsNames));
}

void DeviceInterface::loadSettings(QStringList settingsNames)
{
    //load settings
    settings->beginGroup(name);
    QStringList allSettings = settings->allKeys();

    foreach(QString key, allSettings)
    {
        if(settingsNames.contains(key)) //this is a setting, not a command
        {
            loadedSettings.insert(key, settings->value(key).toString());
        }
        else //this is a command
        {
            QString value = settings->value(key).toString();
            MacroAction *action;

            if(key.contains('/')) // the key contains a modifier
            {
                QStringList list = key.split('/');
                key = list.at(0);
                QString modeName;


                //either find or create an action for this key
                if(actions.contains(key))
                {
                    action = actions.value(key);
                }
                else
                {
                    action = new MacroAction(this);
                    actions.insert(key, action);
                }



                //set to toggle
                if(list.at(1).startsWith('t'))
                {
                    action->setToggle(true);
                }
                //add mode name
                else if(list.at(1).startsWith('m'))
                {
                    modeName = list.at(1);
                    modeName.remove(0,1);

                }

                if(list.length() == 3)
                {
                    if(list.at(2).startsWith('t'))
                    {
                        action->setToggle(true);
                    }
                    else if(list.at(2).startsWith('m'))
                    {
                        modeName = list.at(2);
                        modeName.remove(0,1);

                    }
                }

                //add action to macro
                action->addAction(value,modeName);

            }
            else // macro is a simple alias
            {
                if(actions.contains(key))
                {
                    action = actions.value(key);
                }
                else
                {
                    action = new MacroAction(this);
                    actions.insert(key, action);
                }
                action->addAction(value);
            }
        }
    }

    settings->endGroup();

}

QString DeviceInterface::getName()
{
    return name;
}
