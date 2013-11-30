#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>
#include <QSettings>
#include <QList>
#include "deviceinterface.h"

class Commander : public QObject
{
    Q_OBJECT
public:
    explicit Commander(QObject *parent = 0);
    
signals:
    
public slots:
    void doCommand(QString commandName);

private:
    bool readConfig();
    bool writeConfig();
    QSettings *settings;
    QList<DeviceInterface*> devices;

};

#endif // COMMANDER_H
