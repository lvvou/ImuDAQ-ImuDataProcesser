#ifndef IMUDATA_H
#define IMUDATA_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <QDebug>

typedef std::vector<int> TimeVector;
typedef std::vector<double> SignalVector;
typedef std::vector<bool> MarkerVector;

typedef struct _AllSignalVector{
    SignalVector AccX;
    SignalVector AccY;
    SignalVector AccZ;

    SignalVector CourseRate;
    SignalVector Roll;
    SignalVector Pitch;
    std::vector<SignalVector*> AllAccVector = {&AccX,&AccY,&AccZ};
    std::vector<SignalVector*> AllAngleVector = {&CourseRate,&Roll,&Pitch};
    std::vector<SignalVector*> AllSignalVector ={&AccX,&AccY,&AccZ,&CourseRate,&Roll,&Pitch};
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
    AccX = 0,
    AccY,
    AccZ,
    CoursRate,
    Roll,
    Pitch
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
class ImuData
{
public:
    ImuData();
    bool AppendTimeVector(int time);
    bool AppendLegSignal(LegType legtype,LegPositionType legpositiontype,SignalType signaltype,double signal);
    bool AppendMarkerVector(int marknum);
    bool ImuDataShower();
    TimeVector GetTimeVector();
    LegSignal GetLegSignal();
    MarkerVector GetMarkerVector();
protected:
    TimeVector time;
    LegSignal signal;
    MarkerVector marker;
};

#endif // IMUDATA_H
