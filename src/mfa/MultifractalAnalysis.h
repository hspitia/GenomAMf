/**
 * @file MultifractalAnalysis.h
 * @date 13/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MultifractalAnalysis.h
 *   Created on:  13/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef MULTIFRACTALANALYSIS_H_
#define MULTIFRACTALANALYSIS_H_

// SYSTEM INCLUDES
// Std - STL 
#include <iostream>
#include <vector>

using namespace std;

// Qt libraries
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QtAlgorithms>

// Bio++ libraries
// --

//using namespace bpp;

// PROJECT INCLUDES
#include <cgr/ChaosGameRepresentation.h>
#include <mfa/SandBoxMethod.h>
#include <mfa/MfaParametersSet.h>

// LOCAL INCLUDES
// --


/**
 * 
 */
class MultifractalAnalysis
{
  public:
    enum AnalysisType {CONTINOUS_ANALYSIS, DISCRETE_ANALYSIS, COMPARATIVE_ANALYSIS};
    
    MultifractalAnalysis();

    MultifractalAnalysis(const ChaosGameRepresentation * cgrObject,
                         const MfaParametersSet & mfaParametersSet);
    
    MultifractalAnalysis(const MultifractalAnalysis & mfaObject);
    
    MultifractalAnalysis & operator=(const MultifractalAnalysis & mfaObject);
    
    virtual ~MultifractalAnalysis();
    
    
    void performAnalysis(AnalysisType type);
    
    
    void performComparativeAnalysis();

    
    void calculateDqValues(AnalysisType type);

    
    void calculateTqValues();

    
    void calculateCqValues();
    
    
    MfaParametersSet getMfaParametersSet() const;
    
    void setMfaParametersSet(const MfaParametersSet & mfaParametersSet);
    
    int getMinQ() const;
    
    
    void setMinQ(int minQ);

    
    int getMaxQ() const;
    
    
    void setMaxQ(int qMax);
    
    
    const ChaosGameRepresentation * getCgrObject() const;

    
    void setCgrObject(ChaosGameRepresentation * cgrObject);
    
    
    QString getLinearRegressionImagePath();
    
    
    QString getDqSpectraImagePath();

    
    QString getCqImagePath();

    QList<vector<double> *> getLinearRegressionValues() const;
    
    vector<double> * getDqValues() const;
    
    vector<double> * getCqValues() const;
    
    vector<double> * getTqValues() const;
    
    vector<double> * getQValues() const;
    
    int getNCenters();
    
    int getRadiusStep();
    
    void setRadiusStep(const int & radiusStep);
    
    vector<double> * getLinearRegressionParameters();
    
    vector<int> * getQValuesForLinearRegression();
    
    void setQValuesForLinearRegression(vector<int> * qValuesForLinearRegression);
    
  private:
    const ChaosGameRepresentation * cgrObject; /**< Apuntador al objeto 
    ChaosGameRepresentation sobre el que se realiza el 
      análisis multifractal */
    
    MfaParametersSet mfaParametersSet;
    
    QString linearRegressionImgePath; /**< Ruta a la imagen
      correspondiente a la regresión lineal */
    
    QString dqSpectraImagePath; /**< Ruta a la imagen correspondiente al 
      espectro Dq */
    
    QString cqImagePath; /**< Ruta a la imagen correspondiente al 
      gráfico Dq */
    
    QList<vector<double> *> linearRegressionValues; /**< Contenedor de los 
      valores de la regresión lineal */
    
    vector<double> * dqValues; /**< Contenedor de los valores Dq  */
    
    vector<double> * cqValues; /**< contenedor de los valores Cq */
    
    vector<double> * tqValues; /**< Contenedor para valores tau q */
    
    vector<double> * linearRegressionParameters; /**< Parámetros adicionales 
      calculados en la regresión lineal: pendiente e intercepto */
    
    vector<int> * qValuesForLinearRegression;
};

#endif /* MULTIFRACTALANALYSIS_H_ */
