#ifndef IMULINESERIES_H
#define IMULINESERIES_H

#include <iostream>
#include <QChart>
#include <QPointF>
#include <QString>
#include <QLineSeries>
#include <QDebug>
#include <QtWidgets/QLabel>
QT_CHARTS_USE_NAMESPACE;

class ImuLineSeries:public QLineSeries
{
public:
    ImuLineSeries(QLabel *label);
public slots:
    void showlabel(const QPointF &point);
private:
    QLabel *label;
};
#endif // IMULINESERIES_H
