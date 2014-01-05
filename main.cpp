#include <QCoreApplication>
#include <QTextStream>
#include "commander.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    //need a commander
    Commander *c = new Commander();
    QTextStream qout(stdout); //output to stdout
    if(app.arguments().contains("-h") || app.arguments().contains("--help"))
    {
        qout << endl;
        qout << "------------------------------------------" << endl;
        qout << "             Remote Commander             " << endl;
        qout << "------------------------------------------" << endl;
        qout << "--help -h : Print this help" << endl;
        qout << "--command [device:command] : run a command" << endl;
        qout << " on a specific device" << endl;
        qout << endl;
        return 0;
    }
    else if(app.arguments().contains("--command"))
    {
        QStringList args = app.arguments();
        if(args.length() == args.indexOf("--command") + 1 || args.at(args.indexOf("--command") + 1).startsWith("--") )
        {
            qout << "--command requres an argument" << endl;
            app.processEvents();
            return 0;
        }
        QString command = args.at(args.indexOf("--command") + 1);
        c->doCommand(command);
        app.processEvents();
        return 0;
    }
    else if(app.arguments().length() > 1)
    {
        qout << "unknown argument " << app.arguments().at(1) << endl;
        app.processEvents();
        return 0;
    }

    return app.exec();
}
