/**
* @file     ImuChart.h
* @class    ImuChart
* @brief    this file includes class(ImuChart) for show data from csv file.
* @variable ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*           QChart* chart;  // used to show all lines include curves and vertical lines
*           ImuLineSeries* serie;   // curve for data from csv file
*           QVector<ImuVerticalLine*> series;   // vertical lineseries for fragmenting data
*           QVector<int> positions; // vector for psoition of vertical lineseries
*           QValueAxis *axisX;  // used to set the lineSeries' axis of x
*           QValueAxis *axisY;  // used to set the lineSeries' axis of y
*           double axisYMax;    // max range for axis of y
*           double axisYMin;    // min range for axis of y
*           QGraphicsSimpleTextItem *coordX;    // used to show position(x) of mouse in this chart
*           QGraphicsSimpleTextItem *coordY;    // used to show position(y) of mouse in this chart
*           unsigned int axisXMax;  // max range for axis of x or the data length
*           QString label;  // name of this chart
*           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @author   Flame
* @date     03.05.2019
*/

#ifndef IMUCHART_H
#define IMUCHART_H

#include <QtCharts>
#include <QtCharts/QChart>
#include <QChartView>

#include <QLineSeries>
#include <QValueAxis>
#include <QString>
#include <QSplineSeries>

#include <QPointF>
#include <QVector>
#include <vector>
#include <QtGui/QResizeEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsTextItem>
#include <QtGui/QMouseEvent>

#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>

#include "ImuLineseries.h"
#include "ImuVerticalline.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE;

class ImuChart: public QChartView
{
    Q_OBJECT
public:
    ImuChart(QLabel *shower,unsigned int axisXMax=500,unsigned int axisYMax=1,QString label="AccX",QWidget *parent = nullptr);
    ~ImuChart();
    bool addLine(int position);
    unsigned int GetaxisXMax();
    bool setLabel(QString label);
    bool setSerie(QList<QPointF> points);
    bool showRedLine(bool show);
    bool ishave(int position);
    void delLine(int position);
    void clearLineList();
    void push_back(ImuVerticalLine* serie,int position);
public:
    QChart* chart;
    ImuVerticalLine* ImageLine;
    ImuLineSeries* serie;
    QVector<ImuVerticalLine*> series;
    QVector<int> positions;
    QValueAxis *axisX;
    QValueAxis *axisY;
    double axisYMax;
    double axisYMin;
signals:
    void add(int x);
    void del(int x);
protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
private slots:
    void emitDelLine(int position);
private:
    QGraphicsSimpleTextItem *coordX;
    QGraphicsSimpleTextItem *coordY;
    unsigned int axisXMax;
    QString label;
};

#endif // IMUCHART_H
