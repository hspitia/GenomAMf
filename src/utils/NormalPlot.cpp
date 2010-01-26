/**
 * @file NormalPlot.cpp
 * @date 22/01/2010
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  NormalPlot.cpp
 *   Created on:  22/01/2010
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "NormalPlot.h"

//NormalPlot::NormalPlot(const QList<QVector<double> > & dataList,
NormalPlot::NormalPlot(const QList<vector<double> > & dataList,
                       const QStringList & curveIdentifiers,
                       QWidget *parent) : 
  Plot(dataList, curveIdentifiers, parent)
{
  setupCurves();

}

NormalPlot::NormalPlot(const NormalPlot & dqPlotObject) :
  Plot(dqPlotObject)
{
  
}

NormalPlot & NormalPlot::operator=(const NormalPlot & dqPlotObject)
{
  Q_UNUSED(dqPlotObject);
  return *this;
}

/*void NormalPlot::setupCurves()
{
  // Insert new curves
  QwtPlotCurve *cSin = new QwtPlotCurve("y = sin(x) as s");
  cSin->setRenderHint(QwtPlotItem::RenderAntialiased);
  cSin->setPen(QPen(Qt::red));
  cSin->setCurveAttribute(QwtPlotCurve::Fitted);
  cSin->attach(this);
  
  QwtPlotCurve *cCos = new QwtPlotCurve("y = cos(x) asa ");
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
}*/

//void NormalPlot::setupCurves()
//{
//  int nCurves = dataList.count() - 1;
//  createCurves(nCurves);
//  int nPoints = dataList.at(0).size();
//  
//  QVector<double> tmpXDataVector = 
//          QVector<double>::fromStdVector(dataList.at(0));
//  
////  const double * xValues = /*new double[nPoints]; //*/dataList.at(0).data(); 
//  const double * xValues = tmpXDataVector.data();
//  const double * yValues = 0; 
//  
//  for (int i = 0; i < nCurves; ++i) {
////    yValues = dataList.at(i+1).data();
//    QVector<double> tmpVector = 
//            QVector<double>::fromStdVector(dataList.at(i+1));
//    yValues = tmpVector.data();
//    curves[i].setData(xValues, yValues, nPoints);
//    curves[i].setRenderHint(QwtPlotItem::RenderAntialiased);
////    curves[i].setPen(QPen(colorList.at(i)));
//    curves[i].attach(this);
//  }
//}

void NormalPlot::setupCurves()
{
  int nCurves = dataList.count() - 1;
  curves = createCurves(nCurves);
  int nPoints = dataList.at(0).size();
  
  double * xValues = new double[nPoints];
  copy(dataList.at(0).begin(), dataList.at(0).end(), xValues);
  
  double * yValues = 0; 
  
  for (int i = 0; i < nCurves; ++i) {
    yValues = new double[nPoints];
    copy(dataList.at(i+1).begin(), dataList.at(i+1).end(), yValues);
    curves[i].setData(xValues, yValues, nPoints);
    curves[i].setRenderHint(QwtPlotItem::RenderAntialiased);
    curves[i].setStyle(QwtPlotCurve::Lines);
    curves[i].attach(this);
  }
}

NormalPlot::~NormalPlot()
{
  // TODO Auto-generated destructor stub
}
