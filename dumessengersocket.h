#ifndef DUMESSENGERSOCKET_H
#define DUMESSENGERSOCKET_H
#include <QTcpSocket>
namespace  Duartecorporation
{
class dumessengersocket : public QTcpSocket
{Q_OBJECT
public:
    dumessengersocket(qintptr handle,QObject *parent=nullptr);
signals :
    void DuReadyread(dumessengersocket *);
    void dustatechanged(dumessengersocket*,int);
};
}//endnamespace
#endif // DUMESSENGERSOCKET_H
