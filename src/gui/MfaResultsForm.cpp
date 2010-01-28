/**
 * @file MainWindow.cpp
 * @date 6/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de definiciones para la clase MfaResultsForm
 */

/* 
 *         File:  MfaResultsForm.cpp
 *   Created on:  6/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE
 *                ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de implementacio-.n para la clase MfaResultsForm
 */

#define DEBUG_MODE

#include "MfaResultsForm.h"
#include "utils/Trace.h"

MfaResultsForm::MfaResultsForm(const QList<QStringList> & dqTableContent,
                               const QList<QStringList> & sequenceList,
                               MfaResultsController * parentController,
                               QWidget *parent) :
  QWidget(parent), ui(new Ui::MfaResultsForm)
{
  this->dqTableContent = dqTableContent;
  this->sequenceList = sequenceList;
  this->parentController = parentController;
  ui->setupUi(this);
  setupGraphicWidgets();
  connectSignalsSlots();
  setAttribute(Qt::WA_DeleteOnClose);
}

MfaResultsForm::~MfaResultsForm()
{
  delete ui;
}

void MfaResultsForm::connectSignalsSlots()
{
  QSignalMapper * signalMapper = new QSignalMapper(this);
  signalMapper->setMapping(ui->exportDqPlotPushButton, Plotter::Dq_Plot);
  signalMapper->setMapping(ui->exportCqPlotPushButton, Plotter::Cq_Plot);
//  signalMapper->setMapping(ui->exportLinearPlotPushButton, Plotter::Linear_Plot);
  
  connect(ui->exportDqPlotPushButton, SIGNAL(clicked()),
          signalMapper, SLOT (map()));
  connect(ui->exportCqPlotPushButton, SIGNAL(clicked()),
          signalMapper, SLOT (map()));
//  connect(ui->exportLinearPlotPushButton, SIGNAL(clicked()),
//          signalMapper, SLOT (map()));
  
  connect(signalMapper, SIGNAL(mapped(int /*plotType*/)),
         this, SLOT(exportImage(int /*plotType*/)));
  
  connect(ui->buttonBox, SIGNAL(rejected()), this->parent(),
            SLOT(closeSubWindow()));
  
  connect(ui->exportDqValuesButton, SIGNAL(released()), this, 
          SLOT(exportDqValuesTableToCsv()));
  
  
}

void MfaResultsForm::setupGraphicWidgets()
{
  dqGraphicWidget = new QMathGL(this);
  dqGraphicWidget->autoResize = true;
  dqGraphicWidget->setSize(609, 432);
  ui->dqScrollArea->setWidget(dqGraphicWidget);
  
  cqGraphicWidget = new QMathGL(this);
  cqGraphicWidget->autoResize = true;
  cqGraphicWidget->setSize(609, 432);
  ui->cqScrollArea->setWidget(cqGraphicWidget);
  
//  linearRegressionGraphicWidget = new QMathGL(this);
//  linearRegressionGraphicWidget->autoResize = true;
//  ui->linearRegressionScrollArea->setWidget(linearRegressionGraphicWidget);
}

void MfaResultsForm::setupPlotWidgets()
{
  dqGraphicWidget = new QMathGL(this);
  dqGraphicWidget->autoResize = true;
  dqGraphicWidget->setSize(609, 432);
  ui->dqScrollArea->setWidget(dqGraphicWidget);
  
  cqGraphicWidget = new QMathGL(this);
  cqGraphicWidget->autoResize = true;
  cqGraphicWidget->setSize(609, 432);
  ui->cqScrollArea->setWidget(cqGraphicWidget);
  
//  linearRegressionGraphicWidget = new QMathGL(this);
//  linearRegressionGraphicWidget->autoResize = true;
//  ui->linearRegressionScrollArea->setWidget(linearRegressionGraphicWidget);
}

void MfaResultsForm::setUpDqGraphic(Plotter * plotter)
{
  dqGraphicWidget->setDraw(plotter);
  dqGraphicWidget->update();
}

void MfaResultsForm::setUpCqGraphic(Plotter * plotter)
{
  cqGraphicWidget->setDraw(plotter);
  cqGraphicWidget->update();
}

void MfaResultsForm::setUpLinearRegressionGraphic(Plotter * plotter)
{
  Q_UNUSED(plotter);
//  linearRegressionGraphicWidget->setDraw(plotter);
//  linearRegressionGraphicWidget->update();
}

void MfaResultsForm::setUpDqPlot(NormalPlot * dqPlot)
{
  dqPlotWidget->setDraw(plotter);
  dqPlotWidget->update();
}

void MfaResultsForm::setUpCqPlot(NormalPlot * cqPlot)
{
  cqPlotWidget->setDraw(plotter);
  cqPlotWidget->update();
}

void 
MfaResultsForm::setUpLinearRegressionPlot(QList<LinearPlot *> linearPlotList)
{
  Q_UNUSED(linearPlotList);
//  linearRegressionPlotWidget->setDraw(plotter);
//  linearRegressionPlotWidget->update();
}


void MfaResultsForm::setUpSequenceTable()
{
  QTableWidget * table =  ui->sequenceTable;
  table->setColumnCount(2);
  table->setRowCount(sequenceList.count()); 
  QStringList headers;
  headers << QString::fromUtf8("Código")
          << QString::fromUtf8("Secuencia");
  
  table->setHorizontalHeaderLabels(headers);
  
  for (int row = 0; row < sequenceList.count(); ++row) {
    QStringList contentRow = sequenceList.at(row);
    QTableWidgetItem * codeItem = new QTableWidgetItem(contentRow.at(1));
    QTableWidgetItem * nameItem = new QTableWidgetItem(contentRow.at(2));
    table->setItem(row, 0, codeItem);
    table->setItem(row, 1, nameItem);
    
    int type = contentRow.at(0).toInt();
    int iconType = TreeItem::DnaSequenceItem; 
            
    if (type == GenomAMf::Proteic_Alphabet) 
      iconType = TreeItem::ProteinSequenceItem;
    
      table->item(row, 1)->setIcon(getIcon(iconType));
  }
  
}

void MfaResultsForm::setUpDqValuesTable(/*const QList<QStringList> & contentList*/)
{
  QTableWidget * table =  ui->dqValuesTable;
  int nCols = dqTableContent.at(0).count();
  int nRows = dqTableContent.count();
  table->setColumnCount(nCols);
  table->setRowCount(nRows - 1); 
  
  QStringList headers = dqTableContent.at(0);
    
  for (int row = 0; row < nRows - 1; ++row) {
    QStringList contentRow = dqTableContent.at(row + 1);
    QTableWidgetItem * qItem = new QTableWidgetItem(contentRow.at(0));
    table->setItem(row, 0, qItem);

    for (int j = 0; j < nCols; ++j) {
      QTableWidgetItem * dqValueItem = new QTableWidgetItem(contentRow.at(j));
      table->setItem(row, j, dqValueItem);
//      headers << QString::fromUtf8("Dq Seq_%1").arg(j);
    }
  }
  table->setHorizontalHeaderLabels(headers);
  
}

/*void MfaResultsForm::setUpDqValuesTable(const QList<QStringList> & contentList)
{
  QTableWidget * table =  ui->dqValuesTable;
  int nCols = dqTableContent.at(0).count();
  int nRows = dqTableContent.count();
  table->setColumnCount(nCols);
  table->setRowCount(nRows); 
  
  QStringList headers;
  headers << QString::fromUtf8("q");
  
  for (int row = 0; row < nRows; ++row) {
    QStringList contentRow = dqTableContent.at(row);
    QTableWidgetItem * qItem = new QTableWidgetItem(contentRow.at(0));
    table->setItem(row, 0, qItem);

    for (int j = 1; j < nCols; ++j) {
      QTableWidgetItem * dqValueItem = new QTableWidgetItem(contentRow.at(j));
      table->setItem(row, j, dqValueItem);
      headers << QString::fromUtf8("Dq Seq_%1").arg(j);
    }
  }
  table->setHorizontalHeaderLabels(headers);
  
}*/

void MfaResultsForm::exportImage(int plotType)
{
  
//  int tabIndex = ui->resultsTabWidget->currentIndex();
  
  QMathGL * currentGraphicWidget = 0;
  QString filename = "Grafico";
   
  switch (plotType) {
    case Plotter::Dq_Plot:
      currentGraphicWidget = dqGraphicWidget;
      filename = trUtf8("espectro_Dq");
      break;
      
    case Plotter::Cq_Plot:
      currentGraphicWidget = cqGraphicWidget;
      filename = trUtf8("calor_especifico_analogo_Cq");
      break;
    
    case Plotter::Linear_Plot:
      currentGraphicWidget = linearRegressionGraphicWidget;
      filename = trUtf8("regresión_lineal");
      break;
    
    default:
      return;
  }
  
  QStringList formats;
  formats << "png" << "jpg" << "eps" << "svg"; 
  
  QStringList filters;
  filters << "Imagen PNG (*.png)";
  filters << "Imagen JPEG (*.jpg)";
  filters << "Imagen EPS (*.eps)";
  filters << "Imagen SVG (*.svg)";
  
  QFileDialog * fileDialog = new QFileDialog(this);
  fileDialog->setNameFilters(filters);
  fileDialog->setAcceptMode(QFileDialog::AcceptSave);
  fileDialog->setDirectory(QDir::homePath());
  fileDialog->selectFile(filename);
//  fileDialog->setDefaultSuffix("png");
  
  if(fileDialog->exec()){
    QStringList list = fileDialog->selectedFiles();
    if(!list.isEmpty()){
      filename = list.at(0);
      
//      QString formatExtension = "";
      int format = 0;
      for (int i = 0; i < filters.count(); ++i) {
        if (fileDialog->selectedFilter().compare(filters.at(i)) == 0) {
//          formatExtension = formats.at(i);
          format = i;
          break;
        }
      }
      
      QStringList tokens = filename.split(".", QString::SkipEmptyParts);
      QString tmpName = "";
      int limit = tokens.count() - 1;
      
      if (limit > 0) {
        for (int i = 0; i < limit; ++i) {
          tmpName += tokens.at(i);
          if (i != limit - 1)
            tmpName += "_";
        }
        filename = tmpName;
      }
      
      switch (format) {
        case 0:
          currentGraphicWidget->exportPNG(filename);
          break;
        
        case 1:
          currentGraphicWidget->exportJPG(filename);
          break;
        
        case 2:
          currentGraphicWidget->exportBPS(filename);
          break;
        
        case 3:
          currentGraphicWidget->exportSVG(filename);
          break;
          
        default:
          return;
      }
      
      /*if(!false){
        QMessageBox::information(this,"Error",QString::fromUtf8("Ocurrió un "
                "error mientras se trataba de guardar la imagen.\n "
                "Verifique los permisos del directorio destino e intente "
                "guardar la imagen nuevamente."),
                QMessageBox::Ok);
      }*/
      currentGraphicWidget = 0;
    }
  }
  
}

void MfaResultsForm::exportDqValuesTableToCsv()
{
  QString fileName = trUtf8("DqValues");
  QStringList filters;
  filters << trUtf8("Comma separated values (*.csv)");
  
  QFileDialog * fileDialog = new QFileDialog(this);
  fileDialog->setNameFilters(filters);
  fileDialog->setAcceptMode(QFileDialog::AcceptSave);
  fileDialog->setDirectory(QDir::homePath());
  fileDialog->selectFile(fileName);
  fileDialog->setDefaultSuffix("csv");
  
  if(fileDialog->exec()){
    QStringList list = fileDialog->selectedFiles();
    if(!list.isEmpty()){
      fileName = list.at(0);
      
      bool succes = parentController->exportDqValuesToCsv(fileName);
      if (!succes)
        QMessageBox::critical(this, trUtf8("GenomAMf - Error"), 
                              trUtf8("Ha ocurrido un error al "
                                      "tratar de guardar el archivo:\n %1\n\n"
                                      "Verifique los permisos del directorio "
                                      "destino e intente guardar el archivo"
                                      "nuevamente.").arg(fileName),
                                      QMessageBox::Ok);
    }
  }
  delete fileDialog;
}

Ui::MfaResultsForm * MfaResultsForm::getUi()
{
  return ui;
}

QMathGL * MfaResultsForm::getDqGraphicWidget()
{
  return dqGraphicWidget;
}

void MfaResultsForm::setDqGraphicWidget(QMathGL * dqGraphicWidget)
{
  this->dqGraphicWidget = dqGraphicWidget;
}

QMathGL * MfaResultsForm::getCqGraphicWidget()
{
  return cqGraphicWidget;
}

void MfaResultsForm::setCqGraphicWidget(QMathGL * cqGraphicWidget)
{
  this->cqGraphicWidget = cqGraphicWidget;
}


QMathGL * MfaResultsForm::getLinearRegressionGraphicWidget()
{
  return linearRegressionGraphicWidget;
}

void MfaResultsForm::setLinearRegressionGraphicWidget(QMathGL * 
                                                 linearRegressionGraphicWidget)
{
  Q_UNUSED(linearRegressionGraphicWidget);
//  this->linearRegressionGraphicWidget = linearRegressionGraphicWidget;
//  this->linearRegressionGraphicWidget->setVisible(false);
//  ui->linearRegressionScrollArea->setVisible(false);
//  ui->exportLinearPlotPushButton->setVisible(false);
//  ui->regressionTab->setVisible(false);
}

QIcon MfaResultsForm::getIcon(const int & type) const
{
  QIcon icon;
  if(type == TreeItem::DnaSequenceItem)
    icon = QIcon(":/icons/seq_dna.png");
  else if(type == TreeItem::ProteinSequenceItem)
    icon = QIcon(":/icons/seq_protein.png");
  else if(type == TreeItem::CgrItem)
    icon = QIcon(":/icons/cgr.png");
  return icon;
}


MfaResultsController * MfaResultsForm::getParentController()
{
  return parentController;
}

NormalPlot * MfaResultsForm::getDqPlotWidget()
{
  return dqPlotWidget;
}

void MfaResultsForm::setDqPlotWidget(NormalPlot * dqPlotWidget)
{
  this->dqPlotWidget = dqPlotWidget;
}

NormalPlot * MfaResultsForm::getCqPlotWidget()
{
  return cqPlotWidget;
}

void MfaResultsForm::setCqPlotWidget(NormalPlot * cqPlotWidget)
{
  this->cqPlotWidget = cqPlotWidget;
}

QList<LinearPlot *> MfaResultsForm::getLinearPlotWidgetList()
{
  return linearPlotWidgetList;
}

void MfaResultsForm::setLinearPlotWidgetList(QList<LinearPlot *> linearPlotWidgetList)
{
  this->linearPlotWidgetList = linearPlotWidgetList;
}

QFrame * MfaResultsForm::getlinearPlotFrame()
{
  return linearPlotFrame;
}

void MfaResultsForm::setlinearPlotFrame(QFrame * linearPlotFrame)
{
  this->linearPlotFrame = linearPlotFrame;
}
