#include "conexion.h"
#include <QMessageBox>



conexion::conexion()
{

}

bool conexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_project2A");
db.setUserName("system");
db.setPassword("ena6969");

if (db.open())
test=true;





    return  test;
}

