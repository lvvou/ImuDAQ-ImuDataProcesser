#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include "csvreader.h"
#include "imuchart.h"
#include <algorithm>

typedef std::vector<ImuChart*> AccChart;
typedef std::vector<ImuChart*> AngleChart;
typedef std::vector<QString> AccLabel;
typedef std::vector<QString> AngleLabel;
typedef std::vector<QString> LegPositionLabel;
typedef std::vector<QString> LegLabel;

class SignalChart{
public:
    SignalChart(QLabel *shower):
        AccXChart(shower),
        AccYChart(shower),
        AccZChart(shower),
        CourseChart(shower),
        RollChart(shower),
        PitchChart(shower)
    {}

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
};

class LegPositionChart{
public:
    LegPositionChart(QLabel *shower):
        FootChart(shower),
        ThighChart(shower)
    {}
    SignalChart FootChart;
    SignalChart ThighChart;
    LegPositionLabel legpositionlabel={QString("Foot"),QString("Thigh")};
    std::vector<SignalChart*> LegPositionChartVector ={&FootChart,&ThighChart};
};

class LegChart
{
public:
    LegChart(QLabel *shower):
        RightLegChart(shower),
        LeftLegChart(shower)
    { }
    LegPositionChart RightLegChart;
    LegPositionChart LeftLegChart;
    LegLabel leglabel={QString("RT"),QString("LT")};
    std::vector<LegPositionChart*> LegChartVector ={&RightLegChart,&LeftLegChart};
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    bool ChangePosition(int position);
    ~Widget();
protected:
    CsvReader csvreader;
    LegChart *Chart;

private slots:
    void on_pushButton_clicked();
    void on_WindowPositionhorizontalSlider_sliderMoved(int position);
    void on_ZoomverticalSlider_sliderMoved(int position);
    void on_checkBox_stateChanged(int arg1);
    void on_ZoomverticalSlider_sliderReleased();
    void on_MarkPositionhorizontalSlider_sliderMoved(int position);
    void on_PlaypushButton_clicked();
    void on_AddpushButton_clicked();
    void on_RedcheckBox_stateChanged(int arg1);

private:
    double zoom;
    bool isRT;
    bool isAcc;
    bool isplay;
    int position;
    Ui::Widget *ui;
};

#endif // WIDGET_H
