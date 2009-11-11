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
#include <QtCore/QtAlgorithms>

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
    enum AnalisysType {CONTINOUS_ANALISYS, DISCRETE_ANALISYS};
    
    MultifractalAnalisys();
    MultifractalAnalisys(const MultifractalAnalisys & mfaObject);
    MultifractalAnalisys(const ChaosGameRepresentation * cgrObject,
                         const int & minQ,
                         const int & qMax);
    
    virtual ~MultifractalAnalisys();
    
    MultifractalAnalisys & operator=(const MultifractalAnalisys & mfaObject);
    
    /**
     * 
     */
    void performAnalisys(AnalisysType type);
    
    void performContinousAnalisys();
    
    void performDiscreteAnalisys();

    /**
     * 
     */
    void calculateCqValues();

    /**
     * 
     */
    void calculateTqValues();
    
    
    int getMinQ();
    
    
    void setMinQ(int minQ);

    
    int getMaxQ();
    
    
    void setMaxQ(int qMax);
    
    
    const ChaosGameRepresentation * getCgrObject() const;

    
    void setCgrObject(ChaosGameRepresentation * cgrObject);
    
    
    QString getLinearRegressionImagePath();
    
    
    QString getDqSpectraImagePath();

    
    QString getCqImagePath();

    
    QList<vector<double> > * getLinearRegressionValues();
    
    
    void setLinearRegressionValues(QList<vector<double> > * 
                                   linearRegressionValues);

    
    QList<vector<double> > * getDqValues();
    
    
    void setDqValues(QList<vector<double> > * dqValues);

    
    QList<vector<double> > * getCqValues();
    
    
    void setCqValues(QList<vector<double> > * cqValues);

    
    QList<vector<double> > * getTqValues();
    
    
    void setTqValues(QList<vector<double> > * tqValues);
    
  private:
    const ChaosGameRepresentation * cgrObject; /**< Apuntador al objeto 
      ChaosGameRepresentation sobre el que se realiza el 
      an�lisis multifractal */
    
    int minQ; /**< Valor para el par�metro q m�nimo */
    
    int maxQ; /**< Valor para el par�metro q m�ximo */
    
    QString linearRegressionImgePath; /**< Ruta a la imagen
      correspondiente a la regresi�n lineal */
   
    QString dqSpectraImagePath; /**< Ruta a la imagen correspondiente al 
      espectro Dq */
    
    QString cqImagePath; /**< Ruta a la imagen correspondiente al 
      gr�fico Dq */

    QList<vector<double> > * linearRegressionValues; /**< Contenedor de los 
      valores de la regresi�n lineal */
    
    QList<vector<double> > * dqValues; /**< Contenedor de los valores Dq vs q */
    
    QList<vector<double> > * cqValues; /**< contenedor de los valores Cq vs q */

    QList<vector<double> > * tqValues; /**< Contenedor para valores tau q */
    
    /**
     * 
     */
    QString plotResults(const QList <vector <double> > & values);
    
};

#endif /* MULTIFRACTALANALISYS_H_ */
