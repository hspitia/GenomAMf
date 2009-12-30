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

#include "CorrelationAnalysisResultsController.h"

CorrelationAnalysisResultsController::CorrelationAnalysisResultsController()
{
  

}

CorrelationAnalysisResultsController::
CorrelationAnalysisResultsController(const CorrelationAnalysis & craObject)
{
  
}

CorrelationAnalysisResultsController::
CorrelationAnalysisResultsController(const 
                                     CorrelationAnalysisResultsController &
                                     creResultsControllerObject)
{
  
}

CorrelationAnalysisResultsController &
CorrelationAnalysisResultsController::
operator=(const CorrelationAnalysisResultsController & 
          craResultsControllerObject)
          
{
  
}

CorrelationAnalysisResultsController::~CorrelationAnalysisResultsController()
{
  // TODO Auto-generated destructor stub
}

QList<RowMatrix<int> *> CorrelationAnalysisResultsController::plotMuMeasures()
{
  QList<RowMatrix<int> *> list;
  return list;
} 


QList<QStringList> 
CorrelationAnalysisResultsController::prepareContentSequenceTable()
{
  QList<QStringList > contentList;
  QStringList row;
  int nElements = craObject->getCorrelationElements().count();
  
  for (int i = 0; i < nElements; ++i) {
    const CorrelationElement * cre = craObject->getCorrelationElements().at(i);
    const Sequence * sequence = cre->getCgrObject()->getSequence();
    
    int type = 
            utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType());
    
    QString code = QString("Seq_%1").arg(i + 1);
    
    QString name = QString::fromStdString(sequence->getName());
    
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
