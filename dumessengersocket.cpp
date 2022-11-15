#include "dumessengersocket.h"

namespace  Duartecorporation
{

dumessengersocket::dumessengersocket(qintptr handle,QObject *parent) :QTcpSocket(parent)
{
    setSocketDescriptor(handle);

    connect(this,& dumessengersocket::readyRead,[&](){
        emit DuReadyread(this);
    });
    connect (this,&dumessengersocket::stateChanged,[&](int s){
        emit dustatechanged(this,s);
    });
}


}//endnamespace
