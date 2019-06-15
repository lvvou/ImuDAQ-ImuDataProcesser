#ifndef IMUVIEWFINDER_H
#define IMUVIEWFINDER_H

#include <QTime>
#include <QList>
#include <QCamera>
#include <QtWidgets>
#include <QCameraFocus>
#include <QMainWindow>
#include <QCameraInfo>
#include "ImuVideoSurface.h"
#include "qvideosurfaceformat.h"

namespace Ui {
class ImuViewFinder;
}

class ImuViewFinder : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImuViewFinder(QWidget *parent = nullptr);
    ~ImuViewFinder() override;
    QSize sizeHint() const override;
    void capture(QString address);
    void stop();
    void init();
    bool getstate();
    QCamera * camera;
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ImuViewFinder *ui;
    ImuVideoSurface * surface;

};

#endif // IMUVIEWFINDER_H
