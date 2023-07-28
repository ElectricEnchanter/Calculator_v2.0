#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QMainWindow>
#include <QResource>
#include <QVariant>
#include <QVariantList>
#include <QVector>

#include "../back/Controller.h"
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
  MainWindow(QWidget *parent, s21::Controller &controller);
  ~MainWindow();

private slots:

  void digit(QAbstractButton *btm);

  void digit2(QAbstractButton *btm);

  void on_Graph_clicked();

  void on_Credit_clicked();

  void on_Deposit_clicked();

  void on_equal_clicked();

  void on_addAdededPartsButton_clicked();

  void on_AC_clicked();

protected:
  void keyPressEvent(QKeyEvent *event);

private:
  Ui::MainWindow *ui;
  s21::Controller *controller_;
  Graph graph;
  LoanCalc loancalc;
  DepCalc depcalc;
};
#endif // MAINWINDOW_H
