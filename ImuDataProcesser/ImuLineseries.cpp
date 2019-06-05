#include "ImuLineseries.h"

ImuLineSeries::ImuLineSeries(QLabel *Linelabel):label(Linelabel)
{
    connect(this, &QLineSeries::clicked, this, &ImuLineSeries::showlabel);
}

void ImuLineSeries::showlabel(const QPointF &point)
{
    this->label->setText(QString("("+QString::number(point.x())+','+QString::number(point.y())+")"));
}
