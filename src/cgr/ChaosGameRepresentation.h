/**
 * @file ChaosGameRepresentation.h
 * @date 28/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief
 */

/*
 *         File:  ChaosGameRepresentation.h
 *   Created on:  28/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:
 */

#ifndef CHAOSGAMEREPRESENTATION_H_
#define CHAOSGAMEREPRESENTATION_H_

// SYSTEM INCLUDES
// Std libraries
#include <string>
#include <vector>

// Bio++ libraries
#include <NumCalc/Matrix.h>
#include <NumCalc/MatrixTools.h>
#include <Seq/Alphabet.h>
#include <Seq/AlphabetTools.h>
#include <Seq/DNA.h>
#include <Seq/ProteicAlphabet.h>
#include <Seq/VectorSequenceContainer.h>
#include <Utils/Exceptions.h>


using namespace bpp;

// PROJECT INCLUDES
#include <utils/Utils.h>

// LOCAL INCLUDES
// --

// Cyclic reference


/**
 *
 */
class ChaosGameRepresentation
{
  public:
    ChaosGameRepresentation();
    virtual ~ChaosGameRepresentation();

    /**
     * Retorna
     * @return
     */

    RowMatrix <int> getMatrixOfPoints();

    /**
     * Asigna
     */
    void setMatrixOfPoints(RowMatrix <int> matrixOfPoints);
    
    /**
     * Retorna 
     * @return 
     */
    string getImageFilePath();
    
    /**
     * Asigna 
     */
    void setImageFilePath(string imagefilePath);
    
  private:

    RowMatrix<int> matrixOfPoints; /**< Matriz de enteros que almacena los puntos 
      de la CGR */
    string imagefilePath; /**< Ruta del archivo de imagen generado para la 
      CGR */
};

#endif /* CHAOSGAMEREPRESENTATION_H_ */
