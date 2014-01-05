#include <QDebug>
#include "macroaction.h"

MacroAction::MacroAction(QObject *parent) :
    QObject(parent)
{
    qDebug() << "creating Macro";
}
