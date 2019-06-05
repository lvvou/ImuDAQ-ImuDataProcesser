#ifndef MYVIDEOSURFACE_H
#define MYVIDEOSURFACE_H
#include <QTime>
#include <QImage>
#include <QRect>
#include <QtWidgets>
#include <QVideoFrame>
#include <QVideoSurfaceFormat>
#include <qvideosurfaceformat.h>
#include <QAbstractVideoSurface>

class ImuVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    ImuVideoSurface(QWidget *widget, QObject *parent = nullptr);
    ~ImuVideoSurface() override;
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override;
    bool isFormatSupported(const QVideoSurfaceFormat &format) const override;
    bool start(const QVideoSurfaceFormat &format) override;
    bool present(const QVideoFrame &frame) override;
    void stop() override;
    QRect videoRect() const;
    void updateVideoRect();
    void paint(QPainter *painter, QString filename="None");
    void recoder(QString address);
    void over();
    bool getstate();
private:
    QString address;
    bool record;
    QWidget       *viewFinder;
    QImage::Format imageFormat;
    QRect          targetRect;
    QSize          imageSize;
    QVideoFrame    videoFrame;
};

#endif
