#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSortFilterProxyModel>
client::client()
{
    cin=0;prenom=" ";nom=" ";date=" ";
}
client::client(int a,QString b,QString c,QString d)
{
    cin=a;
    nom=b;
    prenom=c;
    date=d;
}

bool client::ajouter()
{

    QString cin_string =QString::number(cin);
    QSqlQuery query;
    query.prepare("INSERT INTO client (cin, nom, prenom,DATENAISSANCE) "
                       "VALUES (:id, :forename, :surname,:date)");
         query.bindValue(":id", cin_string);
         query.bindValue(":forename", nom);
         query.bindValue(":surname", prenom);
         query.bindValue(":date", date);

    return(query.exec());
}

QSqlQueryModel* client::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM CLIENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE"));
          //model->sort(0,Qt::AscendingOrder);
          return(model);
}

bool client::supprimer(int cin)
{
    QSqlQuery query;
         query.prepare("Delete from client where cin =:id");

         query.bindValue(":id", cin);

         return(query.exec());
}

QSqlQueryModel* client::afficherc1()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM CLIENT ORDER BY CIN");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE"));
          //model->sort(0,Qt::AscendingOrder);
          return(model);
}
QSqlQueryModel* client::afficherc2()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM CLIENT ORDER BY NOM");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE"));
          //model->sort(0,Qt::AscendingOrder);
          return(model);
}
QSqlQueryModel* client::afficherc3()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM CLIENT ORDER BY PRENOM");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE"));
          //model->sort(0,Qt::AscendingOrder);
          return(model);
}

QSqlQueryModel * client::recherche(QString data){
  QSqlQueryModel * model = new QSqlQueryModel();
  model->setQuery("SELECT * FROM CLIENT  where CIN='"+data+"' OR NOM='"+data+"' OR PRENOM='"+data+"' OR DATENAISSANCE='"+data+"'");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE"));
  return model;
}

QSqlQueryModel* client::affichermessage(QString str)
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT emetteur, message FROM messagelist where recepteur='"+str+"'");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("emetteur"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("message"));
          return(model);
}


