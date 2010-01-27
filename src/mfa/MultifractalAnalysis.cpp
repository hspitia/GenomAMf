/**
 * @file MultifractalAnalysis.cpp
 * @date 13/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MultifractalAnalysis.cpp
 *   Created on:  13/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */
//#define DEBUG_MODE

#include "MultifractalAnalysis.h"
#include "utils/Trace.h"


MultifractalAnalysis::MultifractalAnalysis()
{
  this->cgrObject                = 0;
  this->mfaParametersSet         = MfaParametersSet(); 
//  this->minQ                     = 0;
//  this->maxQ                     = 0;
//  this->nCenters                 = 0;
//  this->radiusStep               = 0;
  this->linearRegressionImgePath = "";
  this->dqSpectraImagePath       = "";
  this->cqImagePath              = "";
  this->linearRegressionValues   = QList <vector <double> *>();
  this->dqValues                 = new vector<double>();
  this->cqValues                 = new vector<double>();
  this->tqValues                 = new vector<double>();
  
}

MultifractalAnalysis::MultifractalAnalysis(const ChaosGameRepresentation * 
                                           cgrObject,
                                           const MfaParametersSet & 
                                           mfaParametersSet)
{
  this->cgrObject                = cgrObject;
  this->mfaParametersSet         = mfaParametersSet;
//  this->minQ                     = minQ;
//  this->maxQ                     = maxQ;
//  this->nCenters                 = nCenters;
//  this->radiusStep               = radiusStep;
  this->linearRegressionImgePath = "";
  this->dqSpectraImagePath       = "";
  this->cqImagePath              = "";
  this->linearRegressionValues   = QList <vector <double> *>();
  this->dqValues                 = new vector<double>();
  this->cqValues                 = new vector<double>();
  this->tqValues                 = new vector<double>();
  
}

/*MultifractalAnalysis::MultifractalAnalysis(const ChaosGameRepresentation * 
                                           cgrObject,
                                           const int & minQ, 
                                           const int & maxQ,
                                           const int & nCenters,
                                           const int & radiusStep)
{
  this->cgrObject                = cgrObject;
  this->mfaParametersSet         = MfaParametersSet(); mfaParametersSet;
  this->linearRegressionImgePath = "";
  this->dqSpectraImagePath       = "";
  this->cqImagePath              = "";
  this->linearRegressionValues   = QList <vector <double> *>();
  this->dqValues                 = new vector<double>();
  this->cqValues                 = new vector<double>();
  this->tqValues                 = new vector<double>();
  
}*/

MultifractalAnalysis::MultifractalAnalysis(const MultifractalAnalysis & 
                                           mfaObject)
{
  this->cgrObject                = mfaObject.cgrObject;
  this->mfaParametersSet         = mfaObject.mfaParametersSet;
  this->linearRegressionImgePath = mfaObject.linearRegressionImgePath;
  this->dqSpectraImagePath       = mfaObject.dqSpectraImagePath;
  this->cqImagePath              = mfaObject.cqImagePath;
  this->linearRegressionValues   = 
          QList<vector<double> *>(mfaObject.linearRegressionValues);
  this->dqValues                 = new vector<double>(*(mfaObject.dqValues));
  this->cqValues                 = new vector<double>(*(mfaObject.cqValues));
  this->tqValues                 = new vector<double>(*(mfaObject.tqValues));
}

MultifractalAnalysis & MultifractalAnalysis::operator=(const 
                                                       MultifractalAnalysis & 
                                                       mfaObject)
{
  this->cgrObject                = 
          new ChaosGameRepresentation(*(mfaObject.cgrObject));
  this->mfaParametersSet         = mfaObject.mfaParametersSet;
  this->linearRegressionImgePath = mfaObject.linearRegressionImgePath;
  this->dqSpectraImagePath       = mfaObject.dqSpectraImagePath;
  this->cqImagePath              = mfaObject.cqImagePath;
  this->linearRegressionValues   = 
          QList<vector<double> *>(mfaObject.linearRegressionValues);
  this->dqValues                 = new vector<double>(*(mfaObject.dqValues));
  this->cqValues                 = new vector<double>(*(mfaObject.cqValues));
  this->tqValues                 = new vector<double>(*(mfaObject.tqValues));
  
/*
  this->linearRegressionValues
          = new QList <vector <double> > (*(mfaObject.linearRegressionValues));
  this->dqValues = new QList <vector <double> > (*(mfaObject.dqValues));
  this->cqValues = new QList <vector <double> > (*(mfaObject.cqValues));
  ;
  this->tqValues = new QList <vector <double> > (*(mfaObject.tqValues));
*/
  return *this;
}

MultifractalAnalysis::~MultifractalAnalysis()
{
  if (cgrObject != 0) cgrObject = 0;
  delete cgrObject;
  
  if (!linearRegressionValues.empty())
    linearRegressionValues.clear();

  if (dqValues != 0) {
    delete dqValues;
    dqValues = 0;
  }

  if (cqValues != 0) {
    delete cqValues;
    cqValues = 0;
  }
  
  if (tqValues != 0) {
    delete tqValues;
    tqValues = 0;
  }
  
}

void MultifractalAnalysis::performAnalysis(AnalysisType type)
{
  switch (type) {
    case CONTINOUS_ANALYSIS:
    case DISCRETE_ANALYSIS:
      {
        // Cálculo de valores Dq
        calculateDqValues(type);
        // Cálculo de valores Tauq
        calculateTqValues();
        // Cálculo de valores Cq
        calculateCqValues();
      }
      break;
    case COMPARATIVE_ANALYSIS:
      performComparativeAnalysis();
      break;
    default:
      return;
  }
}

void MultifractalAnalysis::performComparativeAnalysis()
{
//  SandBoxMethod * sandBoxObject = 
//          new SandBoxMethod(cgrObject->getMatrixOfPoints(),
//                            cgrObject->getCumulativeFrequencyMatrix(),
//                            *(cgrObject->getCoordinatesOfPoints()),
//                            minQ - 1, // Dato adicional necesario para calcular Cq
//                            maxQ + 1, // Dato adicional necesario para calcular Cq
//                            30);      // nCenters
  SandBoxMethod * sandBoxObject = 
          new SandBoxMethod(cgrObject->getMatrixOfPoints(),
                            cgrObject->getCumulativeFrequencyMatrix(),
                            *(cgrObject->getCoordinatesOfPoints()),
                            static_cast<int>(cgrObject->getSequence()->size()),
                            mfaParametersSet);      // nCenters
  
  sandBoxObject->performAnalysis(COMPARATIVE_ANALYSIS);
}

void MultifractalAnalysis::calculateDqValues(AnalysisType type)
{
//  SandBoxMethod * sandBoxObject = 
//          new SandBoxMethod(cgrObject->getMatrixOfPoints(),
//                            cgrObject->getCumulativeFrequencyMatrix(),
//                            *(cgrObject->getCoordinatesOfPoints()),
//                            minQ - 1, // Dato adicional necesario para calcular Cq
//                            maxQ + 1, // Dato adicional necesario para calcular Cq
//                            nCenters);      // nCenters
  
  MfaParametersSet newParameters = mfaParametersSet;
  newParameters.setMinQ(newParameters.getMinQ() - 1); // Dato adicional necesario para calcular Cq
  newParameters.setMaxQ(newParameters.getMaxQ() + 1); // Dato adicional necesario para calcular Cq
  
  SandBoxMethod * sandBoxObject = 
          new SandBoxMethod(cgrObject->getMatrixOfPoints(),
                            cgrObject->getCumulativeFrequencyMatrix(),
                            *(cgrObject->getCoordinatesOfPoints()),
                            static_cast<int>(cgrObject->getSequence()->size()),
                            newParameters);
  
  vector<int> qValuesForReg(6);
  qValuesForReg.at(0) = mfaParametersSet.getMinQ();
  qValuesForReg.at(1) = -1;
  qValuesForReg.at(2) =  0;
  qValuesForReg.at(3) =  1;
  qValuesForReg.at(4) =  2;
  qValuesForReg.at(5) = mfaParametersSet.getMaxQ();
  
  sandBoxObject->setQValuesForRegressionPlot(qValuesForReg);
  sandBoxObject->performAnalysis(type);
  
  linearRegressionValues = sandBoxObject->getLinearRegressionValues();
  
  //  linearRegressionValues
  //          = new QList <vector <double> *> 
  //          (*(sandBoxObject->getLinearRegressionValues()));
  
  dqValues = new vector<double>(*(sandBoxObject->getDqValues()));
  
  if (sandBoxObject != 0) 
    delete sandBoxObject;
  
  sandBoxObject = 0;
}

void MultifractalAnalysis::calculateTqValues()
{
//  int dataLenght = maxQ - minQ + 1 + 2; // Dos datos adicionales para cálculo de Cq
  int dataLenght = 
          mfaParametersSet.getMaxQ() - mfaParametersSet.getMinQ() + 1 + 2; // Dos datos adicionales para cálculo de Cq
//  int q = minQ - 1;
  int q = mfaParametersSet.getMinQ() - 1;
//  DEBUG("\nNo.;q;TauQ");
  for (int i = 0; i < dataLenght; ++i) {
    double tqValue = (q - 1) * dqValues->at(i);
    tqValues->push_back(tqValue);
//    DEBUG (i+1 <<";"<< q <<";"<< tqValues->at(i) );
    ++q;
  }
}
  
void MultifractalAnalysis::calculateCqValues()
{
//  int dataLenght = maxQ - minQ + 1;
//  int q = minQ;
  
  int dataLenght = mfaParametersSet.getMaxQ() - mfaParametersSet.getMinQ() + 1;
//  int q = minQ;
  int q = mfaParametersSet.getMinQ() - 1;
//  DEBUG("\nNo.;q;Cq");
  for (int i = 0; i < dataLenght; i++) {
    double cqValue = (2 * tqValues->at(i + 1)) - 
                          tqValues->at(i + 2)  -
                          tqValues->at(i);
    cqValues->push_back(cqValue);
//    DEBUG (i+1 <<";"<< q <<";"<< cqValues->at(i) );
    ++q;
  }
}

//QString MultifractalAnalysis::plotResults(const QList <vector <double> >& 
//                                          values)
//{
//  Q_UNUSED(values);
//  return QString();
//}


MfaParametersSet MultifractalAnalysis::getMfaParametersSet() const
{
  return mfaParametersSet;
}

void MultifractalAnalysis::setMfaParametersSet(const MfaParametersSet & 
                                               mfaParametersSet)
{
  this->mfaParametersSet = mfaParametersSet;
}

//
//int MultifractalAnalysis::getMinQ() const
//{
//  return minQ;
//}
//
//void MultifractalAnalysis::setMinQ(int minQ)
//{
//  this->minQ = minQ;
//}
//
//int MultifractalAnalysis::getMaxQ() const
//{
//  return maxQ;
//}
//
//void MultifractalAnalysis::setMaxQ(int maxQ)
//{
//  this->maxQ = maxQ;
//}

const ChaosGameRepresentation * MultifractalAnalysis::getCgrObject() const
{
  return cgrObject;
}

void MultifractalAnalysis::setCgrObject(ChaosGameRepresentation * cgrObject)
{
  this->cgrObject = cgrObject;
}

QString MultifractalAnalysis::getLinearRegressionImagePath()
{
  return linearRegressionImgePath;
}

QString MultifractalAnalysis::getDqSpectraImagePath()
{
  return dqSpectraImagePath;
}

QString MultifractalAnalysis::getCqImagePath()
{
  return cqImagePath;
}

//QList <vector <double> > * MultifractalAnalysis::getLinearRegressionValues()
QList<vector<double> *> MultifractalAnalysis::getLinearRegressionValues() const
{
  return linearRegressionValues;
}

/*
void MultifractalAnalysis::setLinearRegressionValues(QList <vector <double> > * 
                                                     linearRegressionValues)
{
  this->linearRegressionValues = linearRegressionValues;
}
*/

//QList <vector <double> > * MultifractalAnalysis::getDqValues()
vector<double> * MultifractalAnalysis::getDqValues() const
{
  // Se eliminan los dos datos adicionales (extremos) necesarios para el cálculo
  // de Cq 

  unsigned int dataLength = 
          mfaParametersSet.getMaxQ() - mfaParametersSet.getMinQ() + 1;
  vector<double> * trueDqValues = new vector<double>();
  for (unsigned int i = 1; i <= dataLength; ++i) {
    trueDqValues->push_back(dqValues->at(i));
  }
  
  return trueDqValues;
}

//void MultifractalAnalysis::setDqValues(QList <vector <double> > * dqValues)
//{
//  this->dqValues = dqValues;
//}

//QList <vector <double> > * MultifractalAnalysis::getCqValues()
vector <double> * MultifractalAnalysis::getCqValues() const
{
  return cqValues;
}

//void MultifractalAnalysis::setCqValues(QList <vector <double> > * cqValues)
//{
//  this->cqValues = cqValues;
//}

//QList <vector <double> > * MultifractalAnalysis::getTqValues()
vector <double> * MultifractalAnalysis::getTqValues() const
{
  return tqValues;
}


vector<double> * MultifractalAnalysis::getQValues() const
{
  vector<double> * qValues = new vector<double>();
  for (int i = mfaParametersSet.getMinQ(); i <= mfaParametersSet.getMaxQ(); ++i) {
    qValues->push_back(static_cast<double>(i));
  }
  return qValues;
}

//int MultifractalAnalysis::getNCenters()
//{
//  return nCenters;
//}
//
//int MultifractalAnalysis::getRadiusStep()
//{
//  return radiusStep;
//}
//
//void MultifractalAnalysis::setRadiusStep(const int & radiusStep)
//{
//  this->radiusStep = radiusStep;
//}
