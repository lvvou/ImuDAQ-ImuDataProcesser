/**
* @file     widget.h
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @class    Widget
* @brief    this class is used to show the chart for all sensors.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @class    SignalChart,LegPositionChart,LegChart
* @brief    there are three classes for different signal types,different position and different leg.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @author   Flame
* @date     03.05.2019
*/

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include "CsvReader.h"
#include "CsvWriter.h"
#include "ImuChart.h"
#include "ImageWidget.h"
#include <algorithm>
typedef unsigned int uint;
typedef std::vector<ImuChart*> AccChart;
typedef std::vector<ImuChart*> AngleChart;
typedef std::vector<QString> AccLabel;
typedef std::vector<QString> AngleLabel;
typedef std::vector<QString> LegPositionLabel;
typedef std::vector<QString> LegLabel;

class SignalChart:public QObject
{
    Q_OBJECT
public:
    SignalChart(QLabel *shower):
        AccXChart(shower),
        AccYChart(shower),
        AccZChart(shower),
        CourseChart(shower),
        RollChart(shower),
        PitchChart(shower)
    {
        connect(&AccXChart,   &ImuChart::add, this, &SignalChart::emitadd);
        connect(&AccYChart,   &ImuChart::add, this, &SignalChart::emitadd);
        connect(&AccZChart,   &ImuChart::add, this, &SignalChart::emitadd);

        connect(&CourseChart, &ImuChart::add, this, &SignalChart::emitadd);
        connect(&RollChart,   &ImuChart::add, this, &SignalChart::emitadd);
        connect(&PitchChart,  &ImuChart::add, this, &SignalChart::emitadd);

        connect(&AccXChart,   &ImuChart::del, this, &SignalChart::emitdel);
        connect(&AccYChart,   &ImuChart::del, this, &SignalChart::emitdel);
        connect(&AccZChart,   &ImuChart::del, this, &SignalChart::emitdel);

        connect(&CourseChart, &ImuChart::del, this, &SignalChart::emitdel);
        connect(&RollChart,   &ImuChart::del, this, &SignalChart::emitdel);
        connect(&PitchChart,  &ImuChart::del, this, &SignalChart::emitdel);
    }

    ImuChart AccXChart;
    ImuChart AccYChart;
    ImuChart AccZChart;

    ImuChart CourseChart;
    ImuChart RollChart;
    ImuChart PitchChart;

    AccLabel acclabel={QString("AccX"),QString("AccY"),QString("AccZ")};
    AccChart accChart={&AccXChart,&AccYChart,&AccZChart};
    AngleLabel anglelabel={QString("Course"),QString("Roll"),QString("Pitch")};
    AngleChart angleChart={&CourseChart,&RollChart,&PitchChart};
    std::vector<std::vector<QString>> SignalLabel={acclabel,anglelabel};
    std::vector<std::vector<ImuChart*>> SignalChartVector={accChart,angleChart};
public slots:
    void emitadd(int position)
    {
        emit(add(position));
    }
    void emitdel(int position)
    {
        emit(del(position));
    }
signals:
    void add(int position);
    void del(int position);
};

class LegPositionChart:public QObject
{
    Q_OBJECT
public:
    LegPositionChart(QLabel *shower):
        FootChart(shower),
        ThighChart(shower)
    {
        connect(&FootChart, &SignalChart::add, this, &LegPositionChart::emitadd);
        connect(&ThighChart, &SignalChart::add, this, &LegPositionChart::emitadd);

        connect(&FootChart, &SignalChart::del, this, &LegPositionChart::emitdel);
        connect(&ThighChart, &SignalChart::del, this, &LegPositionChart::emitdel);
    }
    SignalChart FootChart;
    SignalChart ThighChart;
    LegPositionLabel legpositionlabel={QString("Foot"),QString("Thigh")};
    std::vector<SignalChart*> LegPositionChartVector ={&FootChart,&ThighChart};

public slots:
    void emitadd(int position)
    {
        emit(add(position));
    }
    void emitdel(int position)
    {
        emit(del(position));
    }
signals:
    void add(int position);
    void del(int position);
};

class LegChart:public QObject
{
    Q_OBJECT
public:
    LegChart(QLabel *shower):
        RightLegChart(shower),
        LeftLegChart(shower)
    {
        connect(&RightLegChart, &LegPositionChart::add, this, &LegChart::emitadd);
        connect(&LeftLegChart, &LegPositionChart::add, this, &LegChart::emitadd);
        connect(&RightLegChart, &LegPositionChart::del, this, &LegChart::emitdel);
        connect(&LeftLegChart, &LegPositionChart::del, this, &LegChart::emitdel);
    }
    LegPositionChart RightLegChart;
    LegPositionChart  LeftLegChart;
    LegLabel leglabel={QString("RT"),QString("LT")};
    std::vector<LegPositionChart*> LegChartVector ={&RightLegChart,&LeftLegChart};

public slots:
    void emitadd(int position)
    {
        emit(add(position));
    }
    void emitdel(int position)
    {
        emit(del(position));
    }
signals:
    void add(int position);
    void del(int position);
};

namespace Ui {
class Widget;
}

class ImuProcesserWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImuProcesserWidget(QWidget *parent = nullptr);
    bool ChangePosition(int position);
    ~ImuProcesserWidget();
    void closeEvent(QCloseEvent *event);
    bool ChangeImage(int value);
    bool ChangeImageLine(int value);
protected:
    ImageWidget imagewidget;
    CsvWriter csvwriter;
    CsvReader csvreader;
    LegChart *Chart;
    void timerEvent(QTimerEvent*event);
private slots:
    void on_pushButton_clicked();
    void on_WindowPositionhorizontalSlider_sliderMoved(int position);
    void on_ZoomverticalSlider_sliderMoved(int position);
    void on_checkBox_stateChanged(int arg1);
    void on_ZoomverticalSlider_sliderReleased();
    void on_PlaypushButton_clicked();
    void on_RedcheckBox_stateChanged(int show);
    void addline(int position);
    void delline(int position);
    void on_OutputpushButton_clicked();
    void on_axisXRangespinBox_editingFinished();
    void on_FilenamelineEdit_editingFinished();
    void on_ImagPositionhorizontalSlider_valueChanged(int value);
    void on_SelectpushButton_clicked();

signals:
    void deleteme(QString id);
private:
    int timeid;
    unsigned int length;
    bool first;
    double zoom;
    bool isRT;
    bool isAcc;
    bool showred;
    bool isplay;
    int ImagePosition;
    int position;
    unsigned int axisXMax;
    QString rootDir;
    QString ImageDir;
    QString FirstImage;
    QString ImageLogFile;
    QImage img;
    QImageReader reader;
    int firstImageNumber;
    Ui::Widget *ui;
};

#endif // WIDGET_H
