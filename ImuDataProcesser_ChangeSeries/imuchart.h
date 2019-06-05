#ifndef IMUCHART_H
#define IMUCHART_H

#include <QtCharts>
#include <QtCharts/QChart>
#include <QChartView>
QT_CHARTS_USE_NAMESPACE;
#include <QLineSeries>
#include <QValueAxis>
#include <QString>
#include <QSplineSeries>
//#include <QTimer>
//#include <QTime>
//#include <QList>
#include <QPointF>
#include <QVector>
#include "imulineseries.h"
#include <vector>

class ImuChart
{
public:
    ImuChart(QLabel *shower,unsigned int axisXMax=500,unsigned int axisYMax=1,QString label="AccX");
    bool addLine(QLineSeries* serie);
    QLineSeries* initSerie(int position);
    unsigned int GetaxisXMax();
    bool setLabel(QString label);
    bool setSerie(QList<QPointF> points);
    bool setRange(int min,int max);
    bool showRedLine(bool show);
public:
    QChartView* chartView;
    QChart* chart;
    ImuLineSeries* serie;
    std::vector<QLineSeries*> series;
    QSplineSeries* Spserie;
    QValueAxis *axisX;
    QValueAxis *axisY;

private:
    unsigned int axisXMax;
    unsigned int axisYMax;
    QString label;
};

#endif // IMUCHART_H
