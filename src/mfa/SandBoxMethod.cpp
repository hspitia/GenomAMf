/**
 * @file SandBoxMethod.cpp
 * @date 15/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  SandBoxMethod.cpp
 *   Created on:  15/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "SandBoxMethod.h"

SandBoxMethod::SandBoxMethod()
{
  this->qMin = -100;
  this->qMax =  100;
  this->rMin =   10;
  this->rMax =  200;
  this->cgrMatrix = 0;
  this->numberOfCenters = 300;
  this->dqValues = new QList<vector<double> >();
}

SandBoxMethod::SandBoxMethod(const SandBoxMethod & sandBoxObject)
{
  this->qMin = sandBoxObject.qMin;
  this->qMax = sandBoxObject.qMax;
  this->rMin = sandBoxObject.rMin;
  this->rMax = sandBoxObject.rMax;
  this->cgrMatrix = sandBoxObject.cgrMatrix;
  this->numberOfCenters = sandBoxObject.numberOfCenters;
  this->dqValues = sandBoxObject.dqValues;
}

SandBoxMethod::SandBoxMethod(const RowMatrix<int> * cgrMatrix, 
                             const int & qMin, const int & qMax)
{
  this->qMin = qMin;
  this->qMax = qMax;
  this->rMin =   10;
  this->rMax =  200;
  this->cgrMatrix = cgrMatrix;
  this->numberOfCenters = 300;
  this->dqValues = new QList<vector<double> >();
}

SandBoxMethod & SandBoxMethod::operator=(const SandBoxMethod & sandBoxObject)
{
  this->qMin = sandBoxObject.qMin;
  this->qMax = sandBoxObject.qMax;
  this->rMin = sandBoxObject.rMin;
  this->rMax = sandBoxObject.rMax;
  this->cgrMatrix = sandBoxObject.cgrMatrix;
  this->numberOfCenters = sandBoxObject.numberOfCenters;
  this->dqValues = sandBoxObject.dqValues;
  return *this;
}

SandBoxMethod::~SandBoxMethod()
{
  if(cgrMatrix != 0) cgrMatrix = 0;
  delete cgrMatrix;
  dqValues->clear();
}

void SandBoxMethod::performAnalisys()
{
  int nMomentums = qMax - qMin + 1;
  vector<double> qData(nMomentums);
  vector<double> dqData(nMomentums);
  
  for (int q = qMin, index = 0; q <= qMax; ++q, ++index)
  {
    qData.at(index) = q;
    dqData.at(index) = calculateDqValue(q);
  }
  dqValues->append(qData);
  dqValues->append(dqData);
}

double SandBoxMethod::calculateDqValue(const int & q)
{
  int dataLenght = rMax - rMin + 1;
  
  vector<double> xData(dataLenght);
  vector<double> yData(dataLenght);
  
  double massAverage;
  
  for (int radius = rMin, index = 0; radius <= rMax; ++radius, ++index)
  {
    // Sand box centers coordinates
    vector<int> xCoordinates(numberOfCenters);
    vector<int> yCoordinates(numberOfCenters);
    
    generateRandomCenters(&xCoordinates, &yCoordinates);
    
    vector<double> masses(numberOfCenters);
    for (int i = 0; i < numberOfCenters; ++i)
    {
      masses.at(i) = pow(countSandBoxPoints(xCoordinates.at(i), 
                                            yCoordinates.at(i), radius),
                                            static_cast<double>(q - 1));
    }
    
    massAverage = VectorTools::mean<double,double>(masses);
    
    xData.at(index) = (q - 1) * log(radius/fractalSize);
    yData.at(index) = log(massAverage);
  }
  
  Linear * linear = new Linear(dataLenght, &xData, &yData);
  
  return linear->getSlope();
}

void SandBoxMethod::generateRandomCenters(vector<int> * xCoordinates,
                                          vector<int> * yCoordinates)
{
  int maxNumber = static_cast<int>(cgrMatrix->nRows());
//  int maxNumber = 1024;
  for (int i = 0; i < numberOfCenters; ++i)
  {
    xCoordinates->at(i) = RandomTools::
            giveIntRandomNumberBetweenZeroAndEntry(maxNumber);
    yCoordinates->at(i) = RandomTools::
                giveIntRandomNumberBetweenZeroAndEntry(maxNumber);
//    cout << "x: " << xCoordinates->at(i) 
//         << "  y: " << yCoordinates->at(i) << endl;
  }
} 

double SandBoxMethod::countSandBoxPoints(const int & x, 
                                         const int & y, 
                                         const int & radius)
{
  Q_UNUSED(x);
  Q_UNUSED(y);
  Q_UNUSED(radius);
  // TODO Cambiar el valor de retorno del método
  return 0;
}


int SandBoxMethod::getQMin()
{
  return qMin;
}

void SandBoxMethod::setQMin(int qMin)
{
  this->qMin = qMin;
}

int SandBoxMethod::getQMax()
{
  return qMax;
}

void SandBoxMethod::setQMax(int qMax)
{
  this->qMax = qMax;
}

int SandBoxMethod::getRMin()
{
  return rMin;
}

void SandBoxMethod::setRMin(int rMin)
{
  this->rMin = rMin;
}

int SandBoxMethod::getRMax()
{
  return rMax;
}

void SandBoxMethod::setRMax(int rMax)
{
  this->rMax = rMax;
}

const RowMatrix<int> * SandBoxMethod::getCgrMatrix() const
{
  return cgrMatrix;
}

void SandBoxMethod::setCgrMatrix(const RowMatrix<int> * cgrMatrix)
{
  this->cgrMatrix = cgrMatrix;
}

int SandBoxMethod::getNumberOfCenters()
{
  return numberOfCenters;
}

void SandBoxMethod::setNumberOfCenters(int numberOfCenters)
{
  this->numberOfCenters = numberOfCenters;
}

QList<vector<double> > * SandBoxMethod::getDqValues()
{
  return dqValues;
}

void SandBoxMethod::setDqValues(QList<vector<double> > * dqValues)
{
  this->dqValues = dqValues;
}


int SandBoxMethod::getFractalSize()
{
  return fractalSize;
}

void SandBoxMethod::setFractalSize(int fractalSize)
{
  this->fractalSize = fractalSize;
}
