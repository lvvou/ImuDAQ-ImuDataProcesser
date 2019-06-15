#include "ImuProcesserWidget.h"
#include "ui_widget.h"

ImuProcesserWidget::ImuProcesserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    rootDir = "C:/";
    showred = true;
    first = true;
    isAcc = true;
    isRT = true;
    axisXMax = 500;
    isplay = false;
    ui->setupUi(this);
    this->ImagePosition = 0;
    this->position = 0;
    reader.setAutoTransform(true);
    imagewidget.show();
    haveObtainSlice = false;
    setWindowState(Qt::WindowMaximized);
    //imagewidget.move(976+880+40,20);
    Chart = new LegChart(ui->Coordinatelabel);
    this->setWindowTitle("Imu Data Processer");
    connect(Chart,&LegChart::add,this,&ImuProcesserWidget::addline);
    connect(Chart,&LegChart::del,this,&ImuProcesserWidget::delline);
    unsigned int i = 0;
    auto LegSignal = csvreader.imudata.GetLegSignal().LegSignal[1-isRT];
    for (auto LegPositionSignal:LegSignal->LegPositionSignal)
        for(auto signal:LegPositionSignal->ShowSignalVector)
        {
            Q_UNUSED(signal)
            auto chart = Chart->LegChartVector[i/12]->LegPositionChartVector[i%12/6]->SignalChartVector[i%6/3][i%6%3];
            ui->gridLayoutCharts->addWidget(chart,i%4,i/4);
            i++;
        }
}

ImuProcesserWidget::~ImuProcesserWidget()
{
    Chart->clear();
    delete Chart;
    delete ui;
}

void ImuProcesserWidget::on_pushButton_clicked()
{
    std::string Filename = ui->FilenamelineEdit->text().toStdString();
    std::cout<<"Filename : "<<rootDir.toStdString()+"/"+Filename+".csv"<<std::endl;
    csvreader.Init(rootDir.toStdString()+"/"+Filename+".csv");
    csvreader.ClearVector();
    slice.clear();
    slicename.clear();
    length = csvreader.ReadCsv();
    if(length==0) {
        return;
    }
    csvreader.imudata.VerifyEuler2Quaternion();
    ImageDir = rootDir+"/"+ui->FilenamelineEdit->text();
    ImageLogFile = ImageDir+"/"+"log.txt";
    std::ifstream Reader(ImageLogFile.toStdString().data());
    std::string strLineContext;
    getline(Reader, strLineContext);
    FirstImage = QString::fromStdString(strLineContext.substr(strLineContext.find_first_of("_", 0)+1, strLineContext.size()));
    std::cout<<"First Image number :"<<FirstImage.toStdString()<<std::endl;
    firstImageNumber = FirstImage.toInt();
    this->position = 0;
    this->ImagePosition = position+ui->ImagPositionhorizontalSlider->value();
    ChangePosition(0);
    ChangeImage(this->ImagePosition);
    ui->WindowPositionhorizontalSlider->setEnabled(false);
    ui->WindowPositionhorizontalSlider->setValue(0);
    ui->WindowPositionhorizontalSlider->setMinimum(0);
    ui->WindowPositionhorizontalSlider->setMaximum(int(length-axisXMax));
    ui->WindowPositionhorizontalSlider->setEnabled(true);

    ui->ImagPositionhorizontalSlider->setEnabled(false);
    ui->ImagPositionhorizontalSlider->setValue(0);
    ui->ImagPositionhorizontalSlider->setMinimum(0);
    ui->ImagPositionhorizontalSlider->setMaximum(500);
    ui->ImagPositionhorizontalSlider->setEnabled(true);

    if(csvreader.DataChecker())
        qDebug()<<"Data is vaild ";
    else {
        qDebug()<<"Data is invaild ";
        return;
    }

    unsigned int i = 0;

    auto marker = csvreader.imudata.GetMarkerVector();
    std::cout<<"loss package : "<<std::count(marker.begin(),marker.end(),0)<<std::endl;
    auto LegSignal = csvreader.imudata.GetLegSignal().LegSignal[1-isRT];
    for (auto LegPositionSignal:LegSignal->LegPositionSignal)
        for(auto signal:LegPositionSignal->ShowSignalVector)
        {
            auto chart = Chart->LegChartVector[i/12]->LegPositionChartVector[i%12/6]->SignalChartVector[i%6/3][i%6%3];
            chart->clearLineList();
            auto minY = std::min_element(signal->begin(),signal->end()-1);
            auto maxY = std::max_element(signal->begin(),signal->end()-1);
//            if(first){
//                ui->gridLayoutCharts->addWidget(chart,i%4,i/4);
//            }
            chart->chart->setTitle(Chart->leglabel[i/12]+Chart->LegChartVector[i/12]->legpositionlabel[i%12/6]+Chart->LegChartVector[i/12]->LegPositionChartVector[i%12/6]->SignalLabel[i%6/3][i%6%3]);
            chart->axisY->setRange(*minY-abs((*maxY-*minY)/5.0),*maxY+abs((*maxY-*minY)/5.0));
            chart->axisYMax = *maxY+abs((*maxY-*minY)/5.0);
            chart->axisYMin = *minY-abs((*maxY-*minY)/5.0);
            chart->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            chart->serie->clear();

            auto temp=signal->begin();
            for (int var = 0; var <= signal->end()-signal->begin()-1; var++) {
                chart->serie->append(var,*(temp+var));
            }
//            int tempSlice = 0;

            for (unsigned int var = 0; var < marker.size()-1; var++) {
                if(marker[var]==0){
                    chart->addMarker(int(var));
//                    if(!haveObtainSlice)
//                        if(var!=0&&var!=marker.size()-2)
//                            tempSlice++;
                }
//                if(!haveObtainSlice)
//                    slice.push_back(tempSlice);
            }
//            if(!haveObtainSlice)
//                for(int i=0;i<=tempSlice;i++)
//                    slicename.push_back("1000");

            chart->ImageLine->changeHigh(this->ImagePosition,chart->axisY);
//            haveObtainSlice = true;
            i++;
        }
    i=12;
    auto LegSignalOther = csvreader.imudata.GetLegSignal().LegSignal[isRT];
    for (auto LegPositionSignal:LegSignalOther->LegPositionSignal)
        for(auto signal:LegPositionSignal->ShowSignalVector)
        {
            auto chart = Chart->LegChartVector[i/12]->LegPositionChartVector[i%12/6]->SignalChartVector[i%6/3][i%6%3];
            chart->clearLineList();
            auto minY = std::min_element(signal->begin(),signal->end()-1);
            auto maxY = std::max_element(signal->begin(),signal->end()-1);
            chart->chart->setTitle(Chart->leglabel[i/12]+Chart->LegChartVector[i/12]->legpositionlabel[i%12/6]+Chart->LegChartVector[i/12]->LegPositionChartVector[i%12/6]->SignalLabel[i%6/3][i%6%3]);
            chart->axisY->setRange(*minY-abs((*maxY-*minY)/5.0),*maxY+abs((*maxY-*minY)/5.0));
            chart->axisYMax = *maxY+abs((*maxY-*minY)/5.0);
            chart->axisYMin = *minY-abs((*maxY-*minY)/5.0);
            chart->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            chart->serie->clear();
            auto temp=signal->begin();
            for (int var = 0; var <= signal->end()-signal->begin()-1; var++) {
                chart->serie->append(var,*(temp+var));
            }
            for (unsigned int var = 0; var < marker.size()-1; var++) {
                if(marker[var]==0){
                    chart->addMarker(int(var));
                }
            }
            chart->ImageLine->changeHigh(this->ImagePosition,chart->axisY);
            chart->ImageLine->hide();
            chart->showRedLine(false);
            i++;
        }
//    first = false;
//    ui->ZoomverticalSlider->setVisible(true);
    std::cout<<"Init over!"<<std::endl;
}

void ImuProcesserWidget::on_WindowPositionhorizontalSlider_sliderMoved(int position)
{
    if(!isplay){
        ChangePosition(position);
        this->position = position;
        ImagePosition = position+ui->ImagPositionhorizontalSlider->value();
        ChangeImage(ImagePosition);
        ChangeImageLine(ImagePosition);
    }
}

void ImuProcesserWidget::on_ZoomverticalSlider_sliderMoved(int position)
{
    zoom = double(position)/5000.0;
}

void ImuProcesserWidget::on_checkBox_stateChanged(int arg1)
{
    isRT=bool(arg1);
    auto chart=Chart->LegChartVector[isRT];
    for(auto legpositionchart:chart->LegPositionChartVector)
        for(auto signalchart:legpositionchart->SignalChartVector)
            for(auto accangle:signalchart)
            {
                accangle->serie->setVisible(false);
                accangle->showRedLine(false);
                accangle->ImageLine->hide();
                ui->gridLayoutCharts->removeWidget(accangle);
            }
    unsigned int i = 0;
    auto chartadd=Chart->LegChartVector[1-isRT];
    for(auto legpositionchart:chartadd->LegPositionChartVector)
        for(auto signalchart:legpositionchart->SignalChartVector)
            for(auto accangle:signalchart)
            {
                accangle->serie->setVisible(true);
                accangle->ImageLine->show();
                accangle->showRedLine(showred);
                accangle->raise();
                ui->gridLayoutCharts->addWidget(accangle,i%4,i/4);
                i++;
            }
}

void ImuProcesserWidget::on_ZoomverticalSlider_sliderReleased()
{
    for(auto chart:Chart->LegChartVector)
        for(auto legpositionchart:chart->LegPositionChartVector)
            for(auto signalchart:legpositionchart->SignalChartVector)
                for(auto accangle:signalchart)
                {
                    accangle->axisY->setRange(accangle->axisYMin*zoom,accangle->axisYMax*zoom);
                    accangle->chart->update();
                    accangle->update();
                }
}

void ImuProcesserWidget::on_PlaypushButton_clicked()
{
    isplay = !isplay;
    if(isplay)
        timeid = startTimer(100);
    else
        this->killTimer(timeid);

    ui->WindowPositionhorizontalSlider->setDisabled(isplay);

}
void ImuProcesserWidget::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==timeid)
    {
        position+=10*ui->playspeeddoubleSpinBox->value();
        ImagePosition = position+ui->ImagPositionhorizontalSlider->value();
        if(uint(position)>=length-axisXMax)
        {
            position = 0;
            ImagePosition = position+ui->ImagPositionhorizontalSlider->value();
            this->killTimer(timeid);
            isplay = !isplay;
            ui->PlaypushButton->setChecked(false);
            ui->WindowPositionhorizontalSlider->setDisabled(isplay);
        }
        ChangePosition(position);
        ChangeImage(ImagePosition);
        ChangeImageLine(ImagePosition);
        ui->WindowPositionhorizontalSlider->setValue(position);
    }
}
bool ImuProcesserWidget::ChangePosition(int position)
{
    for(auto chart:Chart->LegChartVector)
        for(auto legpositionchart:chart->LegPositionChartVector)
            for(auto signalchart:legpositionchart->SignalChartVector)
                for(auto accangle:signalchart)
                {
                    accangle->axisX->setRange(position,uint(position)+axisXMax);
                    accangle->chart->update();
                    accangle->update();
                }
    return true;
}


void ImuProcesserWidget::on_RedcheckBox_stateChanged(int show)
{
    showred = show;
    auto chart=Chart->LegChartVector[1-isRT];
    for(auto legpositionchart:chart->LegPositionChartVector)
        for(auto signalchart:legpositionchart->SignalChartVector)
            for(auto accangle:signalchart)
            {
                accangle->showRedLine(showred);
            }
}

void ImuProcesserWidget::addline(int position)
{
    auto chart=Chart->LegChartVector[1-isRT];
    for(auto legpositionchart:chart->LegPositionChartVector)
        for(auto signalchart:legpositionchart->SignalChartVector)
            for(auto accangle:signalchart)
            {
                if(!accangle->ishave(position))
                {
                    accangle->addLine(position);
                }
            }
    auto chartother=Chart->LegChartVector[isRT];
    for(auto legpositionchart:chartother->LegPositionChartVector)
        for(auto signalchart:legpositionchart->SignalChartVector)
            for(auto accangle:signalchart)
            {
                if(!accangle->ishave(position))
                {
                    accangle->addLine(position);
                    accangle->showRedLine(false);
                }
            }
}

void ImuProcesserWidget::delline(int position)
{
    for(auto chart:Chart->LegChartVector)
        for(auto legpositionchart:chart->LegPositionChartVector)
            for(auto signalchart:legpositionchart->SignalChartVector)
                for(auto accangle:signalchart)
                {
                    if(accangle->ishave(position))
                    {
                        accangle->delLine(position);
                    }
                }
}

void ImuProcesserWidget::on_OutputpushButton_clicked()
{
    if(slicename.empty()){
        std::cout<<"slicename is empty ! "<<std::endl;
        return;
    }
    else{
        QString address = rootDir+"/"+rootDir.section('/', -1)+"_Process";
        qDebug()<<"address : "<<address;
        QDir dir;
        if(!dir.exists(address))
        {
                std::cout<<"The path does not exist ! "<<std::endl;
                dir.mkpath(address);
        }
        QString Allfilename = address+"/"+ui->lineEdit->text()+".csv";
        csvwriter.toCsv(Allfilename,csvreader.imudata,slice,
                        slicename,length);
    }
}

void ImuProcesserWidget::on_axisXRangespinBox_editingFinished()
{
    for(auto chart:Chart->LegChartVector)
        for(auto legpositionchart:chart->LegPositionChartVector)
            for(auto signalchart:legpositionchart->SignalChartVector)
                for(auto accangle:signalchart)
                {
                    axisXMax = uint(ui->axisXRangespinBox->value());
                    ui->ImagPositionhorizontalSlider->blockSignals(true);
                    ui->WindowPositionhorizontalSlider->blockSignals(true);
                    ui->ImagPositionhorizontalSlider->setMaximum(int(axisXMax));
                    ui->WindowPositionhorizontalSlider->setMaximum(int(length-axisXMax));
                    ui->ImagPositionhorizontalSlider->blockSignals(false);
                    ui->WindowPositionhorizontalSlider->blockSignals(false);
                    accangle->axisX->setRange(position,uint(position)+axisXMax);
                    accangle->chart->update();
                    accangle->update();
                }
}

void ImuProcesserWidget::on_FilenamelineEdit_editingFinished()
{
    ui->lineEdit->setText(ui->FilenamelineEdit->text());
}

void ImuProcesserWidget::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit(deleteme("ImuProcesserWidget"));
}
bool ImuProcesserWidget::ChangeImageLine(int value)
{
    for(auto chart:Chart->LegChartVector)
        for(auto legpositionchart:chart->LegPositionChartVector)
            for(auto signalchart:legpositionchart->SignalChartVector)
                for(auto accangle:signalchart)
                {
                    accangle->ImageLine->changeHigh(value,accangle->axisY);
                    accangle->update();
                }
    if(haveObtainSlice)
        ui->lineEdit_2->setText(QString::fromStdString(slicename[uint(slice[uint(ImagePosition)])]));
    return true;
}
void ImuProcesserWidget::on_ImagPositionhorizontalSlider_valueChanged(int value)
{
    if(!isplay){
        this->ImagePosition = value+position;
        ChangeImage(this->ImagePosition);
        ChangeImageLine(this->ImagePosition);
    }
}
bool ImuProcesserWidget::ChangeImage(int value)
{
    int temp;
    for(temp = 0;temp<100;temp++){
        reader.setFileName(ImageDir+"/"+QString::number(firstImageNumber+10*value+temp)+".jpg");
        img = reader.read();
        if (!img.isNull()) {
            break;
        }
        reader.setFileName(ImageDir+"/"+QString::number(firstImageNumber+10*value-temp)+".jpg");
        img = reader.read();
        if (!img.isNull()) {
            break;
        }
    }
    if(temp<30){
        imagewidget.draw(img);
        imagewidget.show();
    }
    else {
        //QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 //tr("Cannot load Image!"));
        std::cout<<"Cannot load Image!"<<std::endl;
    }
    return true;
}
void ImuProcesserWidget::on_SelectpushButton_clicked()
{
    rootDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     "C:/ImuLog/",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    ui->rootDirLabel->setText(rootDir);
}

void ImuProcesserWidget::on_pushButton_2_clicked()
{
    addline(this->ImagePosition);
}

void ImuProcesserWidget::on_lineEdit_2_editingFinished()
{
    if(haveObtainSlice)
        slicename[uint(slice[uint(ImagePosition)])]=ui->lineEdit_2->text().toStdString();
}

void ImuProcesserWidget::on_GeneratepushButton_clicked()
{
    haveObtainSlice = false;
    slice.clear();
    slicename.clear();
    int tempSlice = 0;
    auto positions = Chart->LeftLegChart.FootChart.AccXChart.positions;
    //auto length = csvreader.imudata.GetLegSignal().LeftLegSignal.FootSignal.AccX.size();
    for (unsigned int var = 0; var < this->length; var++) {
        if(var!=0&&var!=this->length-1)
            if(positions.indexOf(int(var))!=-1)
                tempSlice++;
            slice.push_back(tempSlice);
    }
    for(int i=0;i<=tempSlice;i++)
        slicename.push_back("1000");
    haveObtainSlice = true;
}
