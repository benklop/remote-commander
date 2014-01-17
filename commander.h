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
    explicit Commander(QString configFile = "/etc/remote-commander.conf", QObject *parent = 0);
    
signals:
    
public slots:
    void doCommand(QString command);
    void parseMessage(QString name, QString message);
private:
    bool readConfig(QString configFile);
    bool writeConfig();
    QSettings *settings;
    QHash<QString, DeviceInterface*> devices;
    QHash<QString, QStringList> actions; //list of lists of actions to take
    QList<QString> modes;
    QString currentMode;

};

#endif // COMMANDER_H
