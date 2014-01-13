#include <QDebug>
#include "macroaction.h"

MacroAction::MacroAction(QObject *parent) :
    QObject(parent)
{

}

void MacroAction::addAction(QString action)
{
    actions.append(action);
}
