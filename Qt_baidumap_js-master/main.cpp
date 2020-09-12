#include "mainwindow.h"
#include "paintwidget.h"
#include <QApplication>
#include <QTimer>
#include <QWebChannel>
#include <QWebEngineView>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow mainwindow;
    PaintWidget widget;

    mainwindow.show();
    mainwindow.move(300,300);


    return a.exec();
}
