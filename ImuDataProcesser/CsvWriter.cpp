#include "CsvWriter.h"

CsvWriter::CsvWriter()
{

}

bool CsvWriter::toCsv(QString filename, ImuDataChart imudata,QVector<int> positions,unsigned int length)
{
    std::vector<std::string> Leg = { "RT","LT" };
    std::vector<std::string> Legposition = { "Foot","Thigh" };
    std::ofstream IMU_log = std::ofstream(filename.toStdString().data(), std::ios::out | std::ios::trunc);
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
    for (unsigned int var = 0; var < length; var++) {
        IMU_log << imudata.GetTimeVector()[var]<<",";
        for(auto LegSignal :imudata.GetLegSignal().LegSignal)
            for (auto LegPositionSignal:LegSignal->LegPositionSignal)
                for(auto signal:LegPositionSignal->AllSignalVector)
                {
                    IMU_log <<(*signal)[var]<<',';
                }
        if(positions.indexOf(int(var))!=-1){
            IMU_log << 0;
        }
        else {
            IMU_log << 1 ;
        }
        IMU_log<<std::endl;
    }
    return true;
}
