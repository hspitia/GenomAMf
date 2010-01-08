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
                  const RowMatrix<int> * cumulativeFrequencyMatrix,
                  const int & totalPoints,
                  const int & minQ         = -20,
                  const int & maxQ         =  20,
                  const int & nCenters     = 300,
                  const int & radiusStep   =   2);
    
    SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                  const RowMatrix<int> * cumulativeFrequencyMatrix,
                  const QList<QPointF> & fractalPoints,
                  const int & minQ       = -20,
                  const int & maxQ       =  20,
                  const int & nCenters   =  300,
                  const int & radiusStep =    16); //aqui TODO - cambio - step
    
    SandBoxMethod & operator=( const SandBoxMethod & sandBoxObject);
    
    virtual ~SandBoxMethod();
    
    
    void performAnalysis(int type);
    
    void performContinousAnalysis();
    
    void performDiscreteAnalysis();
    void performDiscreteAnalysis_();
    
    void performComparativeAnalysis();

    
    double calculateContinousDqValue(const double & q, vector<double> & xData,
                                     vector<double> & yData);
    
    void calculateDiscreteDqValues(QList<vector<double> > * 
                                     distributionsList,
                                     vector<double> & xData,
                                     vector<double> & yData);
    
    
    double calculateDiscreteDqValue_(const double & q,
                                     QList<vector<double> > * 
                                     distributionsList,
                                     vector<double> &
                                     sizeRelations,
                                     vector<double> & 
                                     xDataLinearRegression,
                                     vector<double> & 
                                     yDataLinearRegression);
    
    double calculateDiscreteDqValue(const double & q, vector<double> & xData,
                                    vector<double> & yData);

    void generateRandomCenters();
    
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
    
//    const QList<QPointF> * getFractalPoints() const;
    const QList<QPointF> getFractalPoints() const;
    
    
    void setFractalPoints(const QList<QPointF> & fractalPoints);
    
    int getTotalPoints();
    
    QList<int> getIndexesOfCenters();
    
    void setIndexesOfCenters(QList<int> indexesOfCenters);
    
    int getRadiusStep();
    
    void setRadiusStep(const int & radiusStep);
    
  private:
    int minQ; /**< Valor para el parámetro q mínimo */

    int maxQ; /**< Valor para el parámetro q máximo */
    
    int minR; /**< Valor del radio mínimo de las cajas de arena */
    
    int maxR; /**< Valor del radio máximo de las cajas de arena */
    
    int totalPoints; /**< Número total de puntos del fractal */
    
    int radiusStep;
    
    const RowMatrix<int> * cgrMatrix; /**< Apuntador a la matriz de puntos 
      obtenida de la representación de juego del caos*/
    
    const RowMatrix<int> * cumulativeFrequencyMatrix; /**< Apuntador a la matriz 
      de frecuencias acumuladas de puntos obtenida de la representación de 
      juego del caos*/

    QList<QPointF> fractalPoints; /**< Lista de coordenadas de puntos 
      obtenida de la representación de juego del caos*/
    
    int nCenters; /**< Número de centros de caja de arena que serán ser 
      generados aleatoriamente */
    
    QList<int> indexesOfCenters; /**< Listado de índices de los puntos 
      correspondientes a los centros generados aleatoriamente */
    
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
    
    
    QList<vector<double> > * calculateDistributionProbabilities(vector<double> & 
                                                                xData);
    
};

#endif /* SANDBOXMETHOD_H_ */
