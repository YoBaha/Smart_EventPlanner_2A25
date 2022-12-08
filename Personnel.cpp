#include "Personnel.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Personnel::Personnel()
{
cin=0; nom=""; prenom="";
}
Personnel::Personnel(int cin,QString nom,QString prenom)
{this->cin=cin; this->nom=nom; this->prenom=prenom;}
int Personnel::getcin() {return cin;}
QString Personnel::getnom () {return nom;}
QString Personnel:: getprenom () {return prenom;}
void Personnel::setcin(int cin) {this->cin=cin;}
void Personnel:: setnom(QString nom) {this->nom=nom; }
void Personnel:: setprenom (QString prenom) {this->prenom=prenom;}
bool Personnel::ajouter()
{
    QSqlQuery query;
    QString cin_string=QString::number(cin);
         query.prepare("INSERT INTO Personnel (cin, nom, prenom) "
                       "VALUES (:cin, :nom, :prenom)");//pour l'execution
         query.bindValue(":cin", cin);
         query.bindValue(":nom", nom);
         query.bindValue(":prenom", prenom);
        return query.exec();


}
bool Personnel::supprimer(int cin)
{

    QSqlQuery query;
         query.prepare("Delete from Personnel where cin=:cin ");
         query.bindValue(0, cin);

        return query.exec();

}
QSqlQueryModel* Personnel::afficher()
{
 QSqlQueryModel* model=new QSqlQueryModel();


       model->setQuery("SELECT* FROM Personnel");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));//ajouter le nom de tableau
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
    return model;

}
bool Personnel::modifier(int cin,QString nom,QString prenom)
{
QSqlQuery query;
QString cin_string=QString::number(cin);
query.prepare("update personnel set cin=cin,nom=:nom,prenom=:prenom");
query.bindValue(":cin", cin);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);

return    query.exec();
}
QSqlQueryModel *Personnel::tripersonnel()
{

    QSqlQueryModel * model = new QSqlQueryModel();
   model->setQuery("select * from personnel order by cin");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
        return model;
}
QSqlQueryModel * Personnel::recherche(QString data)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM Personnel  where  cin='"+data+"' OR nom='"+data+"' OR prenom='"+data+"'  ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));



    return model;
}



