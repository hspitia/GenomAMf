/**
 * @file CorrelationAnalysisResultsController.cpp
 * @date 29/12/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  CorrelationAnalysisResultsController.cpp
 *   Created on:  29/12/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

//#define DEBUG_MODE

#include <utils/Trace.h>

#include "CorrelationAnalysisResultsController.h"

CorrelationAnalysisResultsController::CorrelationAnalysisResultsController()
{
  this->craObject     = 0;
  this->distanceModel = 0;
}

CorrelationAnalysisResultsController::
CorrelationAnalysisResultsController(const CorrelationAnalysis * craObject)
{
  this->craObject     = craObject;
  this->distanceModel = 0;
}

CorrelationAnalysisResultsController::
CorrelationAnalysisResultsController(const 
                                     CorrelationAnalysisResultsController &
                                     craResultsControllerObject)
{
  this->craObject     = craResultsControllerObject.craObject;
  this->distanceModel = craResultsControllerObject.distanceModel;
}

CorrelationAnalysisResultsController &
CorrelationAnalysisResultsController::
operator=(const CorrelationAnalysisResultsController & 
          craResultsControllerObject)
{
  this->craObject     = craResultsControllerObject.craObject;
  this->distanceModel = craResultsControllerObject.distanceModel;
  return *this;
}

CorrelationAnalysisResultsController::~CorrelationAnalysisResultsController()
{
//  if (craObject)
//    craObject = 0;
//  
  if (distanceModel) 
    delete distanceModel;
}

CorrelationAnalysisResultsForm * 
CorrelationAnalysisResultsController::contructTheResultsForm(QWidget *parent)
{
  QList<QStringList> sequenceContent = prepareContentSequenceTable();
//  DistancesModel * model = prepareDistancesModel();
  distanceModel = prepareDistancesModel();
  Tree * tree = craObject->getTree();
  
  CorrelationAnalysisResultsForm * creResultsForm = 
          new CorrelationAnalysisResultsForm(distanceModel,
                                             tree,
                                             sequenceContent,
                                             this,
                                             parent);
  tree = 0;
  return creResultsForm;
}

bool CorrelationAnalysisResultsController::
exportTreeToNewickFormat(const QString & fileName)
{
  try {
    Newick newick;
    Tree * tree = craObject->getTree();
    newick.write(*tree, fileName.toStdString());
  }
  catch (Exception e) {
    return false;
  }
  return true;
}

DistancesModel * CorrelationAnalysisResultsController::prepareDistancesModel()
{
  QList<double> distances = craObject->getDistances();
  QStringList sequenceCodeList;
  int nElements = craObject->getCorrelationElements().count();
  
  for (int i = 0; i < nElements; ++i) {
    QString code = QString("Seq_%1").arg(i + 1);
    sequenceCodeList.append(code);
  }
  
  DistancesModel * model = new DistancesModel(sequenceCodeList,
                                              distances);
  
  return  model;
}

Plotter * CorrelationAnalysisResultsController::plotMuMeasures()
{
  QList<const RowMatrix<int> *> dataList = QList<const RowMatrix<int> *>();
  
  for (int i = 0; i < craObject->getCorrelationElements().count(); ++i) {
    const CorrelationElement * creObject = 
            craObject->getCorrelationElements().at(i);
    dataList.append(creObject->getCgrObject()->getMatrixOfPoints());
  }
  
  Plotter * plotter = new Plotter(dataList, Plotter::Measures_Plot);
  plotter->setTitle("Medidas \\mu");
  plotter->setXLabel("x");
  plotter->setYLabel("y");
  plotter->setZLabel("z");
  return plotter;
} 

QList<QStringList> 
CorrelationAnalysisResultsController::prepareContentSequenceTable()
{
  QList<QStringList > contentList;
  TRACE (__LINE__ << "\n\t" << "Antes de contar los elementos de correlación");
  int nElements = craObject->getCorrelationElements().count();
  TRACE (__LINE__ << "\n\t" << "nElements: " << nElements);
  for (int i = 0; i < nElements; ++i) {
    const CorrelationElement * cre = craObject->getCorrelationElements().at(i);
    const Sequence * sequence = cre->getCgrObject()->getSequence();
    
    int type = 
            utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType());
    
    QString code = QString("Seq_%1").arg(i + 1);
    
    QString name = QString::fromStdString(sequence->getName());
    
    QStringList row;
    
    row << QString::number(type)
        << code
        << name;
    
    contentList << row;
    TRACE (__LINE__ << "\n\t" << "i: " << i);
  }
  
  return contentList;
}

QString CorrelationAnalysisResultsController::getSequenceCodeAndNames()
{
  TRACE (__LINE__ << "\n\t" << "Antes de prepareContentSequenceTable()");
  QList<QStringList> sequenceList = prepareContentSequenceTable();
  TRACE (__LINE__ << "\n\t" << "Despues prepareContentSequenceTable()");
  QString outString;
  QString headers;
  QString separator = ";";
  QString lineFeed = "\n";
  /*headers += QObject::trUtf8("\"No.\"");
  headers += separator;
  headers += QObject::trUtf8("\"Tipo\"");
  headers += separator;
  headers += QObject::trUtf8("\"Código\"");
  headers += separator;
  headers += QObject::trUtf8("\"Secuencia\"");
  headers += lineFeed;
  
  QString rows;
  
  QStringList types;
  types << QObject::trUtf8("\"ADN\"")
        << QObject::trUtf8("\"Proteína\"")
        << QObject::trUtf8("\"No definido\"");
  
  for (int row = 0; row < sequenceList.count(); ++row) {
    QStringList contentRow = sequenceList.at(row);
    rows += QString::number(row + 1); // No.
    rows += separator;

    int type = contentRow.at(0).toInt();
    rows += types.at(type);  // Tipo
    rows += separator;
    rows += "\"" + contentRow.at(1) + "\""; // Código
    rows += separator;
    rows += "\"" + contentRow.at(2) + "\""; // Nombre
    rows += lineFeed;
  }
  
  outString += headers + rows;*/
  return outString;
}

bool CorrelationAnalysisResultsController::
exportDistanceMatrixToCsv(const QString & fileName)
{
  TRACE (__LINE__ << "\n\t" << "Entes de convertDistanceMatrixToCsv()");
  QString outString = convertDistanceMatrixToCsv();
  
  /*QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;
  
  QTextStream out(&file);
  out << outString;*/
  
  return true;
}

QString CorrelationAnalysisResultsController::convertDistanceMatrixToCsv()
{

  int nCols = distanceModel->columnCount();
  int nRows = distanceModel->rowCount();
  
  
  QString informationBlock = getSequenceCodeAndNames();
  TRACE (__LINE__ << "\n\t" << "nCols: " << nCols << " nRows: " << nRows);
  
  QString headers;
  QString outString;
  QString rows;
  QString separator = ";";
  QString lineFeed  = "\n";
  /*
//  QStringList headersList;
//  for (int i = 0; i < nCols; ++i) {
//    headersList << distanceModel->headerData(i, Qt::Horizontal, 
//                                             Qt::DisplayRole).toString();
//    
//    
//  }
  
  for (int i = 0; i < nCols; ++i) {
    headers += QObject::trUtf8("\"") + 
               distanceModel->headerData(i, Qt::Horizontal,
                                         Qt::DisplayRole).toString() + 
               QObject::trUtf8("\"");
    
    if (i < nCols - 1) 
        headers += separator;
  }
  
  cout << qPrintable(headers) << endl;
  */
  /*for (int row = 1; row < nRows; ++row) {
    QStringList contentRow = dqTableContent.at(row);
//    rows += QString("Seq_%1").arg(row + 1);
//    rows += separator;
    rows += "\"" + contentRow.at(0) + "\""; // Código secuencia
    rows += separator;
    for (int j = 1; j < nCols; ++j) {
      rows += contentRow.at(j); // Dq value
      
      if (j < nCols - 1) 
        rows += separator;
    }
    rows += lineFeed;
  }
  headers += lineFeed;
  outString = informationBlock + lineFeed + headers + rows;*/
  
  return outString;
}

const CorrelationAnalysis * CorrelationAnalysisResultsController::getCraObject()
{
  return craObject;
}

void CorrelationAnalysisResultsController::
setCraObject(const CorrelationAnalysis * craObject)
{
  this->craObject = craObject;
}

DistancesModel * CorrelationAnalysisResultsController::getDistanceModel()
{
  return distanceModel;
}
