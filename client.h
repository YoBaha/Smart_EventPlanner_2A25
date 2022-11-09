#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlQueryModel>
#include <QString>
class client
{
public:
    client();
    client(int a,QString b,QString c,QString d);

    int get_cin(){return(cin);}
    QString get_nom(){return(nom);}
    QString get_prenom(){return(prenom);}
    QString get_date(){return(date);}

    void set_cin(int a){cin=a;}
    void set_nom(int a){nom=a;}
    void set_prenom(int a){prenom=a;}
    void set_date(int a){date=a;}

    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherc1();
    QSqlQueryModel* afficherc2();
    QSqlQueryModel* afficherc3();
    QSqlQueryModel * recherche(QString data);
    bool supprimer(int c);
    QSqlQueryModel* affichermessage(QString str);
private:
    int cin;
    QString nom,prenom,date;
};

#endif // CLIENT_H
