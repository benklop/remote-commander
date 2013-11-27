#include "commander.h"


/*
 *commander object initiates the series of commands called for in the config file
 */

Commander::Commander(QObject *parent) :
    QObject(parent)
{
}

void Commander::doCommand(QString commandName)
{
}
