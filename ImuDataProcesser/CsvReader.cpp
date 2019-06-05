#include "CsvReader.h"

CsvReader::CsvReader()
{
    this->filename = "walk1.csv";
    this->delimiter = ',';
}

bool CsvReader::Init(const std::string filename,char delimiter)
{
    this->filename = filename;
	this->delimiter = delimiter;
	return true;
}
bool CsvReader::spliteLine(const std::string strLine,StringVector& stringvector,bool convert)
{
    unsigned int nBegin = 0;
    unsigned int nEnd = 0;
    unsigned int iter = 0;

    while ((nEnd = strLine.find_first_of(delimiter, nBegin)) != std::string::npos)
    {
        std::string strtemp = strLine.substr(nBegin, nEnd - nBegin);
        stringvector.push_back(strtemp);
        if(convert){
            toImuData(iter,QString::fromStdString(strtemp),&imudata);
            iter++;
        }
        nBegin = nEnd + 1;
    }
    if ((nBegin = strLine.find_last_of(delimiter, strLine.length() - 1)) != std::string::npos)
    {
        std::string strtemp = strLine.substr(nBegin + 1, strLine.length() - nBegin -1);
        stringvector.push_back(strtemp);
        if(convert)
            toImuData(iter,QString::fromStdString(strtemp),&imudata);
    }
    return true;
}

unsigned int CsvReader::ReadCsv()
{
    unsigned int length = 0;
    bool convert = false;
    std::ifstream Reader(filename.data());
    if(!Reader){
       std::cout<<"Open fail!"<<std::endl;
       qDebug()<<"Open fail!";
       return length;
    }
    std::string strLineContext;
    while (getline(Reader, strLineContext))
    {
        length++;
        StringVector vecValue;
        spliteLine(strLineContext, vecValue ,convert);
        content.push_back(vecValue);
        convert=true;
    }
    length -= 1;
    Reader.close();
    return length;
}

bool CsvReader::ClearVector()
{
    content.clear();
    imudata.clear();
    return true;
}

bool CsvReader::DataChecker()
{
    StringMatrix::const_iterator itRowData = content.begin();
    for (; itRowData != content.end(); itRowData++)
    {
        const StringVector curVecString = *itRowData;
        if (curVecString.empty())
        {
            return false;
        }
    }
    return true;
}

bool CsvReader::DataShower()
{
    StringMatrix::const_iterator itRowData = content.begin();
    for (; itRowData != content.end(); itRowData++)
    {
        const StringVector curVecString = *itRowData;
        StringVector::const_iterator itColumnData = curVecString.begin();
        for (; itColumnData != curVecString.end(); itColumnData++)
        {
            std::cout<<*itColumnData<<" ";
        }
        std::cout<<std::endl;
    }
    return true;
}

bool CsvReader::toImuData(unsigned int iter,QString data,ImuDataChart* imudata)
{
    //if(iter==1||iter==18||iter==35||iter==52) return false;
    //if(iter>1&&iter<18) iter-=1;
    //if(iter>18&&iter<35) iter-=2;
    //if(iter>35&&iter<52) iter-=3;
    //if(iter>52) iter-=4;

    if(iter==0)
        imudata->AppendTimeVector(data.toDouble());
    if(iter>=1&&iter<=68)
        imudata->AppendLegSignal(LegType((iter-1)/34),LegPositionType((iter-1)%34/17),SignalType((iter-1)%17),data.toDouble());
    if(iter==69)
        imudata->AppendMarkerVector(data.toInt());
    return true;
}
