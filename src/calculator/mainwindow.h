#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <math.h>
#include <stdio.h>

#include <QAbstractButton>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QMainWindow>
#include <QResource>
#include <QVector>

#include "depcalc.h"
#include "graph.h"
#include "loancalc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_Graph_clicked();

  void on_Credit_clicked();

  void on_Deposit_clicked();

  void on_equal_clicked();

 private:
  Ui::MainWindow *ui;
  Graph graph;
  LoanCalc loancalc;
  DepCalc depcalc;
};
#endif  // MAINWINDOW_H
