/**
* @file     CsvReader.h
* @class    CsvReader
* @brief    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*           this file includes class(CsvReader) for readering the csv file to a string
*           vector and converting strings to structed data type--ImuData.
*           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @details
* @author   Flame
* @date     03.05.2019
*/

#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream> 
#include <QDebug>
#include "ImuData.h"

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
    bool toImuData(unsigned int iter,QString data,ImuDataChart* imudata);
public:
    ImuDataChart imudata;
protected:
    //file read
    std::string filename;
    //Temp variable
    StringMatrix content;
    char delimiter;
};

#endif // CSVREADER_H
