/**
* @file     ImageWidget.h
* @class    ImageWidget
* @brief    this file includes class(ImageWidget) which has the function used to show image get from Camera
* @details
* @author   Flame
* @date     03.05.2019
*/

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QMainWindow>
#include <QImageReader>
#include <QGuiApplication>

class ImageWidget : public QMainWindow
{
    Q_OBJECT

public:
    ImageWidget(QMainWindow *parent = nullptr);
    ~ImageWidget();
    void OpenImage(QString fileName="None");
    void draw(QImage img);
    QImage Image;
    QLabel imageLabel;
};

#endif // IMAGEWIDGET_H
