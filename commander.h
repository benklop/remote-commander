#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>
#include <QSettings>
#include <QList>
#include <QDebug>
#include "deviceinterface.h"
#include "macroaction.h"

class Commander : public QObject
{
    Q_OBJECT
public:
    explicit Commander(QObject *parent = 0);
    
signals:
    
public slots:
    void doCommand(QString deviceName, QString commandName);
    void doCommand(QString directive)
    {
        if(!directive.contains(":"))
        {
            qCritical() << "directive \"" + directive + "\" does not contain \':\' to separate device from command" ;
            return;
        }
        QStringList cmd = directive.split(":");
        doCommand(cmd.at(0),cmd.at(1));
    }

private:
    bool readConfig();
    bool writeConfig();
    QSettings *settings;
    QList<DeviceInterface*> devices;
    QHash<QString, QStringList> actions; //list of lists of actions to take
    QList<QString> modes;
    QString currentMode;

};

#endif // COMMANDER_H
