QT       += core gui sql network printsupport widgets axcontainer serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets
QT += quick qml network positioning location
QT += network
CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += "C:\Users\Yassine\Documents\qttesttttt\ssleay32.dll"
LIBS += "C:\Users\Yassine\Documents\qttesttttt\libeay32.dll"
LIBS += "C:\Users\Yassine\Documents\qttesttttt\libssl32.dll"
LIBS += "C:\Qt\Qt5.9.9\Tools\OpenSSL\Win_x86\lib\libssl.lib"

SOURCES += \
    QrCode.cpp \
    arduino.cpp \
    connection.cpp \
    main.cpp \
    mainwindow.cpp \
    partenaire.cpp \
    smtp.cpp

HEADERS += \
    QrCode.hpp \
    arduino.h \
    connection.h \
    mainwindow.h \
    partenaire.h \
    smtp.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc \
    resource.qrc

DISTFILES += \
    str.png
