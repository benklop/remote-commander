#ifndef MACROACTION_H
#define MACROACTION_H

#include <QObject>
#include <QStringList>

class MacroAction : public QObject
{
    Q_OBJECT
public:
    explicit MacroAction(QObject *parent = 0);
    
signals:
    
public slots:
    void addAction(QString action);
    void setToggle(bool toggle)
    {
        this->toggle = toggle;
    }
    bool getToggle()
    {
        return this->toggle;
    }
    QStringList getActions()
    {
        return actions;
    }
    QString getNext()
    {
        if(current < actions.length())
        {

            return actions.at(current++);
        }
        else
        {
            current = 0;
            return actions.at(current);
        }
    }

private:
    bool toggle = false;\
    int current = 0;
    QStringList actions;
    QString device;
    
};

#endif // MACROACTION_H
