#ifndef MYTHTVINTERFACE_H
#define MYTHTVINTERFACE_H

#include "deviceinterface.h"
#include <QTcpSocket>

class MythTVInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit MythTVInterface(QString mythTvHost = "localhost", QObject *parent = 0);

signals:

public slots:
    void messageSend(QString message);
    void getMessage();

private:
    QTcpSocket *mythSocket;

};

#endif // MYTHTVINTERFACE_H
