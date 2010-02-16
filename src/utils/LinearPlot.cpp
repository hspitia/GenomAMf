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

LinearPlot::LinearPlot(QWidget * parent) : 
  Plot(parent)
{
  this->linearParameters = QList<vector<double> *>();
  this->linearFitCurves  = 0;
}

LinearPlot::LinearPlot(const QList<vector<double> *> & dataList,
                       const QStringList curveIdentifiers,
                       const QList<vector<double> *> & linearParameters,
                       QWidget *parent) : 
  Plot(dataList, curveIdentifiers, parent)
{
  this->linearParameters = linearParameters;
  setupCurves();
}

LinearPlot::LinearPlot(const LinearPlot & dqPlotObject) :
  Plot(dqPlotObject)
{
  this->linearParameters = dqPlotObject.linearParameters;
}

LinearPlot & LinearPlot::operator=(const LinearPlot & dqPlotObject)
{
  this->dataList         = dqPlotObject.dataList;
  this->curveIdentifiers = dqPlotObject.curveIdentifiers;
  this->linearParameters = dqPlotObject.linearParameters;
  
  this->colorList        = dqPlotObject.colorList;
  this->symbolList       = dqPlotObject.symbolList;
  
  this->setupGeneralConfiguration();
  (*this).alignScales();
  (*this).connectSignalsSlots();
  
  return *this;
}


void LinearPlot::setupCurves()
{
  int nCurves = dataList.count() / 2;
  int nPoints = dataList.at(0)->size();
  
  int xDataIndex = 0;
  int yDataIndex = 0;
  
  // Linear fit curves
  linearFitCurves = createLinearFitCurves(nCurves);
  
  double * xValues = 0;
  double * yValues = 0; 
  
  if (linearFitCurves) {
    for (int i = 0; i < nCurves; ++i) {
      xDataIndex = i * 2;
      xValues = new double[2];
      xValues[0] = dataList.at(xDataIndex)->at(0);
      xValues[1] = dataList.at(xDataIndex)->at(nPoints - 1);
      
      yValues = new double[2];
      
      yValues[0] = (linearParameters.at(i)->at(0) * xValues[0]) + 
              linearParameters.at(i)->at(1);
      yValues[1] = (linearParameters.at(i)->at(0) * xValues[1]) + 
              linearParameters.at(i)->at(1);
      
      linearFitCurves[i].setData(xValues, yValues, 2);
      linearFitCurves[i].attach(this);
      showCurve(&linearFitCurves[i], true);
    }
  }
  
  // Points of plot
  curves = createCurves(nCurves);
   
  xValues = 0;
  yValues = 0; 
  
  if (curves) {
    
    for (int i = 0; i < nCurves; ++i) {
      xDataIndex = i * 2;
      xValues = new double[nPoints];
      copy(dataList.at(xDataIndex)->begin(), dataList.at(xDataIndex)->end(), xValues);
      
      yValues = new double[nPoints];
      yDataIndex = xDataIndex + 1; 
      copy(dataList.at(yDataIndex)->begin(), dataList.at(yDataIndex)->end(), yValues);
      
      curves[i].setData(xValues, yValues, nPoints);
      curves[i].attach(this);
      showCurve(&curves[i], true);
    }
   
    
    /*if (linearFitCurves) {
      for (int i = 0; i < nCurves; ++i) {
        xDataIndex = i * 2;
        xValues = new double[nPoints];
        copy(dataList.at(xDataIndex).begin(), dataList.at(xDataIndex).end(), xValues);
        
        yValues = new double[nPoints];
        
        for (int j = 0; j < nPoints; ++j) {
          yValues[j] = (linearParameters.at(i).at(0) * xValues[j]) + 
                  linearParameters.at(i).at(1);
        }
        
        linearFitCurves[i].setData(xValues, yValues, nPoints);
        linearFitCurves[i].attach(this);
      }
    }*/
  }
  
  
}

QwtPlotCurve * LinearPlot::createCurves(const int & nCurves)
{
  QwtPlotCurve * tmpCurves = new QwtPlotCurve[nCurves];
  
  if (nCurves > symbolList.count() || nCurves > colorList.count())
    return 0;
  
  for (int i = 0; i < nCurves; ++i) {
    QwtSymbol sym;
    QPen pen(colorList.at(i));
    
    sym.setStyle(symbolList.at(i+1));
    sym.setPen(QPen(QColor(Qt::black)));
    sym.setBrush(colorList.at(i));
    sym.setSize(5);
    
    QString id = curveIdentifiers.at(i);
//    tmpCurves[i].setTitle(id);
    tmpCurves[i].setTitle("<font size=\"1\">" + id + "</font>");
    
    tmpCurves[i].setSymbol(sym);
    tmpCurves[i].setPen(pen);
    tmpCurves[i].setRenderHint(QwtPlotItem::RenderAntialiased);
    tmpCurves[i].setStyle(QwtPlotCurve::NoCurve);
  } 
  
  return tmpCurves;
}

QwtPlotCurve * LinearPlot::createLinearFitCurves(const int & nCurves)
{
  QwtPlotCurve * tmpCurves = new QwtPlotCurve[nCurves];
  
  if (nCurves > symbolList.count() || nCurves > colorList.count())
    return 0;
  
  for (int i = 0; i < nCurves; ++i) {
    QPen pen(colorList.at(i));
    QwtSymbol sym;
    sym.setStyle(symbolList.at(0));
    QString id = trUtf8("<font size=\"1\">Ajuste lineal para ") + 
            curveIdentifiers.at(i) + 
            trUtf8("</font>");

    tmpCurves[i].setPen(pen);
    tmpCurves[i].setSymbol(sym);
    tmpCurves[i].setTitle(id);
    tmpCurves[i].setRenderHint(QwtPlotItem::RenderAntialiased);
    tmpCurves[i].setStyle(QwtPlotCurve::Lines);
  } 
  
  return tmpCurves;
}

LinearPlot::~LinearPlot()
{
  if (linearFitCurves)
    delete [] linearFitCurves;
}

QList<vector<double> *> LinearPlot::getLinearParameters()
{
  return linearParameters;
}

void LinearPlot::setLinearParameters(const QList<vector<double> *> & linearParameters)
{
  this->linearParameters = linearParameters;
}
