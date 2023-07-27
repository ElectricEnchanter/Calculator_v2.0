#ifndef LOANCALC_H
#define LOANCALC_H

#include <QDialog>
#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include <QtMath>

#include "ui_loancalc.h"

namespace Ui {
class LoanCalc;
}

class LoanCalc : public QDialog {
  Q_OBJECT

public:
  explicit LoanCalc(QWidget *parent = nullptr);
  ~LoanCalc();
  QCPBars *procents;
  QCPBars *restSum;

private slots:
  void on_equalButton_clicked();

  void on_eraseButton_clicked();

  void on_exitButton_clicked();

private:
  Ui::LoanCalc *ui;
  QVector<double> ticks;
  QVector<QString> labels;
  QVector<QString> mesac;
};

#endif // LOANCALC_H
