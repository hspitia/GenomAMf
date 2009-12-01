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

#include "MultifractalAnalysis.h"

MultifractalAnalysis::MultifractalAnalysis()
{
  this->cgrObject = 0;
  this->minQ = 0;
  this->maxQ = 0;
  this->linearRegressionImgePath = "";
  this->dqSpectraImagePath = "";
  this->cqImagePath = "";
//  this->linearRegressionValues = new QList <vector <double> > ();
  this->linearRegressionValues = QList <vector <double> *>();
//  this->dqValues = new QList <vector <double> > ();
  this->dqValues = new vector<double>();
//  this->cqValues = new QList <vector <double> > ();
  this->cqValues = new vector<double>();
//  this->tqValues = new QList <vector <double> > ();
  this->tqValues = new vector<double>();
  
}

MultifractalAnalysis::MultifractalAnalysis(const MultifractalAnalysis & 
                                           mfaObject)
{
  //  this->cgrObject = new ChaosGameRepresentation(*(mfaObject.cgrObject));
  this->cgrObject = mfaObject.cgrObject;
  this->minQ = mfaObject.minQ;
  this->maxQ = mfaObject.maxQ;
  this->linearRegressionImgePath = mfaObject.linearRegressionImgePath;
  this->dqSpectraImagePath = mfaObject.dqSpectraImagePath;
  this->cqImagePath = mfaObject.cqImagePath;
//  this->linearRegressionValues
//          = new QList <vector <double> > (*(mfaObject.linearRegressionValues));
  this->linearRegressionValues
          = QList<vector<double> *>(mfaObject.linearRegressionValues);
//  this->dqValues = new QList <vector <double> > (*(mfaObject.dqValues));
  this->dqValues = new vector<double>(*(mfaObject.dqValues));
//  this->cqValues = new QList <vector <double> > (*(mfaObject.cqValues));
  this->cqValues = new vector<double>(*(mfaObject.cqValues));
//  this->tqValues = new QList <vector <double> > (*(mfaObject.tqValues));
  this->tqValues = new vector<double>(*(mfaObject.tqValues));
}

MultifractalAnalysis::MultifractalAnalysis(const ChaosGameRepresentation * 
                                           cgrObject,
                                           const int & minQ, 
                                           const int & maxQ)
{
  this->cgrObject = cgrObject;
  this->minQ = minQ;
  this->maxQ = maxQ;
  this->linearRegressionImgePath = "";
  this->dqSpectraImagePath = "";
  this->cqImagePath = "";
  //  this->linearRegressionValues = new QList <vector <double> > ();
  this->linearRegressionValues = QList <vector <double> *>();
//  this->dqValues = new QList <vector <double> > ();
  this->dqValues = new vector<double>();
//  this->cqValues = new QList <vector <double> > ();
  this->cqValues = new vector<double>();
//  this->tqValues = new QList <vector <double> > ();
  this->tqValues = new vector<double>();
/*
  this->linearRegressionValues = new QList <vector <double> > ();
  this->dqValues = new QList <vector <double> > ();
  this->cqValues = new QList <vector <double> > ();
  this->tqValues = new QList <vector <double> > ();
*/
  
}

MultifractalAnalysis & MultifractalAnalysis::operator=(const 
                                                       MultifractalAnalysis & 
                                                       mfaObject)
{
  this->cgrObject = new ChaosGameRepresentation(*(mfaObject.cgrObject));
  this->minQ = mfaObject.minQ;
  this->maxQ = mfaObject.maxQ;
  this->linearRegressionImgePath = mfaObject.linearRegressionImgePath;
  this->dqSpectraImagePath = mfaObject.dqSpectraImagePath;
  this->cqImagePath = mfaObject.cqImagePath;
  
//  this->linearRegressionValues
//          = new QList <vector <double> > (*(mfaObject.linearRegressionValues));
  this->linearRegressionValues
          = QList<vector<double> *>(mfaObject.linearRegressionValues);
//  this->dqValues = new QList <vector <double> > (*(mfaObject.dqValues));
  this->dqValues = new vector<double>(*(mfaObject.dqValues));
//  this->cqValues = new QList <vector <double> > (*(mfaObject.cqValues));
  this->cqValues = new vector<double>(*(mfaObject.cqValues));
//  this->tqValues = new QList <vector <double> > (*(mfaObject.tqValues));
  this->tqValues = new vector<double>(*(mfaObject.tqValues));
  
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
  
  /*if (linearRegressionValues != 0) {
    linearRegressionValues->clear();
    delete linearRegressionValues;
    linearRegressionValues = 0;
  }

  if (dqValues != 0) {
    dqValues->clear();
    delete dqValues;
    dqValues = 0;
  }

  if (cqValues != 0) {
    cqValues->clear();
    delete cqValues;
    cqValues = 0;
  }
  
  if (tqValues != 0) {
    tqValues->clear();
    delete tqValues;
    tqValues = 0;
  }*/
  
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
        // C�lculo de valores Dq
        cout << "  DEBUG - MultifractalAnalysis::performAnalysis::182 - antes   calculateDqValues" << endl;
        calculateDqValues(type);
        cout << "  DEBUG - MultifractalAnalysis::performAnalysis::182 - despues calculateDqValues" << endl;
        /*// C�lculo de valores Tauq
        cout << "  DEBUG - MultifractalAnalysis::performAnalysis::182 - antes   calculateTqValues" << endl;
        calculateTqValues();
        cout << "  DEBUG - MultifractalAnalysis::performAnalysis::182 - despues calculateTqValues" << endl;
        // Calcular Cq
        calculateCqValues();*/
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
  SandBoxMethod * sandBoxObject = 
          new SandBoxMethod(cgrObject->getMatrixOfPoints(),
                            *(cgrObject->getCoordinatesOfPoints()),
                            minQ - 1, // Dato adicional necesario para calcular Cq
                            maxQ + 1); // Dato adicional necesario para calcular Cq
  
  sandBoxObject->performAnalysis(COMPARATIVE_ANALYSIS);
//  cout << "DEBUG MultifractalAnalysis::206 - despues de ComparativeAnalysis"<< endl;
}

void MultifractalAnalysis::calculateDqValues(AnalysisType type)
{
  SandBoxMethod * sandBoxObject = 
          new SandBoxMethod(cgrObject->getMatrixOfPoints(),
                            *(cgrObject->getCoordinatesOfPoints()),
                            minQ - 1, // Dato adicional necesario para calcular Cq
                            maxQ + 1);// Dato adicional necesario para calcular Cq
  cout << "    DEBUG - MultifractalAnalysis::216 - calculateDqValues - Antes de performAnalysis("<< type << ")" << endl;
  
  sandBoxObject->performAnalysis(type);
  
  linearRegressionValues = sandBoxObject->getLinearRegressionValues();
  
//  linearRegressionValues
//          = new QList <vector <double> *> 
//          (*(sandBoxObject->getLinearRegressionValues()));
  
  dqValues = new vector<double>(*(sandBoxObject->getDqValues()));
  
  if (sandBoxObject != 0) delete sandBoxObject;
  sandBoxObject = 0;
}

void MultifractalAnalysis::calculateTqValues()
{
  int dataLenght = maxQ - minQ + 1 + 2; //Dos datos adicionales para c�lculo de Cq
  int q = minQ;
  for (int i = 0; i < dataLenght; ++i) {
//    tqValues->at(i) = (q - 1) * dqValues->at(i);
    double tqValue = (q - 1) * dqValues->at(i);
    tqValues->push_back(tqValue);
    cout << "    DEBUG - MultifractalAnalysis::calculateTqValues::243 - tqValues->at(i): "<< dqValues->at(i) <<endl;
    cout << "    DEBUG - MultifractalAnalysis::calculateTqValues::243 - tqValues->at(i): "<< tqValues->at(i) <<endl;
//    cout << "    DEBUG - MultifractalAnalysis::calculateTqValues::242 - tqValues->at(i): ";
//    cout << tqValues->at(i) << endl;
//    cout << "    DEBUG - MultifractalAnalysis::calculateTqValues::243 - dqValues->at(i): " << dqValues->at(i) << endl;
    ++q;
  }
}
  
void MultifractalAnalysis::calculateCqValues()
{
  int dataLenght = maxQ - minQ + 1;
  for (int i = 0; i < dataLenght; i++) {
    cqValues->at(i) = (2 * tqValues->at(i + 1)) - 
                           tqValues->at(i + 2)  -
                           tqValues->at(i);
  }
}

//QString MultifractalAnalysis::plotResults(const QList <vector <double> >& 
//                                          values)
//{
//  Q_UNUSED(values);
//  return QString();
//}

int MultifractalAnalysis::getMinQ()
{
  return minQ;
}

void MultifractalAnalysis::setMinQ(int minQ)
{
  this->minQ = minQ;
}

int MultifractalAnalysis::getMaxQ()
{
  return maxQ;
}

void MultifractalAnalysis::setMaxQ(int maxQ)
{
  this->maxQ = maxQ;
}

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
  // Se eliminan los dos datos adicionales (extremos) necesarios para el c�lculo
  // de Cq 

//  QList <vector <double> > * trueDqValues;
//  vector<double> trueQData;
  unsigned int dataLength = maxQ - minQ + 1;
  vector<double> * trueDqValues = new vector<double>(dataLength);
  
  for (unsigned int i = 1; i <= dataLength; ++i) {
//    trueQData.push_back(dqValues->at(0).at(i));
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
  for (int i = minQ; i <= maxQ; ++i) {
    qValues->push_back(static_cast<double>(i));
  }
  return qValues;
}
//void MultifractalAnalysis::setTqValues(QList <vector <double> > * tqValues)
//{
//  this->tqValues = tqValues;
//}
