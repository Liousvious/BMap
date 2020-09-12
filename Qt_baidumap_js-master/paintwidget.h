#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QPainterPath>
#include <QList>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include "spline.h"
#include <cmath>
#include <QTime>
#include "GpsClient.h"

#define LNG 0.008201
#define LAT 0.003031
#define WID_WIDTH 1827
#define WID_HEIGHT 906
#define TOP_LEFT_LNG 123.409694
#define TOP_LEFT_LAT 41.765275
#define TOP_LEFT_X 20
#define TOP_LEFT_Y 20
#define POINT_NUM 6000

#define INSERT_NUM 4

namespace Ui {
class PaintWidget;

}
//class GpsClient;   //for Gps Thread

struct Widgetloc
{
    double x_coord;
    double y_coord;
};

struct Frenet_path
{
    std::vector<float> d;
    std::vector<float> s;
    std::vector<float> x;  // store the predicted point.x
    std::vector<float> y;  // store the predicted point.y
    float cost;
};

class PaintWidget : public QWidget
{
    Q_OBJECT

public slots:
    void onpathwaypoints(QString gps_wayresult);
    //void ontimeout();
    void frenet(QString revsecond, QString revthird, double longitude1, double latitude1);
    //void onShow(QString revsecond, QString revthird);

public:
    explicit PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget();

private:
    Ui::PaintWidget *ui;

    GpsClient *MyGps;
    QTimer *timer;
    QPointF point;
    QList<QPointF> wid_points, dense_waypoints;
    QPainterPath path_cp, dense_path_cp, optimal_path_cp;
    double s;   // the distance from zero point to (x[i], y[i])
    double distance; // the distance between (x[i], y[i]) and (x[i+1], y[i+1])
    double x =  20 * 10 + 20;
    std::vector<Widgetloc> spare_points;  // store the way points which is struct type(spare points)
    std::vector<Widgetloc> dense_points;  // store the way points which is dense points
    std::vector<double> dense_s;     // store the distance s which is the ith dense point away from origin
    QList<Widgetloc> interp_points;

    // cubic spline interpolation for (s, x) and (s, y) seperately
    tk::spline s1, s2;
    double sj = 0;  // store the closest point distance
    Widgetloc current_pos;  // vehicle current position
    int g_1 = 0;
    float d0_1 = 0;  // store the distance to middle line in the last time
    float time_1 = 0;  // last time, a global variable
    std::vector<Widgetloc> obstacles;
    std::vector<Widgetloc> road_line;   // the fitted road middle line
    QList<QPointF> optimal_path_points; // store the optimal path points
    QList<QPointF> road_line_points;  // store the road middle line points
    QList<QPointF> obstacles_points;  // store the obstacle points


protected:
    void paintEvent(QPaintEvent *event);
    void JudgePoint2Line(Widgetloc &LinePtA, Widgetloc &LinePtB, Widgetloc &LinePtC, int &out);

    Widgetloc wgs2local(double lng, double lat);

};

#endif // PAINTWIDGET_H
