#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<Personnel.h>
#include"smtp.h"
//#include"his.h"
//#include "ui_his.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   //Ui::MainWindow *ui;

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
    Ui::MainWindow *ui;
    Personnel E;
    Smtp *smtp;
   // his *His;

};

#endif // MAINWINDOW_H
