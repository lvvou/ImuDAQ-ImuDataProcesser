#include "imulineseries.h"

ImuLineSeries::ImuLineSeries(QLabel *Linelabel):label(Linelabel)
{
    connect(this, &QLineSeries::doubleClicked, this, &ImuLineSeries::showlabel);
}

void ImuLineSeries::showlabel(const QPointF &point)
{
    std::cout<<"("<<point.x()<<','<<point.y()<<')'<<std::endl;
    this->label->setText(QString("("+QString::number(point.x())+','+QString::number(point.y())+")"));
}
