#include "evenement.h"
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

//test
Evenement::Evenement(int id, QString nomevent,QString typeevent,QString placeevent,QString timeevent,QString date_debut,QString date_fin)
{ this->nomevent=nomevent ;
    this->typeevent=typeevent ;
    this->placeevent=placeevent ;
    this->timeevent=timeevent ;
    this->nomevent=nomevent ;
    this->date_debut=date_debut;
       this->id=id ;
    this->date_fin=date_fin;


}
bool Evenement::ajouter()
{
    QSqlQuery query;
          query.prepare("INSERT INTO evenement (id,nomevent, typeevent, placeevent, timeevent, date_debut, date_fin) "
                        "VALUES (:id,:nomevent, :typeevent, :placeevent, :timeevent, :date_debut, :date_fin)");
          query.bindValue(":nomevent", nomevent);
          query.bindValue(":typeevent", typeevent);
          query.bindValue(":placeevent", placeevent);
          query.bindValue(":timeevent", timeevent);
          query.bindValue(":date_debut", date_debut);
          query.bindValue(":date_fin",date_fin);
          query.bindValue(":id", id);
       return   query.exec();



}


QSqlQueryModel * Evenement::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from evenement");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("nomevent"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("typeevent"));
          model->setHeaderData(3,Qt::Horizontal,QObject::tr("placeevent"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("timeevent"));
       model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_debut"));
       model->setHeaderData(6,Qt::Horizontal,QObject::tr("date_fin"));

     return model;
    }

bool Evenement::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("Delete from evenement where id=:id");
    query.bindValue(":id",id);
    return query.exec();


}

bool Evenement::modifier(int id ,QString nomevent,QString typeevent,QString placeevent,QString timeevent,QString date_debut,QString date_fin)
{
    QSqlQuery query;
    query.prepare("update evenement set  nomevent = :nomevent , typeevent = :typeevent , placeevent =:placeevent , timeevent = :timeevent ,date_debut = :date_debut , date_fin = :date_fin  where id = :id ");
    query.bindValue(":nomevent", nomevent);
    query.bindValue(":typeevent", typeevent);
    query.bindValue(":placeevent", placeevent);
    query.bindValue(":timeevent",timeevent);
    query.bindValue(":date_debut", date_debut);
    query.bindValue(":date_fin", date_fin);
    query.bindValue(":id", id);

     return   query.exec();


}

