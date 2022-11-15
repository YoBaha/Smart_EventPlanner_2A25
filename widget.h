#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
namespace Ui {
class widget;
}

class widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();

private slots:
    void on_sendb_clicked();

    void on_connect_clicked();

private:
    Ui::widget *ui;
    QTcpSocket *mSocket;
};

#endif // WIDGET_H
