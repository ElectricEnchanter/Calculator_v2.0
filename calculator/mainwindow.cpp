#include "mainwindow.h"

#include "depcalc.h"
#include "graph.h"
#include "loancalc.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_Graph_clicked() {
  graph.setModal(true);
  graph.setWindowTitle("ГРАФИК");
  graph.exec();
}

void MainWindow::on_Credit_clicked() {
  loanCalc.setModal(true);
  loanCalc.setWindowTitle("КРЕДИТНЫЙ");
  loanCalc.exec();
}

void MainWindow::on_Deposit_clicked() {
  depCalc.setModal(true);
  depCalc.setWindowTitle("ДЕПОЗИТНЫЙ");
  depCalc.exec();
}
