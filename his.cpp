/*#include "his.h"
#include <QFile>
#include <QDebug>
#include "ui_his.h"

his::his(QWidget *parent) :
    QDialog(parent),
     ui(new Ui::his)
{
    ui->setupUi(this);
    readfile();
}

his::~his()
{
    delete ui;
}
void his::readfile(){
    QString filename="C:/Users/TiTa/Desktop/Atelier_Connexion/historique.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "file doesnt exist "<<filename;
    }else{
        qDebug() << filename<<" file found...";
    }
    QString line;
    ui->history->clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            ui->history->setText(ui->history->toPlainText()+line+"\n");
            qDebug() << "linea: "<<line;
        }
    }
    file.close();
}*/
