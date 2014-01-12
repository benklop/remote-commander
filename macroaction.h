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

private:
    bool toggle = false;
    QStringList actions;
    QString device;
    
};

#endif // MACROACTION_H
