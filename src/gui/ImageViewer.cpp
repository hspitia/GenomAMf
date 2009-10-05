#include "ImageViewer.h"
#include "ui_ImageViewer.h"

ImageViewer::ImageViewer(QImage * image, QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::ImageViewer)
{
  this->image = image;
  ui->setupUi(this);
  loadImage();
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::loadImage()
{
  if (image != 0) {
//    QMessageBox::information(this, tr("Image Viewer"),
//                             tr("Cannot load the cgr image"));
    
    ui->imageLabel->setPixmap(QPixmap::fromImage(*image));
//    ui->imageLabel->setPixmap(ui->imageLabel->pixmap()->scaledToWidth(384,Qt::SmoothTransformation));
//    ui->imageLabel->adjustSize();
//    ui->imageLabel->
//    return;
  }
}

void ImageViewer::loadImage(QImage * newImage)
{
  if (newImage != 0) image = newImage;
  if (image != 0) {
    QPixmap pixmap = QPixmap::fromImage(*image);
    ui->imageLabel->setPixmap(pixmap);
    
  }
}

bool ImageViewer::saveImage(const QString & fileName, const QString & format)
{
  return image->save(fileName, format.toAscii().data(), 100);
}

void ImageViewer::changeEvent(QEvent *e)
{
    QScrollArea::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
