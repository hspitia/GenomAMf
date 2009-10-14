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
  this->qMin = 0;
  this->qMax = 0;
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
  this->qMin = mfaObject.qMin;
  this->qMax = mfaObject.qMax;
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
                                           const int & qMin,
                                           const int & qMax)
{
  this->cgrObject = cgrObject;
  this->qMin = qMin;
  this->qMax = qMax;
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
  this->qMin = mfaObject.qMin;
  this->qMax = mfaObject.qMax;
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
  // TODO Auto-generated destructor stub
}

void MultifractalAnalisys::performAnalisys()
{
  
}

void MultifractalAnalisys::calculateCqValues()
{
  
}

void MultifractalAnalisys::calculateTqValues()
{
  
}

QString MultifractalAnalisys::plotResults(const QList<vector<double> > & values)
{
  Q_UNUSED(values);
  return QString();
}

int MultifractalAnalisys::getQMin()
{
  return qMin;
}

void MultifractalAnalisys::setQMin(int qMin)
{
  this->qMin = qMin;
}

int MultifractalAnalisys::getQMax()
{
  return qMax;
}

void MultifractalAnalisys::setQMax(int qMax)
{
  this->qMax = qMax;
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
