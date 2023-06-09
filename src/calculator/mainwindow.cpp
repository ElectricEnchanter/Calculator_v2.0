#include "mainwindow.h"

#include "QDebug"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->groupBox2->hide();
  ui->groupBox->hide();
  connect(ui->digit, &QButtonGroup::buttonClicked, this, &MainWindow::digit);
  connect(ui->digit2, &QButtonGroup::buttonClicked, this, &MainWindow::digit2);
  ui->XInput->setValidator(new QIntValidator(0, 100000, this));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digit(QAbstractButton *btm) {
  if (ui->input->text() == "INVALID CHARACTER(S)" ||
      ui->input->text() == "EMPTY LINE") {
    ui->input->setText("");
  }
  QString text = btm->text();
  ui->input->setText(ui->input->text() + text);
}

void MainWindow::digit2(QAbstractButton *btm) {
  if (ui->input->text() == "INVALID CHARACTER(S)" ||
      ui->input->text() == "EMPTY LINE") {
    ui->input->setText("");
  }
  QString text = btm->text();
  ui->input->setText(ui->input->text() + text + '(');
}

void MainWindow::on_Graph_clicked() {
  graph.setModal(true);
  graph.setWindowTitle("ГРАФИК");
  graph.exec();
}

void MainWindow::on_Credit_clicked() {
  loancalc.setModal(true);
  loancalc.setWindowTitle("КРЕДИТ");
  loancalc.exec();
}

void MainWindow::on_Deposit_clicked() {
  depcalc.setModal(true);
  depcalc.setWindowTitle("ДЕПОЗИТ");
  depcalc.exec();
}

void MainWindow::on_equal_clicked() {
  std::string input = ui->input->text().toStdString();
  std::string input_x = ui->XInput->text().toStdString();
  s21::Token view;

  try {
    view.CalculateAnswer(input, input_x);
    ui->input->setText(QString::number(view.GetAnswer()));
  } catch (std::string error_message) {
    ui->input->setText(QString::fromStdString(error_message));
  }
}

void MainWindow::on_addAdededPartsButton_clicked() {
  if (ui->addAdededPartsButton->isChecked())
    ui->groupBox2->show();
  else
    ui->groupBox2->hide();
}

void MainWindow::on_addFuncButton_valueChanged(int value) {
  if (value == 1)
    ui->groupBox->show();
  else
    ui->groupBox->hide();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
    on_equal_clicked();
  }
}

void MainWindow::on_AC_clicked() {
  ui->input->setText("");
  ui->XInput->setText("");
}
