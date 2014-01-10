#ifndef LIRCINTERFACE_H
#define LIRCINTERFACE_H

#include <QObject>
#include <QLocalSocket>
#include "deviceinterface.h"

class LircInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit LircInterface(QString name, QSettings *settings, QObject *parent = 0);
    
signals:


public slots:
    void commandReceived();
    void messageSend(QString message);

private:
    QLocalSocket *socket;
    QString remote;
    QString buf;

    void getSettings();
};

#endif // LIRCINTERFACE_H
