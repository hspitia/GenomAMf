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

MfaResultsForm::MfaResultsForm(QWidget *parent) :
  QWidget(parent), ui(new Ui::MfaResultsForm)
{
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
  
  connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(exportImage()));
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

void MfaResultsForm::setUpSequenceTable(const QList<QStringList> & contentList)
{
  QTableWidget * table =  ui->sequenceList;
  table->setColumnCount(2);
  table->setRowCount(contentList.count()); 
  QStringList headers;
  headers << QString::fromUtf8("Código")
          << QString::fromUtf8("Secuencia");
  
  table->setHorizontalHeaderLabels(headers);
  
  for (int row = 0; row < contentList.count(); ++row) {
    QStringList contentRow = contentList.at(row);
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

void MfaResultsForm::exportImage()
{
  
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
