/**
 * @file LinearPlot.h
 * @date 22/01/2010
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  LinearPlot.h
 *   Created on:  22/01/2010
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef LINEARPLOT_H_
#define LINEARPLOT_H_

#include <utils/Plot.h>

/**
 * 
 */
class LinearPlot : public Plot
{
  public:
    LinearPlot(const QList<vector<double> *> & dataList,
                       const QStringList curveIdentifiers,
                       const QList<vector<double> *> & linearParameters,
                       QWidget *parent = 0);
    
    LinearPlot(const LinearPlot & linearPlotObject);
    LinearPlot & operator=(const LinearPlot & linearPlotObject);
    
    virtual ~LinearPlot();
    
    QwtPlotCurve * createCurves(const int & nCurves);
    
    void setupCurves();
    
    QList<vector<double> *> getLinearParameters();
    
    void setLinearParameters(const QList<vector<double> *> & linearParameters);
    
  private:
    QList<vector<double> *> linearParameters;
    
    QwtPlotCurve * linearFitCurves;
    
    QwtPlotCurve * createLinearFitCurves(const int & nCurves);
};

#endif /* LINEARPLOT_H_ */
