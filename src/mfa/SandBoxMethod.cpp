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
  this->qMax = -100;
  this->qMin =  100;
  this->rMin =   10;
  this->rMax =  200;
  

}

SandBoxMethod::SandBoxMethod(const SandBoxMethod & sandBoxObject)
{
  
}

SandBoxMethod::SandBoxMethod(const Matrix<int> * cgrMatrix,
                  const int & qMin = -100,
                  const int & qMax =  100)
{
  
}

SandBoxMethod & SandBoxMethod::operator=(const SandBoxMethod & sandBoxObject)
{
  
}

SandBoxMethod::~SandBoxMethod()
{
  // TODO Auto-generated destructor stub
}

void SandBoxMethod::generateRandomCenters(vector<int> * xCoordinates,
                                          vector<int> * xCoordinates)
{
  
} 

int SandBoxMethod::countSandBoxPoints(const int & x, 
                                      const int & y, 
                                      const int & radius)
{
  
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
