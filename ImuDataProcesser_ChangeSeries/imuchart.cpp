#include "imuchart.h"

ImuChart::ImuChart(QLabel *shower,unsigned int axisXMax,unsigned int axisYMax,QString label):
    chartView(new QChartView),
    chart(new QChart),
    serie(new ImuLineSeries(shower)),
    Spserie(new QSplineSeries),
    axisX(new QValueAxis),
    axisY(new QValueAxis)
{
    this->axisXMax = axisXMax;
    axisX->setRange(0,axisXMax);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("axisX");

    this->axisYMax = axisYMax;
    axisY->setRange(-int(axisYMax),axisYMax);
    axisY->setTitleText("axisY");
    chart->addSeries(serie);

    for(unsigned int i=0;i<axisXMax;i++){
       serie->append(i,0);
    }
    serie->setUseOpenGL(true);//openGl 加速

    chart->setAxisX(axisX,serie);
    chart->setAxisY(axisY,serie);
    chart->legend()->hide();
    this->label = label;
    chart->setTitle(this->label);

    chartView->setRubberBand(QChartView::RectangleRubberBand);
    chartView->setChart(chart);
}

QLineSeries* ImuChart::initSerie(int position)
{
    QLineSeries *serietemp = new QLineSeries;
    serietemp->setColor(QColor(1,0,0));
    serietemp->append(position,axisY->max());
    serietemp->append(position,axisY->min());
    serietemp->setUseOpenGL(true);//openGl 加速
    chart->addSeries(serietemp);
    chart->setAxisX(axisX,serietemp);
    chart->setAxisY(axisY,serietemp);
    series.push_back(serietemp);
    return serietemp;
}

bool ImuChart::setSerie(QList<QPointF> points)
{
    serie->clear();
    serie->append(points);
    return true;
}
bool ImuChart::addLine(QLineSeries *serie)
{
    chart->addSeries(serie);
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
    for(auto serie : series)
        serie->setVisible(show);
    return true;
}
