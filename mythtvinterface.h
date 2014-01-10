#ifndef MYTHTVINTERFACE_H
#define MYTHTVINTERFACE_H

#include "deviceinterface.h"
#include "magicPacket.h"
#include <QTcpSocket>
#include <QSettings>

class MythTVInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit MythTVInterface(QString name, QString mythTvHost = "localhost", QString mythTvMac = "00:00:00:00:00:00", QSettings *settings, QObject *parent = 0);

signals:

public slots:
    void messageSend(QString message);
    void getMessage();

private:
    QTcpSocket *mythSocket;
    magicPacket wol;
    QSettings *settings;

};

#endif // MYTHTVINTERFACE_H
