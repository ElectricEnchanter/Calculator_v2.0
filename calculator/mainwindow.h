#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

 private:
  Ui::MainWindow *ui;
  Graph graph;
  DepCalc depCalc;
  LoanCalc loanCalc;
};
#endif  // MAINWINDOW_H
