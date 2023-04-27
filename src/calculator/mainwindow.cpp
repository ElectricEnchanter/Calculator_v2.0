#include "mainwindow.h"

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
  loancalc.setModal(true);
  loancalc.setWindowTitle("КРЕДИТ");
  loancalc.exec();
}

void MainWindow::on_Deposit_clicked() {
  depcalc.setModal(true);
  depcalc.setWindowTitle("ДЕПОЗИТ");
  depcalc.exec();
}
