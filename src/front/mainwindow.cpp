#include "mainwindow.h"

#include "QDebug"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, s21::Controller &controller)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(&controller),
      graph(parent, controller) {
  ui->setupUi(this);
  ui->dockWidget->hide();
  ui->dockWidget_2->hide();

  connect(ui->digit, &QButtonGroup::buttonClicked, this, &MainWindow::digit);
  connect(ui->digit2, &QButtonGroup::buttonClicked, this, &MainWindow::digit2);

  QLocale lo(QLocale::C);
  lo.setNumberOptions(QLocale::RejectGroupSeparator);
  auto val = new QDoubleValidator(0, 1000000, 2, this);
  val->setLocale(lo);
  ui->input->setValidator(val);
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

  std::string result = controller_->Calculate(input, input_x);
  ui->input->setText(QString::fromStdString(result));
}

void MainWindow::on_addAdededPartsButton_clicked() {
  if (ui->addAdededPartsButton->isChecked()) {
    ui->dockWidget->show();
    ui->dockWidget_2->show();
  } else {
    ui->dockWidget->hide();
    ui->dockWidget_2->hide();
  }
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
