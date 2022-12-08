#ifndef GESTION_PERSONNEL_H
#define GESTION_PERSONNEL_H

#include <Qgestion_personnel>
#include<Personnel.h>
namespace Ui {
class gestion_personnel;
}
class gestion_personnel : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_personnel(QWidget *parent = nullptr);
    ~gestion_personnel();
   //Ui::gestion_personnel *ui;

private slots:
    void on_pb_ajouter_clicked();

    void on_bp_supp_clicked();

    void on_pb_modf_2_clicked();

    void on_pushButton_clicked();
    void on_pb_recherche_clicked();

    void on_pdf_bo_clicked();

    void on_pb_envoyer_clicked();
    void on_pb_his_clicked();


private:
    Ui::gestion_personnel *ui;
    Personnel E;
    Smtp *smtp;
   // his *His;

};


#endif // GESTION_PERSONNEL_H
