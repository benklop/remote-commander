#include <QCoreApplication>
#include <QTextStream>
#include "commander.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    //need a commander
    Commander *c = new Commander();
    if(app.arguments().contains("-h") || app.arguments().contains("--help"))
    {
        QTextStream qout(stdout); //output to stdout
        qout << "     Remote Commander     " << endl;
        qout << "--------------------------" << endl;
        qout << "--help -h : Print this help" << endl;
        qout << "--command [device:command] : run a command" << endl;
        app.exit();
    }
    else if(app.arguments().contains("--command"))
    {
        QStringList args = app.arguments();
        QString command = args.at(args.indexOf("--command") + 1);
        c->doCommand(command);
        app.exit();
    }

    return app.exec();
}
