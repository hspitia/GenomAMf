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

//#include <QPainter>
//#include <QImage>
//#include <QRgb>
//
//
//#include <app/AppController.h>
//#include <gui/MainWindow.h>
//#include <cgr/ChaosGameRepresentation.h>
//#include <mfa/SandBoxMethod.h>
//
//#include <utils/Utils.h>

// The SeqLib library:
//#include <Seq/Alphabet.h>
//#include <Seq/AlphabetTools.h>
//#include <Seq/DNA.h>
//#include <Seq/Sequence.h>
//#include <Seq/VectorSequenceContainer.h>
//
//
//#include <NumCalc/VectorTools.h>
//#include <NumCalc/Matrix.h>
//#include <NumCalc/MatrixTools.h>

#include <QtCore/QList>
#include <QtCore/QString>

//STL library
#include <vector>
#include <iostream>


using namespace std;

//MathGl Library
#include <mgl/mgl_data.h>
#include <mgl/mgl_zb.h>
#include <mgl/mgl_font.h>
#include <mgl/mgl_qt.h>

/**
 * 
 */
class Plotter : public mglDraw
{
  public:
    enum plotType {Linear_Plot, Dq_Plot, Cq_Plot};
    
    Plotter(const QList<vector<double> > * dataList, plotType type);
    Plotter(const QList<QList<vector<double> > > * dataList, 
            plotType type = Linear_Plot);
    virtual ~Plotter();
    
    int Draw(mglGraph * gr);
    void plot0(mglGraph * gr);
    void plot1(mglGraph * gr);
    
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
    
  private:
    const QList<vector<double> > * dataListNormal;
    const QList<QList<vector<double> > > * dataListLinearReg;
    plotType type;
    QString title; /**< Título del gráfico */
    QString xLabel; /**< Etiqueta para el eje x */
    QString yLabel; /**< Etiqueta para el eje y */
    QString zLabel; /**< Etiqueta para el eje z */
    
    QStringList legends; /**< Lista de cadenas correspondientes a las leyendas 
      de los gráficos */
    
    void configure(mglGraph * gr);
    void plotLinearRegression(mglGraph * gr);
    void plotNormalData(mglGraph * gr);
};

#endif /* PLOTTERCLASS_H_ */
