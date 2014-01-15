#include "samsunginterface.h"

SamsungInterface::SamsungInterface(QString name, QSettings *settings, QObject *parent) :
    DeviceInterface(name, settings, parent)
{
    qDebug() << "creating Samsung interface" << name;

    //load settings
    loadSettings("port");

    loadHash();
    serial = new QSerialPort(this);
    serial->setPortName(loadedSettings.value("port"));
    serial->open(serial->ReadWrite);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    connect(serial, SIGNAL(readyRead()), this, SLOT(receiveData()));
}

void SamsungInterface::receiveMessage(QString message)
{
    if(!codes.contains(message))
    {
        qDebug() << "no known command" << message << "for samsung";
        return;
    }
    QByteArray code = codes.value(message);
    qDebug() << "sending message" << message << "to device" << name << "with code" << code.toHex();
    QByteArray pre;
    pre.append(0x08);
    pre.append(0x22);
    QByteArray command;
    command.append(pre);
    command.append(code);
    command.append(csum(command));
    serial->write(command);
    qDebug() << "wrote command" << command.toHex();
}

//load the data out of the port
void SamsungInterface::receiveData()
{
    QByteArray message = serial->readAll();
    qDebug() << "received response from Samsung" << message.toHex();
}

void SamsungInterface::loadHash()
{
    codes.insert("power_on",        QByteArray::fromHex("00 00 00 02"));
    codes.insert("power_off",       QByteArray::fromHex("00 00 00 01"));
    codes.insert("power_toggle",    QByteArray::fromHex("00 00 00 00"));
    codes.insert("source_tv",       QByteArray::fromHex("0a 00 00 00"));
    codes.insert("source_hdmi_1",   QByteArray::fromHex("0a 00 05 00"));
    codes.insert("source_hdmi_2",   QByteArray::fromHex("0a 00 05 01"));
    codes.insert("source_hdmi_3",   QByteArray::fromHex("0a 00 05 02"));
    codes.insert("source_hdmi_4",	QByteArray::fromHex("0a 00 05 03"));
    codes.insert("source_component",QByteArray::fromHex("0a 00 03 00"));
    codes.insert("size_16x9",       QByteArray::fromHex("0b 0a 01 00"));
    codes.insert("size_fit",		QByteArray::fromHex("0b 0a 01 05"));
    codes.insert("external_speaker",QByteArray::fromHex("0c 07 00 01"));
    codes.insert("internal_speaker",QByteArray::fromHex("0c 07 00 00"));
}
