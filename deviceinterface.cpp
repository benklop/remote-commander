#include "deviceinterface.h"
#include <QDebug>

DeviceInterface::DeviceInterface(QString name, QSettings *settings, QObject *parent) :
    QObject(parent), name(name), settings(settings)
{

}

void DeviceInterface::processMessage(QString message)
{
    if(actions.contains(message))
    {
        MacroAction *action = actions.value(message);
        if(action->getToggle())
        {
            QString command = action->getNext();
            QStringList splitCommand = command.split(":");
            emit SendMessage(splitCommand.at(0),splitCommand.at(1));
        }
        else
        {
            foreach(QString command, action->getActions())
            {
                QStringList splitCommand = command.split(":");
                emit SendMessage(splitCommand.at(0),splitCommand.at(1));
            }
        }
    }
    else
    {
        qDebug() << "no such action" << message << "confgured!";
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

                //add action to macro
                action->addAction(value);

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
