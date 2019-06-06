/**
* @file     ImuDaqDialog.h
* @class    ImuDaqDialog
* @brief    this file includes class(ImuDaqDialog) which is a GUI program to use ImuDAQ to get data.
* @author   Flame
* @date     17.05.2019
*/

#ifndef IMUDAQDIALOG_H
#define IMUDAQDIALOG_H
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QImage>
#include <QDialog>
#include <QCamera>
#include <QFileDialog>
#include <QMessageBox>
#include <QCameraInfo>
#include <QMediaRecorder>
#include "ImuViewFinder.h"
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include "LpSetConfiguration.h"

namespace Ui {
class Dialog;
}

class ImuDaqDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImuDaqDialog(QWidget *parent = nullptr);
    bool CmdProcess(int i);
    ~ImuDaqDialog();
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);
    void moveEvent(QMoveEvent *event);
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_PeriodlineEdit_editingFinished();
    void on_NamelineEdit_editingFinished();
    void on_FilenumlineEdit_editingFinished();
    void on_SamplelineEdit_editingFinished();
    void on_StartsendpushButton_clicked();
    void on_ResetpushButton_clicked();
    void on_SyncpushButton_clicked();
    void on_ActivepushButton_clicked();
    void on_ShowImagepushButton_clicked();
    void saveImage(QString time);
    void stopSave(QString time);
    void on_SubjectlineEdit_editingFinished();
    void on_SelectpushButton_clicked();
    void on_StoppushButton_clicked();
    void on_ConnectpushButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void deleteme(QString id);
private:
    int Rate;
    int period;
    int filenum;
    QString rootDir;
    bool timeshow;
    std::string filename;
    QString subject;
    QVector<double> timeseries;
    QString address;
    ImuViewFinder viewFinder;
    RECT mainRect;
    bool limit;
    IMUDAQ_Task* IMUDAQ;
    LpmsSensorI* lpmsRightFoot;
    LpmsSensorI* lpmsRightThigh;
    LpmsSensorI* lpmsLeftFoot;
    LpmsSensorI* lpmsLeftThigh;
    LpmsSensorManagerI* manager;
    std::vector<LpmsSensorI*> Lpms;
    Ui::Dialog *ui;
};

#endif // IMUDAQDIALOG_H
