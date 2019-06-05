#include "ImuViewFinder.h"
#include "ui_ImuViewFinder.h"

ImuViewFinder::ImuViewFinder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImuViewFinder)
{
    ui->setupUi(this);
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
      foreach (const QCameraInfo &cameraInfo, cameras)
          qDebug() << "Camera: " <<cameraInfo.deviceName();
    this->setWindowTitle("Camera");
    camera = new QCamera(cameras.last());
    surface = new ImuVideoSurface(this);
    camera->setViewfinder(surface);
    camera->start();
}

ImuViewFinder::~ImuViewFinder()
{
    camera->stop();
    delete surface;
    delete camera;
    delete ui;
}

QSize ImuViewFinder::sizeHint() const
{
    return surface->surfaceFormat().sizeHint();
}

void ImuViewFinder::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (surface->isActive()) {
        const QRect videoRect = surface->videoRect();
        if (!videoRect.contains(event->rect())) {
            QRegion region = event->region();
            region = region.subtracted(videoRect);
            QBrush brush = palette().background();
            for (const QRect &rect : region){
                painter.fillRect(rect, brush);
            }
        }
        surface->paint(&painter);
    } else {
        painter.fillRect(event->rect(), palette().background());
    }
}

void ImuViewFinder::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    surface->updateVideoRect();
}

void ImuViewFinder::capture(QString address)
{
    surface->recoder(address);
}
void ImuViewFinder::stop()
{
    surface->over();
}
bool ImuViewFinder::getstate()
{
    return surface->getstate();
}
void ImuViewFinder::init()
{
    QList<QSize> sizes = camera->supportedViewfinderResolutions();
    qDebug() << "viewfinderResolutions sizes.len = " << sizes.length();
    foreach (QSize size, sizes) {
        qDebug() << "Resolutions size = " << size;
    }
    QList<QCamera::FrameRateRange> rates = camera->supportedViewfinderFrameRateRanges();
    qDebug() << "FrameRateRange sizes.len = " << rates.length();
    foreach (QCamera::FrameRateRange rate, rates) {
        qDebug() << "FrameRateRange = (" << rate.maximumFrameRate <<","<< rate.minimumFrameRate <<")";
    }
    QCameraViewfinderSettings viewfinderSettings;
    viewfinderSettings.setResolution(424, 240);
    viewfinderSettings.setMinimumFrameRate(15);
    viewfinderSettings.setMaximumFrameRate(30);
    //viewfinderSettings.setMinimumFrameRate(60);
    //viewfinderSettings.setMaximumFrameRate(120);
    camera->setViewfinderSettings(viewfinderSettings);
}
