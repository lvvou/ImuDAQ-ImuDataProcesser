#include "LpSetConfiguration.h"
using namespace std;
ImuSocket_Task ImuSocket;
bool syncaction = false;
#define Debug
#undef Debug

// id >= 0
void setSensorID(int id, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_OPENMAT_ID, id)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

/*
#define SELECT_FM_GYRO_ONLY         0
#define SELECT_FM_GYRO_ACC          1
#define SELECT_FM_GYRO_ACC_MAG      2
#define SELECT_FM_MADGWICK_GYRO_ACC 3
#define SELECT_FM_MADGWICK_GYRO_ACC_MAG 4
*/
void setFilterMode(int mode, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_FILTER_MODE, mode)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

/*
#define SELECT_GYR_RANGE_125DPS     125
#define SELECT_GYR_RANGE_245DPS     245
#define SELECT_GYR_RANGE_250DPS     250
#define SELECT_GYR_RANGE_500DPS     500
#define SELECT_GYR_RANGE_1000DPS    1000
#define SELECT_GYR_RANGE_2000DPS    2000
*/
void setGyroRange(int range, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_GYR_RANGE, range)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

/*
#define SELECT_ACC_RANGE_2G     2
#define SELECT_ACC_RANGE_4G     4
#define SELECT_ACC_RANGE_8G     8
#define SELECT_ACC_RANGE_16G    16
*/
void setAccRange(int range, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_ACC_RANGE, range)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

/*
#define SELECT_MAG_RANGE_4GAUSS     4
#define SELECT_MAG_RANGE_8GAUSS     8
#define SELECT_MAG_RANGE_12GAUSS    12
#define SELECT_MAG_RANGE_16GAUSS    16
*/
void setMagRange(int range, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_MAG_RANGE, range)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

/*
#define SELECT_STREAM_FREQ_5HZ          5
#define SELECT_STREAM_FREQ_10HZ         10
#define SELECT_STREAM_FREQ_25HZ         25
#define SELECT_STREAM_FREQ_50HZ         50
#define SELECT_STREAM_FREQ_100HZ        100
#define SELECT_STREAM_FREQ_200HZ        200
#define SELECT_STREAM_FREQ_400HZ        400
#define SELECT_STREAM_FREQ_800HZ        800
*/
void setSamplingRate(int rate, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_SAMPLING_RATE, rate)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

/*
#define SELECT_LPMS_QUAT_OUTPUT_ENABLED                 0x1
#define SELECT_LPMS_EULER_OUTPUT_ENABLED                (0x1 << 1)
#define SELECT_LPMS_LINACC_OUTPUT_ENABLED               (0x1 << 2)
#define SELECT_LPMS_PRESSURE_OUTPUT_ENABLED             (0x1 << 3)
#define SELECT_LPMS_GYRO_OUTPUT_ENABLED                 (0x1 << 4)
#define SELECT_LPMS_ACC_OUTPUT_ENABLED                  (0x1 << 5)
#define SELECT_LPMS_MAG_OUTPUT_ENABLED                  (0x1 << 6)
#define SELECT_LPMS_GYRO_TEMP_OUTPUT_ENABLED            (0x1 << 7)
#define SELECT_LPMS_TEMPERATURE_OUTPUT_ENABLED          (0x1 << 8)
#define SELECT_LPMS_ALTITUDE_OUTPUT_ENABLED             (0x1 << 9)
#define SELECT_LPMS_ANGULAR_VELOCITY_OUTPUT_ENABLED     (0x1 << 10)
*/
void setOutputData(int data, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_SELECT_DATA, data)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

/*
#define SELECT_IMU_SLOW     0
#define SELECT_IMU_MEDIUM   1
#define SELECT_IMU_FAST     2
#define SELECT_IMU_DYNAMIC  3
*/
void setMagneticCorrection(int mode, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_PARAMETER_SET, mode)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

/*
#define SELECT_LPMS_LIN_ACC_COMP_MODE_OFF       0
#define SELECT_LPMS_LIN_ACC_COMP_MODE_WEAK      1
#define SELECT_LPMS_LIN_ACC_COMP_MODE_MEDIUM    2
#define SELECT_LPMS_LIN_ACC_COMP_MODE_STRONG    3
#define SELECT_LPMS_LIN_ACC_COMP_MODE_ULTRA     4
*/
void setLinAccCompensationMode(int mode, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_LIN_ACC_COMP_MODE, mode)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

/*
#define SELECT_LPMS_CENTRI_COMP_MODE_OFF        0
#define SELECT_LPMS_CENTRI_COMP_MODE_ON         1
*/
void setRotationalAccCompensation(int mode, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_CENTRI_COMP_MODE, mode)))
        this_thread::sleep_for(chrono::milliseconds(100));
}
/*
#define SELECT_GYR_AUTOCALIBRATION_DISABLED     0
#define SELECT_GYR_AUTOCALIBRATION_ENABLED      1
*/
void setGyrAutocalibration(int mode, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while (!(lpms->setConfigurationPrm(PRM_GYR_AUTOCALIBRATION, mode)))
        this_thread::sleep_for(chrono::milliseconds(100));
}
/*
#define SELECT_MAG_AUTOCALIBRATION_DISABLED     0
#define SELECT_MAG_AUTOCALIBRATION_ENABLED      1
*/
void setMagAutocalibration(int mode, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while (!(lpms->setConfigurationPrm(PRM_MAG_AUTOCALIBRATION, mode)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

/*
#define SELECT_LPMS_LPBUS_DATA_MODE_32          0
#define SELECT_LPMS_LPBUS_DATA_MODE_16          1
*/
void setLpBusMode(int mode, LpmsSensorI* lpms) {
    this_thread::sleep_for(chrono::milliseconds(100));
    while(!(lpms->setConfigurationPrm(PRM_LPBUS_DATA_MODE, mode)))
        this_thread::sleep_for(chrono::milliseconds(100));
}

void resetobject(LpmsSensorI* lpms)
{
    this_thread::sleep_for(chrono::milliseconds(100));
    lpms->setOrientationOffset(0);
    while (lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED
        && lpms->getSensorStatus() == SENSOR_STATUS_CALIBRATING) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
void _resetAllobject(std::vector<LpmsSensorI*> Lpms)
{
    for (auto lpms : Lpms) {
        this_thread::sleep_for(chrono::milliseconds(100));
        lpms->setOrientationOffset(0);
        while (lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED
            && lpms->getSensorStatus() == SENSOR_STATUS_CALIBRATING) {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    this_thread::sleep_for(chrono::milliseconds(5000));
    std::cout << "Reset over!" << std::endl;
}
void resetAllobject(std::vector<LpmsSensorI*> Lpms)
{
    std::thread t = std::thread(&_resetAllobject, Lpms);
    t.detach(); //启动线程
}
bool _waitConnect(std::vector<LpmsSensorI*> Lpms,QList<QObject*> ChildList)
{
    for (auto lpms:Lpms)
        while (lpms->getConnectionStatus() != SENSOR_CONNECTION_CONNECTED)
            this_thread::sleep_for(chrono::milliseconds(100));
    for (auto lpms : Lpms)
        lpms->run();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "Already!"<<std::endl;
    foreach(QObject *obj,ChildList){
        //QWidget *widget = qobject_cast<QWidget*>(obj);
        //QList<QObject*> ChildrenList = widget->children();
        //foreach(QObject *childrenobj,ChildrenList){
        QPushButton *button = qobject_cast<QPushButton*>(obj);
        if(button)
            button->setEnabled(true);
        //}
    }
    return true;
}
bool waitConnect(std::vector<LpmsSensorI*> Lpms,QList<QObject*> ChildList)
{
    std::thread t = std::thread(&_waitConnect, Lpms,ChildList);
    t.detach(); //启动线程
    return true;
}
void setLpAll(int id,LpmsSensorI* lpms,int Rate=SELECT_STREAM_FREQ_100HZ)
{
    // wait for sensor connection
    while (lpms->getConnectionStatus() != SENSOR_CONNECTION_CONNECTED)
        this_thread::sleep_for(chrono::milliseconds(100));

    // Set sensor ID
    setSensorID(id, lpms);

    // Select sensor filter mode
    setFilterMode(SELECT_FM_MADGWICK_GYRO_ACC_MAG, lpms);

    // Set Gyro range
    setGyroRange(SELECT_GYR_RANGE_2000DPS, lpms);

    // Set Acc range
    setAccRange(SELECT_ACC_RANGE_4G, lpms);

    // Set Magnetometer range
    setMagRange(SELECT_MAG_RANGE_16GAUSS, lpms);

    // Set Streaming frequency
    setSamplingRate(Rate, lpms);

    // Set output data
    setOutputData(
        SELECT_LPMS_ANGULAR_VELOCITY_OUTPUT_ENABLED |
        SELECT_LPMS_LINACC_OUTPUT_ENABLED |
        SELECT_LPMS_QUAT_OUTPUT_ENABLED|
        SELECT_LPMS_EULER_OUTPUT_ENABLED , lpms);

    // Set magnetic correction
    setMagneticCorrection(SELECT_IMU_DYNAMIC, lpms);

    // Set linear acc compensation mode
    setLinAccCompensationMode(SELECT_LPMS_LIN_ACC_COMP_MODE_MEDIUM, lpms);

    // Set Rotational acc compensation mode
    setRotationalAccCompensation(SELECT_LPMS_CENTRI_COMP_MODE_ON, lpms);

    // Set data transfer data bit mode (32/16 bit)
    setLpBusMode(SELECT_LPMS_LPBUS_DATA_MODE_16, lpms);
    // Gyroscope autocalibration enable

    setGyrAutocalibration(SELECT_GYR_AUTOCALIBRATION_ENABLED,lpms);

    // Magnetometer autocalibration enable
    setMagAutocalibration(SELECT_MAG_AUTOCALIBRATION_ENABLED,lpms);


    resetobject(lpms);

    while (lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED
        && lpms->getSensorStatus() == SENSOR_STATUS_CALIBRATING) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    this_thread::sleep_for(chrono::milliseconds(500));
    // Save parameters to sensor
    lpms->saveCalibrationData();
    this_thread::sleep_for(chrono::milliseconds(500));
    lpms->pause();
    while (lpms->getSensorStatus() != SENSOR_STATUS_PAUSED)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cout <<"Sensor_"<<id<< "-----parameter settings done." << endl;
}

bool _resetTimestamp(std::vector<LpmsSensorI*> Lpms)
{
    int i = 0;
    bool sync = true;
    std::vector<int> timedelay = { 0,0,0,0 };
    std::vector<int> timearray = { 0,0,0,0 };
    for (auto lpms : Lpms) {
        if(lpms->getSensorStatus() != SENSOR_STATUS_RUNNING)
            lpms->run();
    }
    while (sync) {
        for (auto lpms : Lpms) {
            while (lpms->getSensorStatus() != SENSOR_STATUS_RUNNING) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            while (lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED
                && lpms->getSensorStatus() == SENSOR_STATUS_CALIBRATING) {
                std::this_thread::sleep_for(chrono::milliseconds(1));
            }
        }
        for (auto lpms : Lpms) {
            lpms->setTimestamp(0);
        }
        std::this_thread::sleep_for(chrono::milliseconds(500));
        i = 0;
        for (auto lpms : Lpms) {
            while (1) {
                if (lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED &&
                    lpms->hasImuData()) {
                    ImuData imudata = lpms->getCurrentData();
                    timearray[i] = int(imudata.timeStamp * 1000);
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(1));
                timedelay[i] = timedelay[i] + 1;
            }
            i++;
        }
        for (int j = 0; j <= 3; j++) {
            for (int n = j + 1; n <= 3; n++) {
                timearray[j] += timedelay[n];
            }
        }
        if (timearray[0] == timearray[1] &&
            timearray[1] == timearray[2] &&
            timearray[2] == timearray[3])
            sync=false;
    }
    for (int j = 0; j <= 3; j++) {
        std::cout << "Sensor" << j << "'s current timeStamp is : " << timearray[j] << "ms" << std::endl;
    }
    std::cout << "All Sensor are already running,please enter \"start\" command to start measure!" << std::endl;
    syncaction = true;
    return true;
}
bool _sync(std::vector<LpmsSensorI*> Lpms)
{
    //for (auto lpms : Lpms) {
    //	if (lpms->getSensorStatus() != SENSOR_STATUS_PAUSED)
    //		lpms->pause();
    //	while (lpms->getSensorStatus() != SENSOR_STATUS_PAUSED) {
    //		std::this_thread::sleep_for(std::chrono::milliseconds(1));
    //	}
    //}
    for (auto lpms : Lpms) {
        if (lpms->getSensorStatus() != SENSOR_STATUS_RUNNING)
            lpms->run();
    }
    for (auto lpms : Lpms) {
        while (lpms->getSensorStatus() != SENSOR_STATUS_RUNNING) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        while (lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED
            && lpms->getSensorStatus() == SENSOR_STATUS_CALIBRATING) {
            std::this_thread::sleep_for(chrono::milliseconds(1));
        }
    }
    for (auto lpms : Lpms) {
        lpms->setTimestamp(0);
    }
    syncaction = true;
    std::cout << "All Sensor are already running,please enter \"start\" command to start measure!" << std::endl;
    return true;
}
bool resetTimestamp(std::vector<LpmsSensorI*> Lpms)
{
    std::thread t = std::thread(&_sync, Lpms);
    //std::thread t = std::thread(&_resetTimestamp, Lpms);
    t.detach(); //启动线程
    return true;
}
bool sync(std::vector<LpmsSensorI*> Lpms)
{
    std::thread t = std::thread(&_sync, Lpms);
    t.detach(); //启动线程
    return true;
}

bool armTimestampReset(std::vector<LpmsSensorI*> Lpms)
{
    for (auto lpms : Lpms) {
        lpms->armTimestampReset();
        while (lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED
            && lpms->getSensorStatus() == SENSOR_STATUS_CALIBRATING) {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    std::cout << "Arm Timestamp Reset over!" << std::endl;
    std::cout << "Please enter your command : ";
    return true;
}

bool showtime(IMUDAQ_Task* IMUDAQ,bool timeshow,int period)
{
    timeb start, end;
    char temp_[20];
    if (!IMUDAQ->onceonly) {
        SetConsoleTitleA("IMUDAQ starting");
        ftime(&start);
        ftime(&end);
        while (end.millitm - start.millitm + 1000 * (end.time - start.time) <= 2 * 1000)	//采集20s的数据
        {
            std::string string_ = "Waiting for : ";
            string_ += _itoa(end.millitm - start.millitm + 1000 * (end.time - start.time), temp_, 10);
            string_ += "ms";
            SetConsoleTitleA(string_.data());
            ftime(&end);
        }
    }
    std::cout << std::endl << "All sensor are already running!" << std::endl;
    std::cout << "Please enter your command : ";
    IMUDAQ->setrunning(true);
    if (timeshow) {
        if (!IMUDAQ->onceonly) {
            ftime(&start);
            ftime(&end);
            while (end.millitm - start.millitm + 1000 * (end.time - start.time) <= period * 1000)	//采集20s的数据
            {
                std::string string_ = "collecting data for : ";
                string_ += _itoa(end.millitm - start.millitm + 1000 * (end.time - start.time), temp_, 10);
                string_ += "ms";
                SetConsoleTitleA(string_.data());
                ftime(&end);
            }
        }
    }
    SetConsoleTitleA("IMU DAQ Program");
    return(true);
}


void init(std::vector<LpmsSensorI*> Lpms,int Rate)
{
    std::cout << "Sensor initing start!" << std::endl;
    int i = 0;
    for (auto lpms : Lpms)
    {
        setLpAll(i, lpms, Rate);
        i++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "Sensor initing over!" << std::endl;
}

void IMU_active(std::vector<LpmsSensorI*> Lpms, IMUDAQ_Task* IMUDAQ,bool send,bool onceonly,bool stopbyuser,std::string filename,int filenum,int period,std::string rootDir)
{
    bool timeshow = true;
    IMUDAQ->Lpms = Lpms;
    std::string filenameall = filename + std::to_string(filenum);
    IMUDAQ->filename = filenameall;
    IMUDAQ->period = period;
    IMUDAQ->processing = true;
    IMUDAQ->rootDir = rootDir;
#ifdef sendDebug
    IMUDAQ->openfile();
#else
    if (!send)IMUDAQ->openfile();
#endif
    IMUDAQ->onceonly = onceonly;
    IMUDAQ->send = send;
    IMUDAQ->stopbyuser = stopbyuser;
    IMUDAQ->timeStamp = 0;
    IMUDAQ->firstsave = true;
    IMUDAQ->firstcheck = true;
    IMUDAQ->timeseries.clear();
    IMUDAQ->ProcessDataQueue.clear();
    for (unsigned int i = 0; i < Lpms.size(); i++)
    {
        IMUDAQ->active();
    }
    for (auto lpms : Lpms) {
        if (lpms->getSensorStatus() != SENSOR_STATUS_RUNNING)
            lpms->run();
    }
    //resetTimestamp(Lpms);
    std::thread t = std::thread(&showtime, std::ref(IMUDAQ),timeshow,period);
    t.detach(); //启动线程
    std::cout << "All sensor are already active!" << std::endl;
}

bool IMU_terminate(IMUDAQ_Task* IMUDAQ)
{
    IMUDAQ->setrunning(false);
    for (unsigned int i = 0; i < IMUDAQ->Lpms.size(); i++)
    {
        IMUDAQ->Lpms[i]->pause();
        while (IMUDAQ->Lpms[i]->getSensorStatus() != SENSOR_STATUS_PAUSED)
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return true;
}

bool IMU_release(LpmsSensorManagerI* manager ,IMUDAQ_Task* IMUDAQ)
{
    for (auto lpms : IMUDAQ->Lpms) {
        manager->removeSensor(lpms);
    }
    delete IMUDAQ;
    IMUDAQ = nullptr;
    delete manager;
    manager = nullptr;
    return true;
}

void dataoutput(std::string filename,int filenum,int period)
{
    std::cout << "filename : " << filename << std::endl;
    std::cout << "filenum : " << filenum << std::endl;
    std::cout << "period : " << period << std::endl;
}

bool RateAnalysis(int rate)
{
    std::vector<int> RateList = { 5,10,25,50,100,200 };
    for (auto _rate : RateList) {
        if (_rate == rate) return true;
    }
    return false;
}

void getBatteryLevel(std::vector<LpmsSensorI*> Lpms)
{
    for (auto lpms : Lpms)
        std::cout << "Sensor" << lpms->getOpenMatId() << "'s battery level is :" << lpms->getBatteryLevel() << "%" << std::endl;
}

