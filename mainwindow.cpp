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
#include <dumessengerserver.h>
#include <dumessengersocket.h>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTextStream>
#include <QProcess>
#include "widget.h"
#include "connectdialog.h"
#include <QApplication>
#include <QDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QtCharts>

#include <QMessageBox>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QDataStream>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QDesktopServices>
#include <QUrl>
#include "partenaire.h"
#include "smtp.h"
#include"connection.h"
#include"QrCode.hpp"
#include "arduino.h"
using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    series=new QPieSeries();

    //arduino.
        int ret=A.connect_arduino();
            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
            }
             QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
        // end arduino
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
ui->tableView_3->setModel(ptmp.afficher());

    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("stats");
    series->setLabelsVisible(true);

    QChartView  *chartview= new QChartView(chart);
    chartview->setParent(ui->horizontalFrame);
    //
    //
    //begin tcp
   QTcpSocket *mSocket=new QTcpSocket(this);
   connect (mSocket, &QTcpSocket::readyRead, [&]() {
   QTextStream T(mSocket) ;
   auto text = T.readAll();
   });
   mSocket->connectToHost("localhost",320,QIODevice::ReadWrite);

        // end tcp
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
    qreal convch;
    ui->stackedWidget->setCurrentIndex(5);
    //begin piechart
series->clear();
series->setLabelsVisible(true);


    //end piechart
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
        convch=(qreal)360*test/s;
        series->append("2000",convch);

        query1.prepare("SELECT COUNT(*) FROM CLIENT where DATENAISSANCE like '%/199%'");
        query1.exec();
        if(query1.first())
            test = query1.value(0).toInt();
        ui->lcdNumber_3->display(test);
        currenttot=currenttot+test;
        converter=(int) test*100/s;
        ui->progressBar_3->setValue(converter);
        convch=(qreal)360*test/s;
        series->append("1990",convch);

        query1.prepare("SELECT COUNT(*) FROM CLIENT where DATENAISSANCE like '%/198%'");
        query1.exec();
        if(query1.first())
            test = query1.value(0).toInt();
        ui->lcdNumber_4->display(test);
        currenttot=currenttot+test;
        converter=(int) test*100/s;
        ui->progressBar_4->setValue(converter);
        convch=(qreal)360*test/s;
        series->append("1980",convch);

        query1.prepare("SELECT COUNT(*) FROM CLIENT where DATENAISSANCE like '%/197%'");
        query1.exec();
        if(query1.first())
            test = query1.value(0).toInt();
        ui->lcdNumber_5->display(test);
        currenttot=currenttot+test;
        converter=(int) test*100/s;
        ui->progressBar_5->setValue(converter);
        convch=(qreal)360*test/s;
        series->append("1970",convch);

        test=s-currenttot;
        ui->lcdNumber_6->display(test);
        converter=(int) test*100/s;
        ui->progressBar_6->setValue(converter);
        convch=(qreal)360*test/s;
        series->append("others",convch);


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
        {ui->stackedWidget->setCurrentIndex(8);
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
    ui->stackedWidget->setCurrentIndex(7);

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

void MainWindow::on_pushButton_38_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);

}

void MainWindow::on_pushButton_37_clicked()
{
    QTextStream t(mSocket);
        t << ui->lineEdit_11->text() << ":" << ui->lineEdit_15->text();
        mSocket -> flush();
        ui->lineEdit_15->clear();
}

void MainWindow::on_pushButton_39_clicked()
{    mSocket=new QTcpSocket(this);
     connect(mSocket,&QTcpSocket::readyRead, [&](){
         QTextStream t(mSocket);
         auto text=t.readAll();
         ui->textEdit->append(text);
     });
    /*connectdialog d(this);
    d.exec();
    if(d.exec()==QDialog::Rejected){
        return ;
    }
    mSocket->connectToHost(d.hostname(), d.port());*/
      mSocket->connectToHost("localhost", 3333);
}

void MainWindow::on_pushButton_40_clicked()
{
    bool verif=false;
        QString log=ui->lineEdit_11->text();
        QSqlQuery qry;
        QMessageBox msgbox;
        if(log=="")
        {
            ui->stackedWidget->setCurrentIndex(1);
            verif=true;
        }
        else if(qry.exec("select role from PERSONNEL where login =  '"+log+"' " ))
        {
            while(qry.next())
            {   if((qry.value(0)=="") || (qry.value(0)=="rh"))
                {ui->stackedWidget->setCurrentIndex(1);
                        verif=true;}
            }

            if(verif==false)
            {

               msgbox.setText("droits d acces non donnés");
                       msgbox.exec();
            }
        }
        else
        {
            msgbox.setText("erreur req sql");
                    msgbox.exec();
        }

}

void MainWindow::on_pushButton_43_clicked()
{   bool verif=false;
    QString log=ui->lineEdit_11->text();
    QSqlQuery qry;
    QMessageBox msgbox;
    if(log=="")
    {
        ui->stackedWidget->setCurrentIndex(9);
        ui->stackedWidget_2->show();
        verif=true;
    }
    else if(qry.exec("select role from PERSONNEL where login =  '"+log+"' " ))
    {
        while(qry.next())
        {   if((qry.value(0)=="") || (qry.value(0)=="part"))
            {    ui->stackedWidget->setCurrentIndex(9);
                ui->stackedWidget_2->show();
                    verif=true;}
        }

        if(verif==false)
        {

           msgbox.setText("droits d acces non donnés");
                   msgbox.exec();
        }
    }
    else
    {
        msgbox.setText("erreur req sql");
                msgbox.exec();
    }


}

void MainWindow::on_pushButton_44_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void MainWindow::on_pushButton_45_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void MainWindow::on_pushButton_46_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

void MainWindow::on_pushButton_47_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}

void MainWindow::on_pushButton_48_clicked()
{

}

void MainWindow::on_pushButton_49_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    ui->stackedWidget_2->hide();
}

void MainWindow::on_qrcodegen_clicked()
{
    int tabeq=ui->tableView_3->currentIndex().row();
               QVariant idd=ui->tableView_3->model()->data(ui->tableView_3->model()->index(tabeq,0));
               QString id= idd.toString();
               QSqlQuery qry;
               qry.prepare("select * from PARTENAIRE where IDP=:id");
               qry.bindValue(":IDP",id);
               qry.exec();
                  QString nomp, amp, nump, adp, ofrp;

               while(qry.next()){


                   nomp=qry.value(2).toString();
                   amp=qry.value(3).toString();
                   nump=qry.value(4).toString();
                   adp=qry.value(5).toString();
                   ofrp=qry.value(6).toString();


               }


                      id="NOMP:"+nomp+"AMP:"+amp+"NUMP:"+nump+"ADP:"+adp+"OFRP:"+ofrp;
               QrCode qr = QrCode::encodeText(id.toUtf8().constData(), QrCode::Ecc::HIGH);

               // Read the black & white pixels
               QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
               for (int y = 0; y < qr.getSize(); y++) {
                   for (int x = 0; x < qr.getSize(); x++) {
                       int color = qr.getModule(x, y);  // 0 for white, 1 for black

                       // You need to modify this part
                       if(color==0)
                           im.setPixel(x, y,qRgb(254, 254, 254));
                       else
                           im.setPixel(x, y,qRgb(0, 0, 0));
                   }
               }
               im=im.scaled(200,200);
               ui->qrcodecommande->setPixmap(QPixmap::fromImage(im));
}

void MainWindow::on_pushButton_50_clicked()
{
    QPdfWriter pdf("mypdf.pdf");

           QPainter painter(&pdf);
           int i = 4000;
          painter.setPen(Qt::black);
          painter.setFont(QFont("Time New Roman", 25));
          painter.drawText(3000,1400,"Liste Des Partenaires Disponibles");
          painter.setPen(Qt::black);
         painter.setFont(QFont("Time New Roman", 15));
         painter.drawRect(100,100,9400,2500);
        painter.drawRect(100,3000,9400,500);
          painter.setFont(QFont("Time New Roman", 9));
          painter.drawText(400,3300,"ID");
          painter.drawText(1000,3300,"NOM");
           painter.drawText(2200,3300,"NUM TLP");
         painter.drawText(3400,3300,"Offre");
         painter.drawText(5900,3300,"Adresse Mail");
         painter.drawText(8100,3300,"Adresse Physique");

                      painter.drawRect(100,3000,9400,9000);

                      QSqlQuery query;
                      query.prepare("select * from PARTENAIRE");
                      query.exec();
                      while (query.next())
                      {
                          painter.drawText(400,i,query.value(0).toString());
                          painter.drawText(1000,i,query.value(1).toString());
                          painter.drawText(2300,i,query.value(2).toString());
                          painter.drawText(3400,i,query.value(3).toString());
                          painter.drawText(5900,i,query.value(4).toString());
                          painter.drawText(8100,i,query.value(5).toString());



                         i = i + 350;
                      }
                      QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                      QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_51_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

//MAILING
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( """ + QFileInfo(file).fileName() + "" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("yassine.shimi02@gmail.com",ui->mail_pass->text(), "smtp.gmail.com");
    //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("yassine.shimi02@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("yassine.shimi@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

void MainWindow::on_pushButton_53_clicked()
{
    int id=ui->supprimer_part->text().toInt();
    bool test=ptmp.supprimer(id);
    if(test){
        ui->tableView_3->setModel(ptmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("success"),tr("Suppression Effectuée Avec Success"));
    }
    else {

        QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Suppression Non Effectuée!!"));
    }

}

void MainWindow::on_pushButton_55_clicked()
{
    QString nomp;
        QString amp;
        QString nump;
        QString adp;
        QString ofrp;
        int idp ;

    nomp=ui->nom_part->text();
    amp=ui->adm_part->text();
    nump=ui->num_part->text();
    adp=ui->adrs_part->text();
    ofrp=ui->offre_part->text();
    idp=ui->id_part->text().toInt();
    partenaire p(nomp,amp,nump,adp,ofrp,idp);

    if(nomp.isEmpty() || amp.isEmpty() || nump.isEmpty() || adp.isEmpty() || ofrp.isEmpty())
                     {
                         QMessageBox::critical(0,qApp->tr("ERREUR"),qApp->tr("veillez remplir les champs vides."),QMessageBox::Cancel);
                     }
    else{
    bool test= p.ajouter();
        if(test){
            ui->tableView_3->setModel(ptmp.afficher());
            QMessageBox::information(nullptr,QObject::tr("Enregistrer"),tr("Ajout Effectué Avec Success"));
        }
        else
        {     QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Ajout Non Effectué!!"));
        }}
}

void MainWindow::on_pushButton_60_clicked()
{
    QString id=ui->rech_part->text();
    ui->tableView_3->setModel(ptmp.chercher_part(id));
}

void MainWindow::on_pushButton_58_clicked()
{
    partenaire p;
    ui->tableView->setModel(ptmp.triA());

}

void MainWindow::on_pushButton_61_clicked()
{
    partenaire p;
    ui->tableView->setModel(ptmp.triD());

}

void MainWindow::on_pushButton_62_clicked()
{
    QString nomp;
        QString amp;
        QString nump;
        QString adp;
        QString ofrp;
        //int idp ;

    nomp=ui->nom_part_2->text();
    amp=ui->adm_part_2->text();
    nump=ui->num_part_2->text();
    adp=ui->adrs_part_2->text();
    ofrp=ui->offre_part_2->text();
    //idp=ui->id_part->text().toInt();
    int id=ui->id_part_2->text().toInt();
    partenaire p(nomp,amp,nump,adp,ofrp,id);
    bool test= p.mettre_aj(id);
    if(test){
        ui->tableView_3->setModel(p.afficher());
        QMessageBox::information(nullptr,QObject::tr("success"),tr("Modification Effectuée Avec Success"));
    }
    else
    {     QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Modification Non Effectuée!!"));
    }


}

void MainWindow::on_pushButton_63_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_pushButton_52_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_54_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_57_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_59_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pushButton_64_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_pushButton_41_clicked()
{
    bool verif=false;
        QString log=ui->lineEdit_11->text();
        QSqlQuery qry;
        QMessageBox msgbox;
        if(log=="")
        {
            ui->stackedWidget->setCurrentIndex(9);
            verif=true;
        }
        else if(qry.exec("select role from PERSONNEL where login =  '"+log+"' " ))
        {
            while(qry.next())
            {   if((qry.value(0)=="") || (qry.value(0)=="pers"))
                {    ui->stackedWidget->setCurrentIndex(9);

                        verif=true;}
            }

            if(verif==false)
            {

               msgbox.setText("droits d acces non donnés");
                       msgbox.exec();
            }
        }
        else
        {
            msgbox.setText("erreur req sql");
                    msgbox.exec();
        }
}

void MainWindow::on_pushButton_42_clicked()
{
    bool verif=false;
        QString log=ui->lineEdit_11->text();
        QSqlQuery qry;
        QMessageBox msgbox;
        if(log=="")
        {
            ui->stackedWidget->setCurrentIndex(9);
            verif=true;
        }
        else if(qry.exec("select role from PERSONNEL where login =  '"+log+"' " ))
        {
            while(qry.next())
            {   if((qry.value(0)=="") || (qry.value(0)=="espa"))
                {    ui->stackedWidget->setCurrentIndex(9);

                        verif=true;}
            }

            if(verif==false)
            {

               msgbox.setText("droits d acces non donnés");
                       msgbox.exec();
            }
        }
        else
        {
            msgbox.setText("erreur req sql");
                    msgbox.exec();
        }
}

void MainWindow::on_pushButton_65_clicked()
{
    bool verif=false;
        QString log=ui->lineEdit_11->text();
        QSqlQuery qry;
        QMessageBox msgbox;
        if(log=="")
        {
            ui->stackedWidget->setCurrentIndex(9);
            verif=true;
        }

        else if(qry.exec("select role from PERSONNEL where login =  '"+log+"' " ))
        {
            while(qry.next())
            {   if((qry.value(0)=="") || (qry.value(0)=="part"))
                {    ui->stackedWidget->setCurrentIndex(9);

                        verif=true;}
            }

            if(verif==false)
            {

               msgbox.setText("droits d acces non donnés");
                       msgbox.exec();
            }
        }
        else
        {
            msgbox.setText("erreur req sql");
                    msgbox.exec();
        }
}

void MainWindow::update_label()
{
    /*data=A.read_from_arduino();

    if(data=="1")
        qDebug() << "jngdiff";
    else
        qDebug() << "botdiff";*/
    data=A.read_from_arduino();
QMessageBox msgbox;

   if(data=="1")
     {
        ui->stackedWidget->setCurrentIndex(8);
        msgbox.setText("welcome");
                msgbox.exec();

}else if (data=="0"){

       msgbox.setText("wrong card\n");
               msgbox.exec();







}}
