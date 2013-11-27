#ifndef SENDER_H
#define SENDER_H

#include <QObject>

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = 0);
    
    void sendCommand(char* command);

signals:
    
public slots:
    
};

#endif // SENDER_H
