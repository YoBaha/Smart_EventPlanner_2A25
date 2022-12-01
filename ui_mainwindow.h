/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QFrame *line;
    QLineEdit *lineEdit;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_18;
    QPushButton *pushButton_20;
    QPushButton *pushButton_5;
    QWidget *page_6;
    QPushButton *pushButton_21;
    QLineEdit *rcpt;
    QLineEdit *subject;
    QLineEdit *file;
    QPushButton *browseBtn;
    QTextEdit *msg;
    QPushButton *sendBtn;
    QLineEdit *mail_pass;
    QLabel *label;
    QWidget *page_5;
    QLineEdit *lineEdit_13;
    QLineEdit *supprimer_part;
    QPushButton *pushButton_12;
    QPushButton *pushButton_14;
    QWidget *page_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *nom_part;
    QLineEdit *adm_part;
    QLineEdit *offre_part;
    QLineEdit *adrs_part;
    QLineEdit *num_part;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLineEdit *lineEdit_15;
    QLineEdit *id_part;
    QPushButton *pushButton_15;
    QPushButton *qrcodegen;
    QLabel *qrcodecommande;
    QLabel *label_msg;
    QWidget *page_3;
    QPushButton *pushButton_10;
    QPushButton *pushButton_16;
    QTableView *tableView;
    QPushButton *pushButton_11;
    QLineEdit *rech_part;
    QPushButton *pushButton_19;
    QWidget *page_4;
    QLineEdit *lineEdit_17;
    QPushButton *pushButton_13;
    QPushButton *pushButton_17;
    QLineEdit *nom_part_2;
    QLineEdit *num_part_2;
    QLineEdit *offre_part_2;
    QLineEdit *adm_part_2;
    QLineEdit *adrs_part_2;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_12;
    QLineEdit *id_part_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 466);
        MainWindow->setStyleSheet(QStringLiteral("background-image: url(:/backg.png);"));
        MainWindow->setIconSize(QSize(31, 44));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(-10, 0, 871, 501));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        pushButton = new QPushButton(page);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 130, 121, 41));
        pushButton->setStyleSheet(QLatin1String("QPushButton{\n"
"	background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 12px;\n"
"font: 87 italic 8pt \"Segoe UI Black\";\n"
"}"));
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 210, 121, 41));
        pushButton_2->setStyleSheet(QLatin1String("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 12px;\n"
"font: 87 italic 8pt \"Segoe UI Black\";\n"
"}"));
        pushButton_3 = new QPushButton(page);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 300, 121, 41));
        pushButton_3->setStyleSheet(QLatin1String("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 12px;\n"
"font: 87 italic 8pt \"Segoe UI Black\";\n"
"}"));
        pushButton_4 = new QPushButton(page);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(30, 380, 121, 41));
        pushButton_4->setStyleSheet(QLatin1String("QPushButton{\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 12px;\n"
"font: 87 italic 8pt \"Segoe UI Black\";\n"
"}"));
        line = new QFrame(page);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(170, 60, 16, 381));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        lineEdit = new QLineEdit(page);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(170, 50, 201, 31));
        lineEdit->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"color: rgb(0,0,0);\n"
"border-radius: 12px;\n"
"font: 997 italic 14pt \"Segoe UI Black\";\n"
""));
        lineEdit->setReadOnly(true);
        pushButton_6 = new QPushButton(page);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(390, 230, 121, 41));
        pushButton_6->setStyleSheet(QLatin1String("QPushButton{\n"
"qproperty-icon: url(:/lc.png);\n"
"qproperty-iconSize: 17px 17px;\n"
"text-align: center;\n"
"color:red;\n"
"}"));
        pushButton_7 = new QPushButton(page);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(460, 290, 141, 41));
        pushButton_7->setStyleSheet(QLatin1String("QPushButton{\n"
"qproperty-icon: url(:/quit-icon.png);\n"
"qproperty-iconSize: 17px 17px;\n"
"text-align: center;\n"
"color:red;\n"
"}"));
        pushButton_18 = new QPushButton(page);
        pushButton_18->setObjectName(QStringLiteral("pushButton_18"));
        pushButton_18->setGeometry(QRect(260, 230, 111, 41));
        pushButton_18->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/pdf.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_18->setIcon(icon);
        pushButton_20 = new QPushButton(page);
        pushButton_20->setObjectName(QStringLiteral("pushButton_20"));
        pushButton_20->setGeometry(QRect(540, 230, 121, 41));
        pushButton_20->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/mail.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_20->setIcon(icon1);
        pushButton_5 = new QPushButton(page);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(290, 290, 141, 41));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/arduino-icon-28.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon2);
        stackedWidget->addWidget(page);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        pushButton_21 = new QPushButton(page_6);
        pushButton_21->setObjectName(QStringLiteral("pushButton_21"));
        pushButton_21->setGeometry(QRect(30, 20, 121, 28));
        pushButton_21->setStyleSheet(QLatin1String("color: rgb(170, 0, 0);\n"
"border-radius: 12px;\n"
"font: 9pt \"Rockwell\";"));
        rcpt = new QLineEdit(page_6);
        rcpt->setObjectName(QStringLiteral("rcpt"));
        rcpt->setGeometry(QRect(70, 110, 421, 31));
        rcpt->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        subject = new QLineEdit(page_6);
        subject->setObjectName(QStringLiteral("subject"));
        subject->setGeometry(QRect(70, 150, 551, 31));
        file = new QLineEdit(page_6);
        file->setObjectName(QStringLiteral("file"));
        file->setGeometry(QRect(70, 190, 421, 31));
        browseBtn = new QPushButton(page_6);
        browseBtn->setObjectName(QStringLiteral("browseBtn"));
        browseBtn->setGeometry(QRect(500, 190, 71, 31));
        msg = new QTextEdit(page_6);
        msg->setObjectName(QStringLiteral("msg"));
        msg->setGeometry(QRect(70, 230, 641, 181));
        sendBtn = new QPushButton(page_6);
        sendBtn->setObjectName(QStringLiteral("sendBtn"));
        sendBtn->setGeometry(QRect(350, 420, 93, 28));
        mail_pass = new QLineEdit(page_6);
        mail_pass->setObjectName(QStringLiteral("mail_pass"));
        mail_pass->setGeometry(QRect(380, 60, 221, 22));
        mail_pass->setEchoMode(QLineEdit::Password);
        label = new QLabel(page_6);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 60, 181, 21));
        label->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 75 italic 9pt \"Rockwell\";"));
        stackedWidget->addWidget(page_6);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        lineEdit_13 = new QLineEdit(page_5);
        lineEdit_13->setObjectName(QStringLiteral("lineEdit_13"));
        lineEdit_13->setGeometry(QRect(150, 230, 271, 41));
        lineEdit_13->setReadOnly(true);
        supprimer_part = new QLineEdit(page_5);
        supprimer_part->setObjectName(QStringLiteral("supprimer_part"));
        supprimer_part->setGeometry(QRect(420, 230, 171, 41));
        pushButton_12 = new QPushButton(page_5);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(310, 290, 211, 28));
        pushButton_14 = new QPushButton(page_5);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(20, 10, 121, 28));
        pushButton_14->setStyleSheet(QLatin1String("color: rgb(170, 0, 0);\n"
"border-radius: 12px;\n"
"font: 9pt \"Rockwell\";"));
        stackedWidget->addWidget(page_5);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        lineEdit_3 = new QLineEdit(page_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(50, 270, 151, 22));
        lineEdit_3->setReadOnly(true);
        lineEdit_4 = new QLineEdit(page_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(50, 100, 151, 22));
        lineEdit_4->setReadOnly(true);
        lineEdit_5 = new QLineEdit(page_2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(50, 150, 151, 22));
        lineEdit_5->setReadOnly(true);
        lineEdit_6 = new QLineEdit(page_2);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(50, 330, 151, 22));
        lineEdit_6->setReadOnly(true);
        lineEdit_7 = new QLineEdit(page_2);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(50, 210, 151, 22));
        lineEdit_7->setReadOnly(true);
        nom_part = new QLineEdit(page_2);
        nom_part->setObjectName(QStringLiteral("nom_part"));
        nom_part->setGeometry(QRect(220, 100, 191, 22));
        nom_part->setStyleSheet(QStringLiteral(""));
        adm_part = new QLineEdit(page_2);
        adm_part->setObjectName(QStringLiteral("adm_part"));
        adm_part->setGeometry(QRect(220, 150, 191, 21));
        offre_part = new QLineEdit(page_2);
        offre_part->setObjectName(QStringLiteral("offre_part"));
        offre_part->setGeometry(QRect(220, 330, 191, 51));
        adrs_part = new QLineEdit(page_2);
        adrs_part->setObjectName(QStringLiteral("adrs_part"));
        adrs_part->setGeometry(QRect(220, 270, 191, 41));
        num_part = new QLineEdit(page_2);
        num_part->setObjectName(QStringLiteral("num_part"));
        num_part->setGeometry(QRect(220, 210, 191, 21));
        pushButton_8 = new QPushButton(page_2);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(590, 410, 93, 28));
        pushButton_9 = new QPushButton(page_2);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(690, 410, 93, 28));
        lineEdit_15 = new QLineEdit(page_2);
        lineEdit_15->setObjectName(QStringLiteral("lineEdit_15"));
        lineEdit_15->setGeometry(QRect(50, 400, 151, 22));
        lineEdit_15->setReadOnly(true);
        id_part = new QLineEdit(page_2);
        id_part->setObjectName(QStringLiteral("id_part"));
        id_part->setGeometry(QRect(220, 400, 191, 22));
        pushButton_15 = new QPushButton(page_2);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        pushButton_15->setGeometry(QRect(20, 10, 121, 28));
        pushButton_15->setStyleSheet(QLatin1String("color: rgb(170, 0, 0);\n"
"border-radius: 12px;\n"
"font: 9pt \"Rockwell\";"));
        qrcodegen = new QPushButton(page_2);
        qrcodegen->setObjectName(QStringLiteral("qrcodegen"));
        qrcodegen->setGeometry(QRect(490, 340, 121, 41));
        qrcodegen->setStyleSheet(QLatin1String("QPushButton{\n"
"qproperty-icon: url(:/str.png);\n"
"qproperty-iconSize: 17px 17px;\n"
"text-align: center;\n"
"color:red;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/str.png"), QSize(), QIcon::Normal, QIcon::Off);
        qrcodegen->setIcon(icon3);
        qrcodecommande = new QLabel(page_2);
        qrcodecommande->setObjectName(QStringLiteral("qrcodecommande"));
        qrcodecommande->setEnabled(true);
        qrcodecommande->setGeometry(QRect(450, 130, 200, 200));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qrcodecommande->sizePolicy().hasHeightForWidth());
        qrcodecommande->setSizePolicy(sizePolicy);
        qrcodecommande->setMinimumSize(QSize(200, 200));
        qrcodecommande->setMaximumSize(QSize(200, 200));
        label_msg = new QLabel(page_2);
        label_msg->setObjectName(QStringLiteral("label_msg"));
        label_msg->setGeometry(QRect(510, 410, 63, 20));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        pushButton_10 = new QPushButton(page_3);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(340, 370, 141, 41));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/haut.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_10->setIcon(icon4);
        pushButton_16 = new QPushButton(page_3);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        pushButton_16->setGeometry(QRect(20, 20, 121, 28));
        pushButton_16->setStyleSheet(QLatin1String("color: rgb(170, 0, 0);\n"
"border-radius: 12px;\n"
"font: 9pt \"Rockwell\";"));
        tableView = new QTableView(page_3);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(170, 70, 461, 281));
        tableView->setStyleSheet(QStringLiteral("background-image: url(:/bckg2.jpg);"));
        pushButton_11 = new QPushButton(page_3);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(170, 370, 141, 41));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/rech.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_11->setIcon(icon5);
        rech_part = new QLineEdit(page_3);
        rech_part->setObjectName(QStringLiteral("rech_part"));
        rech_part->setGeometry(QRect(190, 420, 101, 22));
        rech_part->setStyleSheet(QStringLiteral("color: rgb(85, 85, 127);"));
        pushButton_19 = new QPushButton(page_3);
        pushButton_19->setObjectName(QStringLiteral("pushButton_19"));
        pushButton_19->setGeometry(QRect(500, 370, 141, 41));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/bas.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_19->setIcon(icon6);
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        lineEdit_17 = new QLineEdit(page_4);
        lineEdit_17->setObjectName(QStringLiteral("lineEdit_17"));
        lineEdit_17->setGeometry(QRect(180, 70, 251, 41));
        lineEdit_17->setReadOnly(true);
        pushButton_13 = new QPushButton(page_4);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(320, 410, 141, 31));
        pushButton_17 = new QPushButton(page_4);
        pushButton_17->setObjectName(QStringLiteral("pushButton_17"));
        pushButton_17->setGeometry(QRect(20, 20, 121, 28));
        pushButton_17->setStyleSheet(QLatin1String("color: rgb(170, 0, 0);\n"
"border-radius: 12px;\n"
"font: 9pt \"Rockwell\";"));
        nom_part_2 = new QLineEdit(page_4);
        nom_part_2->setObjectName(QStringLiteral("nom_part_2"));
        nom_part_2->setGeometry(QRect(400, 160, 191, 22));
        nom_part_2->setStyleSheet(QStringLiteral(""));
        num_part_2 = new QLineEdit(page_4);
        num_part_2->setObjectName(QStringLiteral("num_part_2"));
        num_part_2->setGeometry(QRect(400, 220, 191, 21));
        offre_part_2 = new QLineEdit(page_4);
        offre_part_2->setObjectName(QStringLiteral("offre_part_2"));
        offre_part_2->setGeometry(QRect(400, 300, 191, 51));
        adm_part_2 = new QLineEdit(page_4);
        adm_part_2->setObjectName(QStringLiteral("adm_part_2"));
        adm_part_2->setGeometry(QRect(400, 190, 191, 21));
        adrs_part_2 = new QLineEdit(page_4);
        adrs_part_2->setObjectName(QStringLiteral("adrs_part_2"));
        adrs_part_2->setGeometry(QRect(400, 250, 191, 41));
        lineEdit_8 = new QLineEdit(page_4);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(230, 160, 141, 22));
        lineEdit_9 = new QLineEdit(page_4);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(230, 190, 141, 22));
        lineEdit_10 = new QLineEdit(page_4);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        lineEdit_10->setGeometry(QRect(230, 220, 141, 22));
        lineEdit_11 = new QLineEdit(page_4);
        lineEdit_11->setObjectName(QStringLiteral("lineEdit_11"));
        lineEdit_11->setGeometry(QRect(230, 260, 141, 22));
        lineEdit_12 = new QLineEdit(page_4);
        lineEdit_12->setObjectName(QStringLiteral("lineEdit_12"));
        lineEdit_12->setGeometry(QRect(230, 300, 141, 22));
        id_part_2 = new QLineEdit(page_4);
        id_part_2->setObjectName(QStringLiteral("id_part_2"));
        id_part_2->setGeometry(QRect(430, 70, 161, 41));
        stackedWidget->addWidget(page_4);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_9, SIGNAL(clicked()), id_part, SLOT(clear()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), nom_part, SLOT(clear()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), num_part, SLOT(clear()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), adrs_part, SLOT(clear()));
        QObject::connect(pushButton_7, SIGNAL(clicked()), stackedWidget, SLOT(close()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), offre_part, SLOT(clear()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), adm_part, SLOT(clear()));

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Gestion Partenaires", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Ajouter Partenaire", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Afficher Liste", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "M.A.J Liste", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "Suppr. Partenaire", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("MainWindow", "Tableau De Bord", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "Map", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "Quitter", Q_NULLPTR));
        pushButton_18->setText(QApplication::translate("MainWindow", "Export PDF", Q_NULLPTR));
        pushButton_20->setText(QApplication::translate("MainWindow", "Envoyer Mail", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "Afficher sur LCD", Q_NULLPTR));
        pushButton_21->setText(QApplication::translate("MainWindow", "Revenir au menu", Q_NULLPTR));
        rcpt->setText(QApplication::translate("MainWindow", "Destinataire", Q_NULLPTR));
        subject->setText(QApplication::translate("MainWindow", "Objet", Q_NULLPTR));
        file->setText(QApplication::translate("MainWindow", "Joindre des fichiers", Q_NULLPTR));
        browseBtn->setText(QApplication::translate("MainWindow", "Browse...", Q_NULLPTR));
        msg->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt;\">Contenu de mail</span></p></body></html>", Q_NULLPTR));
        sendBtn->setText(QApplication::translate("MainWindow", "ENVOYER", Q_NULLPTR));
        mail_pass->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Saisir votre mot de passe :", Q_NULLPTR));
        lineEdit_13->setText(QApplication::translate("MainWindow", "Saisir L'ID du partenaire a supprimer : ", Q_NULLPTR));
        pushButton_12->setText(QApplication::translate("MainWindow", "EFFECTUER LA SUPPRESSION", Q_NULLPTR));
        pushButton_14->setText(QApplication::translate("MainWindow", "Revenir au menu", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("MainWindow", "Adresse Physique     :", Q_NULLPTR));
        lineEdit_4->setText(QApplication::translate("MainWindow", "Nom Partenaire", Q_NULLPTR));
        lineEdit_5->setText(QApplication::translate("MainWindow", "Adresse Mail           :", Q_NULLPTR));
        lineEdit_6->setText(QApplication::translate("MainWindow", "Offre(s) propos\303\251e(s) :", Q_NULLPTR));
        lineEdit_7->setText(QApplication::translate("MainWindow", "Num. T\303\251l\303\251phone", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "Enregistrer", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "R\303\251intialiser", Q_NULLPTR));
        lineEdit_15->setText(QApplication::translate("MainWindow", "Saisir un ID             :", Q_NULLPTR));
        pushButton_15->setText(QApplication::translate("MainWindow", "Revenir au menu", Q_NULLPTR));
        qrcodegen->setText(QApplication::translate("MainWindow", "Code QR", Q_NULLPTR));
        qrcodecommande->setText(QString());
        label_msg->setText(QString());
        pushButton_10->setText(QApplication::translate("MainWindow", "Afficher Liste Tri\303\251e", Q_NULLPTR));
        pushButton_16->setText(QApplication::translate("MainWindow", "Revenir au menu", Q_NULLPTR));
        pushButton_11->setText(QApplication::translate("MainWindow", "Chercher Element", Q_NULLPTR));
        rech_part->setText(QString());
        pushButton_19->setText(QApplication::translate("MainWindow", "Afficher Liste Tri\303\251e", Q_NULLPTR));
        lineEdit_17->setText(QApplication::translate("MainWindow", "Saisir L'ID de partenaire a modifier", Q_NULLPTR));
        pushButton_13->setText(QApplication::translate("MainWindow", "Mise a jour", Q_NULLPTR));
        pushButton_17->setText(QApplication::translate("MainWindow", "Revenir au menu", Q_NULLPTR));
        lineEdit_8->setText(QApplication::translate("MainWindow", "Nom Partenaire     :", Q_NULLPTR));
        lineEdit_9->setText(QApplication::translate("MainWindow", "Mail Partenaire     : ", Q_NULLPTR));
        lineEdit_10->setText(QApplication::translate("MainWindow", "Num. Tlph Part     :", Q_NULLPTR));
        lineEdit_11->setText(QApplication::translate("MainWindow", "Adresse Physique  :", Q_NULLPTR));
        lineEdit_12->setText(QApplication::translate("MainWindow", "Offre Propos\303\251       :", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
