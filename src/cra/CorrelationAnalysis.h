/**
 * @file CorrelationAnalysis.h
 * @date 26/11/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  CorrelationAnalysis.h
 *   Created on:  26/11/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef CORRELATIONANALYSIS_H_
#define CORRELATIONANALYSIS_H_

// Bio++ libraries
#include <NumCalc/Matrix.h>
#include <Seq/Sequence.h>

#include <utils/MatrixOperations.h>


/**
 * 
 */
class CorrelationAnalysis
{
  public:
    CorrelationAnalysis();
    virtual ~CorrelationAnalysis();
    
    int getNumberOfMeshFrames();
    
    void setNumberOfMeshFrames(int nMeshFrames);
    
    int getSequenceLength();
    
    void setSequenceLength(int sequenceLength);
    
    const RowMatrix<int> * getCgrMatrix();
    
    void setCgrMatrix(const RowMatrix<int> * cgrMatrix);
    
    const RowMatrix<double> * getMeasuresMatrix() const;
    
    const RowMatrix<double> * getFractalBackgroundMatrix() const;
    
  private:
    int nMeshFrames; /**< Número de cuadros de la malla por fila (o columna).  
      La malla tendrá tamaño nMeshframes x nMeshFrames */
    
    int sequenceLength; /**< longitud de la secuencia bajo análisis */
    
    const RowMatrix<int> * cgrMatrix; /**< Apuntador a la matriz de puntos 
      obtenida de la representación de juego del caos*/
    
    RowMatrix<double> measuresMatrix; /**< Matriz de medidas mu de la secuencia */
    
    RowMatrix<double> fractalBackgroundMatrix; /**< Matriz de base fractal de 
      la matriz de medidas mu*/
    
    
    
    
    
};

#endif /* CORRELATIONANALYSIS_H_ */
