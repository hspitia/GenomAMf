/**
 * @file CorrelationAnalysis.h
 * @date 26/11/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  CorrelationAnalysis.h
 *   Created on:  26/11/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef CORRELATIONANALYSIS_H_
#define CORRELATIONANALYSIS_H_

// Bio++ libraries
#include <NumCalc/Matrix.h>
#include <Seq/Sequence.h>

using namespace bpp;

// Project
#include <utils/MatrixOperations.h>
#include <cra/CorrelationElement.h>


/**
 * 
 */
class CorrelationAnalysis
{
  public:
    CorrelationAnalysis();
    CorrelationAnalysis(const QList<const CorrelationElement *> & 
                        correlationElements,
                        const int & nMeshFrames);
    CorrelationAnalysis(const CorrelationAnalysis & correlationAnalysisObject);
    CorrelationAnalysis & operator=(const CorrelationAnalysis & 
                                    correlationAnalysisObject);
    
    virtual ~CorrelationAnalysis();
    
    QList<double> performAnalysis();
    
    QList<const CorrelationElement *> getCorrelationElements() const;
    
    void setCorrelationElements(const QList<const CorrelationElement *> & 
                                correlationElements);
    
    int getNumberOfMeshFrames() const;
    
    void setNumberOfMeshFrames(int nMeshFrames);
    
    QList<double> getDistances() const;
    
    void setDistances(const QList<double> & distances);
    
    bool isEmpty();
    
  private:
    QList<const CorrelationElement *> correlationElements;
    
    int nMeshFrames; /**< Número de cuadros de la malla por fila (o columna).  
      La malla tendrá tamaño nMeshframes x nMeshFrames */
     
    QList<double> distances;
    
    QList<double> calculateAverages();
    
    QList<double> calculateVariances(const QList<double> & averages);
    
//    QList<double> calculateCovariances(const QList<double> & averages);
    QList<double> calculateCovariances();
    
    QList<double> calculateCorrelationCoefficients(/*const QList<double> & 
                                                   variances,*/
                                                   const QList<double> & 
                                                   covariances);
    
    QList<double> calculateDistances(const QList<double> & correlCoefficients);
    
};

#endif /* CORRELATIONANALYSIS_H_ */
