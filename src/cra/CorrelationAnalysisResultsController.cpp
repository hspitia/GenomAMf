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

#define DEBUG_MODE

#include <utils/Trace.h>

#include "CorrelationAnalysisResultsController.h"

CorrelationAnalysisResultsController::CorrelationAnalysisResultsController()
{
  this->craObject = 0;
}

CorrelationAnalysisResultsController::
CorrelationAnalysisResultsController(const CorrelationAnalysis * craObject)
{
  this->craObject = craObject;
}

CorrelationAnalysisResultsController::
CorrelationAnalysisResultsController(const 
                                     CorrelationAnalysisResultsController &
                                     creResultsControllerObject)
{
  this->craObject = creResultsControllerObject.craObject;
}

CorrelationAnalysisResultsController &
CorrelationAnalysisResultsController::
operator=(const CorrelationAnalysisResultsController & 
          craResultsControllerObject)
{
  this->craObject = craResultsControllerObject.craObject;
  return *this;
}

CorrelationAnalysisResultsController::~CorrelationAnalysisResultsController()
{
  craObject = 0;
}

CorrelationAnalysisResultsForm * 
CorrelationAnalysisResultsController::contructTheResultsForm(QWidget *parent)
{
  QList<QStringList> sequenceContent = prepareContentSequenceTable();
  DistancesModel * model = prepareDistancesModel();
  Tree * tree = craObject->getTree();
  
  CorrelationAnalysisResultsForm * creResultsForm = 
          new CorrelationAnalysisResultsForm(model,
                                             tree,
                                             sequenceContent,
                                             parent);
  
  return creResultsForm;
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
  
  DistancesModel * model = new DistancesModel(sequenceCodeList, distances);
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
  
  int nElements = craObject->getCorrelationElements().count();
  
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
  }
  
  return contentList;
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
