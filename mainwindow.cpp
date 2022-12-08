#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Personnel.h"
#include"QMessageBox"
#include<QIntValidator>
#include<QSqlQuery>
#include <QPainter>
#include <QPdfWriter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtConfig>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include"smtp.h"
//#include"his.h"
//#include "ui_his.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   ui->le_cin->setValidator(new QIntValidator(00000000, 99999999, this));
  ui->tab_Personnel->setModel(E.afficher());//return type sqlmodel

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
   int cin=ui->le_cin->text().toInt();
   QString nom=ui->le_nom->text();
   QString prenom=ui->le_prenom->text();
Personnel E (cin,nom,prenom);
if(E.ajouter())
    {

        QMessageBox::information(nullptr,QObject::tr("ok"),
                              QObject::tr("Ajout effectué\n" "click cancel to exit") ,QMessageBox::Cancel);
ui->tab_Personnel->setModel(E.afficher());
 }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("Ajout non effectué .\n"
                                          "click cancel to exit ."),QMessageBox::Cancel );
foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                                               le->clear();}
                                          QFile file("C:/Users/TiTa/Desktop/Atelier_Connexion/historique.txt");
                                          if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                                              return;
                                          QTextStream cout(&file);
                                          QString d_info = QDateTime::currentDateTime().toString();
                                          QString message2=" + "+d_info+" A personnel has been added by cin : "+cin+"\n";
                                          cout << message2;

}

void MainWindow::on_bp_supp_clicked()
{
    Personnel E1; E1.setcin(ui->le_cin_supp->text().toInt());
    bool test=E1.supprimer(E1.getcin());
    QMessageBox msgBox;
    if(test)
       { msgBox.setText("Suppression avec succés");
ui->tab_Personnel->setModel(E.afficher());
    }
    else
         msgBox.setText("Echec de suppression");
    msgBox.exec();

}




void MainWindow::on_pb_modf_2_clicked()
{
    Personnel e;
   e.setcin(ui->le_cin_mod->text().toInt());
    QString nom=ui->nom_mod->text();
     QString prenom=ui->prenom_mod->text();

    bool test=e.modifier(e.getcin(),nom,prenom);

    QMessageBox msgBox;


    if(test)
    {msgBox.setText("Modification avec succés.");
    ui->tab_Personnel->setModel(e.afficher());

    }
    else msgBox.setText("Echec de modification");
    msgBox.exec();
}


void MainWindow::on_pushButton_clicked()
{
    Personnel e;
        ui->tab_tri->setModel(e.tripersonnel());
}

void MainWindow::on_pb_recherche_clicked()
{
    Personnel e;
         QString s1;
            QSqlQueryModel *model=e.recherche( ui->le_ch->text());
             ui->tab_Personnel->setModel(model);
}



void MainWindow::on_pdf_bo_clicked()
{
    QPdfWriter pdf("C:/Users/TiTa/Desktop/Atelier_Connexion/personnel.pdf");

          QPainter painter(&pdf);
          int i = 4000;
                 painter.setPen(Qt::darkCyan);
                 painter.setFont(QFont("Time New Roman", 25));
                 painter.drawText(3000,1400,"personnel LIST");
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Time New Roman", 15));
                 painter.drawRect(100,100,9400,2500);
                 painter.drawRect(100,3000,9400,500);
                 painter.setFont(QFont("Time New Roman", 9));
                 painter.drawText(400,3300,"cin");
                 painter.drawText(1350,3300,"nom");
                 painter.drawText(2200,3300,"prenom");
                 painter.drawRect(100,3000,9400,9000);

                 QSqlQuery query;
                 query.prepare("select * from personnel");
                 query.exec();
                 while (query.next())
                 {
                     painter.drawText(400,i,query.value(0).toString());
                     painter.drawText(1350,i,query.value(1).toString());
                     painter.drawText(2300,i,query.value(2).toString());
                     painter.drawText(3400,i,query.value(3).toString());
                     painter.drawText(4400,i,query.value(4).toString());
                     painter.drawText(6200,i,query.value(5).toString());




                    i = i + 350;
                 }
                 QMessageBox::information(this, QObject::tr("PDF Saved Successfuly!"),
                 QObject::tr("PDF Saved Successfuly!.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pb_envoyer_clicked()
{
    { smtp = new Smtp("plannerevent990@gmail.com" , "eventplanner123", "smtp.esprit.tn",465);
               connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

               QString msg=ui->plainTextEdit->toPlainText();

               smtp->sendMail("siwar_test",ui->lineEdit_ad->text(),ui->lineEdit_obj->text(),msg);

               QMessageBox::information(nullptr, QObject::tr("SENT"),
                                        QObject::tr("Email Sent Successfully.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

}
/*void MainWindow::on_pb_his_clicked()
{
    his *His=new his(this);
                        His->show();
                        his m;
                      m.readfile();
}*/
