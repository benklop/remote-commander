#ifndef MACROINTERFACE_H
#define MACROINTERFACE_H
#include <QString>
#include "deviceinterface.h"
#include "macroaction.h"

class MacroInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit MacroInterface(QString name, QSettings *settings, QObject *parent = 0);


signals:

public slots:
    void messageSend(QString message);

private:
    QHash<QString, *MacroAction> actions;


    void getSettings();

};

#endif // MACROINTERFACE_H
