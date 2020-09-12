#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebChannel>
#include <QWebEngineView>
#include "GpsClient.h"
#include "paintwidget.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QMouseEvent>
#include <QPainter>
#include "mytcpserver.h"

#define TCPSERVER 10


namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

signals:
  void waypoints(QString);
  void obstacle_road(QString, QString, double, double);

private slots:
  void setflag(bool);
  //void timerout();
  void GpsUpdate(double longitude, double latitude, QJsonArray json_arr, QString revsecond, QString revthird, double longitude1, double latitude1);
  void onGpsClientRun();
  void onPathPlanning();
  void onExitPathPlanning();
  //void onObstacles(QJsonArray json_arr);


  /******************************************************************************
   *
   * TCP Server
   *
   ******************************************************************************/
  void onTcpServerButtonClicked();
  void onTcpServerNewConnection(const QString &from, quint16 port);
  void onTcpServerStopButtonClicked();
  void onTcpServerDisconnectButtonClicked();
  void onTcpServerDisconnected();
  void onTcpServerSendMessage();


public slots:
  void getcoordinates(double lon, double lat);
  void returnWayPoints(const QString &r_waypoints);

private:
  Ui::MainWindow *ui;
  bool loadflag;
  double lat;
  double lon;
  QList<QString> wgs_waypointsArr;
  //QWebEngineView *pEngView;
  GpsClient *MyGps;
  MyTCPServer *mytcpserver = nullptr;
  PaintWidget *MyWidget;
  //********TCP  server************
  QHostAddress localAddr;
  quint16 tcpServerListenPort;
  void initUI();
  void loadSettings();
  void saveSettings();
  void findLocalIPs();
  bool setupConnection(quint8 type);
  void restoreWindowState();

public:
  QString wgs_wayresult;

protected:
  void mouseMoveEvent(QMouseEvent *p);
  void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
