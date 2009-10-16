/**
 * @file MultifractalAnalisys.h
 * @date 13/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MultifractalAnalisys.h
 *   Created on:  13/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef MULTIFRACTALANALISYS_H_
#define MULTIFRACTALANALISYS_H_

// SYSTEM INCLUDES
// Std - STL 
#include <iostream>
#include <vector>

using namespace std;

// Qt libraries
#include <QtCore/QList>
#include <QtCore/QString>

// Bio++ libraries
// --

//using namespace bpp;

// PROJECT INCLUDES
#include <cgr/ChaosGameRepresentation.h>
#include <mfa/SandBoxMethod.h>

// LOCAL INCLUDES
// --


/**
 * 
 */
class MultifractalAnalisys
{
  public:
    MultifractalAnalisys();
    MultifractalAnalisys(const MultifractalAnalisys & mfaObject);
    MultifractalAnalisys(const ChaosGameRepresentation * cgrObject,
                         const int & qMin,
                         const int & qMax);
    
    virtual ~MultifractalAnalisys();
    
    MultifractalAnalisys & operator=(const MultifractalAnalisys & mfaObject);
    
    /**
     * 
     */
    void performAnalisys();

    /**
     * 
     */
    void calculateCqValues();

    /**
     * 
     */
    void calculateTqValues();
    
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
    const ChaosGameRepresentation * getCgrObject() const;

    /**
     * Asigna 
     */
    void setCgrObject(ChaosGameRepresentation * cgrObject);
    
    /**
     * Retorna 
     * @return 
     */
    QString getLinearRegressionImagePath();
    
    /**
     * Retorna 
     * @return 
     */
    QString getDqSpectraImagePath();

    /**
     * Retorna 
     * @return 
     */
    QString getCqImagePath();

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
    QList<vector<double> > * getDqValues();
    
    /**
     * Asigna 
     */
    void setDqValues(QList<vector<double> > * dqValues);

    /**
     * Retorna 
     * @return 
     */
    QList<vector<double> > * getCqValues();
    
    /**
     * Asigna 
     */
    void setCqValues(QList<vector<double> > * cqValues);

    /**
     * Retorna 
     * @return 
     */
    QList<vector<double> > * getTqValues();
    
    /**
     * Asigna 
     */
    void setTqValues(QList<vector<double> > * tqValues);
    
  private:
    const ChaosGameRepresentation * cgrObject; /**< Apuntador al objeto 
      ChaosGameRepresentation sobre el que se realiza el 
      análisis multifractal */
    
    int qMin; /**< Valor para el parámetro q mínimo */
    
    int qMax; /**< Valor para el parámetro q máximo */
    
    QString linearRegressionImgePath; /**< Ruta a la imagen
      correspondiente a la regresión lineal */
   
    QString dqSpectraImagePath; /**< Ruta a la imagen correspondiente al 
      espectro Dq */
    
    QString cqImagePath; /**< Ruta a la imagen correspondiente al 
      gráfico Dq */

    QList<vector<double> > * linearRegressionValues; /**< Contenedor de los 
      valores de la regresión lineal */
    
    QList<vector<double> > * dqValues; /**< Contenedor de los valores Dq vs q */
    
    QList<vector<double> > * cqValues; /**< contenedor de los valores Cq vs q */

    QList<vector<double> > * tqValues; /**< Contenedor para valores tau q */
    
    /**
     * 
     */
    QString plotResults(const QList <vector <double> > & values);
    
};

#endif /* MULTIFRACTALANALISYS_H_ */
