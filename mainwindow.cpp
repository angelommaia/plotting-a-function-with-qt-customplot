#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle); //os pontos sao representados por um circulo
    //ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone); //sem linha entre os pontos
    ui->plot->setInteraction(QCP::iRangeDrag); //permite arrastar o grafico

    ui->plot->setInteraction(QCP::iRangeZoom); //permite dar zoom no grafico

    ui->plot->xAxis->setRange(-8,8);
    ui->plot->yAxis->setRange(-8,8);
    ui->plot->xAxis->setLabel("Eixo x");
    ui->plot->yAxis->setLabel("Eixo y");

    ui->plot->legend->setVisible(true);

    addRandomGraph(); //funcao que acrescenta um graf aleatorio definido no fim desse arquivo. deve ser usada mais tarde com o dado externo
    ui->plot->rescaleAxes(true); ///preciso entender melhor o que isso faz de fato
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::addPoint(double x, double y){
    qv_x.append(x);
    qv_y.append(y);
}

void MainWindow::clearData(){
    ui->plot->clearGraphs(); //limpa todos os graficos da tela
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::plot(){
    ui->plot->graph(0)->setData(qv_x,qv_y);
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::on_btn_add_clicked(){
  addPoint(ui->bx_x->value(), ui->bx_y->value());
  plot();
}

void MainWindow::on_btn_clear_clicked(){
    clearData(); //chama a funcao para limpar a tela ao apertar o botao "limpar tela" na gui
  //  plot(); //estava dando crash com essa funcao
}

void MainWindow::addRandomGraph()
{
  int n = 50; // number of points in graph
  double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
  double yOffset = (rand()/(double)RAND_MAX - 0.5)*10;
  double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; i++)
  {
    x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
    y[i] = (qSin(x[i]*r1*5)*qSin(qCos(x[i]*r2)*r4*3)+r3*qCos(qSin(x[i])*r4*2))*yScale + yOffset;
  }

  ui->plot->addGraph();
  ui->plot->graph()->setName(QString("New graph %1").arg(ui->plot->graphCount()-1));
  ui->plot->graph()->setData(x, y);
  ui->plot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
  if (rand()%100 > 50)
    ui->plot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
  QPen graphPen;
  graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
  graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
  ui->plot->graph()->setPen(graphPen);
  ui->plot->replot();
}
