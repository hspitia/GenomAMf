#include "CgrResultsForm.h"

CgrResultsForm::CgrResultsForm(const ChaosGameRepresentation * cgrObject, 
                               QWidget *parent)
    : QWidget(parent), ui(new Ui::CgrResultsFormClass)
{
  this->imageViewer = 0;
  this->ptrCgr = cgrObject;
  this->fileDialog = new QFileDialog(this);
  setupComponents();
  connectSignalsSlots();
  
}

CgrResultsForm::~CgrResultsForm()
{
  delete ui;
  ptrCgr = 0;
  delete ptrCgr;
  delete imageViewer;
  delete fileDialog;
}

void CgrResultsForm::exportImage()
{
  QString filename = QString::fromStdString(CgrResultsForm::ptrCgr->
                                            getSequence()->getName());
  filename += ".png";
  
  QStringList formats;
  formats << "PNG" << "JPG" << "BMP" << "TIFF"; 
  
  QStringList filters;
  filters << "Imagen PNG (*.png)";
  filters << "Imagen JPEG (*.jpg)";
  filters << "Imagen BMP (*.bmp)";
  filters << "Imagen TIFF (*.tif)";
  
  fileDialog->setNameFilters(filters);
  fileDialog->setAcceptMode(QFileDialog::AcceptSave);
  fileDialog->setDirectory(".");
  fileDialog->selectFile(filename);
  fileDialog->setDefaultSuffix("png");
  
  if(fileDialog->exec()){
    QStringList list = fileDialog->selectedFiles();
    if(!list.isEmpty()){
      filename = list.at(0);
      
      QString format = "";
      for (int i = 0; i < filters.count(); ++i)
      {
        if(fileDialog->selectedFilter().compare(filters.at(i)) == 0){
          format = formats.at(i);
          break;
        }
      }
      
      if(!imageViewer->saveImage(filename, format)){
        QMessageBox::information(this,"Error",QString::fromUtf8("Ocurrió un "
                "error mientras se trataba de guardar la imagen.\n "
                "Verifique los permisos del directorio destino e intente "
                "guardar la imagen nuevamente."),
                QMessageBox::Ok);
      }
      
    }
  }
  
}

void CgrResultsForm::setupComponents(){
  ui->setupUi(this);
  
  QPushButton * exportButton = new QPushButton(tr("&Exportar"));
  exportButton->setIcon(QIcon(":/icons/cgr_save.png"));
  ui->buttonBox->addButton(exportButton, QDialogButtonBox::AcceptRole);
  ui->buttonBox->addButton(QDialogButtonBox::Close);
  QString file = QString::fromStdString(ptrCgr->getImageFilePath());
  QImage * image = new QImage(file);
  imageViewer = new ImageViewer(image, this);
  QGridLayout * layout = new QGridLayout();
  layout->addWidget(imageViewer,0,0);
  layout->addWidget(ui->buttonBox,0,1);
  
  setLayout(layout);
}

void CgrResultsForm::connectSignalsSlots()
{
  connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(exportImage()));
  connect(ui->buttonBox, SIGNAL(rejected()), this->parent(),
            SLOT(closeSubWindow()));
}
