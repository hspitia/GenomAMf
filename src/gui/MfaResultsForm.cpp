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

//#define DEBUG_MODE

#include "MfaResultsForm.h"
#include "utils/Trace.h"

MfaResultsForm::MfaResultsForm(const QList<QStringList> & dqTableContent,
                               const QList<QStringList> & sequenceList,
                               QWidget *parent) :
  QWidget(parent), ui(new Ui::MfaResultsForm)
{
  this->dqTableContent = dqTableContent;
  this->sequenceList = sequenceList;
  ui->setupUi(this);
  setupGraphicWidgets();
  connectSignalsSlots();
}

MfaResultsForm::~MfaResultsForm()
{
  delete ui;
}

void MfaResultsForm::connectSignalsSlots()
{
  connect(ui->buttonBox, SIGNAL(rejected()), this, 
          SLOT(close()));
  
  connect(ui->exportDqValuesButton, SIGNAL(released()), this, 
          SLOT(exportDqValuesTableToCsv()));
  
  
}

void MfaResultsForm::setupGraphicWidgets()
{
  dqGraphicWidget = new QMathGL(this);
  dqGraphicWidget->autoResize = true;
  ui->dqScrollArea->setWidget(dqGraphicWidget);
  
  cqGraphicWidget = new QMathGL(this);
  cqGraphicWidget->autoResize = true;
  ui->cqScrollArea->setWidget(cqGraphicWidget);
  
  linearRegressionGraphicWidget = new QMathGL(this);
  linearRegressionGraphicWidget->autoResize = true;
  ui->linearRegressionScrollArea->setWidget(linearRegressionGraphicWidget);
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
  linearRegressionGraphicWidget->setDraw(plotter);
  linearRegressionGraphicWidget->update();
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
  
}

void MfaResultsForm::exportImage()
{
  
}

void MfaResultsForm::exportDqValuesTableToCsv()
{
  QString fileName = "DqValues";
  QStringList filters;
  filters << "Comma separated values (*.csv)";
  
  QFileDialog * fileDialog = new QFileDialog(this);
  fileDialog->setNameFilters(filters);
  fileDialog->setAcceptMode(QFileDialog::AcceptSave);
  fileDialog->setDirectory(".");
  fileDialog->selectFile(fileName);
  fileDialog->setDefaultSuffix("csv");
  
  if(fileDialog->exec()){
    QStringList list = fileDialog->selectedFiles();
    if(!list.isEmpty()){
      fileName = list.at(0);
      
      bool succes = prepareAndExportDqValues(fileName);
      if (!succes)
        QMessageBox::critical(this, "GenomAMf - Error", 
                              QString::fromUtf8("Ha ocurrido un error al "
                                      "tratar de guardar el archivo:\n %1\n\n"
                                      "Verifique los permisos del directorio "
                                      "destino e intente guardar el archivo"
                                      "nuevamente.").arg(fileName),
                                      QMessageBox::Ok);
    }
  }
  delete fileDialog;
}

bool MfaResultsForm::prepareAndExportDqValues(const QString & fileName)
{
  int nCols = dqTableContent.at(0).count();
  int nRows = dqTableContent.count();
  
  QString informationBlock = getSequenceCodeAndNames();
  
  QString headers;
  QString outString;
  QString rows;
  QString separator = ";";
  QString lineFeed  = "\n";
  headers += "q";
  headers += separator;
  
  for (int i = 1; i < nCols; ++i) {
    headers += QString::fromUtf8("Dq Seq_%1").arg(i);
    if (i < nCols - 1) 
        headers += separator;
  }
  
  for (int row = 0; row < nRows; ++row) {
    QStringList contentRow = dqTableContent.at(row);
    rows += contentRow.at(0); // q value
    rows += separator;
    for (int j = 1; j < nCols; ++j) {
      rows += contentRow.at(j); // Dq value
      
      if (j < nCols - 1) 
        rows += separator;
    }
    rows += lineFeed;
  }
  headers += lineFeed;
  outString = informationBlock + lineFeed + headers + rows;
  
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;
  
  QTextStream out(&file);
  out << outString;
  
  return true;
}

QString MfaResultsForm::getSequenceCodeAndNames()
{
  QTableWidget * table =  ui->sequenceTable;
  table->setColumnCount(2);
  table->setRowCount(sequenceList.count()); 
  QString outString;
  QString headers;
  QString separator = ";";
  QString lineFeed = "\n";
  headers += QString::fromUtf8("No.");
  headers += separator;
  headers += QString::fromUtf8("Tipo");
  headers += separator;
  headers += QString::fromUtf8("Código");
  headers += separator;
  headers += QString::fromUtf8("Secuencia");
  headers += lineFeed;
  
  QString rows;
  
  QStringList types;
  types << QString::fromUtf8("ADN")
        << QString::fromUtf8("Proteína")
        << QString::fromUtf8("No definido");
  
  for (int row = 0; row < sequenceList.count(); ++row) {
    QStringList contentRow = sequenceList.at(row);
    rows += QString::number(row + 1); // No.
    rows += separator;

    int type = contentRow.at(0).toInt();
    rows += types.at(type);  // Tipo
    rows += separator;
    rows += contentRow.at(1); // Código
    rows += separator;
    rows += contentRow.at(2); // Nombre
    rows += lineFeed;
  }
  
  outString += headers + rows;
  return outString;
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
  this->linearRegressionGraphicWidget = linearRegressionGraphicWidget;
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
