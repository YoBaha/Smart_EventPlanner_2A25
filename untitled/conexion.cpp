#include "conexion.h"
#include <QMessageBox>



conexion::conexion()
{

}

bool conexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_project2A");//inserer le nom de la source de données ODBC
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("ena6969");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

