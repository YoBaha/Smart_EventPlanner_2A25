#include "partenaire.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include"connection.h"

partenaire::partenaire(QString nomp,QString amp,QString nump,QString adp,QString ofrp,int idp)
{
    this->idp=idp;
    this->nomp=nomp;
    this->amp=amp;
    this->nump=nump;
    this->adp=adp;
    this->ofrp=ofrp;
}

bool partenaire::ajouter(){
    QSqlQuery query;
    QString res = QString::number(idp);
    query.prepare("insert into PARTENAIRE (idp,nump,nomp,ofrp,amp,adp)" "values (:idp,:nump,:nomp,:ofrp,:amp,:adp)");
    query.bindValue(":idp",res);
    query.bindValue(":nump",nump);
    query.bindValue(":nomp",nomp);
    query.bindValue(":ofrp",ofrp);
    query.bindValue(":amp",amp);
    query.bindValue(":adp",adp);
    return query.exec();
     }

bool partenaire::supprimer(int id){
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from PARTENAIRE where IDP= :id");
    query.bindValue(":id",res);
    return query.exec();
}
QSqlQueryModel * partenaire::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from PARTENAIRE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDP"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMP"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NUMP"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("OFRP"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("AMP"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADP"));
    return model;
}
bool partenaire:: mettre_aj(int id) {
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("Update PARTENAIRE SET idp=:id, nump=:nump, nomp=:nomp, ofrp=:ofrp, amp=:amp, adp=:adp WHERE IDP= :id ");
    query.bindValue(":id",res);
    query.bindValue(":nump",nump);
    query.bindValue(":nomp",nomp);
    query.bindValue(":ofrp",ofrp);
    query.bindValue(":amp",amp);
    query.bindValue(":adp",adp);
    return query.exec();
}
QSqlQueryModel * partenaire::chercher_part(QString idp)
{
   QSqlQueryModel * model= new QSqlQueryModel();
QSqlQuery query;
idp='%'+idp+'%';
query.prepare(" select * from PARTENAIRE where idp like :idp ");
query.bindValue(":idp",idp);
query.exec();
model->setQuery(query);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDP"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMP"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("NUMP"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("OFRP"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("AMP"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADP"));
   return model;
}
QSqlQueryModel * partenaire::triA()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM PARTENAIRE ORDER BY IDP ASC");
        return model;
}
QSqlQueryModel * partenaire::triD()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM PARTENAIRE ORDER BY IDP DESC");
        return model;
}
