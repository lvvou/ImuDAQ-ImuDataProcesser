/**
* @file     ImuData.h
* @class    ImuData
* @brief    this file includes class(ImuData) for structing and storing the data from csvreader ,
*           three enumeration types(SignalType,LegType,LegPositionType) for sensors' different
*           signal types and positions on human body and three structions(AllSignalVector,
*           LegPositionSignal,LegSignal) for storing all data from four sensors.
* @variable ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*           TimeVector GetTimeVector(); // used to stored the timestamps
*           LegSignal GetLegSignal();   // used to stored the all data from four sensors
*           MarkerVector GetMarkerVector(); // used to stored the marker marked by user
*           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @author   Flame
* @date     03.05.2019
*/

#ifndef IMUDATA_H
#define IMUDATA_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <QDebug>
#include "ImuMatrix.h"

typedef std::vector<double> TimeVector;
typedef std::vector<double> SignalVector;
typedef std::vector<int> MarkerVector;

typedef struct _AllSignalVector{

    SignalVector TimeStamp;

    SignalVector AccX;
    SignalVector AccY;
    SignalVector AccZ;

    SignalVector GlobalAccX;
    SignalVector GlobalAccY;
    SignalVector GlobalAccZ;

    SignalVector RollRate;
    SignalVector PitchRate;
    SignalVector CourseRate;

    SignalVector Roll;
    SignalVector Pitch;
    SignalVector Course;

    SignalVector QuaternionS;
    SignalVector QuaternionX;
    SignalVector QuaternionY;
    SignalVector QuaternionZ;

    std::vector<SignalVector*> AllAccVector = {&AccX,&AccY,&AccZ};
    std::vector<SignalVector*> AllGlobalAccVector = {&GlobalAccX,&GlobalAccY,&GlobalAccZ};
    std::vector<SignalVector*> AllAngleVector = {&Course,&Roll,&Pitch};
    std::vector<SignalVector*> AllAngleRateVector = {&CourseRate,&RollRate,&PitchRate};
    std::vector<SignalVector*> Quaternion = {&QuaternionS,&QuaternionX,&QuaternionY,&QuaternionZ};
    std::vector<SignalVector*> ShowSignalVector = {&GlobalAccX,&GlobalAccY,&GlobalAccZ,&CourseRate,&Roll,&Pitch};
    std::vector<SignalVector*> AllSignalVector = {&TimeStamp,&AccX,&AccY,&AccZ,&GlobalAccX,&GlobalAccY,&GlobalAccZ,\
                                                  &RollRate,&PitchRate,&CourseRate,&Roll,&Pitch,&Course,\
                                                  &QuaternionS,&QuaternionX,&QuaternionY,&QuaternionZ};

}AllSignalVector;


typedef struct _LegPositionSignal{
    AllSignalVector FootSignal;
    AllSignalVector ThighSignal;

    std::vector<AllSignalVector*> LegPositionSignal ={&FootSignal,&ThighSignal};
}LegPositionSignal;

typedef struct _LegSignal
{
    LegPositionSignal RightLegSignal;
    LegPositionSignal LeftLegSignal;

    std::vector<LegPositionSignal*> LegSignal ={&RightLegSignal,&LeftLegSignal};
}LegSignal;


enum SignalType
{
    TimeStamp = 0,

    AccX,
    AccY,
    AccZ,

    GlobalAccX,
    GlobalAccY,
    GlobalAccZ,

    RollRate,
    PitchRate,
    CourseRate,

    Roll,
    Pitch,
    Course,

    QuaternionS,
    QuaternionX,
    QuaternionY,
    QuaternionZ
};

enum LegType
{
    RT = 0,
    LT
};

enum LegPositionType
{
    Foot = 0,
    Thigh
};
class ImuDataChart
{
public:
    ImuDataChart();
    bool AppendTimeVector(double time);
    bool AppendLegSignal(LegType legtype,LegPositionType legpositiontype,SignalType signaltype,double signal);
    bool AppendMarkerVector(int marknum);
    bool VerifyEuler2Quaternion();
    bool ImuDataShower();
    bool clear();
    TimeVector GetTimeVector();
    LegSignal GetLegSignal();
    MarkerVector GetMarkerVector();

protected:
    TimeVector time;
    LegSignal signal;
    MarkerVector marker;
};

#endif // IMUDATA_H
