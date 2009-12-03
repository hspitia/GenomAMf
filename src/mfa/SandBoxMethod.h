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
#include <iomanip>
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
#include <mfa/MultifractalAnalysis.h>
#include <utils/Linear.h>
#include <utils/Utils.h>


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
                  const int & minQ     = -20,
                  const int & maxQ     =  20,
                  const int & nCenters = 300);
    
    SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                  const QList<QPointF> & coordinatesOfPoints,
//                  const int & fractalSize,
                  const int & minQ     = -20,
                  const int & maxQ     =  20,
                  const int & nCenters = 300);
    
    SandBoxMethod & operator=( const SandBoxMethod & sandBoxObject);
    
    virtual ~SandBoxMethod();
    
    
    void performAnalysis(int type);
    
    void performContinousAnalysis();
    
    void performDiscreteAnalysis();
    
    void performComparativeAnalysis();

    
    double calculateContinousDqValue(const int & q, vector<double> & xData,
                                     vector<double> & yData);
    
    double calculateDiscreteDqValue(const int & q, vector<double> & xData,
                                    vector<double> & yData);

    
    void generateRandomCenters(vector<int> * xCoordinates,
                               vector<int> * yCoordinates);
    
    void generateRandomCenters(vector<double> * xCoordinates,
                               vector<double> * yCoordinates);
    
    
    double countPointsOnTheDiscreteSquareSandbox(const int & x, 
                                                 const int & y, 
                                                 const int & radius);
    
    
    double countPointsOnTheContinousSquareSandbox(const double & x, 
                                                  const double & y, 
                                                  const double & radius);
    
    
    int getMinQ();
    
    
    void setMinQ(int minQ);

    
    int getMaxQ();
    
    
    void setMaxQ(int maxQ);

    
    int getMinR();
    
    
    void setMinR(int rMin);

    
    int getMaxR();
    
    
    void setMaxR(int maxR);

    
    const RowMatrix<int> * getCgrMatrix() const;
    
    
    void setCgrMatrix(const RowMatrix<int> * cgrMatrix);

    
    int getNCenters();
    
    
    void setNCenters(int nCenters);

    
//    QList<vector<double> > * getDqValues();
    vector<double> * getDqValues();
    
    
    QList<vector<double> *> getLinearRegressionValues();
    
//    const QList<QPointF> * getCoordinatesOfPoints() const;
    const QList<QPointF> getCoordinatesOfPoints() const;
    
    
    void setCoordinatesOfPoints(const QList<QPointF> & coordinatesOfPoints);
    
  private:
    int minQ; /**< Valor para el parámetro q mínimo */

    int maxQ; /**< Valor para el parámetro q máximo */
    
    int minR; /**< Valor del radio mínimo de las cajas de arena */
    
    int maxR; /**< Valor del radio máximo de las cajas de arena */
    
    const RowMatrix<int> * cgrMatrix; /**< Apuntador a la matriz de puntos 
      obtenida de la representación de juego del caos*/

    QList<QPointF> coordinatesOfPoints; /**< Apuntador a la lista de 
      coordenadas de puntos obtenida de la representación de juego del caos*/
    
    int nCenters; /**< Número de centros de caja de arena por cada 
      medida de radio a ser generados aleatoriamente */

//    QList<vector<double> > * dqValues; /**< Contenedor para los valores 
//      Dq vs q */ 
    vector<double> * dqValues; /**< Contenedor para los valores 
      Dq vs q */ 
    
//    QList<vector<double> > * linearRegressionValues; /**< Contenedor de los 
//      valores de la regresión lineal */
    QList<vector<double> *> linearRegressionValues; /**< Contenedor de los 
      valores de la regresión lineal */
   
//    int fractalSize; /**< Longitud lineal del fractal */
   /* 
    bool xCoordinateLessThan(const QPointF & x1, const QPointF & x2);
    
    bool yCoordinateLessThan(const QPointF & y1, const QPointF & y2);
    */
    
    
};

#endif /* SANDBOXMETHOD_H_ */
