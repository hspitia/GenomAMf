/**
 * @file MultifractalAnalisys.cpp
 * @date 13/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MultifractalAnalisys.cpp
 *   Created on:  13/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "MultifractalAnalisys.h"

MultifractalAnalisys::MultifractalAnalisys()
{
  this->cgrObject = 0;
  this->minQ= 0;
  this->maxQ = 0;
  this->linearRegressionImgePath = "";
  this->dqSpectraImagePath = "";
  this->cqImagePath = "";
  this->linearRegressionValues = new QList<vector<double> >();
  this->dqValues = new QList<vector<double> >();
  this->cqValues = new QList<vector<double> >();
  this->tqValues = new QList<vector<double> >();
  
}

MultifractalAnalisys::MultifractalAnalisys(const 
                                           MultifractalAnalisys & mfaObject)
{
//  this->cgrObject = new ChaosGameRepresentation(*(mfaObject.cgrObject));
  this->cgrObject = mfaObject.cgrObject;
  this->minQ = mfaObject.minQ;
  this->maxQ = mfaObject.maxQ;
  this->linearRegressionImgePath = mfaObject.linearRegressionImgePath;
  this->dqSpectraImagePath = mfaObject.dqSpectraImagePath;
  this->cqImagePath = mfaObject.cqImagePath;
  this->linearRegressionValues
          = new QList <vector <double> > (*(mfaObject.linearRegressionValues));
  this->dqValues = new QList <vector <double> > (*(mfaObject.dqValues));
  this->cqValues = new QList<vector<double> > (*(mfaObject.cqValues));;
  this->tqValues = new QList<vector<double> > (*(mfaObject.tqValues));
}

MultifractalAnalisys::MultifractalAnalisys(const ChaosGameRepresentation * 
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
  this->linearRegressionValues = new QList<vector<double> >();
  this->dqValues = new QList<vector<double> >();
  this->cqValues = new QList<vector<double> >();
  this->tqValues = new QList<vector<double> >();
}

MultifractalAnalisys & MultifractalAnalisys::operator=(const 
                                                       MultifractalAnalisys 
                                                       & mfaObject)
{
  this->cgrObject = new ChaosGameRepresentation(*(mfaObject.cgrObject));
  this->minQ = mfaObject.minQ;
  this->maxQ = mfaObject.maxQ;
  this->linearRegressionImgePath = mfaObject.linearRegressionImgePath;
  this->dqSpectraImagePath = mfaObject.dqSpectraImagePath;
  this->cqImagePath = mfaObject.cqImagePath;
  this->linearRegressionValues
          = new QList <vector <double> > (*(mfaObject.linearRegressionValues));
  this->dqValues = new QList <vector <double> > (*(mfaObject.dqValues));
  this->cqValues = new QList<vector<double> > (*(mfaObject.cqValues));;
  this->tqValues = new QList<vector<double> > (*(mfaObject.tqValues));
  return *this;
}

MultifractalAnalisys::~MultifractalAnalisys()
{
  if(cgrObject != 0) cgrObject = 0;
  delete cgrObject;
  
  if (linearRegressionValues != 0)
  {
    linearRegressionValues->clear();
    delete linearRegressionValues;
    linearRegressionValues = 0;
  }
  
  if (dqValues != 0)
  {
    dqValues->clear();
    delete dqValues;
    dqValues = 0;
  }

  if (cqValues != 0)
  {
    cqValues->clear();
    delete cqValues;
    cqValues = 0;
  }
  
  if (tqValues != 0)
  {
    tqValues->clear();
    delete tqValues;
    tqValues = 0;
  }
}

void MultifractalAnalisys::performAnalisys()
{
  int fractalSize = static_cast<int> (cgrObject->getSequence()->size());
  SandBoxMethod * sandBoxObject = new 
          SandBoxMethod(cgrObject->getMatrixOfPoints(), 
                        minQ - 1, // Dato adicional necesario para calcular Cq
                        maxQ + 1, // Dato adicional necesario para calcular Cq
                        fractalSize);
  
  sandBoxObject->performAnalisys();
  
  linearRegressionValues = new QList<vector<double> >(
          *(sandBoxObject->getLinearRegressionValues()));
  
  dqValues = new QList<vector<double> >(*(sandBoxObject->getDqValues()));
  
  if(sandBoxObject != 0) delete sandBoxObject;
  sandBoxObject = 0;
}

void MultifractalAnalisys::calculateCqValues()
{
  int dataLenght = maxQ - minQ;
  vector<double> qData(dataLenght);
  vector<double> tqData(dataLenght);
  
  for (int q = minQ, i = 1; q <= maxQ; ++q, ++i)
  {
    qData.at(i) = q;
    tqData.at(i) = (2 * tqValues->at(1).at(i   )) - 
                        tqValues->at(1).at(i + 1) -
                        tqValues->at(1).at(i - 1);
  } 
  
}

void MultifractalAnalisys::calculateTqValues()
{
  int dataLenght = maxQ - minQ + 1 + 2;  //Dos datos adicionales para calculo de Cq
  vector<double> qData(dataLenght);
  vector<double> tqData(dataLenght);
  for (int q = minQ - 1, i = 0; q <= maxQ + 1; ++q, ++i)
  {
    qData.at(i) = q;
    tqData.at(i) = (q - 1) * dqValues->at(1).at(i);
  }
}

QString MultifractalAnalisys::plotResults(const QList<vector<double> > & values)
{
  Q_UNUSED(values);
  return QString();
}

int MultifractalAnalisys::getMinQ()
{
  return minQ;
}

void MultifractalAnalisys::setMinQ(int minQ)
{
  this->minQ = minQ;
}

int MultifractalAnalisys::getMaxQ()
{
  return maxQ;
}

void MultifractalAnalisys::setMaxQ(int maxQ)
{
  this->maxQ = maxQ;
}

const ChaosGameRepresentation * MultifractalAnalisys::getCgrObject() const
{
  return cgrObject;
}

void MultifractalAnalisys::setCgrObject(ChaosGameRepresentation * cgrObject)
{
  this->cgrObject = cgrObject;
}

QString MultifractalAnalisys::getLinearRegressionImagePath()
{
  return linearRegressionImgePath;
}

QString MultifractalAnalisys::getDqSpectraImagePath()
{
  return dqSpectraImagePath;
}

QString MultifractalAnalisys::getCqImagePath()
{
  return cqImagePath;
}

QList <vector <double> > * MultifractalAnalisys::getLinearRegressionValues()
{
  return linearRegressionValues;
}

void MultifractalAnalisys::setLinearRegressionValues(QList <vector <double> > * 
                                          linearRegressionValues)
{
  this->linearRegressionValues = linearRegressionValues;
}

QList <vector <double> > * MultifractalAnalisys::getDqValues()
{
  return dqValues;
}

void MultifractalAnalisys::setDqValues(QList <vector <double> > * dqValues)
{
  this->dqValues = dqValues;
}

QList <vector <double> > * MultifractalAnalisys::getCqValues()
{
  return cqValues;
}

void MultifractalAnalisys::setCqValues(QList <vector <double> > * cqValues)
{
  this->cqValues = cqValues;
}

QList <vector <double> > * MultifractalAnalisys::getTqValues()
{
  return tqValues;
}

void MultifractalAnalisys::setTqValues(QList <vector <double> > * tqValues)
{
  this->tqValues = tqValues;
}
