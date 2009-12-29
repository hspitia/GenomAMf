/**
 * @file CorrelationElement.cpp
 * @date 25/12/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  CorrelationElement.cpp
 *   Created on:  25/12/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */
//#define DEBUG_MODE

#include "CorrelationElement.h"
#include <utils/Trace.h>


CorrelationElement::CorrelationElement()
{
  this->cgrObject                = 0;
  this->distanceMatrix           = RowMatrix<int>();
  this->nMeshFrames              = 0;
  this->symbolicSequence         = 0;
  this->distanceMatrixCalculated = false;
  this->average                  = 0.0;

}
CorrelationElement::CorrelationElement(const ChaosGameRepresentation * 
                                       cgrObject,
                                       const int & nMeshFrames)
{
  this->cgrObject                = cgrObject;
  this->distanceMatrix           = RowMatrix<int>();
  this->nMeshFrames              = nMeshFrames;
  this->symbolicSequence         = 0;
  this->distanceMatrixCalculated = false;
  this->average                  = 0.0;
  calculateDistanceMatrix();
  calculateAverage();
  calculateVariance();
}
CorrelationElement::CorrelationElement(const CorrelationElement & 
                                       correlationElementObject)
{
  this->cgrObject                = correlationElementObject.cgrObject;
  this->distanceMatrix           = correlationElementObject.distanceMatrix;
  this->nMeshFrames              = correlationElementObject.nMeshFrames;
  this->symbolicSequence         = correlationElementObject.symbolicSequence;
  this->distanceMatrixCalculated = 
          correlationElementObject.distanceMatrixCalculated;
  this->average                  = correlationElementObject.average;
}

CorrelationElement & CorrelationElement::operator=(const CorrelationElement & 
                                                     correlationElementObject)
{
  this->cgrObject                = correlationElementObject.cgrObject;
  this->distanceMatrix           = correlationElementObject.distanceMatrix;
  this->nMeshFrames              = correlationElementObject.nMeshFrames;
  this->symbolicSequence         = correlationElementObject.symbolicSequence;
  this->distanceMatrixCalculated = 
          correlationElementObject.distanceMatrixCalculated;
  this->average                  = correlationElementObject.average;
  
  return *this;
}
CorrelationElement::~CorrelationElement()
{
  if (cgrObject)
    cgrObject = 0;
  
  if (symbolicSequence)
    delete symbolicSequence;
  
  symbolicSequence = 0;
  
}

void CorrelationElement::calculateDistanceMatrix()
{
  if (!distanceMatrixCalculated) {
    symbolicSequence = generateSymbolicSequence();
    ChaosGameRepresentation * symbolicCgr = 
            new ChaosGameRepresentation(symbolicSequence);
    symbolicCgr->performRepresentation(512, 512, true);
//    symbolicCgr->performRepresentation(256, 20, true); // AppController::155
    
    RowMatrix<int> * measureMatrix     = calculateMuMeasures(cgrObject);
    RowMatrix<int> * fractalBackground = calculateMuMeasures(symbolicCgr);
    int size = cgrObject->getMatrixOfPoints()->getNumberOfRows();
     
    MatrixOperations::normalize<int>(*measureMatrix);
    MatrixOperations::normalize<int>(*fractalBackground);
    
//    RowMatrix<int> * measureMatrix = new RowMatrix<int>(size, size);   
//    MatrixOperations::normalize<int>(*(cgrObject->getMatrixOfPoints()),
//                                     *measureMatrix);
//    RowMatrix<int> * fractalBackground = new RowMatrix<int>(size, size);
//    MatrixOperations::normalize<int>(*(symbolicCgr->getMatrixOfPoints()),
//                                     *fractalBackground);
    
    distanceMatrix = RowMatrix<int>(size, size);
    MatrixOperations::sub<int>((*measureMatrix), (*fractalBackground),
                              distanceMatrix);

    TRACE(__LINE__ << "\n\t" << "distanceMatrix:");
//    MatrixTools::print(distanceMatrix);
    TRACE(__LINE__ << "\n\t" << "Sumatorias:");
    DEBUG( "measureMatrix    : " << MatrixOperations::sum<int>(*measureMatrix) );
    DEBUG( "fractalBackground: " << MatrixOperations::sum<int>(*fractalBackground) );
    distanceMatrixCalculated = true;
  }
}


Sequence * CorrelationElement::generateSymbolicSequence_()
{
  Sequence * sequenceOut = 0;
  const Sequence * originalSequence = cgrObject->getSequence();
  unsigned int sequenceLenght =  originalSequence->size();
  int maxNumber = 4; // Por defecto: secuencia de nucleótidos
  int sequenceType = utils::getAlphabetType(originalSequence->getAlphabet()->
                                            getAlphabetType());
  
  if (sequenceType == GenomAMf::Proteic_Alphabet)
    maxNumber = 21;
  
  vector<int> sequenceContent(sequenceLenght);
  
  for (unsigned int i = 0; i < sequenceLenght; ++i) {
    sequenceContent.at(i) = 
            RandomTools::giveIntRandomNumberBetweenZeroAndEntry(maxNumber) ;
  }
  
  if (sequenceType == GenomAMf::Proteic_Alphabet) {
    sequenceOut = new Sequence("Symbolic Sequence", sequenceContent, 
                               new ProteicAlphabet());
    return sequenceOut;
  }
  
  sequenceOut = new Sequence("Symbolic Sequence", sequenceContent, new DNA());
  
//  DEBUG(originalSequence->toString());
//  DEBUG(sequenceOut->toString());
  
  return sequenceOut;
}

Sequence * CorrelationElement::generateSymbolicSequence()
{
  Sequence * sequenceOut = 0;
  const Sequence * originalSequence = cgrObject->getSequence();
  unsigned int sequenceLenght =  originalSequence->size();
  
  int sequenceType = utils::getAlphabetType(originalSequence->getAlphabet()->
                                            getAlphabetType());
  
  int maxNumber = 4; // Por defecto: secuencia de nucleótidos
  
  if (sequenceType == GenomAMf::Proteic_Alphabet)
    maxNumber = 21;
  
  vector<int> sequenceContent(sequenceLenght);
  
  int element  = 0;
  int newIndex = 0;
  
  for (unsigned int i = 0; i < sequenceLenght; ++i) {
    element = originalSequence->getValue(i);
    newIndex = RandomTools::
            giveIntRandomNumberBetweenZeroAndEntry(sequenceLenght);
    sequenceContent.at(newIndex) = element; 
  }
  
  if (sequenceType == GenomAMf::Proteic_Alphabet) {
    sequenceOut = new Sequence("Symbolic Sequence", sequenceContent, 
                               new ProteicAlphabet());
    return sequenceOut;
  }
  
  sequenceOut = new Sequence("Symbolic Sequence", sequenceContent, new DNA());
  
  DEBUG(originalSequence->toString());
  DEBUG(sequenceOut->toString());
  
  return sequenceOut;
}

RowMatrix<int> * 
CorrelationElement::calculateMuMeasures(const ChaosGameRepresentation * 
                                        cgrObject)
{
  RowMatrix<int> * muMeasuresMatrix = 0;
  const RowMatrix<int> * cgrMatrix = cgrObject->getMatrixOfPoints();
  
  int size = nMeshFrames + 1;
  int rows = static_cast<int>(cgrMatrix->getNumberOfRows());
  
  if (size < rows) {
    cout<< "\nENTRO A DIVISION EN MESH" << endl;
    muMeasuresMatrix = new RowMatrix<int>(size, size);
    int frameSize = static_cast<int>(rows / size);
    
    int initRow = 0;
    int endRow  = 0;
    int initCol = 0;
    int endCol  = 0;
    int sum     = 0;
            
    for (int i = 0; i < nMeshFrames; ++i) {
      initRow = i * frameSize;
      endRow  = initRow + frameSize;
      
      for (int j = 0; j < nMeshFrames; ++j) {
        initCol = j * frameSize;
        endCol  = initCol + frameSize;
        sum   = 0;
        
        for (int row = initRow; row < endRow; ++row) {
          for (int col = initCol; col < endCol; ++col) {
            sum += (*cgrMatrix)(row, col);
          }
        }
        
        (*muMeasuresMatrix)(i, j) = sum;
      }
    }
  }
  else {
    if (size > rows)
      size = rows;
      
    muMeasuresMatrix = new RowMatrix<int>(*cgrMatrix);
  }
  
  return muMeasuresMatrix;
}

void CorrelationElement::calculateAverage()
{
  if (distanceMatrixCalculated)
    average = MatrixOperations::average<int>(distanceMatrix);
}

void CorrelationElement::calculateVariance()
{
  if (distanceMatrixCalculated && average != 0.0)
    variance = MatrixOperations::variance<int>(distanceMatrix, average);
}

const ChaosGameRepresentation * CorrelationElement::getCgrObject() const
{
  return cgrObject;
}

void CorrelationElement::setCgrObject(const ChaosGameRepresentation * cgrObject)
{
  this->cgrObject = cgrObject;
}

const RowMatrix<int> * CorrelationElement::getDistanceMatrix() const
{
  if (!distanceMatrixCalculated)
    const_cast<CorrelationElement *>(this)->calculateDistanceMatrix();
  
  return &distanceMatrix;
}

int CorrelationElement::getNumberOfMeshFrames() const
{
  return nMeshFrames;
}

void CorrelationElement::setNumberOfMeshFrames(int nMeshFrames)
{
  this->nMeshFrames = nMeshFrames;
}

const Sequence * CorrelationElement::getSymbolicSequence() const
{
  return symbolicSequence;
}

double CorrelationElement::getAverage() const
{
  return average;
}

double CorrelationElement::getVariance() const
{
  return variance;
}
