#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "client.h"
#include <QTcpSocket>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QtCharts>
#include<Personnel.h>
#include"smtp.h"
#include <QStackedWidget>
#include <QtGui>
#include<QtWidgets/QMainWindow>
#include <QMainWindow>
#include <QDebug>
#include <QSslSocket>
#include <QMainWindow>
#include <QVariant>
#include <partenaire.h>
#include <QMainWindow>
#include <QPainter>
//#include <QPrinter>
//#include <QPrintPreviewDialog>
#include <QTextEdit>
#include "arduino.h"

#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include "espace.h"




#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include "espace.h"
#include "notification.h"
#include "evenement.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
       client cl;
       QSortFilterProxyModel *proxy;
private slots:
       void update_label2();
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_49_clicked();

    void on_qrcodegen_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_51_clicked();
    void browse();
        void sendMail();
        void mailSent(QString status);

        void on_pushButton_53_clicked();

        void on_pushButton_55_clicked();

        void on_pushButton_60_clicked();

        void on_pushButton_58_clicked();

        void on_pushButton_61_clicked();

        void on_pushButton_62_clicked();

        void on_pushButton_63_clicked();

        void on_pushButton_52_clicked();

        void on_pushButton_54_clicked();

        void on_pushButton_57_clicked();

        void on_pushButton_59_clicked();

        void on_pushButton_64_clicked();

        void on_pushButton_41_clicked();

        void on_pushButton_42_clicked();

        void on_pushButton_65_clicked();
        void update_label();
        void on_pb_ajouter_clicked();

        void on_bp_supp_clicked();

        void on_pb_modf_2_clicked();

        void on_pb_tri_clicked();
        void on_pb_recherche_clicked();

        void on_pdf_bo_clicked();

        void on_pb_envoyer_clicked();
        void on_pb_his_clicked();
        void on_pushButton_66_clicked();

        /*********************************ESPACE******************************************/


                void on_pushButton_ajouter_clicked();

                void on_pushButton_modifier_clicked();

                void on_pushButton_afficher_clicked();

                void on_pushButton_PDF_clicked();

                void on_le_recherche_textChanged();

                void on_pushButton_camera_clicked();

                void on_SSS_activated();

                void on_pushButton_68_clicked();

                void on_statistique_clicked();



                /***********************************************************************/


                void on_pushButton_69_clicked();

                void on_pushButton_73_clicked();

                void on_pushButton_70_clicked();

                void on_pushButton_71_clicked();

                void on_pushButton_72_clicked();

                void on_pb_pdf_clicked();

                void on_pushButton_ajout20_clicked();

                void on_pushButton_74_clicked();

private:
    Personnel E;
    Ui::MainWindow *ui;
    QTcpSocket *mSocket;
    QPieSeries *series;
    /*QChart *chart;
    QChartView  *chartview;*/
    QStringList files;
    partenaire ptmp;
    QByteArray data;
    Arduino A;
    Smtp *smtp;
    notification n;
    QWidget Widget;
    Evenement tmp ;

};

#endif // MAINWINDOW_H
