/**
 * @file MfaResultsController.cpp
 * @date 13/11/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MfaResultsController.cpp
 *   Created on:  13/11/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#define DEBUG_MODE
 
#include "MfaResultsController.h"

#include "utils/Trace.h"


MfaResultsController::MfaResultsController()
{
//  this->mfaObjects     = QList<MultifractalAnalysis *>();
  this->mfaObjects     = QList<MultifractalAnalysis>();
  this->mfaResultsForm = 0;
}

//MfaResultsController::MfaResultsController(const QList<MultifractalAnalysis * > & 
MfaResultsController::MfaResultsController(const QList<MultifractalAnalysis> & 
                                           mfaObjects)
{
  this->mfaObjects     = mfaObjects;//QList<MultifractalAnalysis *>(mfaObjects);
  this->mfaResultsForm = 0;
}

MfaResultsController::~MfaResultsController()
{
  if (mfaResultsForm != 0)
    mfaResultsForm = 0;
  
  delete mfaResultsForm;
}


MfaResultsForm * MfaResultsController::contructTheResultsForm()
{
  MfaResultsForm * mfaResultsForm = new MfaResultsForm(0);
  QList<Plotter *> plots = plotResults();
  
  mfaResultsForm->setUpDqGraphic(plots.at(0)); // Dq graphic
  mfaResultsForm->setUpCqGraphic(plots.at(1)); // Cq graphic
  mfaResultsForm->setUpLinearRegressionGraphic(plots.at(2)); // Linear reg.
  mfaResultsForm->setUpSequenceTable(prepareContentSequenceTable());
  mfaResultsForm->setUpDqValuesTable(prepareContentDqValuesTable());
//  prepareContentSequenceTable();
  TRACE (__LINE__ << "\n\t" << "Después setUpDqGraphic()");
  
   
  return mfaResultsForm;
}

QList<Plotter *> MfaResultsController::plotResults()
{
  QList<Plotter *> plots;
  QList<vector<double> *> dqDataSet;
  QList<vector<double> *> cqDataSet;
  QList<QList<vector<double> *> > linearRegressionsDataSet;
  
//  vector<double> * qValues = mfaObjects.at(0)->getQValues();
  vector<double> * qValues = mfaObjects.at(0).getQValues();
  
  dqDataSet.append(qValues);
  cqDataSet.append(qValues);
  
  for (int i = 0; i < mfaObjects.count(); ++i) {
//     dqDataSet.append(mfaObjects.at(i)->getDqValues());
     dqDataSet.append(mfaObjects.at(i).getDqValues());
//     cqDataSet.append(mfaObjects.at(i)->getCqValues());
     cqDataSet.append(mfaObjects.at(i).getCqValues());
//     linearRegressionsDataSet.append(mfaObjects.at(i)->
     linearRegressionsDataSet.append(mfaObjects.at(i).
                                     getLinearRegressionValues());
  }
  
  Plotter * dqPlot = new Plotter(dqDataSet,Plotter::Dq_Plot);
  Plotter * cqPlot = new Plotter(cqDataSet,Plotter::Cq_Plot);
//  Plotter * cqPlot = new Plotter(Plotter::Test_Plot);
  Plotter * linearRegressionPlot = new Plotter(linearRegressionsDataSet,
                                               Plotter::Linear_Plot);
  
  plots.append(dqPlot);
  plots.append(cqPlot);
  plots.append(linearRegressionPlot);
  
  return plots;
}

QList<QStringList > MfaResultsController::prepareContentSequenceTable()
{
  QList<QStringList > contentList;
  QStringList row;
  
  for (int i = 0; i < mfaObjects.count(); ++i) {
    const Sequence * sequence = mfaObjects.at(i).getCgrObject()->getSequence();
    
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

QList<QStringList > MfaResultsController::prepareContentDqValuesTable()
{
  QList<QStringList > contentList;
  int minQ = mfaObjects.at(0).getMinQ();
  int maxQ = mfaObjects.at(0).getMaxQ();
  int i = 0;
  
  for (int q = minQ; q <= maxQ; ++q) {
    for (int j = 0; j < mfaObjects.count(); ++j) {
      double dqValue = mfaObjects.at(j).getDqValues()->at(i);
      
      QStringList row;
      row << QString::number(q)
          << QString::number(dqValue);
           
      contentList << row;
      DEBUG(q << " " << dqValue);
    }
    ++i;
  }
  return contentList;
}

//void MfaResultsController::setMfaObjects(QList <MultifractalAnalysis *> 
void MfaResultsController::setMfaObjects(QList <MultifractalAnalysis> 
                                         mfaObjects)
{
//  this->mfaObjects = QList<MultifractalAnalysis *>(mfaObjects);
  this->mfaObjects = mfaObjects;
}

MfaResultsForm * MfaResultsController::getMfaResultsForm()
{
  return mfaResultsForm;
}
