#include "loancalc.h"

#include "ui_loancalc.h"

LoanCalc::LoanCalc(QWidget *parent) : QDialog(parent), ui(new Ui::LoanCalc) {
  ui->setupUi(this);
  ui->inputSum->setValidator(new QIntValidator(0, 10000000, this));
  ui->inputTerm->setValidator(new QIntValidator(0, 100, this));
  ui->inputRate->setValidator(new QIntValidator(0, 10, this));
  procents = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
  restSum = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);

  QLinearGradient gradient(0, 0, 0, 400);
  gradient.setColorAt(0, QColor(173, 255, 47));
  gradient.setColorAt(0.38, QColor(205, 505, 105));
  gradient.setColorAt(1, QColor(70, 70, 70));
  ui->widget->setBackground(QBrush(gradient));
}

LoanCalc::~LoanCalc() { delete ui; }

void LoanCalc::on_equalButton_clicked() {
  if (ui->inputSum->text().isEmpty() || ui->inputTerm->text().isEmpty() ||
      ui->inputRate->text().isEmpty()) {
  } else {
    ui->widget->clearGraphs();

    double ostat = atof(ui->inputSum->text().toLocal8Bit());
    int month = atof(ui->inputTerm->text().toLocal8Bit());
    double stavka = atof(ui->inputRate->text().toLocal8Bit());
    double mesProc = stavka / (100 * 12);
    int newIndex = ui->inputPayType->currentIndex();

    // create empty bar chart objects:

    double platOsnDolg;
    double procent;

    // set names and colors:

    procents->setAntialiased(false);
    restSum->setAntialiased(false);
    procents->setStackingGap(1);
    restSum->setStackingGap(1);

    restSum->setName("Основной долг");
    restSum->setPen(QPen(QColor(111, 9, 176).lighter(170)));
    restSum->setBrush(QColor(111, 9, 176));
    procents->setName("Проценты");
    procents->setPen(QPen(QColor(250, 170, 20).lighter(150)));
    procents->setBrush(QColor(250, 170, 20));
    procents->moveAbove(restSum);

    // stack bars on top of each other:

    // prepare x axis with country labels:
    labels << "Август"
           << "Сентябрь"
           << "Октябрь"
           << "Ноябрь"
           << "Декабрь"
           << "Январь"
           << "Февраль"
           << "Март"
           << "Апрель"
           << "Май"
           << "Июнь"
           << "Июль";

    for (int i = 0; i < month; i++) {
      ticks.push_back(i); //тут вектор даблов
      mesac.push_back(labels[i % 12]);
    }

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(QVector<double>(ticks), mesac);
    ui->widget->xAxis->setTicker(textTicker);
    ui->widget->xAxis->setTickLabelRotation(180);
    ui->widget->xAxis->setSubTicks(false);
    ui->widget->xAxis->setTickLength(0, 4);
    ui->widget->xAxis->setRange(0, 8);
    ui->widget->xAxis->setBasePen(QPen(Qt::white));
    ui->widget->xAxis->setTickPen(QPen(Qt::white));
    ui->widget->xAxis->grid()->setVisible(true);
    ui->widget->xAxis->grid()->setPen(
        QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->widget->xAxis->setTickLabelColor(Qt::white);
    ui->widget->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->widget->yAxis->setRange(0, 10000);
    ui->widget->yAxis->setPadding(5); // a bit more space to the left border
    ui->widget->yAxis->setLabel("Ежемесячный платеж");
    ui->widget->yAxis->setBasePen(QPen(Qt::white));
    ui->widget->yAxis->setTickPen(QPen(Qt::white));
    ui->widget->yAxis->setSubTickPen(QPen(Qt::white));
    ui->widget->yAxis->grid()->setSubGridVisible(true);
    ui->widget->yAxis->setTickLabelColor(Qt::white);
    ui->widget->yAxis->setLabelColor(Qt::white);
    ui->widget->yAxis->grid()->setPen(
        QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->widget->yAxis->grid()->setSubGridPen(
        QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> restSumData, procentsData;
    double sumPlate;
    if (newIndex == 0) {
      sumPlate = ostat * (mesProc / (1 - (pow(1 + mesProc, -month))));
      double pereplata = (sumPlate * month) - ostat;

      ui->outputMonPay->setText(QString::number(sumPlate, 'f', 2));
      ui->outputAccrInter->setText(QString::number(pereplata, 'f', 2));
      ui->outputSumDebtInter->setText(
          QString::number(ostat + pereplata, 'f', 2));

      procent = ostat * ((stavka / 100) / 12);
      platOsnDolg = sumPlate - procent;
      ostat -= platOsnDolg;

      for (int i = 1; i <= month; i++) {
        procent = ostat * ((stavka / 100) / 12);
        platOsnDolg = sumPlate - procent;
        ostat -= platOsnDolg;
        restSumData.push_back(platOsnDolg);
        procentsData.push_back(procent);
      }
    } else {
      double platOsnDolg = ostat / month;
      procent = (ostat * stavka / 100 * (365 / 12.0)) / 365;
      ui->outputMonPay->setText(QString::number(platOsnDolg + procent, 'f', 2));
      double ostat2 = ostat;
      double dolg = 0;
      double dolg2 = 0;

      ostat -= platOsnDolg;

      for (int i = 1; i <= month; i++) {
        dolg2 = procent;
        dolg += procent;
        procent = (ostat * stavka / 100 * (365 / 12.0)) / 365;
        ostat -= platOsnDolg;
        restSumData.push_back(platOsnDolg);
        procentsData.push_back(procent);
      }

      ui->outputMonPay->setText(ui->outputMonPay->text() + "..." +
                                QString::number(platOsnDolg + dolg2, 'f', 2));
      ui->outputAccrInter->setText(QString::number(dolg, 'f', 2));
      ui->outputSumDebtInter->setText(QString::number(dolg + ostat2, 'f', 2));
    }

    restSum->setData(ticks, restSumData);
    procents->setData(ticks, procentsData);

    // setup legend:
    ui->widget->legend->setVisible(true);
    ui->widget->legend->setBrush(QColor(255, 255, 255, 100));
    ui->widget->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->widget->legend->setFont(legendFont);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->widget->replot();
    ticks.clear();
    mesac.clear();
    labels.clear();
  }
}

void LoanCalc::on_eraseButton_clicked() {
  ui->inputSum->setText("");
  ui->inputTerm->setText("");
  ui->inputRate->setText("");
  ui->outputAccrInter->setText("");
  ui->outputSumDebtInter->setText("");
  ui->outputMonPay->setText("");
}

void LoanCalc::on_exitButton_clicked() { this->close(); }
