#include "ImuDAQ.h"

extern ImuSocket_Task ImuSocket;
/*Debug Define Enable*/
// #define sendDebug

/*Data define*/
#define Quarterinon

double doubleabs(double var)
{
    if (var < 0) return -var;
    return var;
}

bool isequal(double var1, double var2)
{
    if (doubleabs(var1 - var2) < 0.00999)
        return true;
    return false;
}

bool isequal(std::vector<double> var)
{
    if (std::max_element(var.begin(), var.end()) == std::min_element(var.begin(), var.end()))
        return true;
    return false;
}

IMUDAQ_Task::IMUDAQ_Task()
{
    t = nullptr;
    firstsave = true;
    processing = false;
    filename = "walk";
    subject = "Flame";
    rootDir = "C:/";
    onceonly = false;
    stopbyuser = false;
    send = true;
    ImuSignalDatasetNumber = 0;
}

IMUDAQ_Task::~IMUDAQ_Task()
{
    IMU_log.clear();
}

bool IMUDAQ_Task::active()
{
    if (nullptr == t)
    {
        std::cout <<"IMU is active !" << std::endl;
        t = std::make_shared<std::thread>(&IMUDAQ_Task::IMUDAQ, this);
        t->detach(); //启动线程
        }
    return(true);
};

/*打开文件*/
bool IMUDAQ_Task::openfile()
{
    filename = rootDir + "ImuLog/" + subject + "/" + filename + ".csv";
    IMU_log = std::ofstream(filename.data(), std::ios::out | std::ios::trunc);
    IMU_log << "TimeStamp,";
    std::vector<std::string> columns = { "TimeStamp","AccX", "AccY", "AccZ", "GlobalAccX", "GlobalAccY", "GlobalAccZ",\
                                         "RollRate", "PitchRate","CourseRate", "Roll", "Pitch", "Course",\
                                         "QuaternionS","QuaternionX","QuaternionY","QuaternionZ"};
    for (auto legtemp: Leg)
        for (auto legpositiontemp : Legposition) {
            for (auto column : columns) {
                column = legpositiontemp+"_"+ column +"_"+ legtemp;
                for (auto col : column) {
                    IMU_log << col;
                }
                IMU_log << ",";
            }
        }
    IMU_log << "marker" << std::endl;
    return(true);
}

/*保存文件*/
bool IMUDAQ_Task::savedata()
{
    //这里考虑到数据堆积，使用最新的时间戳选择对数据正式采集前采集得到的数据进行舍去
    {
        //if(firstcheck)
        //	for (int i = 0; i < 4; i++) {
        //		ProcessDataQueue.clear();
        //	}
        if(timeseries.empty())
            for (int i = 0; i < 4; i++) {
                ProcessData _processdata = ProcessDataQueue.ProcessDataVector[i]->back();
                timeseries.push_back(_processdata.imudata.timeStamp);
            }
        std::vector<bool> sync = { false,false,false,false };
        if (firstsave == true)
        {
            auto maxtime = std::max_element(timeseries.begin(), timeseries.end());
            std::cout << "last sync timestamp is : " << *maxtime << std::endl;
            for (int i = 0; i < 4; i++) {
                while (1) {
                    if (!ProcessDataQueue.ProcessDataVector[i]->empty()) {
                        ProcessData _processdata = ProcessDataQueue.ProcessDataVector[i]->front();
                        //由于0.01在c++中的表示总是多点或者少点，这会导致判别不准，所以使用0.00999表示0.01
                        if ((*maxtime - _processdata.imudata.timeStamp >= 0.00999)) {
                            std::cout << "the timestamp which sensor" << i << " drop is ：" << _processdata.imudata.timeStamp << std::endl;
                            ProcessDataQueue.ProcessDataVector[i]->pop();
                        }
                        else {
                            sync[i] = true;
                            break;
                        }
                    }
                    else break;
                }
            }
            if (sync[0] && sync[1] && sync[2] && sync[3]) {
                firstsave = false;
                timeseries.clear();
            }
        }
    }
    if (firstsave == false) {
        timeStamp += 1;
        if (!send) {
            IMU_log << timeStamp << ',';
            //linAcc 线性加速度 即为去除重力加速度的加速度值(m/s^2)；
            //r为欧拉角 就是global angle(rad)；
            //w为角速度，陀螺仪的原始数据(rad/s)；
            std::vector<double> timeseriestemp;
            unsigned int lossID = 0;
            for (unsigned int i = 0; i < 4; i++) {
                ProcessData _processdata = ProcessDataQueue.ProcessDataVector[i]->front();
                timeseriestemp.push_back(_processdata.imudata.timeStamp);
            }
            auto mintime = std::min_element(timeseriestemp.begin(), timeseriestemp.end());
            for (unsigned int i = 0; i < 4; i++) {
                ProcessData _processdata = ProcessDataQueue.ProcessDataVector[i]->front();
                IMU_log << _processdata.imudata.timeStamp << ',' \
                        << _processdata.imudata.linAcc[0] << ',' << _processdata.imudata.linAcc[1] << ','<< _processdata.imudata.linAcc[2] << ',' \
                        << _processdata.GlobalLinAcc.data[0] << ',' << _processdata.GlobalLinAcc.data[1] << ','<< _processdata.GlobalLinAcc.data[2] << ',' \
                        << _processdata.imudata.w[0] << ',' << _processdata.imudata.w[1] << ','<< _processdata.imudata.w[2] << ',' \
                        << _processdata.imudata.r[0] << ',' << _processdata.imudata.r[1] << ','<< _processdata.imudata.r[2] << ',' \
                        << _processdata.imudata.q[0] << ',' << _processdata.imudata.q[1] << ',' << _processdata.imudata.q[2] << ',' << _processdata.imudata.q[3] << ',' ;
                if (isequal(_processdata.imudata.timeStamp ,*mintime)) {
                    ProcessDataQueue.ProcessDataVector[i]->pop();
                }
                else{
                    lossID = i;
                }
            }
            IMU_log << isequal(timeseriestemp) << std::endl;
            if (!isequal(timeseriestemp))
                std::cout << "sensor " << lossID << " loss package : "  << ++lossnumber[lossID] << std::endl;
        }
        else {
#ifdef sendDebug
            IMU_log << timeStamp << ',';
#endif
            std::cout << "I'm here! 1" << std::endl;
            std::vector<double> timeseriestemp;
            int lossID;
            for (unsigned int i = 0; i < 4; i++) {
                ProcessData _processdata = ProcessDataQueue.ProcessDataVector[i]->front();
                timeseriestemp.push_back(_processdata.imudata.timeStamp);
            }
            auto mintime = std::min_element(timeseriestemp.begin(), timeseriestemp.end());
            ImuTutorial::ImuSignal *imuSignal = imusignaldataset.add_imusignal();
            imuSignal->set_time(timeStamp);

            for (unsigned int i = 0; i < 4; i++) {
                ProcessData _processdata = ProcessDataQueue.ProcessDataVector[i]->front();
                ImuTutorial::Signal* signal = imuSignal->add_signal();
                signal->set_leg(ImuTutorial::Signal::Leg(i / 2));
                signal->set_legposition(ImuTutorial::Signal::LegPosition(i % 2));
                acc.set_accx(_processdata.GlobalLinAcc.data[0]);
                acc.set_accy(_processdata.GlobalLinAcc.data[1]);
                acc.set_accz(_processdata.GlobalLinAcc.data[2]);
                angle.set_roll(_processdata.imudata.r[0]);
                angle.set_pitch(_processdata.imudata.r[1]);
                anglerate.set_course(_processdata.imudata.w[2]);
#ifdef Quarterinon
                quaternion.set_v(_processdata.imudata.q[0]);
                quaternion.set_x(_processdata.imudata.q[1]);
                quaternion.set_y(_processdata.imudata.q[2]);
                quaternion.set_z(_processdata.imudata.q[3]);
                signal->mutable_quaternion()->CopyFrom(quaternion);
#endif
                signal->mutable_acc()->CopyFrom(this->acc);
                signal->mutable_angle()->CopyFrom(this->angle);
                signal->mutable_anglerate()->CopyFrom(this->anglerate);
#ifdef sendDebug
                IMU_log << _processdata.GlobalLinAcc.data[0] << ',' << _processdata.GlobalLinAcc.data[1] << ',' << _processdata.GlobalLinAcc.data[2] << ','\
                    << _processdata.imudata.w[2] << ',' << _processdata.imudata.r[0] << ',' << _processdata.imudata.r[1] << ',';
#endif
                if (isequal(_processdata.imudata.timeStamp, *mintime)) {
                    ProcessDataQueue.ProcessDataVector[i]->pop();
                }
                else {
                    lossID = i;
                }
            }
            std::cout << "I'm here! 2" << std::endl;
#ifdef sendDebug
            IMU_log << std::endl;
#endif
            if (imusignaldataset.imusignal_size() >= 50) {
                std::cout << "I'm here! 3" << std::endl;
                ImuSignalDatasetNumber++;
                imusignaldataset.SerializeToString(&ImuEncoderData);
                if (imusignaldataset.IsInitialized()) {
                    std::string length;
                    dataLength.set_length(ImuEncoderData.length());
                    dataLength.SerializeToString(&length);
                    std::cout << "I'm here! 4" << std::endl;
                    ImuSocket.ImuSend(length.data(), length.length());
                    std::cout << "I'm here! 5" << std::endl;
                    ftime(&currenttime);
                    std::cout << ImuSignalDatasetNumber << " data length is : " << ImuEncoderData.length() << " time: " << std::fixed << currenttime.time + double(currenttime.millitm) / 1000 << std::endl;
                    ImuSocket.ImuSend(ImuEncoderData.data(), ImuEncoderData.length());
                    imusignaldataset.Clear();
                }
                else {
                    std::cout << "Signal is  not Initialized" << std::endl;
                    return false;
                }
            }
        }
        return(true);
    }
    return(false);
}

int IMUDAQ_Task::datalength()
{
    ProcessData _processdata;
    for (int j = 0; j < 50; j++) {
        ImuTutorial::ImuSignal *imuSignal = imusignaldataset.add_imusignal();
        imuSignal->set_time(0);
        for (int i = 0; i < 4; i++) {
            ImuTutorial::Signal* signal = imuSignal->add_signal();
            signal->set_leg(ImuTutorial::Signal::Leg(i / 2));
            signal->set_legposition(ImuTutorial::Signal::LegPosition(i % 2));
            acc.set_accx(_processdata.GlobalLinAcc.data[0]);
            acc.set_accy(_processdata.GlobalLinAcc.data[1]);
            acc.set_accz(_processdata.GlobalLinAcc.data[2]);
            angle.set_roll(_processdata.imudata.r[0]);
            angle.set_pitch(_processdata.imudata.r[1]);
            anglerate.set_course(_processdata.imudata.w[2]);
#ifdef Quarterinon
            quaternion.set_v(_processdata.imudata.q[0]);
            quaternion.set_x(_processdata.imudata.q[1]);
            quaternion.set_y(_processdata.imudata.q[2]);
            quaternion.set_z(_processdata.imudata.q[3]);
            signal->mutable_quaternion()->CopyFrom(quaternion);
#endif
            signal->mutable_acc()->CopyFrom(this->acc);
            signal->mutable_angle()->CopyFrom(this->angle);
            signal->mutable_anglerate()->CopyFrom(this->anglerate);
        }
    }
    imusignaldataset.SerializeToString(&ImuEncoderData);
    std::string length;
    dataLength.set_length(ImuEncoderData.length());
    dataLength.SerializeToString(&length);
    std::cout << "data number is : " << imusignaldataset.imusignal_size() << std::endl;
    std::cout << "data length is : " << ImuEncoderData.length() << std::endl;
    std::cout << "length's length is : " << length.length() << std::endl;
    imusignaldataset.Clear();
    return(ImuEncoderData.length());
}

bool IMUDAQ_Task::IMUDAQ()
{
    bool first = true;
    timeb start, end;
    int i[4] = { 0,0,0,0};
    int j = 0;
    while (1) {
        ftime(&start);
        ftime(&end);
        while ((end.millitm - start.millitm + 1000 * (end.time - start.time) <= period * 1000 || stopbyuser || onceonly)
            && running)
        {
            j = 0;
            for (auto lpms : Lpms) {
                //使用while循环将dataqueue中的数据全部取出，防止数据堆积整体延迟
                while(lpms->getConnectionStatus() == SENSOR_CONNECTION_CONNECTED &&
                    lpms->hasImuData() > 0) {
                    _processdata.imudata = lpms->getCurrentData();
                    _processdata.imudata.q[0] = -_processdata.imudata.q[0];
                    memcpy(Quaternion.data, _processdata.imudata.q, 4 * sizeof(float));
                    scalarVectMult4x1(vect4x1Norm(Quaternion), &Quaternion, &QuaternionNormal);
                    memcpy(LinAcc.data, _processdata.imudata.linAcc, 3 * sizeof(float));
                    quatRotVec(QuaternionNormal, LinAcc, &_processdata.GlobalLinAcc);
                    ProcessDataQueue.setCurrentData(j, _processdata);
                    i[j]++;
                }
                j++;
            }
            if (first)
            {
                first = false;
                if (onceonly)
                    break;
                if(!send)
                    emit(isObtain(QString::number(_processdata.imudata.timeStamp)+"_"+QString::number(QTime::currentTime().msecsSinceStartOfDay())));
            }
            while(ProcessDataQueue.hasImuData())
                savedata();
            ftime(&end);
        }
        if(end.millitm - start.millitm + 1000 * (end.time - start.time) > period*1000 || stopbyuser || onceonly)
            processing = false;
        if ((running == false)&&!first)
        {
            break;
        }
        if ((running == true) && ((processing == false)|| onceonly)) {
            running = false;
            break;
        }
    }
    emit(acquireOver(QString::number(_processdata.imudata.timeStamp)+"_"+QString::number(QTime::currentTime().msecsSinceStartOfDay())));
    std::cout << std::endl;
    for (int n = 0; n < 4; n++)
        std::cout << Leg[n / 2] << " " << Legposition[n % 2] << " data lenght：" << i[n] << std::endl;
#ifdef sendDebug
    if (processing == false) IMU_log.close();
#else
    if (!send) IMU_log.close();
#endif // sendDebug

    std::cout << "Data Acquisition over !" << std::endl;
    std::cout << "Wait for 1 second !" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Please enter your command : ";
    t = nullptr;
    return(true);
}
bool IMUDAQ_Task::setrunning(bool runbool)
{
    running = runbool;
    return true;
}

ProcessDataAll::ProcessDataAll()
{
    ProcessDataVector.push_back(&ProcessDataFootRT);
    ProcessDataVector.push_back(&ProcessDataFootLT);
    ProcessDataVector.push_back(&ProcessDataThighRT);
    ProcessDataVector.push_back(&ProcessDataThighLT);
}
ProcessDataAll::~ProcessDataAll()
{
}
bool ProcessDataAll::clear()
{
    for (auto process : ProcessDataVector)
        while (!process->empty())
            process->pop();
    return true;
}
bool ProcessDataAll::hasImuData()
{
    if (!ProcessDataFootRT.empty() &&
        !ProcessDataFootLT.empty() &&
        !ProcessDataThighRT.empty() &&
        !ProcessDataThighLT.empty())
        return true;
    else return false;
}
bool ProcessDataAll::setCurrentData(int i, ProcessData _processdata)
{
    if (i >= 0 && i <= 3) {
        ProcessDataVector[uint(i)]->push(_processdata);
        return true;
    }
    else return false;
}
