#-------------------------------------------------
#
# Project created by QtCreator 2019-04-05T14:39:03
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# TARGET = Bmap
CONFIG+=debug_and_release
CONFIG(debug, debug|release){
    TARGET = Bmap
} else {
    TARGET = Bmap
}
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bridge.cpp \
    GpsClient.cpp \
    paintwidget.cpp \
    mytcpserver.cpp

HEADERS += \
        mainwindow.h \
    bridge.h \
    GpsClient.h \
    paintwidget.h \
    spline.h \
    mytcpserver.h

FORMS += \
    mainwindow.ui \
    paintwidget.ui

RESOURCES += \
    javascript.qrc
