#include "depcalc.h"
#include "ui_depcalc.h"

DepCalc::DepCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DepCalc)
{
    ui->setupUi(this);
}

DepCalc::~DepCalc()
{
    delete ui;
}
