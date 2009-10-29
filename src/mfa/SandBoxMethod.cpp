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
  this->minQ = -70;
  this->maxQ =  70;
  this->minR = 1;
  this->maxR = 1;
  this->cgrMatrix = 0;
  this->numberOfCenters = 300;
  this->dqValues = new QList<vector<double> >();
  this->linearRegressionValues = new QList<vector<double> >();
//  this->coordinatesOfPoints = new QList<QPointF>();
  this->coordinatesOfPoints = QList<QPointF> ();
//  this->fractalSize = 1;
}

SandBoxMethod::SandBoxMethod(const SandBoxMethod & sandBoxObject)
{
  this->minQ = sandBoxObject.minQ;
  this->maxQ = sandBoxObject.maxQ;
  this->minR = sandBoxObject.minR;
  this->maxR = sandBoxObject.maxR;
  this->cgrMatrix = sandBoxObject.cgrMatrix;
  this->numberOfCenters = sandBoxObject.numberOfCenters;
  this->dqValues = sandBoxObject.dqValues;
  this->linearRegressionValues = sandBoxObject.linearRegressionValues;
  this->coordinatesOfPoints = sandBoxObject.coordinatesOfPoints; 
//          new QList<QPointF>(*(sandBoxObject.coordinatesOfPoints));
//  this->fractalSize = sandBoxObject.fractalSize;
}

SandBoxMethod::SandBoxMethod(const RowMatrix<int> * cgrMatrix,
//                             const int & fractalSize,
                             const int & minQ,
                             const int & maxQ)
{
  this->minQ = minQ;
  this->maxQ = maxQ;
  this->minR = 1;
  this->maxR = cgrMatrix->nRows();
  this->cgrMatrix = cgrMatrix;
  this->numberOfCenters = 300;
  this->dqValues = new QList<vector<double> >();
  this->linearRegressionValues = new QList<vector<double> >();
//   this->coordinatesOfPoints = new QList<QPointF>();
  this->coordinatesOfPoints = QList<QPointF>();
//  this->fractalSize = fractalSize;
}

SandBoxMethod::SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                             const QList<QPointF> * coordinatesOfPoints,
//                             const int & fractalSize,
                             const int & minQ,
                             const int & maxQ)
{
  this->minQ = minQ;
  this->maxQ = maxQ;
  this->minR = 1;
  this->maxR = cgrMatrix->nRows();
  this->cgrMatrix = cgrMatrix;
  this->numberOfCenters = 300;
  this->dqValues = new QList<vector<double> >();
  this->linearRegressionValues = new QList<vector<double> >();
//  this->coordinatesOfPoints = new QList<QPointF>(*coordinatesOfPoints);
  this->coordinatesOfPoints = QList<QPointF>(*coordinatesOfPoints);
//  this->fractalSize = fractalSize;
}

SandBoxMethod & SandBoxMethod::operator=(const SandBoxMethod & sandBoxObject)
{
  this->minQ = sandBoxObject.minQ;
  this->maxQ = sandBoxObject.maxQ;
  this->minR = sandBoxObject.minR;
  this->maxR = sandBoxObject.maxR;
  this->cgrMatrix = sandBoxObject.cgrMatrix;
  this->numberOfCenters = sandBoxObject.numberOfCenters;
  this->dqValues = sandBoxObject.dqValues;
  this->linearRegressionValues = sandBoxObject.linearRegressionValues;
  this->coordinatesOfPoints = 
          QList<QPointF>(sandBoxObject.coordinatesOfPoints);
//          new QList<QPointF>(*(sandBoxObject.coordinatesOfPoints));
//  this->fractalSize = sandBoxObject.fractalSize;
  return *this;
}

SandBoxMethod::~SandBoxMethod()
{
  if(cgrMatrix != 0) cgrMatrix = 0;
  delete cgrMatrix;
  dqValues->clear();
  linearRegressionValues->clear();
}

void SandBoxMethod::performAnalisys()
{
  int nMomentums = maxQ - minQ + 1;
  int dataLenght = maxR - minR + 1;
  
  vector<double> qData(nMomentums);
  vector<double> dqData(nMomentums);
  
  for (int q = minQ, index = 0; q <= maxQ; ++q, ++index)
  {
    vector<double> xData(dataLenght);
    vector<double> yData(dataLenght);
    
    qData.at(index) = q;
    dqData.at(index) = calculateDqValue(q, xData, yData);
    
    linearRegressionValues->append(xData);
    linearRegressionValues->append(yData);
  }
  dqValues->append(qData);
  dqValues->append(dqData);
}

double SandBoxMethod::calculateDqValue(const int & q, vector<double> & xData,
                                       vector<double> & yData)
{
  int dataLenght = maxR - minR + 1;
  
//  vector<double> xData(dataLenght);
//  vector<double> yData(dataLenght);
  
  double massAverage;
  int fractalSize = cgrMatrix->nRows(); 
  
  for (int radius = minR, index = 0; radius <= maxR; ++radius, ++index)
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
    xData.at(index) = (q - 1) * log(radius / fractalSize);
    yData.at(index) = log(massAverage);
  }
  
  Linear * linear = new Linear(dataLenght, &xData, &yData);
  
  return linear->getSlope();
}

void SandBoxMethod::generateRandomCenters(vector<int> * xCoordinates,
                                          vector<int> * yCoordinates)
{
  int maxNumber = static_cast<int>(cgrMatrix->nRows()) + 1;
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

void SandBoxMethod::generateRandomCenters(vector<double> * xCoordinates,
                                          vector<double> * yCoordinates)
{
  int maxNumber = static_cast<double>(cgrMatrix->nRows()) + 1.0;
//  int maxNumber = 1024;
  for (int i = 0; i < numberOfCenters; ++i)
  {
    xCoordinates->at(i) = RandomTools::
            giveRandomNumberBetweenZeroAndEntry(maxNumber);
    yCoordinates->at(i) = RandomTools::
            giveRandomNumberBetweenZeroAndEntry(maxNumber);
//    cout << "x: " << xCoordinates->at(i) 
//         << "  y: " << yCoordinates->at(i) << endl;
  }
} 

double SandBoxMethod::countSandBoxPoints(const int & x, // col
                                         const int & y, // row
                                         const int & radius)
{
  double sum = 0.0;
  
  if (radius > 1) 
  {
    int minValue = 0;
    int maxValue = cgrMatrix->nRows() - 1;
    int half = floor(radius / 2);
    int initRow = y - half;
    int initCol = x - half;
    int endRow = initRow + radius - 1;
    int endCol = initCol + radius - 1;
    
    if (initRow < minValue) initRow = 0;
    if (initCol < minValue) initCol = 0;
    
    if (endCol > maxValue) endCol = maxValue;
    if (endRow > maxValue) endRow = maxValue;
    
    for (int row = initRow; row <= endRow; ++row)
    {
      for (int col = initCol; col <= endCol; ++col)
      {
        sum = sum + (*cgrMatrix)(row, col);
      }
    }
  }
  else{
    sum += (*cgrMatrix)(y, x);
  }
  
  return sum;
}

bool SandBoxMethod::xCoordinateLessThan(const QPointF & x1, const QPointF & x2)
{
  return x1.x() < x2.x();
}

bool SandBoxMethod::yCoordinateLessThan(const QPointF & y1, const QPointF & y2)
{
  return y1.y() < y2.y();
}

double SandBoxMethod::countSandBoxPoints(const double & x, // col
                                         const double & y, // row
                                         const double & radius)
{
  double sum = 0.0;
  
  double minX = x - radius;
  double maxX = x + radius;
  double minY = y - radius;
  double maxY = y + radius;
  
  qSort(coordinatesOfPoints.begin(), coordinatesOfPoints.end(), 
        SandBoxMethod::xCoordinateLessThan);
  
  
  
  return sum;
}

// Accessors
int SandBoxMethod::getMinQ()
{
  return minQ;
}

void SandBoxMethod::setMinQ(int minQ)
{
  this->minQ = minQ;
}

int SandBoxMethod::getMaxQ()
{
  return maxQ;
}

void SandBoxMethod::setMaxQ(int maxQ)
{
  this->maxQ = maxQ;
}

int SandBoxMethod::getMinR()
{
  return minR;
}

void SandBoxMethod::setMinR(int minR)
{
  this->minR = minR;
}

int SandBoxMethod::getMaxR()
{
  return maxR;
}

void SandBoxMethod::setMaxR(int maxR)
{
  this->maxR = maxR;
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


//int SandBoxMethod::getFractalSize()
//{
//  return fractalSize;
//}

//void SandBoxMethod::setFractalSize(int fractalSize)
//{
//  this->fractalSize = fractalSize;
//}

QList<vector<double> > * SandBoxMethod::getLinearRegressionValues()
{
  return linearRegressionValues;
}

void SandBoxMethod::setLinearRegressionValues(QList<vector<double> > * 
                                              linearRegressionValues)
{
  this->linearRegressionValues = linearRegressionValues;
}


const QList<QPointF> SandBoxMethod::getCoordinatesOfPoints() const
{
  return coordinatesOfPoints;
}

void SandBoxMethod::setCoordinatesOfPoints(const QList<QPointF> & 
                                           coordinatesOfPoints)
{
  this->coordinatesOfPoints = coordinatesOfPoints;
}

