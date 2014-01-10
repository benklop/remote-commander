#include "macrointerface.h"

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

}

void MacroInterface::getSettings()
{
    settings->beginGroup(name);
    settings->endGroup();
}
