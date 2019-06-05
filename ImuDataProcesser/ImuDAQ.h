/**
* @file     IMUDAQ.h
* @class    IMUDAQ_Task
* @brief    this file includes class(IMUDAQ_Task) used to get data from Imu sensors.
* @details  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*           ProcessDataAll is a queue type defined by user to store data from four sensnors ,
*           variable "send"  which is true or false decide whether to send data to python program.
*           variable "stopbyuser" which is true or false decide whether to stop program by period.
*           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @author   Flame
* @date     13.04.2019
*/

#ifndef IMUDAQ_H
#define IMUDAQ_H

#include <thread>
#include <chrono>
#include <vector>
#include <queue>
#include <iomanip>
#include <memory>
#include <sstream>
#include <algorithm>
#include <QObject>
#include "time.h"
#include <QTime>
#include <QString>
#include "ImuSocket.h"
#include <sys/timeb.h>
#include "ImuMatrix.h"
#include "ImuEncode.pb.h"
#include "OpenMAT-1.3.5/include/ImuData.h"
#include "OpenMAT-1.3.5/include/LpmsSensorI.h"
#include "OpenMAT-1.3.5/include/LpmsSensorManagerI.h"

typedef unsigned int uint;

typedef struct _ProcessData
{
    LpVector3f GlobalLinAcc;
    ImuData imudata;
    bool ishave=false;
}ProcessData;

class ProcessDataAll
{
public:
    //考虑到先入先出的问题这里使用queue比vector更易实现，修改为queue
    std::queue <ProcessData> ProcessDataFootRT;
    std::queue <ProcessData> ProcessDataThighRT;
    std::queue <ProcessData> ProcessDataFootLT;
    std::queue <ProcessData> ProcessDataThighLT;
    std::vector<std::queue <ProcessData> *> ProcessDataVector;
    ProcessDataAll();
    ~ProcessDataAll();
public:
    bool clear();
    bool hasImuData();
    bool setCurrentData(int i, ProcessData _processdata);
};

class IMUDAQ_Task:public QObject
{
    Q_OBJECT
public:
    //sensor
    std::vector<LpmsSensorI*> Lpms;
    std::vector<double> timeseries;
    std::vector<int> lossnumber = {0,0,0,0};
    //User setting
    timeb currenttime;
    int period;
    bool running;
    bool processing;
    timeb systime_active;
    std::string rootDir;
    std::string subject;
    std::string filename;
    bool firstsave;
    //model
    bool onceonly;
    bool send;
    bool stopbyuser;
    bool firstcheck;

    //signal information
    ImuData imudata;
    double timeStamp;
    LpVector4f Quaternion;
    LpVector4f QuaternionNormal;
    LpVector3f LinAcc;
    LpVector3f GlobalLinAcc;
    LpVector3f Euler;
    std::string leg;
    std::string legposition;
    std::vector<std::string> Leg= { "RT","LT" };
    std::vector<std::string> Legposition = { "Foot","Thigh" };
    ProcessData _processdata;
    ProcessDataAll ProcessDataQueue;
    //file output
    std::ofstream IMU_log;

    //ImuEncoder ———— protocbuf
    std::string ImuEncoderData;
    long ImuSignalDatasetNumber;
    ImuTutorial::ImuSignalDataset imusignaldataset;
    ImuTutorial::Datalength dataLength;
    //ImuTutorial::Signal signal;
    ImuTutorial::Signal::Acc acc;
    ImuTutorial::Signal::Angle angle;
    ImuTutorial::Signal::AngleRate anglerate;
    ImuTutorial::Signal::Quaternion quaternion;
public:
    IMUDAQ_Task();
    ~IMUDAQ_Task();
    bool active();
    bool openfile();
    int datalength();
    bool setrunning(bool runbool);
    bool savedata();
    bool IMUDAQ();
signals:
    void isObtain(QString time);
    void acquireOver(QString time);
private:
    std::shared_ptr<std::thread> t;
};
#endif // IMUDAQ_H
