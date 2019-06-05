#include "ImuVideoSurface.h"

ImuVideoSurface::ImuVideoSurface(QWidget *widget, QObject *parent)
    : QAbstractVideoSurface(parent)
    , viewFinder(widget)
    , imageFormat(QImage::Format_Invalid)
{
    record = false;
}

QList<QVideoFrame::PixelFormat> ImuVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()<< QVideoFrame::Format_RGB32<< QVideoFrame::Format_ARGB32<< QVideoFrame::Format_ARGB32_Premultiplied<< QVideoFrame::Format_RGB565<< QVideoFrame::Format_RGB555;
    } else {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool ImuVideoSurface::isFormatSupported(const QVideoSurfaceFormat & format) const
{
    return QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat()) != QImage::Format_Invalid && !format.frameSize().isEmpty() && format.handleType() == QAbstractVideoBuffer::NoHandle;
}

bool ImuVideoSurface::start(const QVideoSurfaceFormat &format)
{
    const QImage::Format imageFormatTemp = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();
    if (imageFormatTemp != QImage::Format_Invalid && !size.isEmpty()) {
        this->imageFormat = imageFormatTemp;
        viewFinder->resize(size);
        QAbstractVideoSurface::start(format);
        viewFinder->updateGeometry();
        updateVideoRect();
        return true;
    }
    return false;
}

void ImuVideoSurface::stop()
{
    videoFrame = QVideoFrame();
    targetRect = QRect();
    QAbstractVideoSurface::stop();
    viewFinder->update();
}

bool ImuVideoSurface::present(const QVideoFrame &frame) //每一帧摄像头的数据，都会经过这里
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat() || surfaceFormat().frameSize() != frame.size()) {
        setError(IncorrectFormatError);
        stop();
        return false;
    }
    videoFrame = frame;
    viewFinder->repaint(targetRect);
    return true;
}

QRect ImuVideoSurface::videoRect() const
{
    return targetRect;
}
void ImuVideoSurface::recoder(QString address)
{
    this->address = address;
    record = true;
}
void ImuVideoSurface::over()
{
    record = false;
}
void ImuVideoSurface::updateVideoRect()
{
    QSize size = surfaceFormat().sizeHint();
    size.scale(viewFinder->size().boundedTo(size), Qt::KeepAspectRatio);
    targetRect = QRect(QPoint(0, 0), size);
    targetRect.moveCenter(viewFinder->rect().center());
}

void ImuVideoSurface::paint(QPainter *painter,QString filename)
{
    if (videoFrame.map(QAbstractVideoBuffer::ReadOnly)) {
        QImage img = QImage(videoFrame.bits(),videoFrame.width(),videoFrame.height(),videoFrame.bytesPerLine(),imageFormat).mirrored(true,true).scaled(viewFinder->size());
        if(record){
            if(filename=="None")
                img.save(address+QString::number(QTime::currentTime().msecsSinceStartOfDay())+".jpg");
            if(filename!="None") img.save(filename);
        }
        painter->drawImage(targetRect, img, QRect(QPoint(0,0),img.size()));
        videoFrame.unmap();
    }
}
bool ImuVideoSurface::getstate()
{
    return record;
}
ImuVideoSurface::~ImuVideoSurface()
{

}
