#include "paintwidget.h"
#include "ui_paintwidget.h"
#include <iostream>


PaintWidget::PaintWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintWidget)
{

    ui->setupUi(this);
    resize(800, 600);
    setWindowTitle("Paint Demo");
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    timer = new QTimer();
    MyGps = new GpsClient();
    //connect(timer, SIGNAL(timeout()), this, SLOT(ontimeout()));
    //connect(MyGps, SIGNAL(obstacle_midlle(QString, QString)), this, SLOT(onShow(QString, QString)));
    QTime current_time_1 = QTime::currentTime();
    QString str_time_1 = current_time_1.toString("HH:mm:ss:zzz");
    qDebug () << str_time_1;
    QStringList str_Arr = str_time_1.split(":");
    int hou = str_Arr.at(0).toInt()*3600;
    int min = str_Arr.at(1).toInt()*60;
    int sec = str_Arr.at(2).toInt();
    float msec = str_Arr.at(3).toFloat()/1000;
    qDebug () << msec;
    time_1 = hou + min + sec + msec;
    for (int var = 0; var < 10; ++var) {
        qDebug() << fixed << qSetRealNumberPrecision(5) << time_1;
    }
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::blue, 15, Qt::SolidLine, Qt::RoundCap));
    painter.drawPoint(point);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawPath(dense_path_cp);

    // draw obstacle points
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap));
    for (int i = 0; i < obstacles_points.size(); ++i) {
        painter.drawPoint(obstacles_points.at(i));
    }

    // draw road line points
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap));
    for (int i = 0; i < road_line_points.size(); ++i) {
        painter.drawPoint(road_line_points.at(i));
    }

    // draw the the predicted line
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0, 160, 230), 3, Qt::SolidLine, Qt::RoundCap));
    for (int i = 0; i < optimal_path_points.size(); ++i) {
        painter.drawPoint(optimal_path_points.at(i));
    }
    //painter.drawPath(optimal_path_cp);
}

/*void PaintWidget::ontimeout()
{
    static int i = 0;
    point.setX(interp_points.at(i).x_coord);
    point.setY(interp_points.at(i).y_coord);
    i++;
    if ( i== interp_points.length() - 1)
        i = 0;
    update();
}*/

Widgetloc PaintWidget::wgs2local(double lng, double lat)
{
    Widgetloc widget_coord;
    double relat_lng = lng - TOP_LEFT_LNG;
    double relat_lat = TOP_LEFT_LAT - lat;
    widget_coord.x_coord = (relat_lng / LNG) * WID_WIDTH + TOP_LEFT_X;
    widget_coord.y_coord = (relat_lat / LAT) * WID_HEIGHT + TOP_LEFT_Y;
    return widget_coord;
}

void PaintWidget::onpathwaypoints(QString gps_wayresult)
{
    wid_points.clear();
    dense_waypoints.clear();
    spare_points.clear();
    dense_points.clear();
    dense_s.clear();
    interp_points.clear();
    s = 0.0;
    Widgetloc insert_point;
    gps_wayresult =  gps_wayresult.right(gps_wayresult.length() - 1);
    QStringList gps_wayArr = gps_wayresult.split(";");
    qDebug() << gps_wayresult;
    for (int i = 0; i < gps_wayArr.length(); ++i) {
        QString waypoint = gps_wayArr.at(i);
        double way_lng = waypoint.split(",").at(0).toDouble();
        double way_lat = waypoint.split(",").at(1).toDouble();
        Widgetloc wid_point = wgs2local(way_lng, way_lat);
        spare_points.push_back(wid_point);
        wid_points.append(QPointF(wid_point.x_coord, wid_point.y_coord));
    }

    qDebug() << wid_points;
    // calculate the distance s in path and insert two average points between two spare points
    for (size_t i = 0; i < spare_points.size()-1; ++i) {
        Widgetloc point_first = spare_points.at(i);
        Widgetloc point_second = spare_points.at(i+1);
        double x_relat = point_second.x_coord - point_first.x_coord;
        double y_relat = point_second.y_coord - point_first.y_coord;

        distance = sqrt( x_relat * x_relat + y_relat * y_relat);
        dense_points.push_back(point_first);
        dense_s.push_back(s);

        // insert some points into the spare way points
        for (double j = 1.0; j < INSERT_NUM; ++j) {
            insert_point.x_coord = j/INSERT_NUM * x_relat + point_first.x_coord;
            insert_point.y_coord = j/INSERT_NUM * y_relat + point_first.y_coord;
            dense_points.push_back(insert_point);
            dense_s.push_back(j/INSERT_NUM*distance + s);
        }

        if ( i==spare_points.size() - 2 ){
            dense_points.push_back(point_second);
            dense_s.push_back(s+distance);
        }
        s += distance;
    }

    // calculate the std::vector<double> (s, x) and (s, y)
    std::vector<double> x_points, y_points;
    for (size_t i = 0; i < dense_points.size(); ++i) {
        x_points.push_back(dense_points.at(i).x_coord);
        y_points.push_back(dense_points.at(i).y_coord);
    }

    // set boundary conditions, default is ok
    s1.set_points(dense_s, x_points);
    s2.set_points(dense_s, y_points);
    for (int i = 0; i <= POINT_NUM; ++i) {
        Widgetloc xy_coord;
        xy_coord.x_coord = s1(i*s/POINT_NUM);
        xy_coord.y_coord = s2(i*s/POINT_NUM);
        dense_waypoints.append(QPointF(xy_coord.x_coord, xy_coord.y_coord));
        interp_points.append(xy_coord);
    }

    // set path
    QPainterPath dense_path(dense_waypoints.at(0));
    for (int i = 0; i < dense_waypoints.size(); ++i) {
        dense_path.lineTo(dense_waypoints.at(i));
    }
    dense_path_cp = dense_path;

    qDebug() << dense_path;
    update();
    this->show();
    //timer->start(10);
}
/***************************************************************************************************************
 *
 * In the frenet coordinate, we will do some path planning works, which includes calculating the distance s(t) of
 * vehicle in the reference line and the distance d(t) with regard to road middle line(getting from vision), what's
 * more, selecting the best predicted path from a series paths is necessary, with the help of coss function and
 * detected obstacles, the best collision avoiding path will be selected finally.
 *
 * *************************************************************************************************************/

void PaintWidget::frenet(QString revsecond, QString revthird, double longitude1, double latitude1)
{
    // revscond for obstacle string and revthird for road middle line string
    QStringList revsecond_arr, revthird_arr;
    revsecond_arr.clear();
    revthird_arr.clear();
    obstacles.clear();
    road_line.clear();
    obstacles_points.clear();
    road_line_points.clear();

    //qDebug() << "Liousvious" << revsecond;
    //qDebug() << revthird;
    current_pos = wgs2local(longitude1, latitude1);   // the current position of car
    qDebug() << current_pos.x_coord << current_pos.y_coord;
    if (revsecond !="") {
        revsecond_arr = revsecond.split(";");
        for (int i = 0; i < revsecond_arr.length(); i++) {
            QString obstacle_points = revsecond_arr.at(i);
            double obstacle_lng = obstacle_points.split(",").at(0).toDouble();
            double obstacle_lat = obstacle_points.split(",").at(1).toDouble();
            Widgetloc point1 = wgs2local(obstacle_lng, obstacle_lat);
            obstacles.push_back(point1);
            obstacles_points .append(QPointF(point1.x_coord, point1.y_coord));
        }
    }

    if (revthird !="") {
        revthird_arr = revthird.split(";");
        //qDebug () << revthird_arr;
        for (int j = 0; j < revthird_arr.size(); j++) {
            QString middle_line_points = revthird_arr.at(j);
            double middle_lng = middle_line_points.split(",").at(0).toDouble();
            double middle_lat = middle_line_points.split(",").at(1).toDouble();
            Widgetloc point2 = wgs2local(middle_lng, middle_lat);
            road_line.push_back(point2);
            road_line_points.append(QPointF(point2.x_coord, point2.y_coord));
            //qDebug () << middle_line_points;
        }
        //qDebug () << road_line_points;
    }
    //update();

    // first calculate s, which indicates the nearest point to the car current position in the reference line which has been fitted according to given lng&lat before
   Widgetloc cross_point_1;     // the projection of vehicle current position in the reference line
    Widgetloc cross_point_2;     // the projection of vehicle current position in the fitted middle line
    Widgetloc first, second;     // used to store reference points
    Widgetloc point_;            //  store the distance of the nearest point in reference line
    float closest_point_distance = std::numeric_limits<float>::max();    // store the closest point distance

    first.x_coord = s1(sj);
    first.y_coord = s2(sj);
    second.x_coord = s1(sj+0.2);
    second.y_coord = s2(sj+0.2);

    if (second.x_coord - first.x_coord == 0.0 ) {
        cross_point_1.x_coord = first.x_coord;
        cross_point_1.y_coord = current_pos.y_coord;
    }
    else if (second.y_coord - first.y_coord == 0.0 ) {
        cross_point_1.x_coord = current_pos.x_coord;
        cross_point_1.y_coord = first.y_coord;
    }
    else {
        float k1 = (second.y_coord - first.y_coord)/(second.x_coord - first.x_coord);     // calculate the slope of each segment which length is 0.2
        float b1 = first.y_coord - k1*first.x_coord;                        // calculate the intercept of each segment equation
        float k2 = -1/k1;                                     // calculate the slope of each line which is perpendicular to segment and in each segment, the slope is a constant
        float b2 = current_pos.y_coord - k2*current_pos.x_coord;  // calculate the intercept and therefore the line equation
        cross_point_1.x_coord = (b1-b2)/(k2-k1);                          // calculate the cross point which is s0
        cross_point_1.y_coord = k2*cross_point_1.x_coord + b2;            // cross_point_1.y = (k2*b1-k1*b2)/(k2-k1);
    }

    int g = 0;                             // in order to find the minimal distance point which is in the s line
    if (g_1 < interp_points.size() - 100){
        for (int i = g_1; i < g_1 + 100; ++i) {
            float distance_compt = sqrt((interp_points.at(i).x_coord - cross_point_1.x_coord)*(interp_points.at(i).x_coord - cross_point_1.x_coord)
                                        + (interp_points.at(i).y_coord - cross_point_1.y_coord)*(interp_points.at(i).y_coord - cross_point_1.y_coord));
            if (distance_compt < closest_point_distance) {
                closest_point_distance = distance_compt;
                g = i;
            }
        }
    }
    else {
        for (int i = g_1; i < interp_points.size(); ++i) {
            float distance_compt = sqrt((interp_points.at(i).x_coord - cross_point_1.x_coord)*(interp_points.at(i).x_coord - cross_point_1.x_coord)
                                        + (interp_points.at(i).y_coord - cross_point_1.y_coord)*(interp_points.at(i).y_coord - cross_point_1.y_coord));
            if (distance_compt < closest_point_distance) {
                closest_point_distance = distance_compt;
                g = i;
            }
        }
    }

    g_1 = g;
    if (g_1 >= interp_points.size()) {
        g_1 = 0;
    }

    qDebug() << g_1;
    // seperate three situations which the closest point in the front ,back or at the cross point
    // g is a global variable which stores the index of point which is the closest to the cross point in the s
    float dis_g, dis_g_back, dis_g_front;
    if (g == interp_points.size() - 1) {
        dis_g = sqrt((interp_points.at(g).x_coord-cross_point_1.x_coord)*(interp_points.at(g).x_coord-cross_point_1.x_coord)
                     + (interp_points.at(g).y_coord-cross_point_1.y_coord)*(interp_points.at(g).y_coord-cross_point_1.y_coord));
        dis_g_back = sqrt((interp_points.at(0).x_coord-cross_point_1.x_coord)*(interp_points.at(0).x_coord-cross_point_1.x_coord)
                          + (interp_points.at(0).y_coord-cross_point_1.y_coord)*(interp_points.at(0).y_coord-cross_point_1.y_coord));
        dis_g_front = sqrt((interp_points.at(g-1).x_coord-cross_point_1.x_coord)*(interp_points.at(g-1).x_coord-cross_point_1.x_coord)
                           + (interp_points.at(g-1).y_coord-cross_point_1.y_coord)*(interp_points.at(g-1).y_coord-cross_point_1.y_coord));

        if (dis_g_front < dis_g_back) {
            sj = g*s/INSERT_NUM - dis_g;
        }
        else {
            sj = g*s/INSERT_NUM + dis_g;
        }
    }

    else if (g == 0) {
        dis_g = sqrt((interp_points.at(0).x_coord-cross_point_1.x_coord)*(interp_points.at(0).x_coord-cross_point_1.x_coord)
                     + (interp_points.at(0).y_coord-cross_point_1.y_coord)*(interp_points.at(0).y_coord-cross_point_1.y_coord));
        dis_g_back = sqrt((interp_points.at(1).x_coord-cross_point_1.x_coord)*(interp_points.at(1).x_coord-cross_point_1.x_coord)
                          + (interp_points.at(1).y_coord-cross_point_1.y_coord)*(interp_points.at(1).y_coord-cross_point_1.y_coord));
        dis_g_front = sqrt((interp_points.at(interp_points.size()-1).x_coord-cross_point_1.x_coord)*(interp_points.at(interp_points.size()-1).x_coord-cross_point_1.x_coord)
                           + (interp_points.at(interp_points.size()-1).y_coord-cross_point_1.y_coord)*(interp_points.at(interp_points.size()-1).y_coord-cross_point_1.y_coord));
        if (dis_g_front < dis_g_back) {
            sj = dis_g;
        }
        else {
            sj = dis_g;
        }
    }
    else {
        dis_g = sqrt((interp_points.at(g).x_coord-cross_point_1.x_coord)*(interp_points.at(g).x_coord-cross_point_1.x_coord)
                     + (interp_points.at(g).y_coord-cross_point_1.y_coord)*(interp_points.at(g).y_coord-cross_point_1.y_coord));
        dis_g_back = sqrt((interp_points.at(g+1).x_coord-cross_point_1.x_coord)*(interp_points.at(g+1).x_coord-cross_point_1.x_coord)
                          + (interp_points.at(g+1).y_coord-cross_point_1.y_coord)*(interp_points.at(g+1).y_coord-cross_point_1.y_coord));
        dis_g_front = sqrt((interp_points.at(g-1).x_coord-cross_point_1.x_coord)*(interp_points.at(g-1).x_coord-cross_point_1.x_coord)
                           + (interp_points.at(g-1).y_coord-cross_point_1.y_coord)*(interp_points.at(g-1).y_coord-cross_point_1.y_coord));
        if (dis_g_front < dis_g_back) {
            sj = g*s/INSERT_NUM - dis_g;
        }
        else {
            sj = g*s/INSERT_NUM + dis_g;
        }
    }
    qDebug() << " This is sj" << fixed << qSetRealNumberPrecision(8) << sj;
    // therefore, current position have been calculated
    point_.x_coord = s1(sj);
    point_.y_coord = s2(sj);                            // used to show the pedal point of vehicle current position in reference point




    // in this section, we will calculate the distance to the middle line
    QTime current_time = QTime::currentTime();
    QString str_time = current_time.toString("HH:mm:ss:zzz");
    QStringList str_Arr = str_time.split(":");
    int hou = str_Arr.at(0).toInt()*3600;
    int min = str_Arr.at(1).toInt()*60;
    int sec = str_Arr.at(2).toInt();
    float msec = str_Arr.at(3).toFloat()/1000;
    float time = hou + min + sec + msec;  // get current time and convert it to millisecond
    qDebug() << time;

    float d;
    if (road_line.size() == 0) {  // in swerve, calculate refrence segment line ax+by+c = 0
        float a_refer = first.y_coord - second.y_coord;
        float b_refer = second.x_coord - first.x_coord;
        float c_refer = first.x_coord*second.y_coord - second.x_coord*first.y_coord;
        int nResult;
        JudgePoint2Line(first, second, current_pos, nResult);
        d = nResult*sqrt((first.x_coord - current_pos.x_coord)*(first.x_coord - current_pos.x_coord)
                         + (first.y_coord - current_pos.y_coord)*(first.y_coord - current_pos.y_coord));
        // Judge the relationship between vehicle current position and the reference line
    }
    else {   // in stright line without making a turn
        if (road_line.at(10).x_coord - road_line.at(5).x_coord == 0) {   // when every thing is ok, I will signify this to be a general form
            int nResult;
            JudgePoint2Line(road_line.at(5), road_line.at(10), current_pos, nResult);
            cross_point_2.x_coord = road_line.at(5).x_coord;
            cross_point_2.y_coord = current_pos.y_coord;
            d = nResult*fabs(cross_point_2.x_coord - current_pos.x_coord);
        }
        else if (road_line.at(10).y_coord - road_line.at(5).y_coord == 0) {
            int nResult;
            JudgePoint2Line(road_line.at(5), road_line.at(10), current_pos, nResult);
            cross_point_2.x_coord = current_pos.x_coord;
            cross_point_2.y_coord = road_line.at(5).y_coord;
            d = nResult*fabs(cross_point_2.y_coord - current_pos.y_coord);
        }
        else {
            int nResult;
            JudgePoint2Line(road_line.at(5), road_line.at(10), current_pos, nResult);
            float k1 = (road_line.at(10).y_coord - road_line.at(5).y_coord)/(road_line.at(10).x_coord - road_line.at(5).x_coord);
            float b1 = road_line.at(5).y_coord - k1*road_line.at(5).x_coord;
            float k2 = -1/k1;
            float b2 = current_pos.y_coord - k2*current_pos.x_coord;
            cross_point_2.x_coord = (b1 - b2)/(k2 - k1);
            cross_point_2.y_coord = k2*cross_point_2.x_coord + b2;
            d = nResult*sqrt((cross_point_2.x_coord - current_pos.x_coord)*(cross_point_2.x_coord - current_pos.x_coord)
                             + (cross_point_2.y_coord - current_pos.y_coord)*(cross_point_2.y_coord - current_pos.y_coord));
        }
    }
    // therefore, the cross point in fitted middle line was calculated

    // in this section, we will generate a series of path list which is about 100 alternative paths in the predicted situation
    double ratio_d = (d - d0_1)/(time - time_1);

    qDebug() << " This is d" << fixed << qSetRealNumberPrecision(8) << d;
    qDebug() << " This is delta_t" << fixed << qSetRealNumberPrecision(8) << time - time_1;
    qDebug() << " This is ratio_d" << fixed << qSetRealNumberPrecision(8) << ratio_d;
    if (fabs(ratio_d)> 1.8) {
        double sig = 0;
        if ( ratio_d > 0 ) sig = 1;
        else sig = -1;
        ratio_d = 1.8*sig;
    }

    d0_1 = d;
    time_1 = time; //
    std::vector<Frenet_path> path_list;
    std::vector<Frenet_path> path_list_without_crash;
    path_list.clear();
    path_list_without_crash.clear();
    for (int road_width = -5; road_width <5; road_width++) {   // setting the distance to middle line from -5m to 5m ,road_width is the boundary condition for calculating d
        for (int T = 10; T < 30; T++) {         // setting time from 0 to T, where T ranges from 10s to 30s
            float alpha_0 = d;                  // for each boundary, calculate the coefficient of each polynomial of d
            float alpha_1 = ratio_d;
            float alpha_2 = (3 * road_width - 3 * alpha_0 - 2 * T * alpha_1 )/(T * T);
            float alpha_3 = (-alpha_1 - 2 * alpha_2 * T)/(3 * T * T);

            Frenet_path path;
            path.d.clear();
            path.s.clear();

            float d_element = 0.0;
            for (int t = 0; t <= T; t++) {
                d_element = alpha_0 + alpha_1 * t + alpha_2 * t * t + alpha_3 * t * t * t;
                path.d.push_back(d_element);    // push_back the value of d in every time and get the path
                path.s.push_back(sj + 2 * t);   // for each d, push back the corresponding s
            }
            path.cost = 0.1 * T + d_element * d_element;
            path_list.push_back(path);
        }
    }

    // In this section, we will calculate the predicted path points which contains about 100 paths, and therefore select the best which has minimal cost and satisfies collision avoiding
    // condition
    float x1, y1;       // the predicted points
    float angle_s, angle_d;  // the angle of reference line and road middle line with regard to horizontal

    for (int i = 0; i < path_list.size(); ++i) {  // for each path
        for (int j = 0; j < path_list.at(i).d.size(); ++j) {  // for the ith path, for every time, the value of polynomial d
            Widgetloc s_fir_pnt;  //
            float s_x0 = s1(path_list.at(i).s.at(j));
            float s_y0 = s2(path_list.at(i).s.at(j));
            s_fir_pnt.x_coord = s_x0;
            s_fir_pnt.y_coord = s_y0;
            float s_x1 = s1(path_list.at(i).s.at(j) + 0.1);
            float s_y1 = s2(path_list.at(i).s.at(j) + 0.1);
            float a_refer = s_y0 - s_y1;
            float b_refer = s_x1 - s_x0;
            float c_refer = s_x0 * s_y1 - s_x1 * s_y0;
            angle_s = atan2(-a_refer, b_refer);

            if (road_line.size() > 0) {     // if road middle line size is not zero
                float a_middle = road_line.at(5).y_coord - road_line.at(10).y_coord;
                float b_middle = road_line.at(10).x_coord - road_line.at(5).x_coord;
                float c_middle = road_line.at(5).x_coord * road_line.at(10).y_coord - road_line.at(10).x_coord * road_line.at(5).y_coord;
                angle_d = atan2(-a_middle, b_middle);
                int nResult;
                JudgePoint2Line(road_line.at(5), road_line.at(10), s_fir_pnt, nResult);
                float tao = nResult*fabs(a_middle*s_x0 + b_middle*s_y0 + c_middle)/sqrt(a_middle*a_middle + b_middle*b_middle);
                float theta = angle_s - angle_d;
                if (theta != M_PI_2 || theta != M_PI_2) {
                    float vertical_d = path_list.at(i).d.at(j) - tao;
                    float side_d = vertical_d/cos(theta);
                    x1 = s_x0 - side_d * sin(angle_s);
                    y1 = s_y0 + side_d * cos(angle_s);
                    path_list.at(i).x.push_back(x1);
                    path_list.at(i).y.push_back(y1);

                }
            }
            else {    // if there is no road middle line
                x1 = s_x0 - path_list.at(i).d.at(j)*sin(angle_s);
                y1 = s_y0 + path_list.at(i).d.at(j)*cos(angle_s);
                path_list.at(i).x.push_back(x1);
                path_list.at(i).y.push_back(y1);
            }
        }
    }

    // discard the lines which have obstacle points in them to avoid collision
    int m, n, l;
    for (m = 0; m < path_list.size(); ++m) {    // there are 100 paths which have been calculated before, i.e. road width ranges from -5m to 5m and the terminal time from 10s to 30s
        for (n = 0; n < path_list.at(m).d.size(); ++n) {  // for the mth path, go through the path points
            for (l = 0; l < obstacles.size(); l++) {  // obstacles indicate the recived obstacles GPS
                float delta_x = obstacles.at(l).x_coord - path_list.at(m).x.at(n);
                float delta_y = obstacles.at(l).y_coord - path_list.at(m).y.at(n);
                float dis_obstacle = sqrt(delta_x * delta_x + delta_y * delta_y);
                if ( dis_obstacle < 4 ) break;   // if the distance is lesser than 2m, discard the prediction line
            }
            if (l < obstacles.size()) break;    // if the inner of loop has been break, break, serach next predicted path
        }
        if (n < path_list.at(m).d.size()) continue;   // if the path which has obstacles was discarded, continue to search the next alternative predicted path
        path_list_without_crash.push_back(path_list.at(m));
    }

    float min_cost = std::numeric_limits<float>::max();  // define a variable to store the minimal cost
    int index = 0;
    for (int i = 0; i < path_list_without_crash.size(); ++i) {
        if (path_list_without_crash.at(i).cost < min_cost) {
            min_cost = path_list_without_crash.at(i).cost;
            index = i;   // store the index of the path which has the min_cos
        }
    }
   optimal_path_points.clear();
    if (path_list_without_crash.size() > 0) {
        for (int i = 0; i < path_list_without_crash.at(index).x.size(); ++i) {
            Widgetloc optimal_points;
            optimal_points.x_coord = path_list_without_crash.at(index).x.at(i);
            optimal_points.y_coord = path_list_without_crash.at(index).y.at(i);
            optimal_path_points.append(QPointF(optimal_points.x_coord, optimal_points.y_coord));
        }
    }
    qDebug() << " This is optimal path" << optimal_path_points;
    // set optimal path
    /*QPainterPath optimal_path(optimal_path_points.at(0));
    for (int i = 0; i < optimal_path_points.size(); ++i) {
        optimal_path.lineTo(optimal_path_points.at(i));
    }
    optimal_path_cp = optimal_path;*/
    update();
    //this->show();

}

void PaintWidget::JudgePoint2Line(Widgetloc &LinePtA, Widgetloc &LinePtB, Widgetloc &LinePtC, int &out)
{
    double ax = LinePtB.x_coord - LinePtA.x_coord;
    double ay = LinePtB.y_coord - LinePtA.y_coord;
    double bx = LinePtC.x_coord - LinePtA.x_coord;
    double by = LinePtC.y_coord - LinePtA.y_coord;
    double judge = ax*by - ay*bx;
    if (judge > 0) {
        out = 1;
    }
    else if (judge < 0) {
        out = -1;
    }
    else {
        out = 0;
    }

}

PaintWidget::~PaintWidget()
{
    delete ui;
}
