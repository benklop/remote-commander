#ifndef SAMSUNGINTERFACE_H
#define SAMSUNGINTERFACE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QHash>
#include "commander.h"
#include "deviceinterface.h"
#include <stdint.h>

class SamsungInterface : public DeviceInterface
{
    Q_OBJECT
public:
    explicit SamsungInterface(QString serialPort, QObject *parent = 0);

signals:


public slots:
    void messageSend(QString message);
    void getMessage();

private:
    QSerialPort *serial;
    Commander *commander;
    QHash<QString,QByteArray> codes;

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

    static QByteArray mkArray(const std::initializer_list<u_int8_t>& data) {
        return mkArray(data.begin());
    }

    static QByteArray mkArray(const u_int8_t *data) {
        QByteArray thisData = reinterpret_cast<const char*>(data);
        return thisData;
    }

};

#endif // SAMSUNGINTERFACE_H
