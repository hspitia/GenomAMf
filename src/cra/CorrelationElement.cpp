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

#include "CorrelationElement.h"

CorrelationElement::CorrelationElement()
{
  this->cgrObject         = 0;
  this->distanceMatrix    = RowMatrix<int>();
  this->nMeshFrames       = 0;
  this->symbolicSequence  = 0;
  this->distanceMatrixCalculated = false;

}
CorrelationElement::CorrelationElement(const ChaosGameRepresentation * 
                                         cgrObject,
                                         const int & nMeshFrames)
{
  this->cgrObject         = cgrObject;
  this->distanceMatrix    = RowMatrix<int>();
  this->nMeshFrames       = nMeshFrames;
  this->symbolicSequence  = 0;
  this->distanceMatrixCalculated = false;
}
CorrelationElement::CorrelationElement(const CorrelationElement & 
                                         correlationElementObject)
{
  this->cgrObject         = correlationElementObject.cgrObject;
  this->distanceMatrix    = correlationElementObject.distanceMatrix;
  this->nMeshFrames       = correlationElementObject.nMeshFrames;
  this->symbolicSequence  = correlationElementObject.symbolicSequence;
  this->distanceMatrixCalculated = 
          correlationElementObject.distanceMatrixCalculated;
}

CorrelationElement & CorrelationElement::operator=(const CorrelationElement & 
                                                     correlationElementObject)
{
  this->cgrObject         = correlationElementObject.cgrObject;
  this->distanceMatrix    = correlationElementObject.distanceMatrix;
  this->nMeshFrames       = correlationElementObject.nMeshFrames;
  this->symbolicSequence  = correlationElementObject.symbolicSequence;
  this->distanceMatrixCalculated = 
          correlationElementObject.distanceMatrixCalculated;
  
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
    
    RowMatrix<int> * measureMatrix     = calculateMuMeasures(cgrObject);
    RowMatrix<int> * fractalBackground = calculateMuMeasures(symbolicCgr);
    
    MatrixOperations::sub<int>((*measureMatrix), (*fractalBackground),
                              distanceMatrix);
    
    distanceMatrixCalculated = true;
  }
}


Sequence * CorrelationElement::generateSymbolicSequence()
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
    sequenceOut = new Sequence("Symbolic Secuence", sequenceContent, 
                               new ProteicAlphabet());
    return sequenceOut;
  }
  
  sequenceOut = new Sequence("Symbolic Secuence", sequenceContent, new DNA());
  
  return sequenceOut;
}

RowMatrix<int> * 
CorrelationElement::calculateMuMeasures(const ChaosGameRepresentation * 
                                         cgrObject)
{
  RowMatrix<int> * muMeasuresMatrix = 0;
  const RowMatrix<int> * cgrMatrix = cgrObject->getMatrixOfPoints();
  
  int rows = static_cast<int>(cgrMatrix->getNumberOfRows());
  
  if (nMeshFrames < rows) {
    muMeasuresMatrix = new RowMatrix<int>(nMeshFrames, nMeshFrames);
    int frameSize = static_cast<int>(rows / nMeshFrames);
    
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
    if (nMeshFrames > rows)
      nMeshFrames = rows;
      
    muMeasuresMatrix = new RowMatrix<int>(*cgrMatrix);
  }
  
  return muMeasuresMatrix;
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
