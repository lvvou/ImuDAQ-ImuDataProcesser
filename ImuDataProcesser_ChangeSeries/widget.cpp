#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    isAcc = true;
    isRT = true;
    isplay = false;
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    Chart = new LegChart(ui->Coordinatelabel);
    std::string Filename = ui->FilenamelineEdit->text().toStdString();
    qDebug()<<"Filename : "<<ui->FilenamelineEdit->text();
    csvreader.Init(Filename);
    csvreader.ClearVector();
    ui->WindowPositionhorizontalSlider->setMaximum(int(csvreader.ReadCsv()-500));

    if(csvreader.DataChecker())
        qDebug()<<"Data is vaild ";
    else {
        qDebug()<<"Data is invaild ";
        return;
    }
    unsigned int i = 0;
    auto LegSignal = csvreader.imudata.GetLegSignal().LegSignal[1-isRT];
    for (auto LegPositionSignal:LegSignal->LegPositionSignal)
        for(auto signal:LegPositionSignal->AllSignalVector)
        {
            auto chart = Chart->LegChartVector[i/12]->LegPositionChartVector[i%12/6]->SignalChartVector[i%6/3][i%6%3];
            auto minY = std::min_element(signal->begin(),signal->end());
            auto maxY = std::max_element(signal->begin(),signal->end());
            ui->gridLayoutCharts->addWidget(chart->chartView,i%4,i/4);
            chart->chart->setTitle(Chart->leglabel[i/12]+Chart->LegChartVector[i/12]->legpositionlabel[i%12/6]+Chart->LegChartVector[i/12]->LegPositionChartVector[i%12/6]->SignalLabel[i%6/3][i%6%3]);
            chart->axisY->setRange(*minY-abs(*minY/5.0),*maxY+abs(*maxY/5.0));
            chart->chartView->setBaseSize(200,200);
            chart->chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            chart->serie->clear();
            auto temp=signal->begin();
            for (int var = 0; var < int(chart->GetaxisXMax()); var++) {
                chart->serie->append(var,*(temp+var));
            }
            i++;
        }
    i=12;
    auto LegSignalOther = csvreader.imudata.GetLegSignal().LegSignal[isRT];
    for (auto LegPositionSignal:LegSignalOther->LegPositionSignal)
        for(auto signal:LegPositionSignal->AllSignalVector)
        {
            auto chart = Chart->LegChartVector[i/12]->LegPositionChartVector[i%12/6]->SignalChartVector[i%6/3][i%6%3];
            auto minY = std::min_element(signal->begin(),signal->end());
            auto maxY = std::max_element(signal->begin(),signal->end());
            chart->chart->setTitle(Chart->leglabel[i/12]+Chart->LegChartVector[i/12]->legpositionlabel[i%12/6]+Chart->LegChartVector[i/12]->LegPositionChartVector[i%12/6]->SignalLabel[i%6/3][i%6%3]);
            chart->axisY->setRange(*minY-abs(*minY/5.0),*maxY+abs(*maxY/5.0));
            chart->chartView->setBaseSize(200,200);
            chart->chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            chart->serie->clear();
            auto temp=signal->begin();
            for (int var = 0; var < int(chart->GetaxisXMax()); var++) {
                chart->serie->append(var,*(temp+var));
            }
            i++;
        }
}

void Widget::on_WindowPositionhorizontalSlider_sliderMoved(int position)
{
    if(!isplay){
        ChangePosition(position);
        this->position = position;
    }
}

void Widget::on_ZoomverticalSlider_sliderMoved(int position)
{
    zoom = double(position)/5000.0;
}

void Widget::on_checkBox_stateChanged(int arg1)
{
    isRT=bool(arg1);
    auto chart=Chart->LegChartVector[isRT];
    for(auto legpositionchart:chart->LegPositionChartVector)
        for(auto signalchart:legpositionchart->SignalChartVector)
            for(auto accangle:signalchart)
            {
                accangle->serie->setVisible(false);
                ui->gridLayoutCharts->removeWidget(accangle->chartView);
            }
    unsigned int i = 0;
    auto chartadd=Chart->LegChartVector[1-isRT];
    for(auto legpositionchart:chartadd->LegPositionChartVector)
        for(auto signalchart:legpositionchart->SignalChartVector)
            for(auto accangle:signalchart)
            {
                accangle->serie->setVisible(true);
                accangle->chartView->raise();
                ui->gridLayoutCharts->addWidget(accangle->chartView,i%4,i/4);
                i++;
            }
}

void Widget::on_ZoomverticalSlider_sliderReleased()
{
    ui->ScopedoubleSpinBox->setValue(zoom);
    for(auto chart:Chart->LegChartVector)
        for(auto legpositionchart:chart->LegPositionChartVector)
            for(auto signalchart:legpositionchart->SignalChartVector)
                for(auto accangle:signalchart)
                {
                    accangle->chart->zoomReset();
                    accangle->chart->zoom(zoom);
                    accangle->chart->update();
                    accangle->chartView->update();
                }
}

void Widget::on_MarkPositionhorizontalSlider_sliderMoved(int position)
{

}

void Widget::on_PlaypushButton_clicked()
{
    isplay = !isplay;
    ui->WindowPositionhorizontalSlider->setDisabled(isplay);
}

bool Widget::ChangePosition(int position)
{
    unsigned int i = 0;
    for(auto LegSignal : csvreader.imudata.GetLegSignal().LegSignal)
        for (auto LegPositionSignal:LegSignal->LegPositionSignal)
            for(auto signal:LegPositionSignal->AllSignalVector)
            {
                auto chart = Chart->LegChartVector[i/12]->LegPositionChartVector[i%12/6]->SignalChartVector[i%6/3][i%6%3];
                chart->serie->clear();
                auto temp=signal->begin();
                for (int var = 0; var < int(chart->GetaxisXMax()); var++) {
                    chart->serie->append(var,*(temp+var+position));
                }
                i++;
            }
    return true;
}

void Widget::on_AddpushButton_clicked()
{
    for(auto chart:Chart->LegChartVector)
        for(auto legpositionchart:chart->LegPositionChartVector)
            for(auto signalchart:legpositionchart->SignalChartVector)
                for(auto accangle:signalchart)
                {

                    accangle->initSerie(250);
                }
}

void Widget::on_RedcheckBox_stateChanged(int arg1)
{
    for(auto chart:Chart->LegChartVector)
        for(auto legpositionchart:chart->LegPositionChartVector)
            for(auto signalchart:legpositionchart->SignalChartVector)
                for(auto accangle:signalchart)
                {
                    accangle->showRedLine(arg1);
                }
}
