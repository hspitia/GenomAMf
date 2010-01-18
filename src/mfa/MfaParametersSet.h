/**
 * @file MfaParametersSet.h
 * @date 18/01/2010
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MfaParametersSet.h
 *   Created on:  18/01/2010
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef MFAPARAMETERSSET_H_
#define MFAPARAMETERSSET_H_

#include <QtCore/QString>
#include <QtCore/QObject>

/**
 * 
 */
class MfaParametersSet
{
  public:
    MfaParametersSet();
    MfaParametersSet(const MfaParametersSet & mfaParametersSetObject);
    MfaParametersSet & operator=(const MfaParametersSet & 
                                 mfaParametersSetObject);
    virtual ~MfaParametersSet();
    
    int getMinQ() const;
    
    void setMinQ(const int & minQ);

    int getMaxQ() const;
    
    void setMaxQ(const int &  maxQ);

    int getMinR() const;
    
    void setMinR(const int &  rMin);

    int getMaxR() const;
    
    void setMaxR(const int &  maxR);

    int getRadiusStep() const;
    
    void setRadiusStep(const int & radiusStep);

    int getNCenters() const;
    
    void setNCenters(const int &  nCenters);
    
    int getNIterations() const;
    
    void setNIterations(const int & nIterations);
    
    QString toString() const;
    
  private:
    int minQ; /**< Valor para el parámetro q mínimo */
    
    int maxQ; /**< Valor para el parámetro q máximo */
    
    int minR; /**< Valor del radio mínimo de las cajas de arena */
    
    int maxR; /**< Valor del radio máximo de las cajas de arena */
    
    int radiusStep;  /**< Salto en pixeles entre cada magnitud de radio a 
      ser explorado */ 
    
    int nCenters; /**< Número de centros de caja de arena que serán ser 
      generados aleatoriamente */
    
    int nIterations;
    
};

#endif /* MFAPARAMETERSSET_H_ */
