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
#include <QtCore/QPointF>
#include <QtCore/QString>

// Bio++ libraries
#include <NumCalc/Matrix.h>
#include <NumCalc/RandomTools.h>

using namespace bpp;

// PROJECT INCLUDES
#include <cgr/ChaosGameRepresentation.h>
#include <mfa/MultifractalAnalisys.h>
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
//                  const int & fractalSize,
                  const int & minQ     = -100,
                  const int & maxQ     =  100,
                  const int & nCenters =   50);
    
    SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                  const QList<QPointF> & coordinatesOfPoints,
//                  const int & fractalSize,
                  const int & minQ     = -100,
                  const int & maxQ     =  100,
                  const int & nCenters =   50);
    
    SandBoxMethod & operator=( const SandBoxMethod & sandBoxObject);
    
    virtual ~SandBoxMethod();
    
    /**
     * 
     */
    void performAnalisys(int type);
    
    void performContinousAnalisys();
    
    void performDiscreteAnalisys();

    /**
     * 
     */
    double calculateDqValue(const int & q, vector<double> & xData,
                            vector<double> & yData);

    /**
     * 
     */
    void generateRandomCenters(vector<int> * xCoordinates,
                               vector<int> * yCoordinates);
    /**
     * 
     */
    void generateRandomCenters(vector<double> * xCoordinates,
                               vector<double> * yCoordinates);
    
    /**
     * 
     */
    double countPointsOnTheSquareSandbox(const int & x, 
                                         const int & y, 
                                         const int & radius);
    
    /**
     * 
     */
    double countPointsOnTheSquareSandbox(const double & x, 
                                         const double & y, 
                                         const double & radius);
    
    /**
     * Retorna 
     * @return 
     */
    int getMinQ();
    
    /**
     * Asigna 
     */
    void setMinQ(int minQ);

    /**
     * Retorna 
     * @return 
     */
    int getMaxQ();
    
    /**
     * Asigna 
     */
    void setMaxQ(int maxQ);

    /**
     * Retorna 
     * @return 
     */
    int getMinR();
    
    /**
     * Asigna 
     */
    void setMinR(int rMin);

    /**
     * Retorna 
     * @return 
     */
    int getMaxR();
    
    /**
     * Asigna 
     */
    void setMaxR(int maxR);

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
    int getNCenters();
    
    /**
     * Asigna 
     */
    void setNCenters(int nCenters);

    /**
     * Retorna 
     * @return 
     */
    QList<vector<double> > * getDqValues();
    
    /**
     * Asigna 
     */
    void setDqValues(QList<vector<double> > * dqValues);

//    /**
//     * Retorna 
//     * @return 
//     */
//    int getFractalSize();
//    
//    /**
//     * Asigna 
//     */
//    void setFractalSize(int fractalSize);
    
    /**
     * Retorna 
     * @return 
     */
    QList<vector<double> > * getLinearRegressionValues();
    
    /**
     * Asigna
     */
    void setLinearRegressionValues(QList<vector<double> > * 
                                   linearRegressionValues);
    
    /**
     * Retorna 
     * @return 
     */
//    const QList<QPointF> * getCoordinatesOfPoints() const;
    const QList<QPointF> getCoordinatesOfPoints() const;
    
    /**
     * Asigna 
     */
    void setCoordinatesOfPoints(const QList<QPointF> & coordinatesOfPoints);
    
  private:
    int minQ; /**< Valor para el par�metro q m�nimo */

    int maxQ; /**< Valor para el par�metro q m�ximo */
    
    int minR; /**< Valor del radio m�nimo de las cajas de arena */
    
    int maxR; /**< Valor del radio m�ximo de las cajas de arena */
    
    const RowMatrix<int> * cgrMatrix; /**< Apuntador a la matriz de puntos 
      obtenida de la representaci�n de juego del caos*/

    QList<QPointF> coordinatesOfPoints; /**< Apuntador a la lista de 
      coordenadas de puntos obtenida de la representaci�n de juego del caos*/
    
    int nCenters; /**< N�mero de centros de caja de arena por cada 
      medida de radio a ser generados aleatoriamente */

    QList<vector<double> > * dqValues; /**< Contenedor para los valores 
      Dq vs q */ 
    
    QList<vector<double> > * linearRegressionValues; /**< Contenedor de los 
      valores de la regresi�n lineal */
   
//    int fractalSize; /**< Longitud lineal del fractal */
   /* 
    bool xCoordinateLessThan(const QPointF & x1, const QPointF & x2);
    
    bool yCoordinateLessThan(const QPointF & y1, const QPointF & y2);
    */
    
    
};

#endif /* SANDBOXMETHOD_H_ */
