/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qwebengineview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QWebEngineView *m_webview;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_mouse_longitude;
    QSpacerItem *horizontalSpacer;
    QLabel *label_mouse_latitude;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *client_Clicked;
    QPushButton *Disconnect_Clicked;
    QPushButton *client_connect;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_targetIP;
    QLineEdit *client_ip;
    QLabel *label_targetPort;
    QFrame *line_4;
    QLineEdit *client_port;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *link;
    QPushButton *send;
    QPushButton *path_Clicked;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_targetIP_3;
    QLineEdit *server_ip;
    QFrame *line_6;
    QLabel *label_targetPort_3;
    QLineEdit *server_port;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1172, 640);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_webview = new QWebEngineView(frame);
        m_webview->setObjectName(QString::fromUtf8("m_webview"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_webview->sizePolicy().hasHeightForWidth());
        m_webview->setSizePolicy(sizePolicy);
        m_webview->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(m_webview);

        widget_2 = new QWidget(frame);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_mouse_longitude = new QLabel(widget_2);
        label_mouse_longitude->setObjectName(QString::fromUtf8("label_mouse_longitude"));

        horizontalLayout_3->addWidget(label_mouse_longitude);

        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_mouse_latitude = new QLabel(widget_2);
        label_mouse_latitude->setObjectName(QString::fromUtf8("label_mouse_latitude"));

        horizontalLayout_3->addWidget(label_mouse_latitude);


        verticalLayout->addWidget(widget_2);

        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widget_5 = new QWidget(groupBox_4);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_3 = new QWidget(widget_5);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        client_Clicked = new QPushButton(widget_3);
        client_Clicked->setObjectName(QString::fromUtf8("client_Clicked"));

        horizontalLayout_4->addWidget(client_Clicked);

        Disconnect_Clicked = new QPushButton(widget_3);
        Disconnect_Clicked->setObjectName(QString::fromUtf8("Disconnect_Clicked"));

        horizontalLayout_4->addWidget(Disconnect_Clicked);

        client_connect = new QPushButton(widget_3);
        client_connect->setObjectName(QString::fromUtf8("client_connect"));

        horizontalLayout_4->addWidget(client_connect);


        verticalLayout_3->addWidget(widget_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_targetIP = new QLabel(widget_5);
        label_targetIP->setObjectName(QString::fromUtf8("label_targetIP"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_targetIP->sizePolicy().hasHeightForWidth());
        label_targetIP->setSizePolicy(sizePolicy1);
        label_targetIP->setMinimumSize(QSize(0, 0));
        label_targetIP->setBaseSize(QSize(0, 0));

        horizontalLayout_7->addWidget(label_targetIP);

        client_ip = new QLineEdit(widget_5);
        client_ip->setObjectName(QString::fromUtf8("client_ip"));
        client_ip->setMinimumSize(QSize(150, 0));
        client_ip->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_7->addWidget(client_ip);

        label_targetPort = new QLabel(widget_5);
        label_targetPort->setObjectName(QString::fromUtf8("label_targetPort"));
        sizePolicy1.setHeightForWidth(label_targetPort->sizePolicy().hasHeightForWidth());
        label_targetPort->setSizePolicy(sizePolicy1);
        label_targetPort->setMinimumSize(QSize(0, 0));

        horizontalLayout_7->addWidget(label_targetPort);

        line_4 = new QFrame(widget_5);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_7->addWidget(line_4);

        client_port = new QLineEdit(widget_5);
        client_port->setObjectName(QString::fromUtf8("client_port"));
        client_port->setMinimumSize(QSize(80, 0));
        client_port->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_7->addWidget(client_port);


        verticalLayout_3->addLayout(horizontalLayout_7);


        verticalLayout_4->addWidget(widget_5);


        horizontalLayout_5->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(widget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_5 = new QVBoxLayout(groupBox_5);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        widget_7 = new QWidget(groupBox_5);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        verticalLayout_2 = new QVBoxLayout(widget_7);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_4 = new QWidget(widget_7);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        link = new QPushButton(widget_4);
        link->setObjectName(QString::fromUtf8("link"));

        horizontalLayout_2->addWidget(link);

        send = new QPushButton(widget_4);
        send->setObjectName(QString::fromUtf8("send"));

        horizontalLayout_2->addWidget(send);

        path_Clicked = new QPushButton(widget_4);
        path_Clicked->setObjectName(QString::fromUtf8("path_Clicked"));

        horizontalLayout_2->addWidget(path_Clicked);


        verticalLayout_2->addWidget(widget_4);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_targetIP_3 = new QLabel(widget_7);
        label_targetIP_3->setObjectName(QString::fromUtf8("label_targetIP_3"));
        sizePolicy1.setHeightForWidth(label_targetIP_3->sizePolicy().hasHeightForWidth());
        label_targetIP_3->setSizePolicy(sizePolicy1);
        label_targetIP_3->setMinimumSize(QSize(0, 0));
        label_targetIP_3->setBaseSize(QSize(0, 0));

        horizontalLayout_10->addWidget(label_targetIP_3);

        server_ip = new QLineEdit(widget_7);
        server_ip->setObjectName(QString::fromUtf8("server_ip"));
        server_ip->setMinimumSize(QSize(150, 0));
        server_ip->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_10->addWidget(server_ip);

        line_6 = new QFrame(widget_7);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout_10->addWidget(line_6);

        label_targetPort_3 = new QLabel(widget_7);
        label_targetPort_3->setObjectName(QString::fromUtf8("label_targetPort_3"));
        sizePolicy1.setHeightForWidth(label_targetPort_3->sizePolicy().hasHeightForWidth());
        label_targetPort_3->setSizePolicy(sizePolicy1);
        label_targetPort_3->setMinimumSize(QSize(0, 0));

        horizontalLayout_10->addWidget(label_targetPort_3);

        server_port = new QLineEdit(widget_7);
        server_port->setObjectName(QString::fromUtf8("server_port"));
        server_port->setMinimumSize(QSize(80, 0));
        server_port->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_10->addWidget(server_port);


        verticalLayout_2->addLayout(horizontalLayout_10);


        verticalLayout_5->addWidget(widget_7);


        horizontalLayout_5->addWidget(groupBox_5);


        verticalLayout->addWidget(widget);


        horizontalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1172, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_mouse_longitude->setText(QString());
        label_mouse_latitude->setText(QString());
        groupBox_4->setTitle(QApplication::translate("MainWindow", "TCP client:", nullptr));
        client_Clicked->setText(QApplication::translate("MainWindow", "Start", nullptr));
        Disconnect_Clicked->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        client_connect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        label_targetIP->setText(QApplication::translate("MainWindow", "IP:", nullptr));
        label_targetPort->setText(QApplication::translate("MainWindow", "Port:", nullptr));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "TCP server:", nullptr));
        link->setText(QApplication::translate("MainWindow", "link", nullptr));
        send->setText(QApplication::translate("MainWindow", "send", nullptr));
        path_Clicked->setText(QApplication::translate("MainWindow", "Path Plan", nullptr));
        label_targetIP_3->setText(QApplication::translate("MainWindow", "IP:", nullptr));
        label_targetPort_3->setText(QApplication::translate("MainWindow", "Port:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
