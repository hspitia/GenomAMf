/**
 * @file ChaosGameRepresentation.h
 * @date 28/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief
 */

/*
 *         File:  ChaosGameRepresentation.h
 *   Created on:  28/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:
 */

#ifndef CHAOSGAMEREPRESENTATION_H_
#define CHAOSGAMEREPRESENTATION_H_

// SYSTEM INCLUDES
//Qt Libraries
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtCore/QPointF>
#include <QtCore/QDir>

// STL libraries
#include <string>
#include <vector>

// Bio++ libraries
#include <NumCalc/Matrix.h>
#include <NumCalc/MatrixTools.h>
#include <Seq/Alphabet.h>
#include <Seq/AlphabetTools.h>
#include <Seq/DNA.h>
#include <Seq/ProteicAlphabet.h>
#include <Seq/SequenceTools.h>
#include <Seq/VectorSequenceContainer.h>
#include <Utils/Exceptions.h>


using namespace bpp;

// PROJECT INCLUDES
#include <utils/Utils.h>


using namespace utils;

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
    ChaosGameRepresentation(const Sequence * sequence);
    ChaosGameRepresentation(const ChaosGameRepresentation & cgrObject);
    ChaosGameRepresentation & operator=(const 
                                        ChaosGameRepresentation & cgrObject);
    virtual ~ChaosGameRepresentation();
    
    /**
     * 
     */
    void performRepresentation(const int & cgrSize = 512,
                               const int & matrixSize = 1024,
                               const bool & generateImage = true);
    
    void performRepresentation1(int cgrSize = 512, bool generateImage = true);
    
    /**
     * Retorna 
     * @return 
     */
    const Sequence * getSequence() const;

    /**
     * Asigna 
     */
    void setSequence(const Sequence * sequence);

    /**
     * Retorna
     * @return
     */

    const RowMatrix<int> * getMatrixOfPoints() const;

    /**
     * Asigna
     */
    void setMatrixOfPoints(RowMatrix<int> matrixOfPoints);
    
    /**
     * Retorna 
     * @return 
     */
    string getImageFilePath() const;
    
    /**
     * Asigna 
     */
    void setImageFilePath(string imagefilePath);
    
    /**
     * Retorna 
     * @return 
     */
    vector <int> getTranslatedSequence();

    /**
     * Asigna 
     */
    void setTranslatedSequence(vector<int> translatedSequence);
   
    /**
     * Retorna 
     * @return 
     */
    const QList<QPointF> * getCoordinatesOfPoints() const;
    
    const RowMatrix<int> * getCumulativeFrequencyMatrix() const;
    
    int getTotalNonzeroCells();
    
  private:
    const Sequence * sequence; /**< Apuntador a la secuencia de la cual se 
      obtendrá la GRC */
    
    RowMatrix<int> matrixOfPoints; /**< Matriz de enteros que almacena los 
      puntos de la CGR */
    
    string imagefilePath; /**< Ruta del archivo de imagen generado de la CGR */
    
    vector<int> translatedSequence; /**< Secuencia traducida al alfabeto 
      {0, 1, 2, 3} de acuerdo al modelo HP extendido para lograr la CGR. 
      Aplica solo para secuencias de proteínas. */
    
    QList<QPointF> * coordinatesOfPoints; /**< Lista de coordenadas de los 
      puntos de la CGR */
    
    RowMatrix<int> cumulativeFrequencyMatrix; /**< Matriz de frecuencias 
      acumuladas de puntos de la CGR */
    
    int totalNonzeroCells; /**< Número de celdas en la matriz cuyo valor es 
      distinto de 0 */

    void translateSequence();
    
    void drawBoxAndLabels(QPainter * painter, const int & cgrSize,
                         int alphabetType);
    
    void calculateCumulativeFrequency();
};

#endif /* CHAOSGAMEREPRESENTATION_H_ */
