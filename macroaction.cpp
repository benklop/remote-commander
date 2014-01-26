#include <QDebug>
#include "macroaction.h"

MacroAction::MacroAction(QObject *parent) :
    QObject(parent)
{

}

void MacroAction::addAction(QString action, QString mode)
{

    actions.append(qMakePair(action,mode));
}

QStringList MacroAction::getActions(QString mode)
{
    QStringList simpleActionList;
    QPair<QString, QString> pair;
    foreach(pair, actions)
    {
        if(pair.second == mode || pair.second == QString())
            simpleActionList.append(pair.first); //fill up a list of actions defined with the mode, including actions with no mode defined.
    }
    return simpleActionList;
}

QString MacroAction::getNext(QString mode)
{
    QStringList returnedActionList = getActions(mode);

    if(current < returnedActionList.length())
    {
        return returnedActionList.at(current++);
    }
    else
    {
        current = 0;
        return returnedActionList.at(current);
    }
}
