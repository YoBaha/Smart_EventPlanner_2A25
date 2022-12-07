#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMainWindow>
#include "espace.h"
#include "notification.h"
#include "arduino.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update_label();

private slots:


    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_6_clicked();

    void on_le_recherche_textChanged();

    void on_SSS_activated();


    void on_pushButton_7_clicked();

    void on_statistique_clicked();

    void on_pushButton_modifier_clicked();

    void on_tab_esp_clicked(const QModelIndex &index);

    void on_pushButton_camera_clicked();

    void on_pushButton_camera_2_clicked();

    void on_le_recherche_cursorPositionChanged(int arg1, int arg2);

    void on_lcdNumber_overflow();
    
    void on_le_recherche_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    notification n;
 arduino A;
};

#endif // MAINWINDOW_H
