#include "stat_esp.h"
#include "ui_stat_esp.h"
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QSqlQuery>

stat_esp::stat_esp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stat_esp)
{
    ui->setupUi(this);
}

stat_esp::~stat_esp()
{
    delete ui;
}
