#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "espace.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QFileDialog>
#include "connection.h"
#include <QFile>
#include <QtDebug>
#include <QPdfWriter>
#include <QSqlQuery>
#include<QtCharts>
#include<QPieSlice >
#include<QPieSeries>
#include<QPrinter>
#include<QPrintDialog>
#include "widget.h"
#include "arduino.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    espace esp;
    arduino A;
    ui->setupUi(this);

    ui->tab_esp->setModel(esp.afficher());
    ui->le_id->setValidator(new QIntValidator(0,999999999,this));

    ui->comboBox->setModel(esp.afficheroncomboact());
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





void MainWindow::on_pushButton_3_clicked()
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
        ui->comboBox->setModel(esp.afficheroncomboact());
        QMessageBox::information(nullptr, QObject::tr("success"),
                    QObject::tr("success.\n"
                                "ajout effectue."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr("ajout impossible.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }

//---------------------------------------------------------------------------------------------


void MainWindow::on_pushButton_4_clicked()
{

    espace esp;
        int idd=ui->comboBox->currentText().toInt();
        bool test=esp.supprimer(idd);
         ui->comboBox->setModel(esp.afficheroncomboact());
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

//---------------------------------------------------------------------------------------------
void MainWindow::on_pushButton_clicked()
{

    espace esp;
    ui->tab_esp->setModel(esp.afficher());

    ui->comboBox->setModel(esp.afficheroncomboact());


}
//---------------------------------------------------------------------------------------------
void MainWindow::on_pushButton_2_clicked()
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
//---------------------------------------------------------------------------------------------
void MainWindow::on_pushButton_modifier_clicked()
{

    espace esp;
    int idd=ui->le_id->text().toInt();
    int codepostale =ui->le_codepostale->text().toInt();
    QString nom=ui->le_nom->text();
    QString adresse=ui->le_adresse->text();
    QString ville=ui->le_ville->text();
    espace E (idd,codepostale,nom,adresse,ville);


        bool test=E.modifier(E.getid(),E.getcodepostale(),E.getnom(),E.getadresse(),E.getville());

        QMessageBox msgBox;

        if (test)
        {
            n.notification_modifier();
            QMessageBox::information(this, QObject::tr("Modification Succes"),
                               QObject::tr("Modifications avec Succes"), QMessageBox::Cancel);
            ui->tab_esp->setModel(esp.afficher());


        }
        else
        {

            QMessageBox::critical(this, QObject::tr("Modification Errer"),
                               QObject::tr("Echec de Modification!!!\n""Veuillez remplir tous le champs"), QMessageBox::Cancel);
        }
}
//---------------------------------------------------------------------------------------------

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->comboBox->currentText();
}

//---------------------------------------------------------------------------------------------
void MainWindow::on_pushButton_6_clicked()
{
    QTableView *table;
               table = ui->tab_esp;

               QString filters("CSV files (.csv);;All files (.*)");
               QString defaultFilter("CSV files (*.csv)");
               QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                  filters, &defaultFilter);
               QFile file(fileName);

               QAbstractItemModel *model =  table->model();
               if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                   QTextStream data(&file);
                   QStringList strList;
                   for (int i = 0; i < model->columnCount(); i++) {
                       if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                           strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") << "\n";
                   for (int i = 0; i < model->rowCount(); i++) {
                       strList.clear();
                       for (int j = 0; j < model->columnCount(); j++) {

                           if (model->data(model->index(i, j)).toString().length() > 0)
                               strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(";") + "\n";
                   }
                   file.close();
                   QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
               }
}
//---------------------------------------------------------------------------------------------
void MainWindow::on_le_recherche_textChanged()
{
    espace esp;
    QString rech=ui->le_recherche->text();
    ui->tab_esp->setModel(esp.Rechercheesp(rech));
}
//---------------------------------------------------------------------------------------------

void MainWindow::on_SSS_activated()
{
    if(ui->SSS->currentText()=="Tri par IDD")
    {
        espace esp;
        ui->tab_esp->setModel(esp.trierespParID());

    }
    }
//---------------------------------------------------------------------------------------------
void MainWindow::on_pushButton_7_clicked()
{
    QPdfWriter pdf("C:\\Users\\jordi\\Desktop\\PDF_espace.pdf");

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


//---------------------------------------------------------------------------------------------
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


//---------------------------------------------------------------------------------------------

void MainWindow::on_tab_esp_clicked(const QModelIndex &index)
{

    ui->le_id->setText(ui->tab_esp->model()->data(ui->tab_esp->model()->index(index.row(),0)).toString());
    ui->le_codepostale->setText(ui->tab_esp->model()->data(ui->tab_esp->model()->index(index.row(),1)).toString());
    ui->le_nom->setText(ui->tab_esp->model()->data(ui->tab_esp->model()->index(index.row(),2)).toString());
    ui->le_adresse->setText(ui->tab_esp->model()->data(ui->tab_esp->model()->index(index.row(),3)).toString());
    ui->le_ville->setText(ui->tab_esp->model()->data(ui->tab_esp->model()->index(index.row(),4)).toString());
}



void MainWindow::on_pushButton_camera_clicked()
{
    Widget w ;
    w.setModal(true);
    w.exec();


}
void MainWindow::update_label()
{
    //data=A.read_from_arduino();
}

/*void MainWindow::on_pushButton_camera_2_clicked()
{


         ui->tab_esp->setModel(E1.salaire1());


        QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("calcul effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
}*/

/*void MainWindow::on_lcdNumber_overflow()
{
    
}*/


