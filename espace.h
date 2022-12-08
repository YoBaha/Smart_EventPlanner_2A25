#include <QMainWindow>
#ifndef ESPACE_H
#define ESPACE_H
#include<QSqlQueryModel>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
class espace
{
public:
    espace();
    espace(int,int,QString,QString,QString);
    int getid();
    int getcodepostale();
    QString getnom();
    QString getville();
    QString getadresse();

    void setid(int);
    void setcodepostale(int);
    void setnom(QString);
    void setville(QString);
    void setadresse(QString);
    bool  ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
     bool modifier(int,int,QString,QString,QString);

     QSqlQueryModel * afficheroncomboact();
     void genererPDFact();
     QSqlQueryModel* Rechercheesp(QString);
     QSqlQueryModel * trierespParID();

private:
    int idd,codepostale;
    QString nom,adresse,ville;
 int salaire1,E1;
};

#endif // ESPACE_H

