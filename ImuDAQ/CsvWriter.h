/**
* @file     CsvWriter.h
* @class    CsvWriter
* @brief    this file includes class(CsvWriter) for storing structed data type--Imu
*           Data to a csv file
* @details
* @author   Flame
* @date     03.05.2019
*/

#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <QVector>
#include "ImuData.h"
class CsvWriter
{
public:
    CsvWriter();
    bool toCsv(QString filename,ImuDataChart imudata,std::vector<int> slice,
    std::vector<std::string> slicename,unsigned int length);
};

#endif // CSVWRITER_H
