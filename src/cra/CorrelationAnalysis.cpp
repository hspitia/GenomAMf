/**
 * @file CorrelationAnalysis.cpp
 * @date 26/11/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  CorrelationAnalysis.cpp
 *   Created on:  26/11/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "CorrelationAnalysis.h"

CorrelationAnalysis::CorrelationAnalysis()
{
  this->correlationElements = QList<const CorrelationElement *>();
  this->nMeshFrames         = 0;
  this->distances           = QList<double>();
}

CorrelationAnalysis::CorrelationAnalysis(const 
                                         QList<const CorrelationElement *> &
                                         correlationElements,
                                         const int & nMeshFrames)
{
  this->correlationElements = correlationElements;
  this->nMeshFrames         = nMeshFrames;
  this->distances           = QList<double>();
}

CorrelationAnalysis::CorrelationAnalysis(const CorrelationAnalysis & 
                                         correlationAnalysisObject)
{
  this->correlationElements = correlationAnalysisObject.correlationElements;
  this->nMeshFrames         = correlationAnalysisObject.nMeshFrames;
  this->distances           = correlationAnalysisObject.distances;
}

CorrelationAnalysis & CorrelationAnalysis::operator=(const CorrelationAnalysis & 
                                                     correlationAnalysisObject)
{
  this->correlationElements = correlationAnalysisObject.correlationElements;
  this->nMeshFrames         = correlationAnalysisObject.nMeshFrames;
  this->distances           = correlationAnalysisObject.distances;
  
  return *this;
}

CorrelationAnalysis::~CorrelationAnalysis()
{
  
}

QList<double> CorrelationAnalysis::performAnalysis()
{
  if (distances.isEmpty()) {
    QList<double> averages  = calculateAverages();
    
    MatrixTools::print(averages.toVector().toStdVector());
//    QList<double> variances = calculateVariances(averages);
//    QList<double> covariances = calculateCovariances(averages);
//    QList<double> correlCoefficients = 
//            calculateCorrelationCoefficients(variances, covariances);
//    distances = calculateDistances(correlCoefficients);
  }
  
  return distances;
}

QList<double> CorrelationAnalysis::calculateAverages()
{
  QList<double> averages;
  const RowMatrix<int> * matrix = 0;
  for (int i = 0; i < correlationElements.count(); ++i) {
    matrix = correlationElements.at(i)->getDistanceMatrix();
    double average = MatrixOperations::average<int>(*matrix);
    averages.append(average);
    matrix = 0;
  }
  
  return averages;
}

QList<double> 
CorrelationAnalysis::calculateVariances(const QList<double> & averages)
{
  QList<double> variances;
  const RowMatrix<int> * matrix = 0;
  double average = 0.0;
  
  for (int i = 0; i < averages.count(); ++i) {
    matrix = correlationElements.at(i)->getDistanceMatrix();
    average = averages.at(i);
    double variance = MatrixOperations::variance<int>(*matrix, average);
    variances.append(variance);
    matrix = 0;
  }
  
  return variances;
}

QList<double> 
CorrelationAnalysis::calculateCovariances(const QList<double> & averages)
{
  QList<double> covariances;
  int nElements = correlationElements.count();
  const RowMatrix<int> * matrixA = 0;
  const RowMatrix<int> * matrixB = 0;
  double averageA = 0.0;
  double averageB = 0.0;
  
  for (int i = 0; i < nElements; ++i) {
    matrixA  = correlationElements.at(i)->getDistanceMatrix();
    averageA = averages.at(i);
    
    for (int j = i + 1; j < nElements; ++j) {
      matrixB  = correlationElements.at(j)->getDistanceMatrix();
      averageB = averages.at(j);
      double covariance = 
              MatrixOperations::covariance<int>(*matrixA, *matrixB,
                                                averageA, averageB);
      covariances.append(covariance);
    }
    matrixA = 0;
    matrixB = 0;
  }
  
  return covariances;
}


QList<double> 
CorrelationAnalysis::calculateCorrelationCoefficients(const QList<double> & 
                                                      variances,
                                                      const QList<double> & 
                                                      covariances)
{
  QList<double> correlCoefficients;
  int nElements = correlationElements.count();
  double varianceA    = 0.0;
  double varianceB    = 0.0;
  double covarianceAB = 0.0;
  int index = 0;
  
  for (int i = 0; i < nElements; ++i) {
    varianceA  = variances.at(i);
    
    for (int j = i + 1; j < nElements; ++j) {
      varianceB = variances.at(j);
      covarianceAB = covariances.at(index);
      double correlCoefficient = covarianceAB / (varianceA * varianceB);
      correlCoefficients.append(correlCoefficient);
      ++index;
    }
  }
  
  return correlCoefficients;
}

QList<double> CorrelationAnalysis::calculateDistances(const QList<double> & 
                                                      correlCoefficients)
{
  QList<double> dists;
  int nElements = correlCoefficients.count();
  double correlCoefficient = 0.0;
  
  for (int i = 0; i < nElements; ++i) {
    correlCoefficient = correlCoefficients.at(i);
    double distance = (1.0 - correlCoefficient) / 2.0;
    dists.append(distance);
  }
  
  return dists;
}

int CorrelationAnalysis::getNumberOfMeshFrames()
{
  return nMeshFrames;
}

void CorrelationAnalysis::setNumberOfMeshFrames(int nMeshFrames)
{
  this->nMeshFrames = nMeshFrames;
}

QList<const CorrelationElement *> CorrelationAnalysis::getCorrelationElements() const
{
  return correlationElements;
}

void 
CorrelationAnalysis::setCorrelationElements(const QList<const CorrelationElement *> & 
                                            correlationElements)
{
  this->correlationElements = correlationElements;
}

QList<double> CorrelationAnalysis::getDistances()
{
  return distances;
}

void CorrelationAnalysis::setDistances(const QList<double> & distances)
{
  this->distances = distances;
}

bool CorrelationAnalysis::isEmpty()
{
  bool isEmpty = correlationElements.isEmpty() && 
                 nMeshFrames == 0 &&
                 distances.isEmpty();
          
  return isEmpty;
}
