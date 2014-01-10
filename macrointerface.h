#ifndef MACROINTERFACE_H
#define MACROINTERFACE_H
#include <QString>
#include "deviceinterface.h"

class MacroInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit MacroInterface(QString deviceName, QObject *parent = 0);


signals:

public slots:

};

#endif // MACROINTERFACE_H
