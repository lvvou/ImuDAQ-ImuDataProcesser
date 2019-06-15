#include "ImuData.h"

ImuDataChart::ImuDataChart()
{
}

bool ImuDataChart::AppendTimeVector(double time){
    this->time.push_back(time);
    return true;
}

bool ImuDataChart::AppendLegSignal(LegType legtype,LegPositionType legpositiontype,SignalType signaltype,double signal)
{
    switch (legtype) {
    case RT:
        switch(legpositiontype){
        case Foot:
            switch (signaltype) {
            case TimeStamp:
                this->signal.RightLegSignal.FootSignal.TimeStamp.push_back(signal);
                break;
            case AccX:
                this->signal.RightLegSignal.FootSignal.AccX.push_back(signal);
                break;
            case AccY:
                this->signal.RightLegSignal.FootSignal.AccY.push_back(signal);
                break;
            case AccZ:
                this->signal.RightLegSignal.FootSignal.AccZ.push_back(signal);
                break;
            case GlobalAccX:
                this->signal.RightLegSignal.FootSignal.GlobalAccX.push_back(signal);
                break;
            case GlobalAccY:
                this->signal.RightLegSignal.FootSignal.GlobalAccY.push_back(signal);
                break;
            case GlobalAccZ:
                this->signal.RightLegSignal.FootSignal.GlobalAccZ.push_back(signal);
                break;
            case Course:
                this->signal.RightLegSignal.FootSignal.Course.push_back(signal);
                break;
            case Roll:
                this->signal.RightLegSignal.FootSignal.Roll.push_back(signal);
                break;
            case Pitch:
                this->signal.RightLegSignal.FootSignal.Pitch.push_back(signal);
                break;
            case CourseRate:
                this->signal.RightLegSignal.FootSignal.CourseRate.push_back(signal);
                break;
            case RollRate:
                this->signal.RightLegSignal.FootSignal.RollRate.push_back(signal);
                break;
            case PitchRate:
                this->signal.RightLegSignal.FootSignal.PitchRate.push_back(signal);
                break;
            case QuaternionS:
                this->signal.RightLegSignal.FootSignal.QuaternionS.push_back(signal);
                break;
            case QuaternionX:
                this->signal.RightLegSignal.FootSignal.QuaternionX.push_back(signal);
                break;
            case QuaternionY:
                this->signal.RightLegSignal.FootSignal.QuaternionY.push_back(signal);
                break;
            case QuaternionZ:
                this->signal.RightLegSignal.FootSignal.QuaternionZ.push_back(signal);
                break;
            }
            break;
        case Thigh:
            switch (signaltype) {
            case TimeStamp:
                this->signal.RightLegSignal.ThighSignal.TimeStamp.push_back(signal);
                break;
            case AccX:
                this->signal.RightLegSignal.ThighSignal.AccX.push_back(signal);
                break;
            case AccY:
                this->signal.RightLegSignal.ThighSignal.AccY.push_back(signal);
                break;
            case AccZ:
                this->signal.RightLegSignal.ThighSignal.AccZ.push_back(signal);
                break;
            case GlobalAccX:
                this->signal.RightLegSignal.ThighSignal.GlobalAccX.push_back(signal);
                break;
            case GlobalAccY:
                this->signal.RightLegSignal.ThighSignal.GlobalAccY.push_back(signal);
                break;
            case GlobalAccZ:
                this->signal.RightLegSignal.ThighSignal.GlobalAccZ.push_back(signal);
                break;
            case Course:
                this->signal.RightLegSignal.ThighSignal.Course.push_back(signal);
                break;
            case Roll:
                this->signal.RightLegSignal.ThighSignal.Roll.push_back(signal);
                break;
            case Pitch:
                this->signal.RightLegSignal.ThighSignal.Pitch.push_back(signal);
                break;
            case CourseRate:
                this->signal.RightLegSignal.ThighSignal.CourseRate.push_back(signal);
                break;
            case RollRate:
                this->signal.RightLegSignal.ThighSignal.RollRate.push_back(signal);
                break;
            case PitchRate:
                this->signal.RightLegSignal.ThighSignal.PitchRate.push_back(signal);
                break;
            case QuaternionS:
                this->signal.RightLegSignal.ThighSignal.QuaternionS.push_back(signal);
                break;
            case QuaternionX:
                this->signal.RightLegSignal.ThighSignal.QuaternionX.push_back(signal);
                break;
            case QuaternionY:
                this->signal.RightLegSignal.ThighSignal.QuaternionY.push_back(signal);
                break;
            case QuaternionZ:
                this->signal.RightLegSignal.ThighSignal.QuaternionZ.push_back(signal);
                break;
            }
            break;
        }

        break;
    case LT:
        switch(legpositiontype){
        case Foot:
            switch (signaltype) {
            case TimeStamp:
                this->signal.LeftLegSignal.FootSignal.TimeStamp.push_back(signal);
                break;
            case AccX:
                this->signal.LeftLegSignal.FootSignal.AccX.push_back(signal);
                break;
            case AccY:
                this->signal.LeftLegSignal.FootSignal.AccY.push_back(signal);
                break;
            case AccZ:
                this->signal.LeftLegSignal.FootSignal.AccZ.push_back(signal);
                break;
            case GlobalAccX:
                this->signal.LeftLegSignal.FootSignal.GlobalAccX.push_back(signal);
                break;
            case GlobalAccY:
                this->signal.LeftLegSignal.FootSignal.GlobalAccY.push_back(signal);
                break;
            case GlobalAccZ:
                this->signal.LeftLegSignal.FootSignal.GlobalAccZ.push_back(signal);
                break;
            case Course:
                this->signal.LeftLegSignal.FootSignal.Course.push_back(signal);
                break;
            case Roll:
                this->signal.LeftLegSignal.FootSignal.Roll.push_back(signal);
                break;
            case Pitch:
                this->signal.LeftLegSignal.FootSignal.Pitch.push_back(signal);
                break;
            case CourseRate:
                this->signal.LeftLegSignal.FootSignal.CourseRate.push_back(signal);
                break;
            case RollRate:
                this->signal.LeftLegSignal.FootSignal.RollRate.push_back(signal);
                break;
            case PitchRate:
                this->signal.LeftLegSignal.FootSignal.PitchRate.push_back(signal);
                break;
            case QuaternionS:
                this->signal.LeftLegSignal.FootSignal.QuaternionS.push_back(signal);
                break;
            case QuaternionX:
                this->signal.LeftLegSignal.FootSignal.QuaternionX.push_back(signal);
                break;
            case QuaternionY:
                this->signal.LeftLegSignal.FootSignal.QuaternionY.push_back(signal);
                break;
            case QuaternionZ:
                this->signal.LeftLegSignal.FootSignal.QuaternionZ.push_back(signal);
                break;
            }
            break;
        case Thigh:
            switch (signaltype) {
            case TimeStamp:
                this->signal.LeftLegSignal.ThighSignal.TimeStamp.push_back(signal);
                break;
            case AccX:
                this->signal.LeftLegSignal.ThighSignal.AccX.push_back(signal);
                break;
            case AccY:
                this->signal.LeftLegSignal.ThighSignal.AccY.push_back(signal);
                break;
            case AccZ:
                this->signal.LeftLegSignal.ThighSignal.AccZ.push_back(signal);
                break;
            case GlobalAccX:
                this->signal.LeftLegSignal.ThighSignal.GlobalAccX.push_back(signal);
                break;
            case GlobalAccY:
                this->signal.LeftLegSignal.ThighSignal.GlobalAccY.push_back(signal);
                break;
            case GlobalAccZ:
                this->signal.LeftLegSignal.ThighSignal.GlobalAccZ.push_back(signal);
                break;
            case Course:
                this->signal.LeftLegSignal.ThighSignal.Course.push_back(signal);
                break;
            case Roll:
                this->signal.LeftLegSignal.ThighSignal.Roll.push_back(signal);
                break;
            case Pitch:
                this->signal.LeftLegSignal.ThighSignal.Pitch.push_back(signal);
                break;
            case CourseRate:
                this->signal.LeftLegSignal.ThighSignal.CourseRate.push_back(signal);
                break;
            case RollRate:
                this->signal.LeftLegSignal.ThighSignal.RollRate.push_back(signal);
                break;
            case PitchRate:
                this->signal.LeftLegSignal.ThighSignal.PitchRate.push_back(signal);
                break;
            case QuaternionS:
                this->signal.LeftLegSignal.ThighSignal.QuaternionS.push_back(signal);
                break;
            case QuaternionX:
                this->signal.LeftLegSignal.ThighSignal.QuaternionX.push_back(signal);
                break;
            case QuaternionY:
                this->signal.LeftLegSignal.ThighSignal.QuaternionY.push_back(signal);
                break;
            case QuaternionZ:
                this->signal.LeftLegSignal.ThighSignal.QuaternionZ.push_back(signal);
                break;
            }
            break;
        }
        break;
    }
    return true;
}

bool ImuDataChart::AppendMarkerVector(int marknum)
{
    this->marker.push_back(marknum);
    return true;
}

TimeVector ImuDataChart::GetTimeVector()
{
    return this->time;
}

LegSignal ImuDataChart::GetLegSignal()
{
    return this->signal;
}

MarkerVector ImuDataChart::GetMarkerVector()
{
    return this->marker;
}

bool ImuDataChart::ImuDataShower()
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

bool ImuDataChart::clear()
{
    this->time.clear();
    this->marker.clear();
    for (auto LegSignal : this->signal.LegSignal)
        for (auto LegPositionSignal:LegSignal->LegPositionSignal)
            for(auto signal:LegPositionSignal->AllSignalVector)
                signal->clear();
    return true;
}

bool ImuDataChart::VerifyEuler2Quaternion()
{
    for(auto LegSignal : this->signal.LegSignal)
        for (auto LegPositionSignal:LegSignal->LegPositionSignal)
        {
            float r2d = 1;

            LpVector4f q;

            q.data[0] = *(LegPositionSignal->QuaternionS.end()-1);
            q.data[1] = *(LegPositionSignal->QuaternionX.end()-1);
            q.data[2] = *(LegPositionSignal->QuaternionY.end()-1);
            q.data[3] = *(LegPositionSignal->QuaternionZ.end()-1);

            std::cout << "q.data[0] : " << *(LegPositionSignal->QuaternionS.end()-1) << std::endl;
            std::cout << "q.data[1] : " << *(LegPositionSignal->QuaternionX.end()-1) << std::endl;
            std::cout << "q.data[2] : " << *(LegPositionSignal->QuaternionY.end()-1) << std::endl;
            std::cout << "q.data[3] : " << *(LegPositionSignal->QuaternionZ.end()-1) << std::endl;

            LpVector3f r;

            quaternionToEuler(&q,&r);

            std::cout<< "angle : "<<r.data[0] << " angletruth : " << *(LegPositionSignal->Roll.end()-1) << std::endl;
            std::cout<< "angle : "<<r.data[1] << " angletruth : " << *(LegPositionSignal->Pitch.end()-1) << std::endl;
            std::cout<< "angle : "<<r.data[2] << " angletruth : " << *(LegPositionSignal->Course.end()-1) << std::endl;

            std::cout<< std::endl<<"VerifyEuler2Quaternion:" \
                     << " "<<r.data[0] - *(LegPositionSignal->Roll.end()-1)\
                     << " "<<r.data[1] - *(LegPositionSignal->Pitch.end()-1)\
                     << " "<<r.data[2] - *(LegPositionSignal->Course.end()-1) << std::endl;


        }
    return true;
}
