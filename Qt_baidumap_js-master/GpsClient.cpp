#include "GpsClient.h"
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <QTextCodec>
#include <stdio.h>

GpsClient::GpsClient(QObject *parent) : QThread (parent)
{
    tcpSocket = new QTcpSocket();
}

void GpsClient::Tcpclientconnect()
{
    tcpClientTargetAddr.setAddress(client_ip);
    tcpSocket->connectToHost(tcpClientTargetAddr, client_port);

}

void GpsClient::run()
{
    tcpClientTargetAddr.setAddress(client_ip);
    tcpSocket->connectToHost(tcpClientTargetAddr,client_port);

    if (!tcpSocket->waitForConnected(timeout)){
        return;
    }
    for (;;) {
        if (tcpSocket->waitForReadyRead()){  //this function returns true if the readyRead() is emitted
                                           //This function blocks until new data is avaliable
             QByteArray data = tcpSocket->readAll();    //receive data from server which is encoded by UTF-8
             std::string s_data=  data.toStdString();
             QString qt_data = QString::fromStdString(s_data);
             //qDebug() << qt_data;
             parse(qt_data);
            }
        }
}

void GpsClient::onDisconnect()
{
    tcpSocket->disconnectFromHost();
}

void GpsClient::onsendwaypoints(QString wgs_wayresult)
{
    Data.clear();
    qDebug() << wgs_wayresult;
    Data.append(wgs_wayresult);
    if(tcpSocket->state() == QTcpSocket::ConnectedState){
        tcpSocket->write(Data);
        tcpSocket->flush();
    }
}

void GpsClient::parse(const QString &rmc)
{
    QJsonObject json_obj;
    QJsonArray json_arr;
    std::vector<loc> road_line_arr, obstacle_arr;
    road_line_arr.clear();
    loc gpscoord, gcjcoord, bdcoord;
    loc obstaclecoord_w, obstaclecoord_g, obstaclecoord_b;
    //loc road_middle_w;
    double longitude, longitude1;
    double latitude, latitude1;
    if (rmc.startsWith("#") && rmc.endsWith("?")){
        QStringList array = rmc.split('$');
        //if (array.length() == 2){
            QString revfirst = array.at(0);   // store #GPS
            QString revright = array.at(1);
            //if ( revright !="" ) {
                //revright = revright.left(revright.length() - 1);
                QStringList revleftArr = revright.split("*");
                QString revsecond = revleftArr.at(0);    // store obstacles
                QString revthird = revleftArr.at(1).left(revleftArr.at(1).length() - 1);  // store Road_middle_line

                /**********For GPS*************************/
                QString GPScoord = revfirst.right(revfirst.length() - 1);
                QStringList GPScoordArr = GPScoord.split(",");
                gpscoord.lon = GPScoordArr.at(0).toDouble();
                gpscoord.lat = GPScoordArr.at(1).toDouble();
                //qDebug() << gpscoord.lon;
                gcjcoord = wgs2gcj(gpscoord);
                bdcoord = gcj2bd(gcjcoord);

                longitude1 = gpscoord.lon;
                latitude1 = gpscoord.lat;

                longitude = bdcoord.lon;
                latitude = bdcoord.lat;

                /***********For Obstacle information***************/
                QStringList ObstacleArr = revsecond.split(";");
                for (int i = 0; i < ObstacleArr.length(); i++) {
                    QString Obstacle_gps = ObstacleArr.at(i);
                    obstaclecoord_w.lon = Obstacle_gps.split(",").at(0).toDouble();
                    obstaclecoord_w.lat = Obstacle_gps.split(",").at(1).toDouble();
                    obstaclecoord_g = wgs2gcj(obstaclecoord_w);
                    obstaclecoord_b = gcj2bd(obstaclecoord_g);
                    QString ob_lng = QString::number(obstaclecoord_b.lon, 'g', 9);
                    QString ob_lat = QString::number(obstaclecoord_b.lat, 'g', 8);
                    json_obj.insert("lng", ob_lng.toDouble());
                    json_obj.insert("lat", ob_lat.toDouble());
                    json_arr.append(json_obj);
                    obstacle_arr.push_back(obstaclecoord_w);
                }
                qDebug() << fixed << qSetRealNumberPrecision(10) << longitude1 << latitude1;

                /*************Emit information************/
                //emit obstacle_midlle(revsecond, revthird);   // for obstacles and middle line
                emit position_obstacle(longitude, latitude, json_arr, revsecond, revthird, longitude1, latitude1);
                //qDebug() <<  " I am "  << revsecond;
                //qDebug() << " You are " << revthird;
            //}
        //}
    }

}



/*bool GpsClient::outOfChina(double lon, double lat)
{
    if (lon < 72.004 || lon > 137.8347)
        return true;
    if (lat < 0.8293 || lat > 55.8271)
        return true;
    return  false;
}*/

/******************************************************
 *
 * Coordinates Converter:From WGS-84 to BD-09
 *
 * ***************************************************/

double GpsClient::transformLon(double x, double y)
{
    double ret = 300.0 + x + 2.0 * y + 0.1 * x * x + 0.1 * x * y + 0.1 * sqrt(std::abs(x));
    ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(x * pi) + 40.0 * sin(x / 3.0 * pi)) * 2.0 / 3.0;
    ret += (150.0 * sin(x / 12.0 * pi) + 300.0 * sin(x / 30.0 * pi)) * 2.0 / 3.0;
    return ret;
}

double GpsClient::transformLat(double x, double y)
{
    double ret = -100.0 + 2.0 * x + 3.0 * y + 0.2 * y * y + 0.1 * x * y + 0.2 * sqrt(std::abs(x));
    ret += (20.0 * sin(6.0 * x * pi) + 20.0 * sin(2.0 * x * pi)) * 2.0 / 3.0;
    ret += (20.0 * sin(y * pi) + 40.0 * sin(y / 3.0 * pi)) * 2.0 / 3.0;
    ret += (160.0 * sin(y / 12.0 * pi) + 320 * sin(y * pi / 30.0)) * 2.0 / 3.0;
    return ret;
}

 loc GpsClient::wgs2gcj(loc gps)
{
    loc gcjcoord;
    double dLon = transformLon(gps.lon - 105.0, gps.lat - 35.0);
    double dLat = transformLat(gps.lon - 105.0, gps.lat - 35.0);
    double radLat = gps.lat / 180.0 * pi;
    double magic = sin(radLat);
    magic = 1 - ee * magic * magic;
    double sqrtMagic = sqrt(magic);
    dLon = (dLon * 180.0) / (a / sqrtMagic * cos(radLat) * pi);
    dLat = (dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * pi);
    gcjcoord.lon = gps.lon + dLon;
    gcjcoord.lat = gps.lat + dLat;
    return gcjcoord;

}

loc GpsClient::gcj2bd(loc gg)     //right conversion
{
    loc bdcoord;
    double x = gg.lon;
    double y = gg.lat;
    double z = sqrt(x * x + y * y) + 0.00002 * sin(y * x_pi);
    double theta = atan2(y, x) + 0.000003 * cos(x * x_pi);
    bdcoord.lon = z * cos(theta) + 0.0065;
    bdcoord.lat = z * sin(theta) + 0.006;
    return bdcoord;
}

/****************************************************************
 *
 * Coordinates Converter:From BD-09 to WGS-84
 *
 * *************************************************************/

loc GpsClient::bd2gcj(loc bd)
{
    loc gcjcoord;
    double x = bd.lon - 0.0065;
    double y = bd.lat - 0.006;
    double z = sqrt(x * x + y * y) - 0.00002 * sin(y * x_pi);
    double theta = atan2(y, x) - 0.000003 * cos(x * x_pi);
    gcjcoord.lon = z * cos(theta);
    gcjcoord.lat = z * sin(theta);
    return gcjcoord;
}

loc GpsClient::gcj2wgs(loc gcj)
{
    loc wgscoord;
    double dLon = transformLon(gcj.lon - 105.0, gcj.lat - 35.0);
    double dLat = transformLat(gcj.lon - 105.0, gcj.lat - 35.0);
    double radLat = gcj.lat / 180.0 * pi;
    double magic = sin(radLat);
    magic = 1 - ee * magic * magic;
    double sqrtMagic = sqrt(magic);
    dLon = (dLon * 180.0) / (a / sqrtMagic * cos(radLat) * pi);
    dLat = (dLat * 180.0) / ((a * (1 - ee)) / (magic * sqrtMagic) * pi);
    double mglon = gcj.lon + dLon;
    double mglat = gcj.lat + dLat;
    wgscoord.lon = gcj.lon * 2 - mglon;
    wgscoord.lat = gcj.lat * 2 - mglat;
    return wgscoord;
}

