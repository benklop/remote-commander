#include <QCoreApplication>
#include <QTextStream>
#include "commander.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QStringList args = app.arguments();
    Commander *c;
    QTextStream qout(stdout); //output to stdout
    if(app.arguments().contains("-h") || app.arguments().contains("--help"))
    {
        qout << endl;
        qout << "------------------------------------------" << endl;
        qout << "             Remote Commander             " << endl;
        qout << "------------------------------------------" << endl;
        qout << "--help -h : Print this help" << endl;
        qout << "--command [device:command] : run a command" << endl;
        qout << "                      on a specific device" << endl;
        qout << "--config [file] : use specified config file"<< endl;
        qout << endl;
        return 0;
    }
    else if(args.contains("--command"))
    {
        if(args.length() == args.indexOf("--command") + 1 || args.at(args.indexOf("--command") + 1).startsWith("--") )
        {
            qout << "--command requres an argument" << endl;
            app.processEvents();
            return 0;
        }
        QString command = args.at(args.indexOf("--command") + 1);
        //need a commander
        Commander *c = new Commander();
        c->doCommand(command);
        app.processEvents();
        return 0;
    }
    else if(args.contains("--config"))
    {
        if(args.length() == args.indexOf("--config") + 1 || args.at(args.indexOf("--config") + 1).startsWith("--") )
        {
            qout << "--config requres an argument" << endl;
            app.processEvents();
            return 0;
        }
        else
        {
            QString config = args.at(args.indexOf("--config") + 1);
            //need a commander
            c = new Commander(config);
        }
    }
    else
    {
        c = new Commander();
    }
    return app.exec();
}
