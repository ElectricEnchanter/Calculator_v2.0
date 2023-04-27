#include "depcalc.h"

#include "ui_depcalc.h"

DepCalc::DepCalc(QWidget *parent) : QDialog(parent), ui(new Ui::DepCalc) {
  ui->setupUi(this);
  ui->calendarWidget->hide();

  ui->depAmountInput->setValidator(new QIntValidator(0, 10000000, this));
  ui->interRateInput->setValidator(new QIntValidator(0, 10, this));
}

DepCalc::~DepCalc() { delete ui; }

void DepCalc::on_closeButton_clicked() { this->close(); }
