#ifndef CGRRESULTSFORM_H
#define CGRRESULTSFORM_H
#include <iostream>

using namespace std;


#include <QtGui/QFileDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QImage>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

#include <Seq/Sequence.h>

using namespace bpp;

#include <cgr/ChaosGameRepresentation.h>
#include <gui/ImageViewer.h>
#include "ui_CgrResultsForm.h"

namespace Ui
{
  class CgrResultsFormClass;
}

class CgrResultsForm : public QWidget
{
  Q_OBJECT

  public:
    CgrResultsForm(const ChaosGameRepresentation * cgrObject, QWidget *parent = 0);
    ~CgrResultsForm();

  private:
    Ui::CgrResultsFormClass *ui;
    const ChaosGameRepresentation * ptrCgr;
    ImageViewer * imageViewer;
    QFileDialog * fileDialog;

    void setupComponents();
    void connectSignalsSlots();
    
  private slots:
    void exportImage();
};

#endif // CGRRESULTSFORM_H
