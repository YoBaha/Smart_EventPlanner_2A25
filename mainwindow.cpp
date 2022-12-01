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
#include "arduino.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    series=new QPieSeries();
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
        ui->stackedWidget->setCurrentIndex(1);
        msgbox.setText("welcome");
                msgbox.exec();

}else if (data=="0"){

       msgbox.setText("wrong card\n");
               msgbox.exec();







}


}

void MainWindow::on_pushButton_40_clicked()
{  A.write_to_arduino("1");
    do
    {
        A.serial->waitForReadyRead() ;
    }
    while(A.serial->bytesAvailable()!=11) ;
    data=A.read_from_arduino();
    qDebug() << data;


}

void MainWindow::on_pushButton_41_clicked()
{

        data=A.read_from_arduino();


       if(data=="1")
         {
            ui->stackedWidget->setCurrentIndex(5);
      /*     QString ch="a306ef11";
           qDebug()<<ch;
          int k=ch.toInt();
           juje j;
    query
           query->prepare("SELECT * FROM jugeee WHERE (identifiant  LIKE "+k+")");

          // model->setQuery("SELECT* FROM jugeee");

           //model->setQuery(*query);

           query->exec();

           if(query->exec()){
           model->setQuery(*query);
           table->setModel(model);


           table->show();
           }

                if(query->numRowsAffected()==0){

              QMessageBox::warning(nullptr, QObject::tr("database is open"),
                       QObject::tr("juge introvale .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


         }}*/

    }else if (data=="0"){

           QMessageBox::warning(nullptr, QObject::tr("database is open"),
                    QObject::tr("EURREUR .\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);







    }
}
