#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  h = 0.01;

  ui->widget->xAxis->setRange(-15, 15);
  ui->widget->yAxis->setRange(-15, 15);

  ui->widget->addGraph();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->graph(0)->addData(x, y);
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
  s21::Calculator view;
  double Dot = stod(input_x);
  ui->widget->xAxis->setRange(-Dot, Dot);
  ui->widget->yAxis->setRange(-Dot, Dot);
  ui->widget->clearGraphs();
  x.clear();
  y.clear();

  std::string x_value = std::to_string(X);
  try {
    for (X = -Dot; X <= fabs(Dot); X += h) {
      x_value = std::to_string(X);
      view.CalculateAnswer(input, x_value);
      x.push_back(X);
      y.push_back(view.GetAnswer());
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDot, Qt::red, Qt::red, 30));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();

  } catch (std::string error_message) {
    ui->inputLine->setText(QString::fromStdString(error_message));
  }
}
