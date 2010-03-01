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
//#define DEBUG_MODE

#include <utils/Trace.h>

#include "CorrelationAnalysis.h"

CorrelationAnalysis::CorrelationAnalysis()
{
  this->correlationElements = QList<const CorrelationElement *>();
  this->nMeshFrames         = 0;
  this->distances           = QList<double>();
  this->tree                = 0;
//  this->treeTemplate        = 0;
}

CorrelationAnalysis::CorrelationAnalysis(const 
                                         QList<const CorrelationElement *> &
                                         correlationElements,
                                         const int & nMeshFrames)
{
  this->correlationElements = correlationElements;
  this->nMeshFrames         = nMeshFrames;
  this->distances           = QList<double>();
  this->tree                = 0;
//  this->treeTemplate        = 0;
}

CorrelationAnalysis::CorrelationAnalysis(const CorrelationAnalysis & 
                                         correlationAnalysisObject)
{
  this->correlationElements = correlationAnalysisObject.correlationElements;
  this->nMeshFrames         = correlationAnalysisObject.nMeshFrames;
  this->distances           = correlationAnalysisObject.distances;
//  this->tree                = correlationAnalysisObject.tree->clone();
  this->tree                = correlationAnalysisObject.tree;
//  this->treeTemplate        = correlationAnalysisObject.treeTemplate->clone();
  
}

CorrelationAnalysis & CorrelationAnalysis::operator=(const CorrelationAnalysis & 
                                                     correlationAnalysisObject)
{
  this->correlationElements = correlationAnalysisObject.correlationElements;
  this->nMeshFrames         = correlationAnalysisObject.nMeshFrames;
  this->distances           = correlationAnalysisObject.distances;
//  this->tree                = correlationAnalysisObject.tree->clone();
  this->tree                = correlationAnalysisObject.tree;
//  this->treeTemplate        = correlationAnalysisObject.treeTemplate->clone();
  
  return *this;
}

CorrelationAnalysis::~CorrelationAnalysis()
{
  if (tree)
    tree = 0;
  
//  if (treeTemplate)
//    treeTemplate = 0;
}

/*
QList<double> CorrelationAnalysis::performAnalysis()
{
  if (distances.isEmpty()) {
    QList<double> covariances = calculateCovariances();
    QList<double> correlCoefficients = 
            calculateCorrelationCoefficients(variances, covariances);
    distances = calculateDistances(correlCoefficients);
    makePhylogeneticTree();
  }
  
  return distances;
}
*/

void CorrelationAnalysis::performAnalysis()
{
  if (distances.isEmpty()) {
    QList<double> covariances = calculateCovariances();
    QList<double> correlCoefficients = 
            calculateCorrelationCoefficients(/*variances,*/ covariances);
    distances = calculateDistances(correlCoefficients);
    makePhylogeneticTree();
  }
}

/*QList<double> CorrelationAnalysis::calculateAverages()
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
//    cout << correlationElements.at(i)->getVariance() << " "; 
    matrix = 0;
  }
  
  return variances;
}*/

QList<double> CorrelationAnalysis::calculateCovariances()
{
  QList<double> covariances;
  int nElements = correlationElements.count();
  const RowMatrix<int> * matrixA = 0;
  const RowMatrix<int> * matrixB = 0;
  double averageA = 0.0;
  double averageB = 0.0;
  
  for (int i = 0; i < nElements; ++i) {
    matrixA  = correlationElements.at(i)->getDistanceMatrix();
    averageA = correlationElements.at(i)->getAverage();
    
    for (int j = i + 1; j < nElements; ++j) {
      matrixB  = correlationElements.at(j)->getDistanceMatrix();
      averageB = correlationElements.at(j)->getAverage();
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
                                                      covariances)
{
  QList<double> correlCoefficients;
  int nElements = correlationElements.count();
  double varianceA    = 0.0;
  double varianceB    = 0.0;
  double covarianceAB = 0.0;
  int index = 0;
  
  for (int i = 0; i < nElements; ++i) {
    varianceA  = correlationElements.at(i)->getVariance();
    
    for (int j = i + 1; j < nElements; ++j) {
      varianceB  = correlationElements.at(j)->getVariance();
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

void CorrelationAnalysis::makePhylogeneticTree()
{
  int nElements = correlationElements.count();
  vector<string> names(nElements);
  
  for (int i = 0; i < nElements; ++i) {
    names.at(i) = QString("Seq_%1").arg(i+1).toStdString();  
  }
  
  DistanceMatrix * matrix = new DistanceMatrix(names);
  
//  int nDistances = (nElements * (nElements - 1)) / 2;
  int index = 0; 
  double distance = 0.0;
  
  for (int i = 0; i < nElements; ++i) {
    for (int j = 0; j < nElements; ++j) {
      index = offsetOf(i,j);
      distance = 0.0;
      
      if (i != j) 
        distance = distances.at(index);
      
      (*matrix)(i, j) = distance;
    }
  }
  
//  MatrixTools::print(*matrix);
  
//  NeighborJoining nj(*matrix, false, true);
  NeighborJoining nj(*matrix, false, false);
  
  tree = nj.getTree()->clone();
  
//  treeTemplate = new TreeTemplate<Node>(*(nj.getTree()));
  Newick newick;
  newick.write(*tree,"tmp/tree.dnd");
  
  delete matrix;
}

int CorrelationAnalysis::getNumberOfMeshFrames() const
{
  return nMeshFrames;
}

void CorrelationAnalysis::setNumberOfMeshFrames(int nMeshFrames)
{
  this->nMeshFrames = nMeshFrames;
}

QList<const CorrelationElement *> 
CorrelationAnalysis::getCorrelationElements() const
{
  return correlationElements;
}

void 
CorrelationAnalysis::setCorrelationElements(const 
                                            QList<const CorrelationElement *> & 
                                            correlationElements)
{
  this->correlationElements = correlationElements;
}

QList<double> CorrelationAnalysis::getDistances() const
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

Tree * CorrelationAnalysis::getTree() const
{
  return tree;
}

//TreeTemplate<Node> * CorrelationAnalysis::getTreeTemplate() const
//{
//  return treeTemplate;
//}

//void CorrelationAnalysis::setTreeTemplate(TreeTemplate<Node> * treeTemplate)
//{
//  this->treeTemplate = treeTemplate;
//}

