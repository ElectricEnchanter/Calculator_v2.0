#ifndef LOANCALC_H
#define LOANCALC_H

#include <QDialog>

namespace Ui {
class LoanCalc;
}

class LoanCalc : public QDialog
{
    Q_OBJECT

public:
    explicit LoanCalc(QWidget *parent = nullptr);
    ~LoanCalc();

private:
    Ui::LoanCalc *ui;
};

#endif // LOANCALC_H
