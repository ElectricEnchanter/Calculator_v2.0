#ifndef DEPCALC_H
#define DEPCALC_H

#include <QDialog>

namespace Ui {
class DepCalc;
}

class DepCalc : public QDialog
{
    Q_OBJECT

public:
    explicit DepCalc(QWidget *parent = nullptr);
    ~DepCalc();

private:
    Ui::DepCalc *ui;
};

#endif // DEPCALC_H
