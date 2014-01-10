#include "macrointerface.h"

/*
 * MacroInterface provides a way to create a
 * virtual device which uses user defined commands to send commands to another device
 */

MacroInterface::MacroInterface(QString deviceName, QObject *parent) :
    DeviceInterface(deviceName, parent)
{
}
