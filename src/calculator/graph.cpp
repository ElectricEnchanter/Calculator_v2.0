#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  double h = 0.0001;

  ui->widget->xAxis->setRange(-15, 15);
  ui->widget->yAxis->setRange(-15, 15);

  ui->widget->addGraph();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  //  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

Graph::~Graph() { delete ui; }

void Graph::on_exit_clicked() { this->close(); }

void Graph::on_erase_clicked() {
  ui->inputLine->setText("");
  ui->inputXLine->setText("");
}
