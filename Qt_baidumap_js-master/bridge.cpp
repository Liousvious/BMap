#include "bridge.h"

#include <QMessageBox>
bridge::bridge() {}

bridge *bridge::instance() {
  static bridge s_obj;
  return &s_obj;
}

void bridge::showMsgBox()
{
    QMessageBox::aboutQt(nullptr, tr("Qt"));
}
