/**
 * @file SandBoxMethod.h
 * @date 15/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  SandBoxMethod.h
 *   Created on:  15/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef SANDBOXMETHOD_H_
#define SANDBOXMETHOD_H_

// SYSTEM INCLUDES
// Std - STL 
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Qt libraries
#include <QtCore/QList>
#include <QtCore/QString>

// Bio++ libraries
#include <NumCalc/Matrix.h>
#include <NumCalc/RandomTools.h>

using namespace bpp;

// PROJECT INCLUDES
#include <cgr/ChaosGameRepresentation.h>
#include <utils/Linear.h>


// LOCAL INCLUDES
// --

/**
 * 
 */
class SandBoxMethod
{
  public:
    SandBoxMethod();
    SandBoxMethod(const SandBoxMethod & sandBoxObject);
    SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                  const int & qMin = -100,
                  const int & qMax =  100);
    SandBoxMethod & operator=( const SandBoxMethod & sandBoxObject);
    virtual ~SandBoxMethod();
    
    /**
     * 
     */
    void performAnalisys();

    /**
     * 
     */
    double calculateDqValue(const int & q);

    /**
     * 
     */
    void generateRandomCenters(vector<int> * xCoordinates,
                               vector<int> * yCoordinates);
    
    /**
     * 
     */
    double countSandBoxPoints(const int & x, const int & y, const int & radius);
    
    /**
     * Retorna 
     * @return 
     */
    int getQMin();
    
    /**
     * Asigna 
     */
    void setQMin(int qMin);

    /**
     * Retorna 
     * @return 
     */
    int getQMax();
    
    /**
     * Asigna 
     */
    void setQMax(int qMax);

    /**
     * Retorna 
     * @return 
     */
    int getRMin();
    
    /**
     * Asigna 
     */
    void setRMin(int rMin);

    /**
     * Retorna 
     * @return 
     */
    int getRMax();
    
    /**
     * Asigna 
     */
    void setRMax(int rMax);

    /**
     * Retorna 
     * @return 
     */
    const RowMatrix<int> * getCgrMatrix() const;
    
    /**
     * Asigna 
     */
    void setCgrMatrix(const RowMatrix<int> * cgrMatrix);

    /**
     * Retorna 
     * @return 
     */
    int getNumberOfCenters();
    
    /**
     * Asigna 
     */
    void setNumberOfCenters(int numberOfCenters);

    /**
     * Retorna 
     * @return 
     */
    QList<vector<double> > * getDqValues();
    
    /**
     * Asigna 
     */
    void setDqValues(QList<vector<double> > * dqValues);

    /**
     * Retorna 
     * @return 
     */
    int getFractalSize();
    
    /**
     * Asigna 
     */
    void setFractalSize(int fractalSize);
    
  private:
    int qMin; /**< Valor para el parámetro q mínimo */

    int qMax; /**< Valor para el parámetro q máximo */
    
    int rMin; /**< Valor del radio mínimo de las cajas de arena */
    
    int rMax; /**< Valor del radio máximo de las cajas de arena */
    
    const RowMatrix<int> * cgrMatrix; /**< Apuntador a la matriz de puntos 
      obtenida de la representación de juego del caos*/

    int numberOfCenters; /**< Número de centros de caja de arena por cada 
      medida de radio a ser generados aleatoriamente */

    QList<vector<double> > * dqValues; /**< Contenedor para los valores 
      Dq vs q */
    
    int fractalSize; /**< Longitud lineal del fractal */
};

#endif /* SANDBOXMETHOD_H_ */
