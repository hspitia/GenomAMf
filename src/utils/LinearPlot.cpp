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

LinearPlot::LinearPlot(const QList<vector<double> > & dataList,
                       const QStringList curveIdentifiers,
                       const QList<vector<double> > & linearParameters,
                       QWidget *parent) : 
  Plot(dataList, curveIdentifiers, parent)
{
  setupCurves();

}

LinearPlot::LinearPlot(const LinearPlot & dqPlotObject) :
  Plot(dqPlotObject)
{
  
}

LinearPlot & LinearPlot::operator=(const LinearPlot & dqPlotObject)
{
  Q_UNUSED(dqPlotObject);
  return *this;
}

QwtPlotCurve * LinearPlot::createCurves(const int & nCurves)
{

  int nColors = colorList.count();
  QwtPlotCurve * tmpCurves = new QwtPlotCurve[nCurves];
  
  if (nCurves > symbolList.count() || nCurves > colorList.count())
    return 0;
  
  for (int i = 0; i < nCurves; ++i) {
    QwtSymbol sym;
    sym.setStyle(symbolList.at(i+1));
    sym.setPen(QPen(QColor(Qt::black)));
    sym.setSize(5);
    QString id = curveIdentifiers.at(index);
    sym.setBrush(colorList.at(j));
    tmpCurves[index].setTitle(id);
    tmpCurves[index].setSymbol(sym);
    QPen pen(colorList.at(j));
    tmpCurves[index].setPen(pen);
    ++index;
    ++j;
  } 
  
  return tmpCurves;
}

void LinearPlot::setupCurves()
{
  int nCurves = dataList.count() - 1;
  curves = createCurves(nCurves);
  int nPoints = dataList.at(0).size();
  
  // Points of plot
  double * xValues = 0;
  double * yValues = 0; 
  
  for (int i = 0; i < nCurves; ++i) {
    xValues = new double[nPoints];
    copy(dataList.at(i).begin(), dataList.at(i).end(), xValues);
    
    yValues = new double[nPoints];
    copy(dataList.at(i).begin(), dataList.at(i).end(), yValues);
    
    curves[i].setData(xValues, yValues, nPoints);
    curves[i].setRenderHint(QwtPlotItem::RenderAntialiased);
    curves[i].setStyle(QwtPlotCurve::NoCurve);
    curves[i].attach(this);
  }
  
  // Linear fit curves
  linearFitCurves = createLinearFitCurves(nCurves);
  
  xValues = 0;
  yValues = 0; 
  
  for (int i = 0; i < nCurves; ++i) {
    xValues = new double[nPoints];
    copy(dataList.at(i).begin(), dataList.at(i).end(), xValues);
    
    yValues = new double[nPoints];
    
    for (int j = 0; j < nPoints; ++j) {
      yValues[i] = (linearParameters.at(i).at(0) * xValues[0]) + 
                    linearParameters.at(i).at(1);
    }
    
    linearFitCurves[i].setData(xValues, yValues, nPoints);
    linearFitCurves[i].setRenderHint(QwtPlotItem::RenderAntialiased);
    linearFitCurves[i].setStyle(QwtPlotCurve::Lines);
    linearFitCurves[i].attach(this);
  }
}

QwtPlotCurve * LinearPlot::createLinearFitCurves(const int & nCurves)
{

  int nColors = colorList.count();
  QwtPlotCurve * tmpCurves = new QwtPlotCurve[nCurves];
  int nSymForAssign = static_cast<int>(ceil(static_cast<double>(nCurves) / 
                                            static_cast<double>(nColors)));
  
  if (nSymForAssign > symbolList.count())
    return 0;
  
  for (int i = 0; i < nSymForAssign; ++i) {
    QwtSymbol sym;
    sym.setStyle(QwtSymbol::NoSymbol);
    
    int index = i * nColors;
    int j = 0;
    while(j < nColors && j < nCurves) {
      QString id = curveIdentifiers.at(index);
      sym.setBrush(colorList.at(j));
      tmpCurves[index].setTitle(id);
      tmpCurves[index].setSymbol(sym);
      QPen pen(colorList.at(j));
      tmpCurves[index].setPen(pen);
      ++index;
      ++j;
    }
  } 
  
  return tmpCurves;
}

LinearPlot::~LinearPlot()
{
  // TODO Auto-generated destructor stub
}

QList<vector<double> > LinearPlot::getLinearParameters()
{
  return linearParameters;
}

void LinearPlot::setLinearParameters(const QList<vector<double> > & linearParameters)
{
  this->linearParameters = linearParameters;
}
