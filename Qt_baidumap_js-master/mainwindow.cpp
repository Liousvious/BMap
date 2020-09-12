#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QWebChannel>
#include <QWebEngineView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    this->setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
    ui->frame->setMouseTracking(true);

    setStyleSheet("QFrame{background:gray}");
    ui->client_Clicked->setStyleSheet("QPushButton{border-image: url(:/new/icons/icons/play.png);}"
                                      "QPushButton:hover{border-image: url(:/new/icons/icons/play-hover.png);}"
                                      "QPushButton:pressed{border-image: url(:/new/icons/icons/play-pressed.png);}");
    setWindowTitle("BMAP GUI");

    MyGps = new GpsClient();
    MyWidget = new PaintWidget();
    loadflag = false;

    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QString("showcoord"), this);
    channel->registerObject(QString("returnpoints"), this);

    ui->m_webview->page()->setWebChannel(channel);
    ui->m_webview->setContextMenuPolicy(Qt::NoContextMenu);
    ui->m_webview->page()->load(QUrl("qrc:/Bmap.html"));
    ui->m_webview->show();

    //*************************INI   ui************
    ui->server_ip->setText("127.0.0.1");
    ui->client_ip->setText("127.0.0.1");
    ui->server_port->setText("65500");
    ui->client_port->setText("65500");

    MyGps->client_ip=ui->client_ip->text();
    MyGps->client_port=ui->client_port->text().toInt();





    connect(ui->client_Clicked, SIGNAL(clicked()), this, SLOT(onGpsClientRun()));
    connect(ui->m_webview, SIGNAL(loadFinished(bool)), this, SLOT(setflag(bool)));    //this indicate once the page was loaded
                                                                                        //successfully, the load flag will become true
    connect(MyGps, SIGNAL(position_obstacle(double, double, QJsonArray, QString, QString, double, double)), SLOT(GpsUpdate(double, double, QJsonArray, QString, QString, double, double)));
    connect(this, SIGNAL(obstacle_road(QString, QString, double, double)), MyWidget, SLOT(frenet(QString, QString, double, double)));
    connect(ui->Disconnect_Clicked, SIGNAL(clicked()), MyGps, SLOT(onDisconnect()));
    connect(ui->path_Clicked, SIGNAL(clicked()), this, SLOT(onPathPlanning()));
    connect(this, SIGNAL(waypoints(QString)), MyGps, SLOT(onsendwaypoints(QString)));
    connect(this, SIGNAL(waypoints(QString)), MyWidget, SLOT(onpathwaypoints(QString)));
    connect(ui->client_connect, SIGNAL(clicked()), MyGps, SLOT(Tcpclientconnect()));
    QObject::connect(ui->link, SIGNAL(clicked()), this, SLOT(onTcpServerButtonClicked()));
    QObject::connect(ui->send, SIGNAL(clicked()), this, SLOT(onTcpServerSendMessage()));


    //connect(MyGps, SIGNAL(obstacles(QJsonArray)), this, SLOT(onObstacles(QJsonArray)));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), QColor(50, 50, 50, 80));
}

void MainWindow::mouseMoveEvent(QMouseEvent *p)
{
    p->accept();

    //qDebug() << p->pos().x() << "," << p->pos().y();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGpsClientRun()
{
    MyGps->start();
}

void MainWindow::setflag(bool t)
{
    loadflag = t;
}

/*******************************************************************************
 *
 * run javascript via TCP protocal
 *
 * ****************************************************************************/

void MainWindow::GpsUpdate(double longitude, double latitude, QJsonArray json_arr, QString revsecond, QString revthird, double longitude1, double latitude1)
{
    //qDebug() << "Hweekhun" <<revsecond << revthird;
    emit obstacle_road(revsecond, revthird, longitude1, latitude1);
    QString json_str = QString(QJsonDocument(json_arr).toJson()).remove(QRegExp("\\s"));
    //qDebug() << json_str;
    if (loadflag == true){
        double lng = longitude;
        double lat = latitude;
        //qDebug() << fixed << qSetRealNumberPrecision(10) << longitude << latitude;
        ui->m_webview->page()->runJavaScript(QString("theLocation_obstacle(%1,%2,%3)").arg(lng, 0, 'g', 11).arg(lat, 0, 'g', 10).arg(json_str));
    }
}

void MainWindow::onPathPlanning()
{
    disconnect(ui->path_Clicked, SIGNAL(clicked()), this, SLOT(onPathPlanning()));
    connect(ui->path_Clicked,SIGNAL(clicked()), this, SLOT(onExitPathPlanning()));
    ui->path_Clicked->setText("Exit");
    if (loadflag == true){
        ui->m_webview->page()->runJavaScript(QString("pathplanning()"));
    }
}

void MainWindow::onExitPathPlanning()
{
    disconnect(ui->path_Clicked,SIGNAL(clicked()), this, SLOT(onExitPathPlanning()));
    connect(ui->path_Clicked, SIGNAL(clicked()), this, SLOT(onPathPlanning()));
    ui->path_Clicked->setText("Path Plan");
    ui->m_webview->page()->runJavaScript(QString("exitPathPlanning()"));
}
/**************************************************************************************
 *
 * Qwebchannel: for data interaction
 *
 * ************************************************************************************/

void MainWindow::getcoordinates(double lon, double lat)
{
    double wgs_longitude;
    double wgs_latitude;
    loc bdcoord, gcjcoord, wgscoord;
    bdcoord.lon = lon;
    bdcoord.lat = lat;
    gcjcoord = MyGps->bd2gcj(bdcoord);
    wgscoord = MyGps->gcj2wgs(gcjcoord);
    wgs_longitude = wgscoord.lon;
    wgs_latitude = wgscoord.lat;

    QString showlon = "Mouse WGS_Longitude: " + QString::number(wgs_longitude, 'g' , 12) + " °";
    QString showlat = "Mouse WGS_Latitude: " + QString::number(wgs_latitude, 'g', 11) + " °";
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::white);
    ui->label_mouse_longitude->setPalette(pa);
    ui->label_mouse_latitude->setPalette(pa);
    ui->label_mouse_longitude->setText(showlon);
    ui->label_mouse_latitude->setText(showlat);
}

void MainWindow::returnWayPoints(const QString &r_waypoints)
{
    //qDebug() << r_waypoints;
    wgs_wayresult = "";
    wgs_waypointsArr.clear();
    loc point_bd, point_gcj, point_wgs;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(r_waypoints.toLocal8Bit().data());
    QJsonArray jsonarray = jsonDocument.array();
    //qDebug() << jsonarray;

    for (int i = 0; i < jsonarray.size(); i++) {
        point_bd.lat = jsonarray.at(i).toObject().value("lat").toDouble();
        point_bd.lon = jsonarray.at(i).toObject().value("lng").toDouble();
        //qDebug() << fixed << qSetRealNumberPrecision(8) << point_bd.lon;
        point_gcj = MyGps->bd2gcj(point_bd);
        point_wgs = MyGps->gcj2wgs(point_gcj);
        QString wgs_waypoints = QString::number(point_wgs.lon, 'g', 11) + "," + QString::number(point_wgs.lat, 'g', 10);
        wgs_waypointsArr.append(wgs_waypoints);
        //qDebug() <<  fixed << qSetRealNumberPrecision(8) << point_wgs.lon <<','<< point_wgs.lat;
    }

    for (int i = 0; i < wgs_waypointsArr.size(); i++) {
        wgs_wayresult += wgs_waypointsArr.at(i) + ";";
    }
    wgs_wayresult = "$" + wgs_wayresult.left(wgs_wayresult.length()-1);
    emit waypoints(wgs_wayresult);
    //mytcpserver->sendMessage(wgs_wayresult);
    //qDebug() << wgs_wayresult;  //used to store a list of QString which is the final result path planning waypoints
}
//*************************TCP   SERVER*********************************
void MainWindow::onTcpServerButtonClicked()
{
    disconnect(ui->link, SIGNAL(clicked()), this, SLOT(onTcpServerButtonClicked()));

    if (setupConnection(TCPSERVER))
    {

        connect(ui->link, SIGNAL(clicked()), this, SLOT(onTcpServerStopButtonClicked()));
        ui->link->setText("Stop");
        connect(mytcpserver, SIGNAL(myServerConnected(QString, quint16)), this, SLOT(onTcpServerNewConnection(QString, quint16)));
    }
    else
    {
          connect(ui->link, SIGNAL(clicked()), this, SLOT(onTcpServerButtonClicked()));
    }


}
/***********************************
 *
 * TCP server has a new connection
 *
 ***********************************/
void MainWindow::onTcpServerNewConnection(const QString &from, quint16 port)
{
    disconnect(mytcpserver, SIGNAL(myServerConnected(QString, quint16)), this, SLOT(onTcpServerNewConnection(QString, quint16)));

    disconnect(ui->link, SIGNAL(clicked()), this, SLOT(onTcpServerStopButtonClicked()));
    ui->link->setText("Disconnect");
    connect(ui->link, SIGNAL(clicked()), this, SLOT(onTcpServerDisconnectButtonClicked()));

    connect(mytcpserver, SIGNAL(myServerDisconnected()), this, SLOT(onTcpServerDisconnected()));

    ui->send->setDisabled(false);
    connect(ui->send, SIGNAL(clicked()), this, SLOT(onTcpServerSendMessage()));

}
/***********************************
 *
 * TCP server stop button clicked
 *
 ***********************************/
void MainWindow::onTcpServerStopButtonClicked()
{
    disconnect(ui->link, SIGNAL(clicked()), this, SLOT(onTcpServerStopButtonClicked()));

    disconnect(mytcpserver, SIGNAL(myServerConnected(QString, quint16)));
    mytcpserver->stopListening();
    ui->link->setText("link");
    connect(ui->link, SIGNAL(clicked()), this, SLOT(onTcpServerButtonClicked()));
}
void MainWindow::onTcpServerDisconnectButtonClicked()
{
    mytcpserver->stopConnection();
}
void MainWindow::onTcpServerDisconnected()
{

    disconnect(ui->link, SIGNAL(clicked()), this, SLOT(onTcpServerDisconnectButtonClicked()));
    disconnect(mytcpserver, SIGNAL(myServerDisconnected()), this, SLOT(onTcpServerDisconnected()));
    disconnect(mytcpserver, SIGNAL(newMessage(QString, QString)), this, SLOT(onTcpServerAppendMessage(QString, QString)));
    disconnect(ui->send, SIGNAL(clicked()), this, SLOT(onTcpServerSendMessage()));

    connect(ui->link, SIGNAL(clicked()), this, SLOT(onTcpServerStopButtonClicked()));
    ui->link->setText("Stop");
    connect(mytcpserver, SIGNAL(myServerConnected(QString, quint16)), this, SLOT(onTcpServerNewConnection(QString, quint16)));
}
void MainWindow::onTcpServerSendMessage()
{
    if (wgs_wayresult.isEmpty())
    {
        return;
    }

    mytcpserver->sendMessage(wgs_wayresult);

}
/***********************************
 *
 * Setup connections
 *
 ***********************************/
bool MainWindow::setupConnection(quint8 type)
{
    bool isSuccess = false;
    localAddr.setAddress(ui->server_ip->text());
    switch (type)
    {
    case TCPSERVER:
        tcpServerListenPort =ui->server_port->text().toInt();
        if (mytcpserver == nullptr)
        {
            mytcpserver = new MyTCPServer;
        }
        isSuccess = mytcpserver->listen(localAddr, tcpServerListenPort);
        break;

    }
    return isSuccess;
}
