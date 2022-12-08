#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <QString>
#include<QSqlQueryModel>
class Personnel
{
public:
    Personnel();
    Personnel(int,QString,QString);
    int getcin();
    QString getnom() ;
    QString getprenom() ;
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    bool ajouter();
   QSqlQueryModel* afficher();
   bool supprimer(int cin);
bool modifier(int cin, QString nom,QString prenom);
QSqlQueryModel * tripersonnel();
QSqlQueryModel * recherche(QString data);

private:
int cin;
QString nom,prenom;
};

#endif // PERSONNEL_H
