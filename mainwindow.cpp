#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegExp>
#include <QSortFilterProxyModel>
#include <QDebug>
#include<QFile>
#include<QTextDocument>
#include<QTextStream>
#include <QPdfWriter>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->tableView->setSortingEnabled(true); // sorting
    ui->tableView->setModel(cl.afficher());
    ui->tableView->sortByColumn(0);
    //ui->tableView->sortByColumn(0,Qt::AscendingOrder);
    //ui->tableView->horizontalHeader()->setSectionsClickable(1);
    ui->tableView_2->setColumnWidth(0, ui->tableView_2->width()/3);
    ui->tableView_2->setColumnWidth(1,500);

    ui->lineEdit->setInputMask("aaaaaaaaaaaaaaaaaaa");
    ui->lineEdit->setCursorPosition(0);
    ui->lineEdit_2->setInputMask("aaaaaaaaaaaaaaaaaaa");
    ui->lineEdit_3->setInputMask("99999999");
    QRegExp R_date("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/(19[0-9][0-9]|20[0-9][0-9])");
    QRegExpValidator *valid = new QRegExpValidator(R_date, this);
    ui->lineEdit_4->setValidator(valid);
    ui->lineEdit_4->setPlaceholderText("Example : 21/05/2022");


    ui->lineEdit_6->setInputMask("aaaaaaaaaaaaaaaaaaa");
    ui->lineEdit_6->setCursorPosition(0);
    ui->lineEdit_7->setInputMask("aaaaaaaaaaaaaaaaaaa");
    ui->lineEdit_8->setInputMask("99999999");
    //QRegExp R_date("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/(19[0-9][0-9]|20[0-9][0-9])");
    //QRegExpValidator *valid = new QRegExpValidator(R_date, this);
    ui->lineEdit_9->setValidator(valid);
    ui->lineEdit_9->setPlaceholderText("Example : 21/05/2022");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{bool verif;
    int c=ui->lineEdit_3->text().toInt();

    QString a=ui->lineEdit->text();
    QString b=ui->lineEdit_2->text();
   QString d=ui->lineEdit_4->text();
    client cl(c,a,b,d);
    verif=cl.ajouter();
    QMessageBox msgbox;
    if(verif)
    {msgbox.setText("verifiee");
    ui->tableView->setModel(cl.afficher());}
    else
        msgbox.setText("non verifiee");
    msgbox.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_14_clicked()
{int c;
    QMessageBox msgbox;
    client cl;
    cl.set_cin(ui->lineEdit_5->text().toInt());
    bool verif=cl.supprimer(cl.get_cin());
    c=cl.get_cin();
    QSqlQuery query1;
    /*query1.prepare("select(*) cin from client where c=:cin");
    if(query1.exec()==false)
     {   msgbox.setText("CIN inexistant");
        msgbox.exec();
    }
    else
    {*/
    if(verif)
    {msgbox.setText("verifiee");
        msgbox.exec();
        ui->tableView->setModel(cl.afficher());}
    else
        {msgbox.setText("non verifiee");
    msgbox.exec();}

}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_19_clicked()
{
        QMessageBox msgbox;
    QString c=ui->lineEdit_8->text();
        QString a=ui->lineEdit_6->text();
        QString b=ui->lineEdit_7->text();
       QString d=ui->lineEdit_9->text();
      QSqlQuery query1;
      /*query1.prepare("select(*) cin from client where cin='"+c+"'");
      query1.exec();
      if(query1.exec()==false)
       {   msgbox.setText("CIN inexistant");
          msgbox.exec();
      }
      else
      {*/
       QSqlQuery query;
            query.prepare("update client set cin='"+c+"',nom='"+a+"',prenom='"+b+"' where cin='"+c+"' ");


                //QMessageBox msgbox;
                if(query.exec())
                {msgbox.setText("verifiee");
                    msgbox.exec();
                    ui->tableView->setModel(cl.afficher());}
                else
                {msgbox.setText("non verifiee");
                msgbox.exec();}
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_21_clicked()
{
    /*QMessageBox msgbox;

    QSqlQuery query;
       QFile myfile("mydata.pdf");
       myfile.open(QIODevice::WriteOnly);
       query.prepare("select * from client");
       query.exec();
       QString line="";
       QTextStream out(&myfile);
       while (query.next()) {
          line+=query.value(0).toString()+"\t";
          line+=query.value(1).toString()+"\t";
          line+=query.value(2).toString()+"\t";
          line+=query.value(3).toString()+"\n";
          qDebug()<<line;
          out<<line;
          line="";
       }
       myfile.close();*/

    QPdfWriter pdf("listt.pdf");

       QPainter painter(&pdf);
       int i = 4000;
              painter.setPen(Qt::black);
              painter.setFont(QFont("Time New Roman", 25));
              painter.drawText(3000,1400,"Liste Des Clients");
              painter.setPen(Qt::black);
              painter.setFont(QFont("Time New Roman", 15));
              painter.drawRect(100,100,9400,2500);
              painter.drawRect(100,3000,9400,500);
              painter.setFont(QFont("Time New Roman", 9));
              painter.drawText(400,3300,"cin");
              painter.drawText(1350,3300,"NOM");
              painter.drawText(2200,3300,"PRENOM");
              painter.drawText(3400,3300,"DATENAISSANCE");
              painter.drawRect(100,3000,9400,9000);

              QSqlQuery query;
              query.prepare("select * from client");
              query.exec();
              while (query.next())
              {
                  painter.drawText(400,i,query.value(0).toString());
                  painter.drawText(1350,i,query.value(1).toString());
                  painter.drawText(2300,i,query.value(2).toString());
                  painter.drawText(3400,i,query.value(3).toString());



                 i = i + 350;
              }
              QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
              QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_22_clicked()
{
    ui->tableView->setModel(cl.afficherc1());
}

void MainWindow::on_pushButton_23_clicked()
{
    ui->tableView->setModel(cl.afficherc2());
}

void MainWindow::on_pushButton_24_clicked()
{
    ui->tableView->setModel(cl.afficherc3());
}

void MainWindow::on_pushButton_25_clicked()
{
    QString str;
    str=ui->lineEdit_10->text();
    ui->tableView->setModel(cl.recherche(str));
}

void MainWindow::on_pushButton_26_clicked()
{
    ui->tableView->setModel(cl.afficher());
}

void MainWindow::on_pushButton_27_clicked()
{int s=0,test=0,converter,currenttot=0;
    ui->stackedWidget->setCurrentIndex(5);
    QSqlQuery query,query1;
    query.prepare("SELECT COUNT(*) FROM CLIENT");
        query.exec();
        if(query.first())
            s = query.value(0).toInt();

        ui->lcdNumber->display(s);
        ui->progressBar->setValue(100);

        query1.prepare("SELECT COUNT(*) FROM CLIENT where DATENAISSANCE like '%/20%'");
        query1.exec();
        if(query1.first())
            test = query1.value(0).toInt();
        ui->lcdNumber_2->display(test);
        currenttot=currenttot+test;
        converter=(int) test*100/s;
        ui->progressBar_2->setValue(converter);

        query1.prepare("SELECT COUNT(*) FROM CLIENT where DATENAISSANCE like '%/199%'");
        query1.exec();
        if(query1.first())
            test = query1.value(0).toInt();
        ui->lcdNumber_3->display(test);
        currenttot=currenttot+test;
        converter=(int) test*100/s;
        ui->progressBar_3->setValue(converter);

        query1.prepare("SELECT COUNT(*) FROM CLIENT where DATENAISSANCE like '%/198%'");
        query1.exec();
        if(query1.first())
            test = query1.value(0).toInt();
        ui->lcdNumber_4->display(test);
        currenttot=currenttot+test;
        converter=(int) test*100/s;
        ui->progressBar_4->setValue(converter);


        query1.prepare("SELECT COUNT(*) FROM CLIENT where DATENAISSANCE like '%/197%'");
        query1.exec();
        if(query1.first())
            test = query1.value(0).toInt();
        ui->lcdNumber_5->display(test);
        currenttot=currenttot+test;
        converter=(int) test*100/s;
        ui->progressBar_5->setValue(converter);

        test=s-currenttot;
        ui->lcdNumber_6->display(test);
        converter=(int) test*100/s;
        ui->progressBar_6->setValue(converter);

}


void MainWindow::on_pushButton_29_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_30_clicked()
{bool verif=false;
    QString log=ui->lineEdit_11->text();
    QString pass=ui->lineEdit_12->text();
    QSqlQuery qry;
    QMessageBox msgbox;
    if(qry.exec("select login, pass from PERSONNEL where login =  '"+log+"' and pass = '" +pass+ "' " ))
    {
        while(qry.next())
        {ui->stackedWidget->setCurrentIndex(1);
            ui->tableView_2->setModel(cl.affichermessage(log));
            msgbox.setText("welcome");
                    msgbox.exec();
                    verif=true;
        }

        if(verif==false)
        {

           msgbox.setText("id/mot de passe incorrect");
                   msgbox.exec();
        }
    }
    else
    {
        msgbox.setText("erreur req sql");
                msgbox.exec();
    }

}

void MainWindow::on_pushButton_34_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);

}

void MainWindow::on_pushButton_31_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_33_clicked()
{
    QString log=ui->lineEdit_11->text();
    QSqlQuery query;
         query.prepare("Delete from messagelist where recepteur='"+log+"'");
         query.exec();
         ui->tableView_2->setModel(cl.affichermessage(log));
}

void MainWindow::on_pushButton_32_clicked()
{   QMessageBox msgbox;
    bool verif=false;
    QString dest=ui->lineEdit_13->text();
    QString mess=ui->lineEdit_14->text();
    QString log=ui->lineEdit_11->text();
    QSqlQuery qry;
    if(qry.exec("select login from PERSONNEL where login ='"+dest+"'" ))
    {
        while(qry.next())
        { if(mess!="")
            {QSqlQuery query;
            query.prepare("INSERT INTO messagelist (emetteur, recepteur,message) "
                               "VALUES (:emetteur,:recepteur,:message)");
                 query.bindValue(":emetteur", log);
                 query.bindValue(":recepteur", dest);
                 query.bindValue(":message", mess);
                 query.exec();
                 verif=true;
                 ui->lineEdit_13->clear();
                 ui->lineEdit_14->clear();}
        }
      if(verif)
      {
          msgbox.setText("succes");
                  msgbox.exec();
                  ui->lineEdit_13->clear();
                  ui->lineEdit_14->clear();
      }
      else if((verif==false) && (mess==""))
      {
          msgbox.setText("on ne peut pas envoyer un msg vide");
                  msgbox.exec();
                  ui->lineEdit_13->clear();
                  ui->lineEdit_14->clear();
      }
      else if((verif==false) && (mess!=""))
      {
          msgbox.setText("erreur au niveau login du recepteur");
                  msgbox.exec();
                  ui->lineEdit_13->clear();
                  ui->lineEdit_14->clear();
      }
}
}

void MainWindow::on_pushButton_35_clicked()
{
    QString log=ui->lineEdit_11->text();
    ui->tableView_2->setModel(cl.affichermessage(log));
}