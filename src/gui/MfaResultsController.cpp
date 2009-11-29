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

#include "MfaResultsController.h"

MfaResultsController::MfaResultsController()
{
  this->mfaObjects     = QList<MultifractalAnalysis *>();
  this->mfaResultsForm = 0;
}

MfaResultsController::MfaResultsController(const QList<MultifractalAnalysis * > & 
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
  
  // TODO 1.- Agregar ScrollArea's en MfaResultsForm
  // TODO 2.- Implementar métodos en MfaResultForm para asignar cada plot
  // TODO 3.- Asignar cada plot
   
  return mfaResultsForm;
}

QList<Plotter *> MfaResultsController::plotResults()
{
  QList<Plotter *> plots;
  QList<vector<double> *> dqDataSet;
  QList<vector<double> *> cqDataSet;
  QList<QList<vector<double> *> > linearRegressionsDataSet;
  
  vector<double> * qValues = mfaObjects.at(0)->getQValues();
  
  dqDataSet.append(qValues);
  cqDataSet.append(qValues);
  
  for (int i = 0; i < mfaObjects.count(); ++i) {
     dqDataSet.append(mfaObjects.at(i)->getDqValues());
     cqDataSet.append(mfaObjects.at(i)->getCqValues());
     linearRegressionsDataSet.append(mfaObjects.at(i)->
                                     getLinearRegressionValues());
  }
  
  Plotter * dqPlot = new Plotter(dqDataSet,Plotter::Dq_Plot);
  Plotter * cqPlot = new Plotter(cqDataSet,Plotter::Cq_Plot);
  Plotter * linearRegressionPlot = new Plotter(linearRegressionsDataSet,
                                               Plotter::Linear_Plot);
  
  plots.append(dqPlot);
  plots.append(cqPlot);
  plots.append(linearRegressionPlot);
  
  return plots;
}

void MfaResultsController::setMfaObjects(QList <MultifractalAnalysis *> 
                                         mfaObjects)
{
//  this->mfaObjects = QList<MultifractalAnalysis *>(mfaObjects);
  this->mfaObjects = mfaObjects;
}

MfaResultsForm * MfaResultsController::getMfaResultsForm()
{
  return mfaResultsForm;
}
