#ifndef DEPCALC_H
#define DEPCALC_H

#include <QDialog>

namespace Ui {
class DepCalc;
}

class DepCalc : public QDialog {
  Q_OBJECT

 public:
  explicit DepCalc(QWidget *parent = nullptr);
  ~DepCalc();

 private slots:
  void on_closeButton_clicked();

  void on_periodStartInputButton_clicked();

  void on_periodEndInputButton_clicked();

  void on_calendarWidget_clicked(const QDate &date);

  void on_eraseButton_clicked();

  void on_equalButton_clicked();

 private:
  Ui::DepCalc *ui;
};

#endif  // DEPCALC_H
