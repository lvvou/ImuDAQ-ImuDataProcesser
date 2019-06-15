#include "ImuVerticalline.h"

ImuVerticalLine::ImuVerticalLine(int position, QValueAxis *axisY, Qt::GlobalColor color)
{

    this->position = position;
    setPen(QPen(color, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
    append(position,axisY->max());
    append(position,axisY->min());
    setUseOpenGL(true);//openGl 加速
    //connect(this, &QLineSeries::hovered, this, &ImuVerticalLine::tooltip);
    connect(this, &QLineSeries::doubleClicked, this, &ImuVerticalLine::sendposition);
}

void ImuVerticalLine::sendposition(const QPointF &point)
{
    Q_UNUSED(point)
    emit(ImuVerticalLine::deleteme(position));
    this->disconnect(SIGNAL(deleteme(int)));
}
void ImuVerticalLine::changeHigh(int position,QValueAxis *axisY)
{
    this->clear();
    append(position,axisY->max());
    append(position,axisY->min());
}

//void ImuVerticalLine::tooltip(QPointF point, bool state)
//{
//    Q_UNUSED(point)
//    Q_UNUSED(state)
//}
