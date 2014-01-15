#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H

#include <QObject>
#include <QStringList>
#include <QSettings>
#include "macroaction.h"

class DeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInterface(QString name, QSettings *settings, QObject *parent = 0);
signals:
    void SendMessage(QString name, QString message);
    void success();
    void error();
public slots:
    virtual void receiveMessage(QString message) = 0;
    void getMessage(QString);
protected:
    QString name;
    QSettings *settings;
    QHash<QString, QString> loadedSettings;
    QHash<QString, MacroAction*> actions;

    void loadSettings(QStringList settingsNames = QStringList()); // names of settings which are not used as actions
    void loadSettings(QString settingsNames);
public:
    QString getName();
};

#endif // DEVICEINTERFACE_H
