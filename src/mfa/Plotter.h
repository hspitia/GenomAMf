/**
 * @file Plotter.h
 * @date 21/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  Plotter.h
 *   Created on:  21/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef PLOTTERCLASS_H_
#define PLOTTERCLASS_H_

// Qt library
#include <QtCore/QList>
#include <QtCore/QString>

// STL library
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// MathGl Library
#include <mgl/mgl_data.h>
#include <mgl/mgl_zb.h>
#include <mgl/mgl_font.h>
#include <mgl/mgl_qt.h>

// NumCalc Library
#include <NumCalc/Matrix.h>

using namespace bpp;

// Project library
#include <utils/Utils.h>

/**
 * 
 */
class Plotter : public mglDraw
{
  public:
    enum plotType {Linear_Plot, Dq_Plot, Cq_Plot, Measures_Plot, Test_Plot};
    /*
    Plotter(const QList<vector<double> > * dataList, plotType type);
    Plotter(const QList<QList<vector<double> > > * dataList, 
            plotType type = Linear_Plot);
    Plotter(const QList<RowMatrix<int> * > * dataListMatrix, 
            plotType type = Measures_Plot);
    */
    Plotter(plotType type);
    Plotter(const QList<vector<double> *> & dataList, plotType type);
    Plotter(const QList<QList<vector<double> *> > & dataList, 
            plotType type = Linear_Plot);
    Plotter(const QList<const RowMatrix<int> * > & dataListMatrix, 
            plotType type = Measures_Plot);
    
    virtual ~Plotter();
    
    int Draw(mglGraph * gr);
    void plot0(mglGraph * gr);
//    void plot1(mglGraph * gr);
    
    /**
     * Asigna 
     */
    void setTitle(QString title);

    /**
     * Asigna 
     */
    void setXLabel(QString xLabel);

    /**
     * Asigna 
     */
    void setYLabel(QString yLabel);
    
    /**
     * Asigna 
     */
    void setZLabel(QString zLabel);

    /**
     * Retorna 
     * @return 
     */
    QStringList getLegends();
    
    /**
     * Asigna 
     */
    void setLegends(QStringList legends);
    
    int getRowsOfPlot();
    
    void setRowsOfPlot(const int & rowsOfPlot);
    
  private:
    /*
    const QList<vector<double> > * dataListNormal;
    const QList<QList<vector<double> > > * dataListLinearReg;
    const QList<RowMatrix<int> * > * dataListMatrix;
    */
    QList<vector<double> *> dataListNormal;
    QList<QList<vector<double> *> > dataListLinearReg;
    QList<const RowMatrix<int> * >  dataListMatrix;
    
    plotType type;
    QString title; /**< Título del gráfico */
    QString xLabel; /**< Etiqueta para el eje x */
    QString yLabel; /**< Etiqueta para el eje y */
    QString zLabel; /**< Etiqueta para el eje z */
    
    QStringList legends; /**< Lista de cadenas correspondientes a las leyendas 
      de los gráficos */
    
    int rowsOfPlot;
    
    void plotLinearRegression(mglGraph * gr);
    void plotNormalData(mglGraph * gr);
    void plotNormalData_(mglGraph * gr);
    void plotMeasures(mglGraph * gr);
    void setLabels(mglGraph *gr);
    void setTitle(mglGraph *gr);
    void setTicks(mglGraph *gr);
};

#endif /* PLOTTERCLASS_H_ */
