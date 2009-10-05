#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QtGui/QScrollArea>
#include <QtGui/QMessageBox>
#include <QtGui/QImage>
#include <iostream>

using namespace std;


namespace Ui {
    class ImageViewer;
}

class ImageViewer : public QScrollArea
{
  Q_OBJECT
  public:
//    ImageViewer(QWidget * parent = 0);
    ImageViewer(QImage * image = 0, QWidget *parent = 0);
    ~ImageViewer();

    /**
     * 
     */
    void loadImage();
    void loadImage(QImage * image);
    
    /**
     * 
     */
    bool saveImage(const QString & fileName, const QString & format);

  protected:
    void changeEvent(QEvent *e);

  private:
    Ui::ImageViewer *ui;
    QImage * image;
};

#endif // IMAGEVIEWER_H
