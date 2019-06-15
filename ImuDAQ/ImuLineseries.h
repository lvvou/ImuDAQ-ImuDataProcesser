/**
* @file     ImuLineSeries.h
* @class    ImuLineSeries
* @brief    this file includes class for painting lines whose data is get from imudata.
* @details  when you click the points of the line,the label will show the axisx and axisy information of it.
* @variable QLabel *label; //used to show the point clicked by mouse but it is only a pointer,so
*                           when using this label ,we should define a label on other window.
* @author   Flame
* @date     03.05.2019
*/

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
    Q_OBJECT
public:
    ImuLineSeries(QLabel *label);
public slots:
    void showlabel(const QPointF &point);
private:
    QLabel *label;
};
#endif // IMULINESERIES_H
