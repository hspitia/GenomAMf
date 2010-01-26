/**
 * @file NormalPlot.h
 * @date 22/01/2010
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  NormalPlot.h
 *   Created on:  22/01/2010
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef NORMALPLOT_H_
#define NORMALPLOT_H_

#include <utils/Plot.h>
#include <NumCalc/MatrixTools.h>

using namespace bpp;

#include <algorithm>

using namespace std;


/**
 * 
 */
class NormalPlot : public Plot
{
  public:
//    NormalPlot(const QList<QVector<double> > & dataList,
    NormalPlot(const QList<vector<double> > & dataList,
               const QStringList & curveIdentifiers,
               QWidget *parent = 0);
    
    NormalPlot(const NormalPlot & dqPlotObject);
    NormalPlot & operator=(const NormalPlot & dqPlotObject);
    
    virtual ~NormalPlot();
    
    void setupCurves();
    
  private:
    
};

#endif /* NORMALPLOT_H_ */
