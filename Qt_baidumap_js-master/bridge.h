#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>

class bridge : public QObject {
  Q_OBJECT
public:
  static bridge *instance();
public slots:
  void showMsgBox();

private:
  bridge();
};

#endif // BRIDGE_H
