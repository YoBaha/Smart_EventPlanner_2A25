#ifndef DUMESSENGERSERVER_H
#define DUMESSENGERSERVER_H
#include <QTcpServer>
#include <dumessengersocket.h>
namespace  Duartecorporation
{
class dumessengerserver : public QTcpServer
{
public:
    dumessengerserver(QObject *parents=nullptr);
    bool startserver(quint16 port);
protected:
    void incomingConnection(qintptr handle);
private :
    QList <dumessengersocket*> mSockets;
};
}
#endif // DUMESSENGERSERVER_H
