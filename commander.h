#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>

class Commander : public QObject
{
    Q_OBJECT
public:
    explicit Commander(QObject *parent = 0);
    
signals:
    
public slots:
    void doCommand(QString commandName);

};

#endif // COMMANDER_H
