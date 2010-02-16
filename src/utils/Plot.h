/**
 * @file Plot.h
 * @date 22/01/2010
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  Plot.h
 *   Created on:  22/01/2010
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef PLOT_H_
#define PLOT_H_

#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_data.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_engine.h>
#include <qwt_plot_layout.h>
#include <qwt_legend_item.h>

#include <iostream>

using namespace std;

/**
 * 
 */
class Plot : public QwtPlot 
{
  Q_OBJECT

  public:
    Plot(QWidget *parent = 0);
//    Plot(const QList<QVector<double> > & dataList,
    Plot(const QList<vector<double> *> & dataList,
         const QStringList curveIdentifiers,
         QWidget *parent = 0);
    Plot(const Plot & plotObject);
    Plot & operator=(const Plot & plotObject);
    
    virtual ~Plot();
    
//    QList<QVector<double> > getDataList();
    QList<vector<double> *> getDataList();
    
//    void setDataList(const QList<QVector<double> > & dataList);
    void setDataList(const QList<vector<double> *> & dataList);
    
    QStringList getCurveIdentifiers();
    
    void setCurveIdentifiers(const QStringList & curveIdentifiers);
    
    QList<QColor> getColorList();
    
    void setColorList(QList<QColor> colorList);
    
    QList<QwtSymbol::Style> getSymbolList();
    
    void setSymbolList(QList<QwtSymbol::Style> symbolList);
    
  protected slots:
    void showCurve(QwtPlotItem *item, bool on);
    
  protected:
    virtual void setupCurves() = 0;
    virtual QwtPlotCurve * createCurves(const int & nCurves);
    void setupGeneralConfiguration() ;
    void alignScales() ;
    void initColorList() ;
    void initSymbolList() ;
    void connectSignalsSlots() ;
    
    QList<vector<double> *> dataList;
    QList<QColor> colorList;
    QStringList curveIdentifiers;
    QList<QwtSymbol::Style> symbolList;
    QwtPlotCurve * curves; 

    
};

#endif /* PLOT_H_ */
