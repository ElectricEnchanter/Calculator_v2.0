#include "loancalc.h"
#include "ui_loancalc.h"

LoanCalc::LoanCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoanCalc)
{
    ui->setupUi(this);
}

LoanCalc::~LoanCalc()
{
    delete ui;
}
