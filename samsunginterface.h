#ifndef SAMSUNGINTERFACE_H
#define SAMSUNGINTERFACE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QHash>
#include "commander.h"
#include "deviceinterface.h"

class SamsungInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit SamsungInterface(QString name, QSettings *settings, QObject *parent = 0);

signals:


public slots:
    void receiveMessage(QString message);
    void receiveData();

private:
    QSerialPort *serial;
    Commander *commander;
    QHash<QString,QByteArray> codes;
    QString serialPort;

    static char csum (QByteArray cmd)
    {
        u_int8_t csum = 0;

        foreach(char byte, cmd)
        {
            u_int8_t ubyte = reinterpret_cast<u_int8_t&>(byte);
            csum += ubyte;
        }

        csum = (~csum + 1) & 0xff;
        return reinterpret_cast<char&>(csum);
    }

    void loadHash();
    void getSettings();

};

#endif // SAMSUNGINTERFACE_H
