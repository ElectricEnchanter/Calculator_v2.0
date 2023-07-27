#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

#include "../back/Token.h"

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

private slots:
  void on_exit_clicked();

  void on_erase_clicked();

  void on_buildButton_clicked();

private:
  Ui::Graph *ui;
  double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;
};

#endif // GRAPH_H
