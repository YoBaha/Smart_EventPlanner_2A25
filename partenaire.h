#ifndef PARTENAIRE_H
#define PARTENAIRE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class partenaire
{
QString nomp, amp, nump, adp, ofrp;
int idp;
public:
// constructeurs
partenaire() {};
partenaire (QString,QString,QString,QString,QString,int);
//getters
    QString getNomp() {return nomp;}
    QString getAmp() {return amp;}
    QString getNump() {return nump;}
    QString getAdp() {return adp;}
    QString getOfrp() {return ofrp;}
    int getIdp() {return idp;}
//setters
    void setNomp(QString n) {nomp=n;}
    void setAmp(QString a) {amp=a;}
    void setNump (QString nu) {nump=nu;}
    void setAdp (QString ap) {adp=ap;}
    void setOfrp(QString op) {ofrp= op;}
    void setIdp(int id) {this->idp=id;}
//fcts relatives
   QSqlQueryModel * chercher_part(QString id);
   QSqlQueryModel * triA();
   QSqlQueryModel * triD();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool mettre_aj(int);
    bool supprimer(int);
};
#endif // PARTENAIRE_H
