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
  // TODO Auto-generated constructor stub
  
}

CorrelationAnalysis::~CorrelationAnalysis()
{
  // TODO Auto-generated destructor stub
}

int CorrelationAnalysis::getNumberOfMeshFrames()
{
  return nMeshFrames;
}

void CorrelationAnalysis::setNumberOfMeshFrames(int nMeshFrames)
{
  this->nMeshFrames = nMeshFrames;
}

int CorrelationAnalysis::getSequenceLength()
{
  return sequenceLength;
}

void CorrelationAnalysis::setSequenceLength(int sequenceLength)
{
  this->sequenceLength = sequenceLength;
}

const RowMatrix<int> * CorrelationAnalysis::getCgrMatrix()
{
  return cgrMatrix;
}

void CorrelationAnalysis::setCgrMatrix(const RowMatrix<int> * cgrMatrix)
{
  this->cgrMatrix = cgrMatrix;
}


const RowMatrix<double> * CorrelationAnalysis::getMeasuresMatrix() const
{
  return measuresMatrix;
}

const RowMatrix<double> * CorrelationAnalysis::getFractalBackgroundMatrix() const
{
  return fractalBackgroundMatrix;
}


