#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------
QT += core network
QT       += core gui sql
QT += sql
QT += charts
QT       += core gui  serialport

QT       += core gui sql \
    quick
QT  +=charts

QT += multimedia multimediawidgets
QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

QT += widgets multimedia
QT += printsupport
QT       += network
QT       += core gui  serialport
QT +=gui
QT += widgets
QT +=charts
QT += multimedia multimediawidgets

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    QrCode.cpp \
    arduino.cpp \
    client.cpp \
    connectdialog.cpp \
    dumessengerserver.cpp \
    dumessengersocket.cpp \
    espace.cpp \
    evenement.cpp \
    main.cpp \
    mainwindow.cpp \
    connection.cpp \
    notification.cpp \
    partenaire.cpp \
    personnel.cpp \
    smtp.cpp \
    widget.cpp

HEADERS += \
    QrCode.hpp \
    arduino.h \
    client.h \
    connectdialog.h \
    dumessengerserver.h \
    dumessengersocket.h \
    espace.h \
    evenement.h \
    mainwindow.h \
    connection.h \
    notification.h \
    partenaire.h \
    personnel.h \
    smtp.h \
    widget.h

FORMS += \
    connectdialog.ui \
    mainwindow.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QMAKE_CXXFLAGS +=-std=gnu++11


