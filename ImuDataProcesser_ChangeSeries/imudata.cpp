#include "imudata.h"

ImuData::ImuData()
{
}
bool ImuData::AppendTimeVector(int time){
    this->time.push_back(time);
    return true;
}
bool ImuData::AppendLegSignal(LegType legtype,LegPositionType legpositiontype,SignalType signaltype,double signal)
{
    switch (legtype) {
    case RT:
        switch(legpositiontype){
        case Foot:
            switch (signaltype) {
            case AccX:
                this->signal.RightLegSignal.FootSignal.AccX.push_back(signal);
                break;
            case AccY:
                this->signal.RightLegSignal.FootSignal.AccY.push_back(signal);
                break;
            case AccZ:
                this->signal.RightLegSignal.FootSignal.AccZ.push_back(signal);
                break;
            case CoursRate:
                this->signal.RightLegSignal.FootSignal.CourseRate.push_back(signal);
                break;
            case Roll:
                this->signal.RightLegSignal.FootSignal.Roll.push_back(signal);
                break;
            case Pitch:
                this->signal.RightLegSignal.FootSignal.Pitch.push_back(signal);
                break;
            }
            break;
        case Thigh:
            switch (signaltype) {
            case AccX:
                this->signal.RightLegSignal.ThighSignal.AccX.push_back(signal);
                break;
            case AccY:
                this->signal.RightLegSignal.ThighSignal.AccY.push_back(signal);
                break;
            case AccZ:
                this->signal.RightLegSignal.ThighSignal.AccZ.push_back(signal);
                break;
            case CoursRate:
                this->signal.RightLegSignal.ThighSignal.CourseRate.push_back(signal);
                break;
            case Roll:
                this->signal.RightLegSignal.ThighSignal.Roll.push_back(signal);
                break;
            case Pitch:
                this->signal.RightLegSignal.ThighSignal.Pitch.push_back(signal);
                break;
            }
            break;
        }

        break;
    case LT:
        switch(legpositiontype){
        case Foot:
            switch (signaltype) {
            case AccX:
                this->signal.LeftLegSignal.FootSignal.AccX.push_back(signal);
                break;
            case AccY:
                this->signal.LeftLegSignal.FootSignal.AccY.push_back(signal);
                break;
            case AccZ:
                this->signal.LeftLegSignal.FootSignal.AccZ.push_back(signal);
                break;
            case CoursRate:
                this->signal.LeftLegSignal.FootSignal.CourseRate.push_back(signal);
                break;
            case Roll:
                this->signal.LeftLegSignal.FootSignal.Roll.push_back(signal);
                break;
            case Pitch:
                this->signal.LeftLegSignal.FootSignal.Pitch.push_back(signal);
                break;
            }
            break;
        case Thigh:
            switch (signaltype) {
            case AccX:
                this->signal.LeftLegSignal.ThighSignal.AccX.push_back(signal);
                break;
            case AccY:
                this->signal.LeftLegSignal.ThighSignal.AccY.push_back(signal);
                break;
            case AccZ:
                this->signal.LeftLegSignal.ThighSignal.AccZ.push_back(signal);
                break;
            case CoursRate:
                this->signal.LeftLegSignal.ThighSignal.CourseRate.push_back(signal);
                break;
            case Roll:
                this->signal.LeftLegSignal.ThighSignal.Roll.push_back(signal);
                break;
            case Pitch:
                this->signal.LeftLegSignal.ThighSignal.Pitch.push_back(signal);
                break;
            }
            break;
        }
        break;
    }
    return true;
}
bool ImuData::AppendMarkerVector(int marknum)
{
    this->marker.push_back(marknum);
    return true;
}

TimeVector ImuData::GetTimeVector()
{
    return this->time;
}
LegSignal ImuData::GetLegSignal()
{
    return this->signal;
}
MarkerVector ImuData::GetMarkerVector()
{
    return this->marker;
}

bool ImuData::ImuDataShower()
{
    unsigned int length = time.size();
    for(unsigned int i=0;i<length;i++)
    {
        std::cout<<" Time : "<<time[i]<<std::endl;
        std::cout<<" Right"<<"Foot AccX       : "<<signal.RightLegSignal.FootSignal.AccX[i]<<std::endl;
        std::cout<<" Right"<<"Foot AccY       : "<<signal.RightLegSignal.FootSignal.AccY[i]<<std::endl;
        std::cout<<" Right"<<"Foot AccZ       : "<<signal.RightLegSignal.FootSignal.AccZ[i]<<std::endl;
        std::cout<<" Right"<<"Foot CourseRate : "<<signal.RightLegSignal.FootSignal.CourseRate[i]<<std::endl;
        std::cout<<" Right"<<"Foot Roll       : "<<signal.RightLegSignal.FootSignal.Roll[i]<<std::endl;
        std::cout<<" Right"<<"Foot Pitch      : "<<signal.RightLegSignal.FootSignal.Pitch[i]<<std::endl;

        std::cout<<" Right"<<"Thigh AccX       : "<<signal.RightLegSignal.ThighSignal.AccX[i]<<std::endl;
        std::cout<<" Right"<<"Thigh AccY       : "<<signal.RightLegSignal.ThighSignal.AccY[i]<<std::endl;
        std::cout<<" Right"<<"Thigh AccZ       : "<<signal.RightLegSignal.ThighSignal.AccZ[i]<<std::endl;
        std::cout<<" Right"<<"Thigh CourseRate : "<<signal.RightLegSignal.ThighSignal.CourseRate[i]<<std::endl;
        std::cout<<" Right"<<"Thigh Roll       : "<<signal.RightLegSignal.ThighSignal.Roll[i]<<std::endl;
        std::cout<<" Right"<<"Thigh Pitch      : "<<signal.RightLegSignal.ThighSignal.Pitch[i]<<std::endl;

        std::cout<<" Left"<<"Foot AccX       : "<<signal.LeftLegSignal.FootSignal.AccX[i]<<std::endl;
        std::cout<<" Left"<<"Foot AccY       : "<<signal.LeftLegSignal.FootSignal.AccY[i]<<std::endl;
        std::cout<<" Left"<<"Foot AccZ       : "<<signal.LeftLegSignal.FootSignal.AccZ[i]<<std::endl;
        std::cout<<" Left"<<"Foot CourseRate : "<<signal.LeftLegSignal.FootSignal.CourseRate[i]<<std::endl;
        std::cout<<" Left"<<"Foot Roll       : "<<signal.LeftLegSignal.FootSignal.Roll[i]<<std::endl;
        std::cout<<" Left"<<"Foot Pitch      : "<<signal.LeftLegSignal.FootSignal.Pitch[i]<<std::endl;

        std::cout<<" Left"<<"Thigh AccX       : "<<signal.LeftLegSignal.ThighSignal.AccX[i]<<std::endl;
        std::cout<<" Left"<<"Thigh AccY       : "<<signal.LeftLegSignal.ThighSignal.AccY[i]<<std::endl;
        std::cout<<" Left"<<"Thigh AccZ       : "<<signal.LeftLegSignal.ThighSignal.AccZ[i]<<std::endl;
        std::cout<<" Left"<<"Thigh CourseRate : "<<signal.LeftLegSignal.ThighSignal.CourseRate[i]<<std::endl;
        std::cout<<" Left"<<"Thigh Roll       : "<<signal.LeftLegSignal.ThighSignal.Roll[i]<<std::endl;
        std::cout<<" Left"<<"Thigh Pitch      : "<<signal.LeftLegSignal.ThighSignal.Pitch[i]<<std::endl;
        std::cout<<" Marker : "<<marker[i]<<std::endl;
    }
    return true;
}
