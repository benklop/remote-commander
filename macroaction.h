#ifndef MACROACTION_H
#define MACROACTION_H

#include <QObject>
#include <QStringList>
#include <QPair>

class MacroAction : public QObject
{
    Q_OBJECT
public:
    explicit MacroAction(QObject *parent = 0);
    
signals:
    
public slots:
    void addAction(QString action, QString mode = QString());
    void setToggle(bool toggle)
    {
        this->toggle = toggle;
    }
    bool getToggle()
    {
        return this->toggle;
    }
    QStringList getActions(QString mode = QString());
    QString getNext(QString mode = QString());

private:
    bool toggle = false;
    int current = 0;
    QList<QPair<QString, QString>> actions;
    QString device;
    
};

#endif // MACROACTION_H
