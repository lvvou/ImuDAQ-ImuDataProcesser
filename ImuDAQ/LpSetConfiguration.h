#ifndef LPSETCONFIGURATION_H
#define LPSETCONFIGURATION_H
#include <QObject>
#include <QPushButton>
#include <thread>
#include <chrono>
#include <vector>
#include "ImuDAQ.h"
#include "OpenMAT-1.3.5/include/LpmsSensorI.h"
#include "OpenMAT-1.3.5/include/LpmsSensorManagerI.h"

void setLpAll(int id, LpmsSensorI* lpms,int Rate);
bool resetTimestamp(std::vector<LpmsSensorI*> Lpms);
bool sync(std::vector<LpmsSensorI*> Lpms);
bool armTimestampReset(std::vector<LpmsSensorI*> Lpms);
bool waitConnect(std::vector<LpmsSensorI*> Lpms, QList<QObject *> ChildList);
void resetAllobject(std::vector<LpmsSensorI*> Lpms);
void IMU_active(std::vector<LpmsSensorI*> Lpms, IMUDAQ_Task* IMUDAQ, bool send, bool onceonly,bool stopbyuser=false,std::string filename="walk",int filenum=1,int period=10,std::string rootDir="F:/");
void init(std::vector<LpmsSensorI*> Lpms,int Rate);
bool showtime(IMUDAQ_Task* IMUDAQ,bool timeshow,int period);
bool IMU_terminate(IMUDAQ_Task* IMUDAQ);
bool IMU_release(LpmsSensorManagerI* manager ,IMUDAQ_Task* IMUDAQ);
void dataoutput(std::string filename,int filenum,int period);
bool RateAnalysis(int rate);
void getBatteryLevel(std::vector<LpmsSensorI*> Lpms);

#endif // LPSETCONFIGURATION_H
