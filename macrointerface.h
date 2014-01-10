#ifndef MACROINTERFACE_H
#define MACROINTERFACE_H
#include <QString>
#include "deviceinterface.h"

class MacroInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit MacroInterface(QString name, QSettings *settings, QObject *parent = 0);


signals:

public slots:

private:
    void messageSend(QString message);
    void getSettings();

};

#endif // MACROINTERFACE_H
