/**
 * @file CorrelationElement.h
 * @date 25/12/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  CorrelationElement.h
 *   Created on:  25/12/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef CORRELATIONELEMENT_H_
#define CORRELATIONELEMENT_H_

// Bio++ libraries
#include <NumCalc/Matrix.h>
#include <Seq/Sequence.h>



using namespace bpp;

// Project
#include <cgr/ChaosGameRepresentation.h>
#include <utils/MatrixOperations.h>

/**
 * 
 */
class CorrelationElement
{
  public:
    // Constructors
    CorrelationElement();
    CorrelationElement(const ChaosGameRepresentation * cgrObject,
                        const int & nMeshFrames);
    CorrelationElement(const CorrelationElement & distanceInformationObject);
    CorrelationElement & operator=(const CorrelationElement & 
                                    distanceInformationObject);
    
    // Destructor
    virtual ~CorrelationElement();
    
    // Methods
    void calculateDistanceMatrix();
    
    // Access
    const ChaosGameRepresentation * getCgrObject() const;
    
    void setCgrObject(const ChaosGameRepresentation * cgrObject);
    
    int getNumberOfMeshFrames() const;
    
    void setNumberOfMeshFrames(int nMeshFrames);
    
    const RowMatrix<int> * getDistanceMatrix() const;
    
    const Sequence * getSymbolicSequence() const;
    
  private:
    const ChaosGameRepresentation * cgrObject;
    
    RowMatrix<int> distanceMatrix;
    
    int nMeshFrames; /**< Número de cuadros de la malla por fila (o columna).  
      La malla tendrá tamaño nMeshframes x nMeshFrames */
    
    bool distanceMatrixCalculated;
    
    Sequence * symbolicSequence;

    // Methods
    
    
    Sequence * generateSymbolicSequence();
    
    RowMatrix<int> * calculateMuMeasures(const ChaosGameRepresentation * 
                                         cgrObject);
    
};

#endif /* CORRELATIONELEMENT_H_ */
