#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "evenement.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_7_clicked();

      void on_pushButton_8_clicked();

      void on_pushButton_9_clicked();

      void on_pushButton_16_clicked();

      void on_pushButton_17_clicked();


private:
    Ui::MainWindow *ui;
    Evenement tmp ;
};
#endif // MAINWINDOW_H