#include "ImuChart.h"

ImuChart::ImuChart(QLabel *shower,unsigned int axisXMax,unsigned int axisYMax,QString label,QWidget *parent):
    QChartView (parent),
    chart(new QChart),
    serie(new ImuLineSeries(shower)),
    axisX(new QValueAxis),
    axisY(new QValueAxis)
{
    setDragMode(QGraphicsView::RubberBandDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRubberBand(QChartView::RectangleRubberBand);
    QChartView::setChart(chart);
    this->axisXMax = axisXMax;
    axisX->setRange(0,axisXMax);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("axisX");

    this->axisYMax = axisYMax;
    axisY->setRange(-int(axisYMax),axisYMax);
    axisY->setTitleText("axisY");

    for(unsigned int i=0;i<axisXMax;i++){
       serie->append(i,0);
    }
    serie->setUseOpenGL(true); //openGl 加速
    setBaseSize(200,200);
    chart->addSeries(serie);
    chart->setAxisX(axisX,serie);
    chart->setAxisY(axisY,serie);
    chart->legend()->hide();
    this->label = label;
    chart->setTitle(this->label);

    coordX = new QGraphicsSimpleTextItem(chart);
    coordX->setPos(chart->size().width()/2 - 50, chart->size().height());
    coordX->setText("X: ");
    coordX->setVisible(false);
    coordY = new QGraphicsSimpleTextItem(chart);
    coordY->setPos(chart->size().width()/2 + 50, chart->size().height());
    coordY->setText("Y: ");
    coordY->setVisible(false);

    ImageLine = new ImuVerticalLine(0,axisY,Qt::green);
    chart->addSeries(ImageLine);
    chart->setAxisX(axisX,ImageLine);
    chart->setAxisY(axisY,ImageLine);
    this->setCursor(Qt::CrossCursor);
    chart->setAcceptHoverEvents(true);
    this->setMouseTracking(true);
}

bool ImuChart::setSerie(QList<QPointF> points)
{
    serie->clear();
    serie->append(points);
    return true;
}
bool ImuChart::addLine(int position)
{
    ImuVerticalLine *serietemp = new ImuVerticalLine(position,axisY);
    serietemp->setColor(Qt::red);
    chart->addSeries(serietemp);
    chart->setAxisX(axisX,serietemp);
    chart->setAxisY(axisY,serietemp);
    push_back(serietemp,position);
    return true;
}
bool ImuChart::addMarker(int position)
{
    ImuVerticalLine *serietemp = new ImuVerticalLine(position,axisY);
    //serietemp->setColor(Qt::blue);
    serietemp->setPen(QPen(Qt::yellow, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
    chart->addSeries(serietemp);
    chart->setAxisX(axisX,serietemp);
    chart->setAxisY(axisY,serietemp);
    Markerpush_back(serietemp,position);
    return true;
}
unsigned int ImuChart::GetaxisXMax()
{
    return axisXMax;
}

bool ImuChart::setLabel(QString label)
{
    this->label = label;
    return true;
}

bool ImuChart::showRedLine(bool show)
{
    for(auto serie : Markerseries)
        serie->setVisible(show);
    return true;
}

void ImuChart::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
         chart->resize(event->size());
         coordX->setPos(chart->size().width()/2 - 50, chart->size().height() - 20);
         coordY->setPos(chart->size().width()/2 + 50, chart->size().height() - 20);
    }
    QGraphicsView::resizeEvent(event);
}

void ImuChart::mouseMoveEvent(QMouseEvent *event)
{
    coordX->setText(QString("X: %1").arg(chart->mapToValue(event->pos()).x()));
    coordY->setText(QString("Y: %1").arg(chart->mapToValue(event->pos()).y()));
    QGraphicsView::mouseMoveEvent(event);
}

void ImuChart::mouseDoubleClickEvent(QMouseEvent *event)
{
    int position = int(chart->mapToValue(event->pos()).x());
    addLine(position);
    emit(add(position));
    QGraphicsView::mouseDoubleClickEvent(event);
}

bool ImuChart::ishave(int position)
{
    if(positions.indexOf(position)!=-1)
        return true;
    else
        return false;
}

void ImuChart::push_back(ImuVerticalLine *serie, int position)
{
    series.push_back(serie);
    positions.push_back(position);
    connect(serie, &ImuVerticalLine::deleteme, this, &ImuChart::emitDelLine);
}

void ImuChart::Markerpush_back(ImuVerticalLine *serie, int position)
{
    Markerseries.push_back(serie);
    MarkerPosition.push_back(position);
//    connect(serie, &ImuVerticalLine::deleteme, this, &ImuChart::emitDelLine);
}

void ImuChart::emitDelLine(int position)
{
    delLine(position);
    emit(del(position));
}
void ImuChart::delLine(int position)
{
    int iter = positions.indexOf(position);
    positions.remove(iter);
    series[iter]->hide();
    chart->removeSeries(series[iter]);
    series.remove(iter);
}
void ImuChart::delMarker(int position)
{
    int iter = MarkerPosition.indexOf(position);
    MarkerPosition.remove(iter);
    Markerseries[iter]->hide();
    chart->removeSeries(Markerseries[iter]);
    Markerseries.remove(iter);
}
void ImuChart::clearLineList()
{
    for (int var=0;var<series.size();var++){
        chart->removeSeries(series[var]);
    }
    for (int var=0;var<Markerseries.size();var++){
        chart->removeSeries(Markerseries[var]);
    }
    positions.clear();
    MarkerPosition.clear();
    series.clear();
    Markerseries.clear();
}
ImuChart::~ImuChart()
{
    delete chart;
    delete serie;
    delete axisX;
    delete axisY;
    delete coordX;
    delete coordY;
    delete ImageLine;
}
