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

  QLocale lo(QLocale::C);
  lo.setNumberOptions(QLocale::RejectGroupSeparator);
  auto val = new QDoubleValidator(0, 1000000, 2, this);
  val->setLocale(lo);
  ui->inputXLine->setValidator(val);
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
  if (input_x.empty()) {
    ui->inputLine->setText("MISSING X VALUE");
  } else {
    double Dot = stod(input_x);
    ui->widget->xAxis->setRange(-Dot, Dot);
    ui->widget->yAxis->setRange(-Dot, Dot);

    ui->widget->clearGraphs();

    std::string result = con_->CalculateGraph(input, input_x);
    ui->inputLine->setText(QString::fromStdString(result));
    ui->widget->addGraph();
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDot, Qt::red, Qt::red, 30));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    std::vector<double> x = con_->GetCoordinatesX();
    std::vector<double> y = con_->GetCoordinatesY();
    ui->widget->graph(0)->addData(QVector<double>(x.begin(), x.end()),
                                  QVector<double>(y.begin(), y.end()));
    ui->widget->replot();
  }
}
