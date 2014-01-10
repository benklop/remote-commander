#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H

#include <QObject>
#include <QStringList>
#include <QSettings>

class DeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInterface(QString name, QSettings *settings, QObject *parent = 0);
signals:
    void messageReceive(QString name, QString message);
    void success();
    void error();
public slots:
    virtual void messageSend(QString message);
protected:
    QString name;
    QSettings *settings;

    virtual void getSettings();
public:
    QString getName();
};

#endif // DEVICEINTERFACE_H
