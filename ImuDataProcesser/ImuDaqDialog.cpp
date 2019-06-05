#include "ImuDaqDialog.h"
#include "ui_dialog.h"
extern ImuSocket_Task ImuSocket;
extern bool syncaction;
ImuDaqDialog::ImuDaqDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QList<QObject*> ChildList = children();
    foreach(QObject *obj,ChildList){
        //QWidget *widget = qobject_cast<QWidget*>(obj);
        //QList<QObject*> ChildrenList = widget->children();
        //foreach(QObject *childrenobj,ChildrenList){
        QPushButton *button = qobject_cast<QPushButton*>(obj);
        if(button)
            button->setEnabled(false);
        //}
    }

    period = 5;
    filenum = 0;
    Rate = 100;
    timeshow = false;
    filename = "walk";
    subject = "Flame";
    rootDir = "C:/";
    IMUDAQ = new IMUDAQ_Task;
    IMUDAQ->subject = subject.toStdString();
    IMUDAQ->filename = filename;
    IMUDAQ->rootDir = rootDir.toStdString();
    manager = LpmsSensorManagerFactory();
    lpmsRightFoot  = manager->addSensor(DEVICE_LPMS_B2, "00:04:3E:4B:32:30");
    lpmsRightThigh = manager->addSensor(DEVICE_LPMS_B2, "00:04:3E:4B:32:5B");
    lpmsLeftFoot   = manager->addSensor(DEVICE_LPMS_B2, "00:04:3E:4B:33:BB");
    lpmsLeftThigh  = manager->addSensor(DEVICE_LPMS_B2, "00:04:3E:4B:33:F1");
    Lpms = { lpmsRightFoot,lpmsRightThigh,lpmsLeftFoot,lpmsLeftThigh };
    waitConnect(Lpms,ChildList);
    viewFinder.init();
    //viewFinder.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    viewFinder.move(20,20);
    viewFinder.show();

    //this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    connect(IMUDAQ,&IMUDAQ_Task::isObtain,this,&ImuDaqDialog::saveImage);
    connect(IMUDAQ,&IMUDAQ_Task::acquireOver,this,&ImuDaqDialog::stopSave);
    this->setWindowTitle("Imu DAQ Programer");
    this->show();
    this->move(360,20);
}

ImuDaqDialog::~ImuDaqDialog()
{
    for (auto lpms : Lpms) {
        manager->removeSensor(lpms);
    }
    delete IMUDAQ;
    delete manager;
    delete ui;
}

bool ImuDaqDialog::CmdProcess(int i)
{
    std::vector<std::string> cmd = { "mkdir","period","startsend","stop","close","init","data","battery","reboot",\
                                    "sync","cls","rate","help","connect","testconnect","datalength","startsave",\
                                    "runbyuser","timeshow","reset"};
    std::vector<int> RateList = { 5,10,25,50,100,200 };
    switch (i)
    {
    case 0:
        //"mkdir"
        std::cout << "Enter your file name : ";
        std::cin >> filename;
        filenum = 1;
        std::cout << "Your file name is already set to " << filename << std::endl;
        break;
    case 1:
        //"period"
        std::cout << "Enter Acquisition cycle you need : ";
        while (1) {
            std::cin >> period;
            if ((period > 500) || (period <= 0)) {
                std::cout << "please enter a number between 1~500 : ";
            }
            if ((period < 500) && (period > 0)) {
                break;
            }
        }
        std::cout << "Your Acquisition cycle is already set to " << period << "s" << std::endl;
        break;
    case 2:
        //"startsend"
        if (syncaction) {
            //filenum++;
            IMU_active(Lpms, IMUDAQ, true, false,false,filename,filenum,period);
        }
        else QMessageBox::information(this,
                                     tr("please start sync command"),
                                     tr("please start sync command!"));
            //std::cout << "please start sync command" << std::endl;
        break;
    case 3:
        //"stop"
        IMU_terminate(IMUDAQ);
        break;
    case 4:
        //"close"
        //*processing = false;
        std::cout << "close" << std::endl;
        break;
    case 5:
        //"init"
        init(Lpms,Rate);
        break;
    case 6:
        //"data"
        dataoutput(filename,filenum,period);
        break;
    case 7:
        //"battery"
        getBatteryLevel(Lpms);
        break;
    case 8:
        //"reboot"
        armTimestampReset(Lpms);
        break;
    case 9:
        //"sync"
        //sync(Lpms);
        resetTimestamp(Lpms);
        break;
    case 10:
        //"cls"
        system("cls");
        break;
    case 11:
        //"rate"
        while (1) {
            std::cout << "Enter Acquisition frequent rate you need : ";
            std::cin >> Rate;
            if (RateAnalysis(Rate)) break;
            else {
                std::cout << "please enter a number as list : ";
                for (auto _rate : RateList)
                    std::cout << _rate << " ";
                std::cout << std::endl;
            }
        }
        std::cout << "Your Acquisition frequent rate is already set to " << Rate << "Hz" << std::endl;
        break;
    case 12:
        //"help"
        std::cout << "All Command is as follows : " << std::endl;
        for (auto help : cmd)
            std::cout << help << " ";
        std::cout << std::endl;
        break;
    case 13:
        //"connect"
        std::cout << "waiting for connect!" << std::endl;
        ImuSocket.ImuAccept();
        break;
    case 14:
        //"testconnect"
        std::cout << "test connect!" << std::endl;
        IMU_active(Lpms, IMUDAQ, true, true);
        break;
    case 15:
        //"datalength"
        IMUDAQ->send = true;
        IMUDAQ->datalength();
        break;
    case 16:
        //"startsave"
        IMU_active(Lpms, IMUDAQ, false, false,false,filename,filenum,period,rootDir.toStdString());
        //std::cout << "please start sync command" << std::endl;
        break;
    case 17:
        //"runbyuser"
        IMU_active(Lpms, IMUDAQ, true, false, true,filename,filenum,period,rootDir.toStdString());
        //filenum++;
        break;
    case 18:
        //"timeshow"
        timeshow = !timeshow;
        break;
    case 19:
        //"reset"
        resetAllobject(Lpms);
        break;
    default:
        std::cout << "Command error!" << std::endl;
        break;
    }
    return true;
}

void ImuDaqDialog::on_PeriodlineEdit_editingFinished()
{
    period = ui->PeriodlineEdit->text().toInt();
}

void ImuDaqDialog::on_NamelineEdit_editingFinished()
{
    filename = ui->NamelineEdit->text().toStdString();
}

void ImuDaqDialog::on_FilenumlineEdit_editingFinished()
{
    filenum = ui->FilenumlineEdit->text().toInt();
}

void ImuDaqDialog::on_SamplelineEdit_editingFinished()
{
    Rate = ui->SamplelineEdit->text().toInt();
}

void ImuDaqDialog::on_StartsendpushButton_clicked()
{
    CmdProcess(2);
}

void ImuDaqDialog::on_ResetpushButton_clicked()
{
    CmdProcess(19);
}

void ImuDaqDialog::on_SyncpushButton_clicked()
{
    CmdProcess(9);
}

void ImuDaqDialog::on_ActivepushButton_clicked()
{
    QDir dir;
    if (syncaction) {
        filenum++;
        address = rootDir+"ImuLog/"+subject+"/"+QString::fromStdString(filename)+QString::number(filenum)+"/";
        if(!dir.exists(address))
        {
                qDebug()<<QObject::tr("The path does not exist ! ")<<endl;
                dir.mkpath(address);
        }
        CmdProcess(16);
    }
    else QMessageBox::information(this,
                                 tr("please start sync command"),
                                 tr("please start sync command!"));
    ui->FilenumlineEdit->blockSignals(true);
    ui->FilenumlineEdit->setText(QString::number(filenum));
    ui->FilenumlineEdit->blockSignals(false);
}

void ImuDaqDialog::on_ShowImagepushButton_clicked()
{
    if(viewFinder.isVisible())
        viewFinder.hide();
    else viewFinder.show();
}

void ImuDaqDialog::saveImage(QString time)
{
    std::ofstream IMU_log = std::ofstream((address+"log.txt").toStdString().data(), std::ios::out | std::ios::trunc);
    IMU_log << time.toStdString()<<std::endl;
    IMU_log.close();
    viewFinder.capture(address);
}

void ImuDaqDialog::stopSave(QString time)
{
    std::ofstream IMU_log = std::ofstream((address+"log.txt").toStdString().data(), std::ios::out | std::ios::app);
    IMU_log << time.toStdString();
    IMU_log.close();
    viewFinder.stop();
}

void ImuDaqDialog::on_SubjectlineEdit_editingFinished()
{
    subject = ui->SubjectlineEdit->text();
    IMUDAQ->subject = subject.toStdString();
}

void ImuDaqDialog::closeEvent(QCloseEvent *event)
{
    if (viewFinder.getstate()) {
        event->ignore();
        qDebug()<<"please close after over-recording ! ";
    } else {
        event->accept();
    }
    emit(deleteme("ImuDaqDialog"));
}

void ImuDaqDialog::hideEvent(QHideEvent *event)
{
    event->accept();
    viewFinder.hide();
}

void  ImuDaqDialog::showEvent(QShowEvent *event)
{
    event->accept();
    viewFinder.show();
}

void ImuDaqDialog::on_SelectpushButton_clicked()
{
    rootDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     "C:/",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    //IMUDAQ->rootDir = rootDir.toStdString();
    ui->Filelabel->setText(rootDir);
}

void ImuDaqDialog::on_StoppushButton_clicked()
{
    CmdProcess(3);
}

void ImuDaqDialog::on_ConnectpushButton_clicked()
{
    CmdProcess(13);
}
