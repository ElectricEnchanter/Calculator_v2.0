#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

//#include "../back/Calculator.h"
#include "../back/Controller.h"

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

public:
  Graph(QWidget *parent, s21::Controller &con);

  ~Graph();

private slots:
  void on_exit_clicked();

  void on_erase_clicked();

  void on_buildButton_clicked();

private:
  Ui::Graph *ui;
  s21::Controller *con_;
};

#endif // GRAPH_H
