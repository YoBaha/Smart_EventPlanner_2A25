#ifndef EVENEMENT_H
#define EVENEMENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

//test rbk
class Evenement

{ int id ; QString nomevent,typeevent;
    QString placeevent,timeevent,date_debut,date_fin;
public:
    Evenement(){}
    Evenement(int,QString,QString,QString,QString,QString,QString);
    int getId(){return id ; }
    QString getNomevent(){return nomevent;}
     QString getTypeevent(){return typeevent;}
    QString getPlaceevent(){return placeevent;}
    QString getTimeevent(){return timeevent;}
   QString getDate_debut(){return date_debut;}
    QString getDate_fin(){return date_fin;}





    void setNomevent(QString nomevent) {nomevent=nomevent ; }
    void setTypeevent(QString typeevent) {typeevent=typeevent ; }
    void setPlaceevent(QString placeevent) {placeevent=placeevent ; }
    void setTimeevent(QString timeevent) {timeevent=timeevent ; }
    void setDate_debut(QString date_debut) {date_debut=date_debut ; }
    void setDate_fin(QString date_fin) {date_fin=date_fin ; }
    void setId(int id){id=id;}



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
     bool modifier(int, QString,QString,QString,QString,QString,QString);






};

#endif // EVENEMENT_H
