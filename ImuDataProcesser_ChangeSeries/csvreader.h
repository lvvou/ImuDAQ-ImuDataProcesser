#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream> 
#include <QDebug>
#include "imudata.h"

typedef std::vector<std::string> StringVector;
typedef std::vector<StringVector> StringMatrix;


class CsvReader
{
public:
    CsvReader();
    bool Init(const std::string filename,char delimiter = ',');
    bool spliteLine(const std::string strLine,StringVector& stringvector,bool convert);
    unsigned int ReadCsv();
	bool ClearVector();
    bool DataChecker();
    bool DataShower();
    bool toImuData(unsigned int iter,QString data,ImuData* imudata);
public:
    ImuData imudata;
protected:
    //file read
    std::string filename;
    //Temp variable
    StringMatrix content;
    char delimiter;
};

#endif // CSVREADER_H
