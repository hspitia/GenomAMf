/**
 * @file Plotter.cpp
 * @date 21/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  Plotter.cpp
 *   Created on:  21/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "Plotter.h"

Plotter::Plotter(const QList<vector<double> > * dataList,
                           plotType type)
: mglDraw()
{
  this->dataList = dataList;
  this->type = type;
  this->title = 0;
  this->xLabel = 0;
  this->yLabel = 0;
  this->zLabel = 0;
}

Plotter::~Plotter()
{
  
}

void Plotter::configure(mglGraph * gr)
{
  gr->SetFontSizePT(9);
  gr->SetTicks('x',5,4);
  gr->SetTicks('y',5,4);
  
  if(type != Linear_Plot){
    // Set title
    if(title != 0) gr->Title(title);
  }
  
  if(xLabel != 0) gr->Label('x', xLabel, 0);
  if(yLabel != 0) gr->Label('y', yLabel, 0);
  if(zLabel != 0) gr->Label('z', zLabel, 0);
  
//  gr->Grid("xy","W;");
}

int Plotter::Draw(mglGraph *gr)
{
  configure(gr);
  
  switch (type) {
    case Linear_Plot:
      plotLinearRegression(gr);
      return 0;
    case Dq_plot:
    case Cq_plot:
      plotNormalData(gr);
      return 0;
    default:
      return 0;
  }
  
//  plot0(gr);
//  plotNormalData(gr);

  return 0;
}

void Plotter::plotLinearRegression(mglGraph * gr)
{
  
}

void Plotter::plotNormalData(mglGraph *gr)
{
  int nData = static_cast<int>(dataList->at(0).size());
  int nSlices = dataList->count() - 1;
  
  double minValue =  800000;
  double maxValue = -800000;
  
  mglData y(nData, nSlices);
  int index = 0;
  for (int i = 0; i < nData; ++i)
  {
    for (int j = 0; j < nSlices; ++j)
    {
      index = i + (nData * j);
      y.a[index] = dataList->at(j+1).at(i); 
      if(y.a[index] < minValue) minValue = y.a[index];
      if(y.a[index] > maxValue) maxValue = y.a[index];
      
    }
  }
  int minX = dataList->at(0).at(0);
  int maxX = dataList->at(0).at(nData-1);
  cout << maxX;
  gr->SetRanges(minX, minValue, maxX,maxValue);
  gr->Axis(mglPoint(minX, minValue, minX), mglPoint(maxX, maxValue, maxValue));
//  gr->SetTicks('x',5,4);
  gr->Grid("xy","W");
  gr->Axis();
  gr->Box();
  gr->Plot(y, "2");
}

void Plotter::plot0(mglGraph *gr)
{
  mglData x(100);
  mglData y(100);
  
  int xSize = static_cast<int>(dataList->at(0).size());
  int ySize = static_cast<int>(dataList->at(1).size());
  //  int nTicks = 
  
  mglData data(xSize,ySize);
  
  x.Set(dataList->at(0));
  y.Set(dataList->at(1));
  
  double minX = dataList->at(0).at(0);
  double maxX = dataList->at(0).at(xSize - 1); 
  double minY = dataList->at(1).at(0);
  double maxY = dataList->at(1).at(ySize - 1);
  
  gr->SetRanges(minX,maxX,minY,maxY);
  gr->SetFontSizePT(9);
  gr->SetTicks('x',5,4);
  gr->Plot(y,"b2");
  gr->Axis();
  gr->SetFontSizePT(14);
  gr->AddLegend("lectura para x","b");
  gr->Legend();
  
}

void Plotter::setTitle(char * title)
{
  this->title = title;
}

void Plotter::setXLabel(char * xLabel)
{
  this->xLabel = xLabel;
}

void Plotter::setYLabel(char * yLabel)
{
  this->yLabel = yLabel;
}

void Plotter::setZLabel(char * zLabel)
{
  this->zLabel = zLabel;
}
