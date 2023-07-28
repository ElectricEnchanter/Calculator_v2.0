#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent, s21::Controller &con)
    : QDialog(parent), ui(new Ui::Graph), con_(&con) {
  ui->setupUi(this);

  ui->widget->xAxis->setRange(-15, 15);
  ui->widget->yAxis->setRange(-15, 15);

  ui->widget->addGraph();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);

  ui->widget->replot();
}

Graph::~Graph() { delete ui; }

void Graph::on_exit_clicked() { this->close(); }

void Graph::on_erase_clicked() {
  ui->inputLine->setText("");
  ui->inputXLine->setText("");
}

void Graph::on_buildButton_clicked() {
  std::string input = ui->inputLine->text().toStdString();
  std::string input_x = ui->inputXLine->text().toStdString();
  double Dot = stod(input_x);
  ui->widget->xAxis->setRange(-Dot, Dot);
  ui->widget->yAxis->setRange(-Dot, Dot);
  ui->widget->clearGraphs();

  try {
    con_->CalculateGraph(input, input_x);
    ui->widget->addGraph();
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDot, Qt::red, Qt::red, 30));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    std::vector<double> x = con_->GetxСoordinates();
    std::vector<double> y = con_->GetyСoordinates();
    ui->widget->graph(0)->addData(QVector<double>(x.begin(), x.end()),
                                  QVector<double>(y.begin(), y.end()));
    ui->widget->replot();

  } catch (std::string error_message) {
    ui->inputLine->setText(QString::fromStdString(error_message));
  }
}
