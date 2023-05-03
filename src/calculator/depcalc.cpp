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

void DepCalc::on_periodStartInputButton_clicked() {
  if (ui->periodStartInputButton->isChecked()) {
    ui->calendarWidget->show();
  } else
    ui->calendarWidget->hide();
}

void DepCalc::on_periodEndInputButton_clicked() {
  if (ui->periodEndInputButton->isChecked()) {
    ui->calendarWidget->show();
  } else
    ui->calendarWidget->hide();
}

void DepCalc::on_calendarWidget_clicked(const QDate &date) {
  if (ui->periodStartInputButton->text() == "yyyy.mm.dd") {
    ui->periodStartInputButton->setText(date.toString("yyyy.MM.dd"));
    ui->periodStartInputButton->setStyleSheet("color:#FFFFFF");
  } else {
    ui->periodEndInputButton->setText(date.toString("yyyy.MM.dd"));
    ui->periodEndInputButton->setStyleSheet("color:#FFFFFF");
  }
  ui->calendarWidget->hide();
}

void DepCalc::on_eraseButton_clicked() {
  ui->depAmountInput->setText("");
  ui->periodStartInputButton->setText("");
  ui->periodEndInputButton->setText("");
  ui->interRateInput->setText("");
  ui->periodStartInputButton->setText("yyyy.mm.dd");
  ui->periodEndInputButton->setText("yyyy.mm.dd");
  ui->periodStartInputButton->setStyleSheet("color:#00796B");
  ui->periodEndInputButton->setStyleSheet("color:#00796B");
}

void DepCalc::on_equalButton_clicked() {
  QByteArray ar = (ui->periodStartInputButton->text().toLocal8Bit());
  char *inputStart = ar.data();
  QByteArray ar2 = (ui->periodEndInputButton->text().toLocal8Bit());
  char *inputEnd = ar2.data();

  if (ui->depAmountInput->text().isEmpty() ||
      ui->interRateInput->text().isEmpty() ||
      ui->periodStartInputButton->text() == "yyyy.mm.dd" ||
      ui->interRateInput->text() == "yyyy.mm.dd") {
    //      ui->statusbar->showMessage("Данные введены не полностью");
  } else {
    //      ui->statusbar->showMessage("");
    double depAmount = atof(ui->depAmountInput->text().toLocal8Bit());
    double interRate = atof(ui->interRateInput->text().toLocal8Bit());

    double procents = 0;
    double payout2 = 0;
    double payout = depAmount;
    double depAmount2 = depAmount;
    int payoutCount = 0;
    int y, m, d, y1, m1, d1;
    int days = 365;
    //          int days = ymd_to_mord(inputEnd) - ymd_to_mord(inputStart) - 1;
    sscanf(inputStart, "%d.%d.%d", &y, &m, &d);
    sscanf(inputEnd, "%d.%d.%d", &y1, &m1, &d1);
    QVector<QString> labels;
    labels << "Дата"
           << "Начислено процентов"
           << "Вклад пополнен"
           << "Остаток на вкладе";
    ui->tableWidget->setColumnCount(4);  // Указываем число колонок
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    ui->tableWidget->setShowGrid(true);  // Включаем сетку
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    //  ui->tableWidget->resizeColumnsToContents();

    if (!ui->capitalization->checkState()) {
      switch (ui->payFrequencyBox->currentIndex()) {
        case 0:
          procents = (depAmount * interRate * days / 365) / 100;
          ui->AccruedIntOutput->setText(QString::number(procents, 'f', 2));
          ui->endAmountOutput->setText(QString::number(depAmount, 'f', 2));
          payoutCount = days / 30;

          ui->tableWidget->setRowCount(payoutCount + 1);
          for (int i = 0; i <= payoutCount; i++) {
            ui->tableWidget->setItem(
                i, 0,
                new QTableWidgetItem(QString::number(y) + '.' +
                                     QString::number(m) + '.' +
                                     QString::number(d)));
            if (i != 0) {
              ui->tableWidget->setItem(i, 1,
                                       new QTableWidgetItem(QString::number(
                                           procents / payoutCount, 'f', 2)));
              ui->tableWidget->setItem(i, 2, new QTableWidgetItem("0.00"));
            } else
              ui->tableWidget->setItem(
                  i, 2,
                  new QTableWidgetItem(QString::number(depAmount, 'f', 2)));
            ui->tableWidget->setItem(
                i, 3, new QTableWidgetItem(QString::number(depAmount, 'f', 2)));
            payout2 = depAmount2 * (interRate / 100) / 365 * 30;
            depAmount2 += payout2;
            m += 1;
            if (m > 12) {
              m %= 12;
              y++;
            }
          }
          break;
        case 1:
          procents = (depAmount * interRate * days / 365) / 100;  // четка
          payoutCount = days / 365 + 1;
          ui->tableWidget->setRowCount(payoutCount);
          for (int i = 0; i <= payoutCount; i++) {
            ui->tableWidget->setItem(
                i, 0,
                new QTableWidgetItem(QString::number(y) + '.' +
                                     QString::number(m) + '.' +
                                     QString::number(d)));
            if (i != 0) {
              ui->tableWidget->setItem(
                  i, 1,
                  new QTableWidgetItem(
                      QString::number(procents / (payoutCount - 1), 'f', 2)));
              ui->tableWidget->setItem(i, 2, new QTableWidgetItem("0.00"));
            } else {
              ui->tableWidget->setItem(
                  i, 2,
                  new QTableWidgetItem(QString::number(depAmount, 'f', 2)));
            }
            ui->tableWidget->setItem(
                i, 3, new QTableWidgetItem(QString::number(depAmount, 'f', 2)));
            y++;
          }
          ui->AccruedIntOutput->setText(QString::number(procents, 'f', 2));
          ui->endAmountOutput->setText(QString::number(depAmount, 'f', 2));
          break;
        case 2:
          procents = (depAmount * interRate * days / 365) / 100;
          ui->AccruedIntOutput->setText(QString::number(procents, 'f', 2));
          ui->endAmountOutput->setText(QString::number(depAmount, 'f', 2));
          payoutCount = 2;
          ui->tableWidget->setRowCount(payoutCount);
          for (int i = 0; i <= payoutCount; i++) {
            ui->tableWidget->setItem(
                i, 0,
                new QTableWidgetItem(QString::number(y) + '.' +
                                     QString::number(m) + '.' +
                                     QString::number(d)));
            if (i != 0) {
              ui->tableWidget->setItem(
                  i, 1,
                  new QTableWidgetItem(QString::number(procents, 'f', 2)));
              ui->tableWidget->setItem(i, 2, new QTableWidgetItem("0.00"));
            } else
              ui->tableWidget->setItem(
                  i, 2,
                  new QTableWidgetItem(QString::number(depAmount, 'f', 2)));
            ui->tableWidget->setItem(
                i, 3, new QTableWidgetItem(QString::number(depAmount, 'f', 2)));

            y = y1;
            m = m1;
            d = d1;
          }
          break;
      }

    } else {
      switch (ui->payFrequencyBox->currentIndex()) {
        case 0:
          procents = depAmount * pow(1 + (((interRate / 100) / 12)), days / 30);
          payoutCount = days / 30;

          ui->tableWidget->setRowCount(payoutCount + 1);
          ui->AccruedIntOutput->setText(
              QString::number(procents - depAmount, 'f', 2));
          ui->endAmountOutput->setText(
              QString::number((procents - depAmount) + depAmount, 'f', 2));
          for (int i = 0; i <= payoutCount; i++) {
            ui->tableWidget->setItem(
                i, 0,
                new QTableWidgetItem(QString::number(y) + '.' +
                                     QString::number(m) + '.' +
                                     QString::number(d)));
            if (i != 0) {
              ui->tableWidget->setItem(
                  i, 1, new QTableWidgetItem(QString::number(payout2, 'f', 2)));
              ui->tableWidget->setItem(
                  i, 2, new QTableWidgetItem(QString::number(payout2, 'f', 2)));
            } else
              ui->tableWidget->setItem(
                  i, 2, new QTableWidgetItem(QString::number(payout, 'f', 2)));
            ui->tableWidget->setItem(
                i, 3,
                new QTableWidgetItem(QString::number(depAmount2, 'f', 2)));
            payout2 = depAmount2 * (interRate / 100) / 365 * 30;
            depAmount2 += payout2;
            m += 1;
            if (m > 12) {
              m %= 12;
              y++;
            }
          }
          break;

        case 1:
          procents = depAmount * pow(1 + (((interRate / 100) / 1)), days / 365);
          payoutCount = days / 365 + 1;

          ui->tableWidget->setRowCount(payoutCount);
          ui->AccruedIntOutput->setText(
              QString::number(procents - depAmount, 'f', 2));
          ui->endAmountOutput->setText(
              QString::number((procents - depAmount) + depAmount, 'f', 2));

          for (int i = 0; i <= payoutCount; i++) {
            ui->tableWidget->setItem(
                i, 0,
                new QTableWidgetItem(QString::number(y) + '.' +
                                     QString::number(m) + '.' +
                                     QString::number(d)));
            if (i != 0)
              ui->tableWidget->setItem(
                  i, 1, new QTableWidgetItem(QString::number(payout2, 'f', 2)));
            if (i != 0)
              ui->tableWidget->setItem(
                  i, 2, new QTableWidgetItem(QString::number(payout2, 'f', 2)));
            else
              ui->tableWidget->setItem(
                  i, 2, new QTableWidgetItem(QString::number(payout, 'f', 2)));
            ui->tableWidget->setItem(
                i, 3,
                new QTableWidgetItem(QString::number(depAmount2, 'f', 2)));
            depAmount2 = depAmount2 + (depAmount2 * (interRate / 100));
            payout = depAmount2 - depAmount;
            payout2 = payout - payout2;
            y++;
          }
          break;
        case 2:
          procents = (depAmount * interRate * days / 365) / 100;
          ui->AccruedIntOutput->setText(QString::number(procents, 'f', 2));
          ui->endAmountOutput->setText(
              QString::number(depAmount + procents, 'f', 2));
          payoutCount = 2;
          ui->tableWidget->setRowCount(payoutCount);
          for (int i = 0; i <= payoutCount; i++) {
            ui->tableWidget->setItem(
                i, 0,
                new QTableWidgetItem(QString::number(y) + '.' +
                                     QString::number(m) + '.' +
                                     QString::number(d)));
            if (i == 0) {
              ui->tableWidget->setItem(
                  i, 2,
                  new QTableWidgetItem(QString::number(depAmount, 'f', 2)));
              ui->tableWidget->setItem(
                  i, 3,
                  new QTableWidgetItem(QString::number(depAmount, 'f', 2)));

            } else {
              ui->tableWidget->setItem(
                  i, 1,
                  new QTableWidgetItem(QString::number(procents, 'f', 2)));

              ui->tableWidget->setItem(
                  i, 2,
                  new QTableWidgetItem(QString::number(procents, 'f', 2)));
              ui->tableWidget->setItem(i, 3,
                                       new QTableWidgetItem(QString::number(
                                           procents + depAmount, 'f', 2)));
            }

            y = y1;
            m = m1;
            d = d1;
          }
          break;
      }
    }
  }
}
