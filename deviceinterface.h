#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H

#include <QObject>
#include <QStringList>

class DeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInterface(QString name, QObject *parent = 0);
signals:
    void messageReceive(QString message);
public slots:
    virtual void messageSend(QString message);
protected:
    QString name;
public:
    QString getName();
};

#endif // DEVICEINTERFACE_H
