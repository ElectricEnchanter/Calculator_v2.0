#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <math.h>
#include <stdio.h>

#include <QAbstractButton>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QMainWindow>
#include <QResource>
#include <QVariant>
#include <QVariantList>
#include <QVector>

#include "depcalc.h"
#include "graph.h"
#include "loancalc.h"

extern "C++" {
#include "../Token.h"
}

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

  void digit(QAbstractButton *btm);

  void digit2(QAbstractButton *btm);

  void on_Graph_clicked();

  void on_Credit_clicked();

  void on_Deposit_clicked();

  void on_equal_clicked();

  void on_addAdededPartsButton_clicked();

  void on_addFuncButton_valueChanged(int value);

  void on_AC_clicked();

 protected:
  void keyPressEvent(QKeyEvent *event);

 private:
  Ui::MainWindow *ui;
  Graph graph;
  LoanCalc loancalc;
  DepCalc depcalc;
};
#endif  // MAINWINDOW_H
