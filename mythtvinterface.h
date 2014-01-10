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
    explicit MythTVInterface(QString name, QSettings *settings, QObject *parent = 0);

signals:

public slots:
    void messageSend(QString message);
    void getMessage();

private:
    QTcpSocket *mythSocket;
    magicPacket wol;
    QSettings *settings;
    QString host;
    QString mac;

    //key values
    QString offKey;

   void  getSettings();

};

#endif // MYTHTVINTERFACE_H
