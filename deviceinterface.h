#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H

#include <QObject>
#include <QStringList>

class DeviceInterface : public QObject
{
    Q_OBJECT
public:
    explicit DeviceInterface(QObject *parent = 0);
signals:
    void messageReceive(QString message);
public slots:
    virtual void messageSend(QString message);
protected:

public:

};

#endif // DEVICEINTERFACE_H
