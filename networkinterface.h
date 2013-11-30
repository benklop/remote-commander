#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H
#include "deviceinterface.h"

class NetworkInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit NetworkInterface(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // NETWORKINTERFACE_H
