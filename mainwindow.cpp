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
#include<QIntValidator>
#include <QMessageBox>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QDataStream>
#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QDesktopServices>
#include <QUrl>
#include <QtConfig>
#include "partenaire.h"
#include "smtp.h"
#include"connection.h"
#include"QrCode.hpp"
#include "arduino.h"
#include"Personnel.h"
#include "evenement.h"

#include <QWidget>
#include "widget.h"


using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    series=new QPieSeries();
    ui->le_cin->setValidator(new QIntValidator(00000000, 99999999, this));
   ui->tab_Personnel->setModel(E.afficher());//return type sqlmodel
   ui->tableView_3->setModel(tmp.afficher());
   ui->lineEdit_nom->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z_ ]"),this));

   ui->lineEdit_place->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z_ ]{0,20}"),this));
   ui->lineEdit_tp->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z_ ]{0,20}"),this));
   ui->lineEdit_time->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z_ ]{0,20}"),this));
   ui->lineEdit_idc->setValidator(new QIntValidator(0,9999));
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
               //id=QString(id);
               QSqlQuery qry;
               qry.prepare("select * from PARTENAIRE");
               //qry.bindValue(":IDP",id);
               qry.exec();
                  QString nomp, amp, nump, adp, ofrp;

               while(qry.next()){


                   id=qry.value(0).toString();
                   nomp=qry.value(1).toString();
                   nump=qry.value(2).toString();
                    ofrp=qry.value(3).toString();
                     amp=qry.value(4).toString();
                     adp=qry.value(5).toString();


               }


                      id="IDP:\t" +id+ "NOMP\t:" +nomp+ "NUMP:\t" +nump+ "OFRP:\t" +ofrp+ "AMP:\t" +amp+ "ADP:\t" +adp ;
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
            ui->stackedWidget->setCurrentIndex(10);
            verif=true;
        }
        else if(qry.exec("select role from PERSONNEL where login =  '"+log+"' " ))
        {
            while(qry.next())
            {   if((qry.value(0)=="") || (qry.value(0)=="pers"))
                {    ui->stackedWidget->setCurrentIndex(10);

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
            ui->stackedWidget->setCurrentIndex(11);
            verif=true;
        }
        else if(qry.exec("select role from PERSONNEL where login =  '"+log+"' " ))
        {
            while(qry.next())
            {   if((qry.value(0)=="") || (qry.value(0)=="espa"))
                {    ui->stackedWidget->setCurrentIndex(11);

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
/*foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                                               le->clear();}
                                          QFile file("C:/Users/TiTa/Desktop/Atelier_Connexion/historique.txt");
                                          if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
                                              return;
                                          QTextStream cout(&file);
                                          QString d_info = QDateTime::currentDateTime().toString();
                                          QString message2=" + "+d_info+" A personnel has been added by cin : "+cin+"\n";
                                          cout << message2;*/

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


void MainWindow::on_pb_tri_clicked()
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
    //QPdfWriter pdf("C:/Users/TiTa/Desktop/Atelier_Connexion/personnel.pdf");
        QPdfWriter pdf("personnel.pdf");
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
//ARDUINO CAPTEUR SON
void MainWindow::update_label2()
{
    data=A.read_from_arduino();

    if(data=="1")

    ui->etat_capt2->setText("SON DETECTE");

    else if (data=="0")

        ui->etat_capt2->setText("SON NON DETECTE");
     //alors afficher msg
}

void MainWindow::on_pushButton_66_clicked()
{
     ui->stackedWidget->setCurrentIndex(8);
}
/******************************************************************************/



void MainWindow::on_pushButton_ajouter_clicked()
{
    espace esp;
    int idd=ui->le_id->text().toInt();
    int codepostale =ui->le_codepostale->text().toInt();
    QString nom=ui->le_nom->text();
    QString adresse=ui->le_adresse->text();
    QString ville=ui->le_ville->text();
    espace E (idd,codepostale,nom,adresse,ville);
    bool test=E.ajouter();
    if(test) {
        n.notification_ajout();
        ui->comboBox_supprimer->setModel(esp.afficheroncomboact());
        QMessageBox::information(nullptr, QObject::tr("success"),
                    QObject::tr("success.\n"
                                "ajout effectue."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr("ajout impossible.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}




void MainWindow::on_pushButton_modifier_clicked()
{

    espace esp;
    int idd=ui->le_id->text().toInt();
    int codepostale =ui->le_codepostale->text().toInt();
    QString nom=ui->le_nom->text();
    QString adresse=ui->le_adresse->text();
    QString ville=ui->le_ville->text();

    bool    test=esp.modifier(idd,codepostale,nom,adresse,ville);

          if (test)
          {
                  ui->tab_esp->setModel(esp.afficher());
              QMessageBox::information(nullptr,QObject::tr("OK"),
                                   QObject::tr("modification établie"),
                                   QMessageBox::Ok);}
          else{
          QMessageBox::critical(nullptr,QObject::tr("ERROR404"),
                                  QObject::tr("modification non établie"),
                                  QMessageBox::Cancel);}
}

void MainWindow::on_pushButton_afficher_clicked()
{

    espace esp;
    ui->tab_esp->setModel(esp.afficher());

    ui->comboBox_supprimer->setModel(esp.afficheroncomboact());

}

void MainWindow::on_pushButton_PDF_clicked()
{
    //QPdfWriter pdf("C:\\Users\\jordi\\Desktop\\PDF_espace.pdf");
QPdfWriter pdf("PDF_espace.pdf");
       QPainter painter(&pdf);
       int i = 4000;
              painter.setPen(Qt::red);
              painter.setFont(QFont("Time New Roman", 25));
              painter.drawText(3000,1400,"Liste Des Espaces");
              painter.setPen(Qt::black);
              painter.setFont(QFont("Time New Roman", 15));
              painter.drawRect(100,3000,9400,500);
              painter.setFont(QFont("Time New Roman", 9));
              painter.drawText(1000,3300,"Idd");
              painter.drawText(2500,3300,"Codepostal");
              painter.drawText(4000,3300,"Nom");
              painter.drawText(5500,3300,"Adresse");
              painter.drawText(7000,3300,"Ville");
              painter.drawRect(100,3000,9400,9000);

              QSqlQuery query;
              query.prepare("select * from GESTIONESPACE");
              query.exec();
              while (query.next())
              {
                  painter.drawText(1000,i,query.value(0).toString());
                  painter.drawText(2500,i,query.value(1).toString());
                  painter.drawText(4000,i,query.value(2).toString());
                  painter.drawText(5500,i,query.value(3).toString());
                  painter.drawText(7000,i,query.value(4).toString());


                 i = i + 350;
              }
              QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
              QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_le_recherche_textChanged()
{

    espace esp;
    QString rech=ui->le_recherche->text();
    ui->tab_esp->setModel(esp.Rechercheesp(rech));
}


void MainWindow::on_SSS_activated()
{
    if(ui->SSS->currentText()=="Tri par IDD")
    {
        espace esp;
        ui->tab_esp->setModel(esp.trierespParID());

    }
}

void MainWindow::on_pushButton_68_clicked()
{
    espace esp;
        int idd=ui->comboBox_supprimer->currentText().toInt();
        bool test=esp.supprimer(idd);
         ui->comboBox_supprimer->setModel(esp.afficheroncomboact());
        if (test)
        {
            n.notification_supprimer();
            ui->tab_esp->setModel(esp.afficher());
                    QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("suppression effectué\n"
                                        "click cancel to exit."), QMessageBox::Cancel);

              }
                else QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Suppression non effectué\n""click cancel to exit"), QMessageBox::Cancel);


}

void MainWindow::on_statistique_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                     model->setQuery("select * from GESTIONESPACE where codepostale < 100 ");
                     float code=model->rowCount();
                     model->setQuery("select * from GESTIONESPACE where codepostale  between 100 and 1000 ");
                     float codee=model->rowCount();
                     model->setQuery("select * from GESTIONESPACE where codepostale >1000 ");
                     float codeee=model->rowCount();
                     float total=code+codee+codeee;
                     QString a=QString("moins de 100 \t"+QString::number((code*100)/total,'f',2)+"%" );
                     QString b=QString("entre 100 et 1000 \t"+QString::number((codee*100)/total,'f',2)+"%" );
                     QString c=QString("+1000 \t"+QString::number((codeee*100)/total,'f',2)+"%" );
                     QPieSeries *series = new QPieSeries();
                     series->append(a,code);
                     series->append(b,codee);
                     series->append(c,codeee);
             if (code!=0)
             {QPieSlice *slice = series->slices().at(0);
              slice->setLabelVisible();
              slice->setPen(QPen());}
             if ( codee!=0)
             {
                      // Add label, explode and define brush for 2nd slice
                      QPieSlice *slice1 = series->slices().at(1);
                      //slice1->setExploded();
                      slice1->setLabelVisible();
             }
             if(codeee!=0)
             {
                      // Add labels to rest of slices
                      QPieSlice *slice2 = series->slices().at(2);
                      //slice1->setExploded();
                      slice2->setLabelVisible();
             }
                     // Create the chart widget
                     QChart *chart = new QChart();
                     // Add data to chart with title and hide legend
                     chart->addSeries(series);
                     chart->setTitle("Pourcentage Par Code postale :Nombre Des Espaces "+ QString::number(total));
                     chart->legend()->hide();
                     // Used to display the chart
                     QChartView *chartView = new QChartView(chart);
                     chartView->setRenderHint(QPainter::Antialiasing);
                     chartView->resize(1000,500);
                     chartView->show();



}

void MainWindow::on_pushButton_69_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}
/********************************************* events*/


void MainWindow::on_pushButton_ajout20_clicked()
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



void MainWindow::on_pushButton_73_clicked()//upd
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

void MainWindow::on_pushButton_70_clicked()//supr
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

void MainWindow::on_pushButton_71_clicked()//tri
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

void MainWindow::on_pushButton_72_clicked()//reche
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

void MainWindow::on_pb_pdf_clicked()//pdf
{
    QPdfWriter pdf("C:/Users/MSI/Desktop/New folder (2)/Atelier_Connexion - Copie (3) - Copie/evenement.pdf");

          QPainter painter(&pdf);
          int i = 4000;
                 painter.setPen(Qt::darkCyan);
                 painter.setFont(QFont("Time New Roman", 25));
                 painter.drawText(3000,1400,"Event LIST");
                 painter.setPen(Qt::black);
                 painter.setFont(QFont("Time New Roman", 15));
                 painter.drawRect(100,100,9400,2500);
                 painter.drawRect(100,3000,9400,500);
                 painter.setFont(QFont("Time New Roman", 9));
                 painter.drawText(400,3300,"id");
                 painter.drawText(1350,3300,"nomevent");
                 painter.drawText(2200,3300,"typeevent");
                 painter.drawText(2200,3300,"placeevent");
                 painter.drawText(2200,3300,"timeevent");
                 painter.drawText(2200,3300,"date_debut");
                 painter.drawText(2200,3300,"date_fin");


                 painter.drawRect(100,3000,9400,9000);

                 QSqlQuery query;
                 query.prepare("select * from evenement");
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



void MainWindow::on_pushButton_74_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_pushButton_camera_clicked()
{
    QWidget w ;
    w.show();

}
