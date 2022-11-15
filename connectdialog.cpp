#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QDialog>
#include<QtGui>
connectdialog::connectdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectdialog)
{
    ui->setupUi(this);
}

connectdialog::~connectdialog()
{
    delete ui;
}

void connectdialog::on_acceptbu_clicked()
{
    mHostname=ui->hostin->text();
    mPort=ui->spinBox->value();
        accept();
}

void connectdialog::on_cancelbu_clicked()
{
    reject();
}
