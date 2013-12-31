#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>
#include <QSettings>
#include <QList>
#include "deviceinterface.h"
#include "macroaction.h"

class Commander : public QObject
{
    Q_OBJECT
public:
    explicit Commander(QObject *parent = 0);
    
signals:
    
public slots:
    void doCommand(QString DeviceName, QString commandName);

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
