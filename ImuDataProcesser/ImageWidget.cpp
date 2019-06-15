#include "ImageWidget.h"

ImageWidget::ImageWidget(QMainWindow *parent)
    : QMainWindow(parent)
{
    imageLabel.setBackgroundRole(QPalette::Base);
    imageLabel.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel.setScaledContents(true);
    setMinimumSize(424, 240);
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    setCentralWidget(&imageLabel);
}

ImageWidget::~ImageWidget()
{

}

void ImageWidget::draw(QImage img)
{
    imageLabel.setPixmap(QPixmap::fromImage(img));
    imageLabel.resize(img.size());
    this->resize(img.size());
}

void ImageWidget::OpenImage(QString fileName)
{
    QString ImageName;
    if(fileName!="None")
        ImageName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "C:/",tr("Images (*.png *.xpm *.jpg)"));
    QImageReader reader(ImageName);
    reader.setAutoTransform(true);
    Image = reader.read();
    if (Image.isNull()) {
             QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                      tr("Cannot load %1: %2")
                                      .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
    }
    imageLabel.setPixmap(QPixmap::fromImage(Image));
    imageLabel.resize(Image.size());
    this->resize(Image.size());
}
