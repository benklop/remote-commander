#include "macrointerface.h"
#include <QDebug>

/*
 * MacroInterface provides a way to create a
 * virtual device which uses user defined commands to send commands to another device
 */

MacroInterface::MacroInterface(QString name, QSettings *settings, QObject *parent) :
    DeviceInterface(name, settings, parent)
{
    //load settings
    getSettings();
}

void MacroInterface::messageSend(QString message)
{
    if(actions.contains(message))
    {
        MacroAction *action = actions.value(message);
        if(action->getToggle())
        {

        }
        else
        {
            foreach(QString command, action->getActions())
            {
                QStringList splitCommand = command.split(":");
                emit messageReceive(splitCommand.at(0),splitCommand.at(1));
            }
        }
    }
    else
    {
        qDebug() << "no such macro!";
    }
}

void MacroInterface::getSettings()
{
    settings->beginGroup(name);
    QStringList allSettings = settings->allKeys();

    foreach(QString key, allSettings)
    {
        QString value = settings->value(key).toString();
        MacroAction *action;

        if(key.contains('/')) // the key contains a modifier
        {
            QStringList list = value.split('/');
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
            action->addAction(list.at(1));

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

    settings->endGroup();
}
