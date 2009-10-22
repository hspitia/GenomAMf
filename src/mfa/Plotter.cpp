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

Plotter::Plotter(const QList<vector<double> > * dataListNormal,
                           plotType type)
: mglDraw()
{
  this->dataListNormal = dataListNormal;
  this->dataListLinearReg = dataListLinearReg;
  this->type = type;
  this->title = "";
  this->xLabel = "";
  this->yLabel = "";
  this->zLabel = "";
}

Plotter::Plotter(const QList<QList<vector<double> > > * dataListLinearReg,
                           plotType type)
: mglDraw()
{
  this->dataListNormal = 0;
  this->dataListLinearReg = dataListLinearReg;
  this->type = type;
  this->title = "";
  this->xLabel = "";
  this->yLabel = "";
  this->zLabel = "";
}

Plotter::~Plotter()
{
  if(dataListNormal != 0) dataListNormal = 0;
  delete dataListNormal;
  
  if(dataListLinearReg != 0) dataListLinearReg = 0;
  delete dataListLinearReg;
}

void Plotter::configure(mglGraph * gr)
{
  gr->SetFontSizePT(9);
  gr->SetTicks('x',5,4);
  gr->SetTicks('y',5,4);
  
  if(type != Linear_Plot){
    // Set title
    if(title != 0) gr->Title(title.toLatin1().data());
  }
  
  if(!xLabel.isEmpty()) gr->Label('x', xLabel.toLatin1().data(), 0, -1.2, 1);
  if(!yLabel.isEmpty()) gr->Label('y', yLabel.toLatin1().data(), 0, -1.2, 1);
  if(!zLabel.isEmpty()) gr->Label('z', zLabel.toLatin1().data(), 0, -1.2, 1);
  
//  gr->Grid("xy","W;");
}

int Plotter::Draw(mglGraph *gr)
{
  configure(gr);
  
  switch (type) {
    case Linear_Plot:
      plotLinearRegression(gr);
      return 0;
    case Dq_Plot:
    case Cq_Plot:
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
  Q_UNUSED(gr);
}

void Plotter::plotNormalData(mglGraph *gr)
{
  int nData = static_cast<int>(dataListNormal->at(0).size());
  int nSlices = dataListNormal->count() - 1;
  
  double minValue =  800000;
  double maxValue = -800000;
  
  mglData y(nData, nSlices);
  int index = 0;
  for (int i = 0; i < nData; ++i)
  {
    for (int j = 0; j < nSlices; ++j)
    {
      index = i + (nData * j);
      y.a[index] = dataListNormal->at(j+1).at(i); 
      if(y.a[index] < minValue) minValue = y.a[index];
      if(y.a[index] > maxValue) maxValue = y.a[index];
      
    }
  }
  int minX = dataListNormal->at(0).at(0);
  int maxX = dataListNormal->at(0).at(nData-1);
  cout << maxX;
  gr->SetRanges(minX, minValue, maxX*1.2,maxValue*1.2);
  gr->Axis(mglPoint(minX, minValue, minX), mglPoint(maxX*1.2, maxValue*1.2, maxValue*1.2));
  gr->Grid("xy","W");
//  gr->Grid("xy","N");
  gr->Axis();
  gr->Box();
  gr->Plot(y, "2");
  gr->AddLegend("Leyenda 1","-");
  gr->AddLegend("Leyenda 2","-");
  gr->AddLegend("Leyenda 3","-");
  
  gr->Puts(mglPoint(maxX*1.28,10,10),"texto");
  gr->Legend();
}

void Plotter::plot0(mglGraph *gr)
{
  mglData x(100);
  mglData y(100);
  
  int xSize = static_cast<int>(dataListNormal->at(0).size());
  int ySize = static_cast<int>(dataListNormal->at(1).size());
  //  int nTicks = 
  
  mglData data(xSize,ySize);
  
  x.Set(dataListNormal->at(0));
  y.Set(dataListNormal->at(1));
  
  double minX = dataListNormal->at(0).at(0);
  double maxX = dataListNormal->at(0).at(xSize - 1); 
  double minY = dataListNormal->at(1).at(0);
  double maxY = dataListNormal->at(1).at(ySize - 1);
  
  gr->SetRanges(minX,maxX,minY,maxY);
  gr->SetFontSizePT(9);
  gr->SetTicks('x',5,4);
  gr->Plot(y,"b2");
  gr->Axis();
  gr->SetFontSizePT(14);
  gr->AddLegend("lectura para x","b");
  gr->Legend();
  
}

void Plotter::setTitle(QString title)
{
  this->title = title;
}

void Plotter::setXLabel(QString xLabel)
{
  this->xLabel = xLabel;
}

void Plotter::setYLabel(QString yLabel)
{
  this->yLabel = yLabel;
}

void Plotter::setZLabel(QString zLabel)
{
  this->zLabel = zLabel;
}

QStringList Plotter::getLegends()
{
  return legends;
}

void Plotter::setLegends(QStringList legends)
{
  this->legends = legends;
}
