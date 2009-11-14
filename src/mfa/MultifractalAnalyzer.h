/**
 * @file MultifractalAnalyzer.h
 * @date 11/11/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MultifractalAnalyzer.h
 *   Created on:  11/11/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef MULTIFRACTALANALYZER_H_
#define MULTIFRACTALANALYZER_H_

//QT Libraries
#include <QtCore/QList>

//Project
#include <cgr/ChaosGameRepresentation.h>
#include <mfa/MultifractalAnalisys.h>
#include <app/AppController.h>

/**
 * @brief Ejecuta el an�lisis multifractal sobre m�ltiples objetos 
 * ChaosGameRepresentation. 
 */
class MultifractalAnalyzer
{
  public:
    MultifractalAnalyzer();

    MultifractalAnalyzer(
//                         const AppController * parentApp,
                         QList<const ChaosGameRepresentation * >  cgrObjects,
                         MultifractalAnalisys::AnalisysType type,
                         const int & minQ     = -70,
                         const int & maxQ     =  70,
                         const int & nCenters =  50,
                         const double & minR  =   1.0,
                         const double & maxR  = 256.0);
    
    
    MultifractalAnalyzer(const MultifractalAnalyzer & multifractalAnalyzerObject);
    
    virtual ~MultifractalAnalyzer();
    
    
    QList<const ChaosGameRepresentation *> getCgrObjects();
    
    
    void setCgrObjects(QList<const ChaosGameRepresentation *>  cgrObjects);

    
    int getMinQ();
    
    
    void setMinQ(int minQ);
    
    
    int getMaxQ();
    
    
    void setMaxQ(int maxQ);
    
    
    int getNCenters();
    
    
    void setNCenters(int nCenters);
    
    
    double getMinR();
    
    
    void setMinR(double minR);
    
    
    QList<MultifractalAnalisys *>  getMfaObjects();
    
    
    void setMfaObjects(QList<MultifractalAnalisys *>  mfaObjects);
    
    double getMaxR();
    
    void setMaxR(double maxR);
    
//    AppController * getParentApp();
    
  private:
    QList<const ChaosGameRepresentation *> cgrObjects; /**< Lista de apuntadores a 
      los objetos CGR sobre los cuales se realizar� el an�lisis multifractal. */
    
    QList<MultifractalAnalisys *> mfaObjects; /**< Lista de apuntadores a los 
      objetos MFA generados al ejecutar el proceso de an�lisis sobre los objetos
      CGR. */
    
    int minQ; /**< Valor para el par�metro q m�nimo */
    
    int maxQ; /**< Valor para el par�metro q m�ximo */
    
    int nCenters; /**< N�mero de centros para el an�lisis multifractal */
    
    double minR; /**< Valor para el par�metro radio m�nimo de las cajas de 
      arena del an�lisis multifractal */
    
    double maxR; /**< Valor para el par�metro radio m�ximo de las cajas de 
      arena del an�lisis multifractal */
    
//    AppController * parentApp; /**< Pauntador al objeto AppController padre. */
    
    MultifractalAnalisys::AnalisysType type;
        
};

#endif /* MULTIFRACTALANALYZER_H_ */
