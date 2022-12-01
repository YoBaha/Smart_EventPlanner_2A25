#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QAxWidget>
#include "smtp.h"
#include"QrCode.hpp"
using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(ptmp.afficher());
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
}
 QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
 //le slot update_label suite à la reception du signal readyRead (reception des données).
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}



void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}
void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")

        ui->label_msg->setText("on"); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher msg

    else if (data=="0")

        ui->label_msg->setText("off");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher msg
}
void MainWindow::on_pushButton_8_clicked()
{
    A.write_to_arduino("1"); //envoyer 1 à arduino

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
                     A.write_to_arduino("0");  //envoyer 0 à arduino

                 }
else{
bool test= p.ajouter();
    if(test){
        ui->tableView->setModel(ptmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("Enregistrer"),tr("Ajout Effectué Avec Success"));
        A.write_to_arduino("1"); //envoyer 1 à arduino

    }
    else
    {
        A.write_to_arduino("0");  //envoyer 0 à arduino
        QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Ajout Non Effectué!!"));

    }}}
void MainWindow::on_pushButton_12_clicked()
{

int id=ui->supprimer_part->text().toInt();
bool test=ptmp.supprimer(id);
if(test){
    ui->tableView->setModel(ptmp.afficher());
    QMessageBox::information(nullptr,QObject::tr("success"),tr("Suppression Effectuée Avec Success"));
}
else {

    QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Suppression Non Effectuée!!"));
}}


void MainWindow::on_pushButton_13_clicked()
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
    ui->tableView->setModel(p.afficher());
    QMessageBox::information(nullptr,QObject::tr("success"),tr("Modification Effectuée Avec Success"));
}
else
{     QMessageBox::critical(nullptr,QObject::tr("erreur!!"),tr("Modification Non Effectuée!!"));
}
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
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("yassine.shimi02@gmail.com",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

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

//EXPORT PDF

void MainWindow::on_pushButton_18_clicked()
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

//RECHERCHE SELON ID
void MainWindow::on_pushButton_11_clicked()
{
    QString id=ui->rech_part->text();
    ui->tableView->setModel(ptmp.chercher_part(id));
}


// TRI SELON ID


void MainWindow::on_pushButton_10_clicked()
{
    partenaire p;
    ui->tableView->setModel(ptmp.triA());
}

void MainWindow::on_pushButton_19_clicked()
{
    partenaire p;
    ui->tableView->setModel(ptmp.triD());
}

void MainWindow::on_pushButton_20_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_21_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
//bouton qr code
void MainWindow::on_qrcodegen_clicked()
{
           int tableView=ui->tableView->currentIndex().row();           
          QVariant idp=ui->tableView->model()->data(ui->tableView->model()->index(tableView,0));
           QString id=idp.toString();
          // id=QString(id);
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
                id=QString(id);
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


