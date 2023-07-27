#include <QApplication>

#include "../back/Controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Calculator cal;
  s21::Controller con(cal);
  MainWindow w(nullptr, con);

  w.setWindowTitle("СМАРТ КАЛк");
  w.show();
  return a.exec();
}
