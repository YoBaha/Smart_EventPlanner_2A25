#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <dumessengerserver.h>
#include"widget.h"
#include "espace.h"
#include "evenement.h"
using namespace Duartecorporation;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test=c.createconnect();
    MainWindow w;
    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

 QMessageBox msgbox;
    dumessengerserver server;
    if(!server.startserver(3333))
    {

        msgbox.setText("erreur server");
        msgbox.exec();
    }
    msgbox.setText("server started...");
    msgbox.exec();
    /*widget wid;
     wid.show();*/


    return a.exec();
}
