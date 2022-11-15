#include "dumessengerserver.h"
#include <QDebug>
#include <dumessengersocket.h>
#include <QTextStream>
namespace  Duartecorporation
{
dumessengerserver::dumessengerserver(QObject *parent):QTcpServer(parent)
{

}

void dumessengerserver::incomingConnection(qintptr handle)
{
    auto socket=new dumessengersocket(handle ,this);
    mSockets << socket;
        for( auto i:mSockets )
        {
            QTextStream t(i);
            t << "conected:"<< handle;
            i->flush();
        }
    connect(socket,&dumessengersocket::DuReadyread, [&](dumessengersocket *s) {
        qDebug()<<"Dureadyread";
        QTextStream t(s);
        auto text= t.readAll();

        for(auto i:mSockets) {
            QTextStream k(i);
            k<< text;
            i->flush();
        }
    });
    connect (socket,&dumessengersocket::dustatechanged,[&](dumessengersocket *s,int st)
    {   qDebug()<<"dustatechanged";
        if (st==QTcpSocket::UnconnectedState) {
            qDebug() << "unconnected state";
            mSockets.removeOne(s);
            for(auto i:mSockets) {
                QTextStream k(i);
                k << "server:client" << s->socketDescriptor() << "dcd";
                i->flush();
            }
        }
    });
}

bool dumessengerserver::startserver(quint16 port)
{
    return(listen(QHostAddress::Any,port));
}

}//endnamespace











