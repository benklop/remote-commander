#ifndef MACROACTION_H
#define MACROACTION_H

#include <QObject>

class MacroAction : public QObject
{
    Q_OBJECT
public:
    explicit MacroAction(QObject *parent = 0);
    
signals:
    
public slots:

private:
    bool toggle = false;
    QList<MacroAction*> actions;
    QString action;
    QString name;
    QString device;
    
};

#endif // MACROACTION_H
