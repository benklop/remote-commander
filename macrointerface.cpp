#include "macrointerface.h"
#include <QDebug>

/*
 * MacroInterface provides a way to create a
 * virtual device which uses user defined commands to send commands to another device
 */

MacroInterface::MacroInterface(QString name, QSettings *settings, QObject *parent) :
    DeviceInterface(name, settings, parent)
{
    qDebug() << "creating Macro interface" << name;

    //load settings
    loadSettings();
}

void MacroInterface::receiveMessage(QString message)
{
    processMessage(message);
}
