#include "samsunginterface.h"
#include <QDebug>

SamsungInterface::SamsungInterface(QString name, QString serialPort, QObject *parent) :
    DeviceInterface(name, parent)
{
    qDebug() << "creating Samsung interface";

    serial = new QSerialPort(this);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setPortName(serialPort);
    serial->open(serial->ReadWrite);

    connect(serial, SIGNAL(readyRead()), this, SLOT(getMessage()));
}

void SamsungInterface::messageSend(QString message)
{
    QByteArray code = codes.value(message);
    QByteArray pre;
    pre.append(0x08);
    pre.append(0x22);
    QByteArray command;
    command.append(pre);
    command.append(code);
    command.append(csum(command));
}

//load the data out of the port
void SamsungInterface::getMessage()
{
    QByteArray message = serial->readAll();
    //do something for each char
    qDebug() << "received response from Samsung" << message;
    foreach(char ch, message)
    {
        //each char
    }
}

void SamsungInterface::loadHash()
{
    codes.insert("power_on",        mkArray({0x00,0x00,0x00,0x02}));
    codes.insert("power_off",       mkArray({0x00,0x00,0x00,0x01}));
    codes.insert("power_toggle",    mkArray({0x00,0x00,0x00,0x00}));
    codes.insert("source_tv",       mkArray({0x0a,0x00,0x00,0x00}));
    codes.insert("source_hdmi_1",   mkArray({0x0a,0x00,0x05,0x00}));
    codes.insert("source_hdmi_2",   mkArray({0x0a,0x00,0x05,0x01}));
    codes.insert("source_hdmi_3",   mkArray({0x0a,0x00,0x05,0x02}));
    codes.insert("source_hdmi_4",	mkArray({0x0a,0x00,0x05,0x03}));
    codes.insert("source_component",mkArray({0x0a,0x00,0x03,0x00}));
    codes.insert("size_16x9",       mkArray({0x0b,0x0a,0x01,0x00}));
    codes.insert("size_fit",		mkArray({0x0b,0x0a,0x01,0x05}));
    codes.insert("external_speaker",mkArray({0x0c,0x07,0x00,0x01}));
    codes.insert("internal_speaker",mkArray({0x0c,0x07,0x00,0x00}));
}
