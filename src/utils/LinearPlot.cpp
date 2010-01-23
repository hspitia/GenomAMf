/**
 * @file LinearPlot.cpp
 * @date 22/01/2010
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  LinearPlot.cpp
 *   Created on:  22/01/2010
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "LinearPlot.h"

LinearPlot::LinearPlot(QWidget *parent) : 
  Plot(parent)
{
  setupCurves();

}

LinearPlot::LinearPlot(const LinearPlot & dqPlotObject) :
  Plot(dqPlotObject)
{
  
}

LinearPlot & LinearPlot::operator=(const LinearPlot & dqPlotObject)
{
  return *this;
}

void LinearPlot::setupCurves()
{
  // Insert new curves
  QwtPlotCurve *cSin = new QwtPlotCurve("y = sin(x)");
  cSin->setRenderHint(QwtPlotItem::RenderAntialiased);
  cSin->setPen(QPen(Qt::red));
  cSin->setCurveAttribute(QwtPlotCurve::Fitted);
  cSin->attach(this);
  
  QwtPlotCurve *cCos = new QwtPlotCurve("y = cos(x)");
  cCos->setRenderHint(QwtPlotItem::RenderAntialiased);
  cCos->setPen(QPen(Qt::blue));
  cCos->attach(this);
  
//  // Create sin and cos data
  const int nPoints = 360;
  double xSinVal[nPoints];
  double ySinVal[nPoints];
  double xCosVal[nPoints];
  double yCosVal[nPoints];
  double pi = 3.1416;
  
  for (int i = 0; i < nPoints; i++) {
    xSinVal[i] = ((double)i * pi) / 180;
    ySinVal[i] = sin(xSinVal[i]);
    xCosVal[i] = ((double)i * pi) / 180;
    yCosVal[i] = cos(xCosVal[i]);
  }
  
//  //Isert data
  cSin->setData(xSinVal, ySinVal, nPoints);
  cCos->setData(xSinVal, yCosVal, nPoints);
}

LinearPlot::~LinearPlot()
{
  // TODO Auto-generated destructor stub
}
