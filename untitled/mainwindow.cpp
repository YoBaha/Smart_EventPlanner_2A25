#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include <QMessageBox>
#include<QSqlQuery>
#include<QSqlQueryModel>

#include<QTime>
#include <QTimer>
#include <qdebug.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_3->setModel(tmp.afficher());


    ui->lineEdit_nom->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z_ ]"),this));

    ui->lineEdit_place->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z_ ]{0,20}"),this));
    ui->lineEdit_tp->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z_ ]{0,20}"),this));
    ui->lineEdit_time->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z_ ]{0,20}"),this));
    ui->lineEdit_idc->setValidator(new QIntValidator(0,999));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_7_clicked() // ajouter
{
     QString nomevent=ui->lineEdit_nom->text();
    QString typeevent=ui->lineEdit_tp->text();
    QString placeevent=ui->lineEdit_place->text();
    QString timeevent=ui->lineEdit_time->text();
    QString date_debut=ui->lineEdit_datedeb->text();
    QString date_fin=ui->lineEdit_datefin->text();
    int id=ui->lineEdit_idc->text().toInt() ;

    Evenement c (id,nomevent,typeevent,placeevent,timeevent,date_debut,date_fin) ;

    bool test=c.ajouter() ;
    if(test)
    {
        ui->tableView_3->setModel(c.afficher());
        QMessageBox::information(nullptr, QObject::tr("ajouter"),
                    QObject::tr("ajout avec succes.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("ajouter"),
                    QObject::tr("erreur d'ajout.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}




void MainWindow::on_pushButton_8_clicked() //upd
{

    QString nomevent=ui->lineEdit_nommod->text();
   QString typeevent=ui->lineEdit_typemod->text();
   QString placeevent=ui->lineEdit_placemod->text();
   QString timeevent=ui->lineEdit_timemod->text();
   QString date_debut=ui->lineEdit_debutmod->text();
   QString date_fin=ui->lineEdit_finmod->text();
   int id=ui->lineEdit_idmod->text().toInt() ;



    bool test=tmp.modifier(id,nomevent,typeevent,placeevent,timeevent,date_debut,date_fin) ;
    QMessageBox msBox;
    if(test)
    {
        ui->tableView_3->setModel(tmp.afficher());
        ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        msBox.setText("modification reussite");
        msBox.exec();

        ui->lineEdit_placemod->clear();
        ui->lineEdit_nommod->clear();
        ui->lineEdit_typemod->clear();
        ui->lineEdit_timemod->clear();
        ui->lineEdit_debutmod->clear();
        ui->lineEdit_finmod->clear();
    }
    else
    {
        msBox.setText("ERREUR");
        msBox.exec();}
    ui->lineEdit_placemod->clear();
    ui->lineEdit_nommod->clear();
    ui->lineEdit_typemod->clear();
    ui->lineEdit_timemod->clear();
    ui->lineEdit_debutmod->clear();
    ui->lineEdit_finmod->clear();

}


void MainWindow::on_pushButton_9_clicked() //suprr
{
    int id=ui->lineEdit_idc->text().toInt() ;
    bool test=tmp.supprimer(id) ;
    if(test)
    {
        ui->tableView_3->setModel(tmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("suprimer"),
                    QObject::tr("Evenement supprime!!!.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("supprimer"),
                    QObject::tr("suppression non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_pushButton_16_clicked() //tri
{
    QMessageBox msgBox ;
         QSqlQueryModel *model = new QSqlQueryModel();
               model->setQuery("select * from evenement order by id ASC,nomevent");
               model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
                 model->setHeaderData(1,Qt::Horizontal,QObject::tr("nomevent"));
                   model->setHeaderData(2,Qt::Horizontal,QObject::tr("typeevent"));
                     model->setHeaderData(3,Qt::Horizontal,QObject::tr("placeevent"));
               model->setHeaderData(4,Qt::Horizontal,QObject::tr("timeevent"));
                  model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_debut"));
                  model->setHeaderData(6,Qt::Horizontal,QObject::tr("date_fin"));
               ui->tableView_3->setModel(model);
               ui->tableView_3->show();
                msgBox.setText("Tri avec succés.");
                msgBox.exec();
}


void MainWindow::on_pushButton_17_clicked()  // rech
{
    QMessageBox msgBox ;
        QSqlQueryModel *model = new QSqlQueryModel();
        QString cod;
        cod = ui->lineEdit_idc->text();
        model->setQuery("Select * from evenement where id = '"+cod+"' ");

        model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("nomevent"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("typeevent"));
              model->setHeaderData(3,Qt::Horizontal,QObject::tr("placeevent"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("timeevent"));
           model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_debut"));
           model->setHeaderData(6,Qt::Horizontal,QObject::tr("date_fin"));
        ui->tableView_3->setModel(model);
        ui->tableView_3->show();
        msgBox.setText("Evenement trouver ");
        msgBox.exec();
        ui->lineEdit_idmc->clear();
        QSqlQuery qry;
        qry.prepare("select * from evenement where id='"+cod+"'  " );

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->lineEdit_idmod->setText(qry.value(0).toString());
                 ui->lineEdit_nommod->setText(qry.value(1).toString());
                ui->lineEdit_typemod->setText(qry.value(2).toString());
               ui->lineEdit_placemod->setText(qry.value(3).toString());
               ui->lineEdit_timemod->setText(qry.value(4).toString());
               ui->lineEdit_debutmod->setText(qry.value(5).toString());
               ui->lineEdit_finmod->setText(qry.value(6).toString());


            }
        }
}


