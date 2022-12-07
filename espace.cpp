#include "espace.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDebug>
#include <QDate>
#include<QPainter>
#include<QPdfWriter>
espace::espace()
{
idd=0;codepostale=0;adresse="";nom="";ville="";
}

espace::espace(int idd ,int codepostale,QString nom,QString adresse,QString ville)
{this->idd=idd;this->codepostale=codepostale;this->nom=nom;this->ville=ville  ;this->adresse=adresse ; }
int espace::getid(){return idd;}
int espace::getcodepostale(){return codepostale;}
QString espace::getadresse(){return adresse;}
QString espace::getnom(){return nom;}
QString espace::getville(){return ville;}
void espace::setid(int idd){this->idd =idd;}
void espace::setcodepostale(int codepostale){this->codepostale=codepostale;}
void espace::setnom(QString nom){this->nom=nom;}
void espace::setadresse(QString adresse){this->adresse=adresse;}
void espace::setville(QString ville){this->ville=ville;}
bool espace::ajouter()
{
   // bool test=false;
    QSqlQuery query;

   // QString id_stringr=QString::number(idd);
         query.prepare("insert into GESTIONESPACE (idd, codepostale,nom,adresse,ville) "
                       "values (:idd, :codepostale, :nom, :adresse, :ville)");
         query.bindValue(":idd", idd );
         query.bindValue(":codepostale", codepostale);
         query.bindValue(":nom", nom);
         query.bindValue(":adresse", adresse);
         query.bindValue(":ville", ville);

    return query.exec();


}
//------------------------------------------------------------------------------------------

QSqlQueryModel *  espace::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from  GESTIONESPACE");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("idd"));//nom entite
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("codepostale"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("ville"));

     return model;
}

//----------------------------------------------------------------------------------------------



bool espace::supprimer(int idd)
{
     QSqlQuery query;
    query.prepare("Delete from GESTIONESPACE where idd=:idd");
    query.bindValue(":idd",idd );


return query.exec() ;


}
//----------------------------------------------------------------------------------------------

bool espace::modifier(int idd ,int codepostale,QString nom,QString adresse,QString ville)

{
    QSqlQuery query;



    query.prepare("update GESTIONESPACE SET codepostale= :codepostale,nom= :nom,adresse= :adresse,ville= :ville where idd= :idd ");
    query.bindValue(":idd",idd);
     query.bindValue(":codepostale",codepostale);
      query.bindValue(":nom",nom);
      query.bindValue(":adresse",adresse);
       query.bindValue(":ville",ville);
        return    query.exec();


    }

//----------------------------------------------------------------------------------------------

QSqlQueryModel * espace ::afficheroncomboact()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from GESTIONESPACE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("idd"));

        return model;
}
//----------------------------------------------------------------------------------------------

void espace::genererPDFact()
{
   // QPdfWriter pdf("C://Users//jordi//Desktop//Atelier_Connexion 2//PDF.pdf");

    QPdfWriter pdf("C:/Users/jordi/Desktop/Atelier_Connexion 2/PDF.pdf");
    QPainter painter(&pdf);
   int i = 4000;
        painter.setPen(Qt::green);
        painter.setFont(QFont("Arial", 50));
        painter.drawText(1100,1200,"Liste Des Espaces");
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 15));
        painter.drawRect(100,100,7300,2600);
        painter.drawRect(0,3000,9600,500);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(200,3300,"idd");
        painter.drawText(1300,3300,"codepostale");
        painter.drawText(2400,3300,"nom");
           painter.drawText(3500,3300,"adresse");
              painter.drawText(4600,3300,"ville");

        QSqlQuery query;
        query.prepare("select * from GESTIONESPACE");
        query.exec();
        while (query.next())
        {
            painter.drawText(200,i,query.value(0).toString());
            painter.drawText(1300,i,query.value(1).toString());
            painter.drawText(2400,i,query.value(2).toString());
            painter.drawText(3500,i,query.value(3).toString());
            painter.drawText(4600,i,query.value(4).toString());


           i = i + 500;
        }


}
//----------------------------------------------------------------------------------------------

QSqlQueryModel* espace::Rechercheesp(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM GESTIONESPACE WHERE IDD LIKE '"+recherche+"%' OR CODEPOSTALE LIKE '"+recherche+"%' OR NOM LIKE '"+recherche+"%'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDD"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("CODEPOSTALE"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("VILLE"));

return model;
}
//----------------------------------------------------------------------------------------------

QSqlQueryModel * espace::trierespParID()
{

    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM GESTIONESPACE order by IDD ASC ");

           q->exec();
           model->setQuery(*q);
           return model;

}
