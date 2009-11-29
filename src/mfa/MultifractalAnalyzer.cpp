/**
 * @file MultifractalAnalyzer.cpp
 * @date 11/11/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MultifractalAnalyzer.cpp
 *   Created on:  11/11/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "MultifractalAnalyzer.h"

MultifractalAnalyzer::MultifractalAnalyzer()
{
  this->cgrObjects = QList<const ChaosGameRepresentation *>();
  this->mfaObjects = QList<MultifractalAnalysis *>();
  this->minQ       = -70;
  this->maxQ       =  70;
  this->nCenters   =  50;
  this->minR       =   1.0;
  this->maxR       = 256.0; 
  this->type       = MultifractalAnalysis::CONTINOUS_ANALYSIS;
}

MultifractalAnalyzer::MultifractalAnalyzer(
//                                           const AppController * parentApp,
                                           QList<const ChaosGameRepresentation * >  
                                           cgrObjects,
                                           MultifractalAnalysis::AnalysisType type,
                                           const int & minQ,
                                           const int & maxQ,
                                           const int & nCenters,
                                           const double & minR,
                                           const double & maxR)
{ 
  
//  this->parentApp  = parentApp;
  this->cgrObjects = cgrObjects;
  this->mfaObjects = QList<MultifractalAnalysis *>();
  this->minQ       = minQ;
  this->maxQ       = maxQ;
  this->nCenters   = nCenters;
  this->minR       = minR;
  this->maxR       = maxR;
  this->type       = type;
}

MultifractalAnalyzer::MultifractalAnalyzer(const MultifractalAnalyzer & 
                                           multifractalAnalyzerObject)
{ 
//  this->parentApp  = multifractalAnalyzerObject.parentApp;
  this->cgrObjects = multifractalAnalyzerObject.cgrObjects;
  this->mfaObjects = QList<MultifractalAnalysis *>();
  this->minQ       = multifractalAnalyzerObject.minQ;
  this->maxQ       = multifractalAnalyzerObject.maxQ;
  this->nCenters   = multifractalAnalyzerObject.nCenters;
  this->minR       = multifractalAnalyzerObject.minR;
  this->maxR       = multifractalAnalyzerObject.maxR;
  this->type       = multifractalAnalyzerObject.type;
}

MultifractalAnalyzer::~MultifractalAnalyzer()
{
//  if(parentApp != 0)
//    parentApp = 0;
}

QList<MultifractalAnalysis *> MultifractalAnalyzer::performAnalysis()
{
//  MultifractalAnalysis * mfaObject = 0;
//  //  MultifractalAnalyzer * mfAnalyzer = 0;
//  QList<int> mfaKeys;
//  QList<const ChaosGameRepresentation * > cgrListForAnalysis;
//  
//  for (int i = 0; i < cgrKeys.count(); ++i) {
//    int cgrKey = cgrKeys.at(i);
//    if(cgrKey != -1){
//      const ChaosGameRepresentation * cgrObject = cgrHash->value(cgrKey);
//      if(cgrObject)
//        cgrListForAnalysis.append(cgrObject);
//    }
//  }  
//  //    cout << "AppController::125 - " << qPrintable(QString::
//  //            fromStdString(sequence->getName())) << endl;
//  mfaObject = new MultifractalAnalysis(cgrListForAnalysis.at(0), minQ, maxQ);
//  mfaObject->performAnalysis(MultifractalAnalysis::COMPARATIVE_ANALYSIS);
  
  
  return QList<MultifractalAnalysis *>();
}

QList<const ChaosGameRepresentation *> MultifractalAnalyzer::getCgrObjects()
{
  return cgrObjects;
}

void MultifractalAnalyzer::setCgrObjects(QList<const ChaosGameRepresentation *>  
                                         cgrObjects)
{
  this->cgrObjects = cgrObjects;
}

int MultifractalAnalyzer::getMinQ()
{
  return minQ;
}

void MultifractalAnalyzer::setMinQ(int minQ)
{
  this->minQ = minQ;
}

int MultifractalAnalyzer::getMaxQ()
{
  return maxQ;
}

void MultifractalAnalyzer::setMaxQ(int maxQ)
{
  this->maxQ = maxQ;
}

int MultifractalAnalyzer::getNCenters()
{
  return nCenters;
}

void MultifractalAnalyzer::setNCenters(int nCenters)
{
  this->nCenters = nCenters;
}

double MultifractalAnalyzer::getMinR()
{
  return minR;
}

void MultifractalAnalyzer::setMinR(double minR)
{
  this->minR = minR;
}

QList<MultifractalAnalysis *>  MultifractalAnalyzer::getMfaObjects()
{
  return mfaObjects;
}

void MultifractalAnalyzer::setMfaObjects(QList<MultifractalAnalysis *> 
                                         mfaObjects)
{
  this->mfaObjects = mfaObjects;
}

double MultifractalAnalyzer::getMaxR()
{
  return maxR;
}

void MultifractalAnalyzer::setMaxR(double maxR)
{
  this->maxR = maxR;
}

//AppController * MultifractalAnalyzer::getParentApp() {
//  return parentApp;
//}
