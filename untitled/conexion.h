#ifndef CONEXION_H
#define CONEXION_H
#include<QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class conexion
{
public:
   conexion();
    bool createconnect();
};








#endif // CONEXION_H
