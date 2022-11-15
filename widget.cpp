#include "widget.h"
#include "ui_widget.h"
#include "connectdialog.h"
#include <QTcpSocket>
#include <QDialog>
widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    mSocket=new QTcpSocket(this);
    connect(mSocket,&QTcpSocket::readyRead, [&](){
        QTextStream t(mSocket);
        auto text=t.readAll();
        ui->textEdit->append(text);
    });
}

widget::~widget()
{
    delete ui;
}

void widget::on_sendb_clicked()
{
    QTextStream t(mSocket);
        t << ui->nickin->text() << ":" << ui->msgin->text();
        mSocket -> flush();
        ui->msgin->clear();
}

void widget::on_connect_clicked()
{
    connectdialog d(this);
    d.exec();
    if(d.exec()==QDialog::Rejected){
        return ;
    }
    mSocket->connectToHost(d.hostname(), d.port());

}
