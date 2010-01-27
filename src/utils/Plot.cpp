/**
 * @file Plot.cpp
 * @date 22/01/2010
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  Plot.cpp
 *   Created on:  22/01/2010
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "Plot.h"
Plot::Plot(QWidget *parent) :
  QwtPlot(parent)
{
  initColorList();
  initSymbolList();
  setupGeneralConfiguration();
  alignScales();
  
  // Insert markers

  //  ...a horizontal line at y = 0...
  QwtPlotMarker *mY = new QwtPlotMarker();
  mY->setLabel(QString::fromLatin1("y = 0"));
  mY->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
  mY->setLineStyle(QwtPlotMarker::HLine);
  mY->setYValue(0.0);
  mY->attach(this);
  
  //  ...a vertical line at x = 2 * pi
  QwtPlotMarker *mX = new QwtPlotMarker();
  mX->setLabel(QString::fromLatin1("x = 2 pi"));
  mX->setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
  mX->setLabelOrientation(Qt::Vertical);
  mX->setLineStyle(QwtPlotMarker::VLine);
  mX->setLinePen(QPen(Qt::black, 0, Qt::DashDotLine));
  mX->setXValue(2.0 * M_PI);
  mX->attach(this);
}

//Plot::Plot(const QList<QVector<double> > & dataList,
Plot::Plot(const QList<vector<double> *> & dataList,
           const QStringList curveIdentifiers,
           QWidget *parent) : 
  QwtPlot(parent)
{
  this->dataList         = dataList;
  this->curveIdentifiers = curveIdentifiers;
  initColorList();
  initSymbolList();
  setupGeneralConfiguration();
  alignScales();
  connectSignalsSlots();
}

Plot::Plot(const Plot & plotObject) : 
  QwtPlot(plotObject.parentWidget())
{
  this->dataList         = plotObject.dataList;
  this->curveIdentifiers = plotObject.curveIdentifiers;
  initColorList();
  initSymbolList();
  setupGeneralConfiguration();
  alignScales();
  connectSignalsSlots();
}

Plot & Plot::operator=(const Plot & plotObject)
{
  this->dataList         = plotObject.dataList;
  this->curveIdentifiers = plotObject.curveIdentifiers;
  initColorList();
  initSymbolList();
  setupGeneralConfiguration();
  alignScales();
  connectSignalsSlots();
  
  return *this;
}

//void Plot::createCurves(const int & nCurves)
QwtPlotCurve * Plot::createCurves(const int & nCurves)
{

  int nColors = colorList.count();
  QwtPlotCurve * tmpCurves = new QwtPlotCurve[nCurves];
  int nSymForAssign = static_cast<int>(ceil(static_cast<double>(nCurves) / 
                                            static_cast<double>(nColors)));
  
  if (nSymForAssign > symbolList.count() + 1)
    return 0;
  
  for (int i = 0; i < nSymForAssign; ++i) {
    QwtSymbol sym;
    sym.setStyle(symbolList.at(i+1));
    sym.setPen(QPen(QColor(Qt::black)));
    sym.setSize(7);
    
    int index = i * nColors;
    int j = 0;
    while(j < nColors && j < nCurves) {
//      cout << "index: " << index << "  j: " << j<< endl;
      QString id = curveIdentifiers.at(index);
      sym.setBrush(colorList.at(j));
      tmpCurves[index].setTitle(id);
      tmpCurves[index].setSymbol(sym);
//      tmpCurves[index].setPen(QPen(Qt::red));
      QPen pen(colorList.at(j));
      pen.setWidth(2);
      tmpCurves[index].setPen(pen);
//      tmpCurves[index].setCurveAttribute(QwtPlotCurve::Fitted);
      ++index;
      ++j;
    }
  } 
  
  return tmpCurves;
}

void Plot::setupGeneralConfiguration()
{
  setAutoReplot(false);
  
  QwtLegend *legend = new QwtLegend;
  legend->setItemMode(QwtLegend::CheckableItem);
  legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
//  legend->setFrameStyle(QFrame::Panel|QFrame::Plain);
  
//  legend->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
  insertLegend(legend, QwtPlot::RightLegend);
//  insertLegend(legend, QwtPlot::BottomLegend);
  
//  setCanvasBackground(QColor(250,250,250));
  setCanvasBackground(Qt::white);
  
  // Set grid
  QwtPlotGrid *grid = new QwtPlotGrid;
  grid->enableXMin(true);
  grid->enableYMin(true);
  grid->setMajPen(QPen(Qt::lightGray, 0, Qt::SolidLine));
  grid->setMinPen(QPen(Qt::lightGray, 0 , Qt::DotLine));
  grid->attach(this);
  
  setMargin(20);
  
  axisScaleEngine(QwtPlot::xBottom)->
          setAttribute(QwtScaleEngine::Floating, true);
  axisScaleEngine(QwtPlot::yLeft)->
          setAttribute(QwtScaleEngine::Floating, true);
  
//  setPalette(QPalette(Qt::white));
}

void Plot::alignScales()
{
//   plotLayout()->setAlignCanvasToScales(true);
  
  // The code below shows how to align the scales to
  // the canvas frame, but is also a good example demonstrating
  // why the spreaded API needs polishing.

  canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
  canvas()->setLineWidth(1);
  
  for ( int i = 0; i < QwtPlot::axisCnt; i++ )
  {
    QwtScaleWidget *scaleWidget = (QwtScaleWidget *)axisWidget(i);
    if ( scaleWidget )
      scaleWidget->setMargin(0);
    
    QwtScaleDraw *scaleDraw = (QwtScaleDraw *)axisScaleDraw(i);
    if ( scaleDraw )
      scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
  }
}


void Plot::initColorList()
{
  colorList = QList<QColor>();
  colorList.append(QColor(Qt::blue));
  colorList.append(QColor(Qt::red));
//  colorList.append(QColor(Qt::green));
  colorList.append(QColor(155,187,89));
  colorList.append(QColor(Qt::magenta));
  colorList.append(QColor(255, 192, 0));
  colorList.append(QColor(Qt::darkBlue));
  colorList.append(QColor(Qt::darkRed));
  colorList.append(QColor(Qt::darkGreen));
  colorList.append(QColor("#31849B"));
  colorList.append(QColor(Qt::darkMagenta));
}

void Plot::initSymbolList()
{
//   symbolList = QList<int>();
   symbolList = QList<QwtSymbol::Style>();
   symbolList.append(QwtSymbol::NoSymbol);
   symbolList.append(QwtSymbol::Ellipse);
   symbolList.append(QwtSymbol::Rect);
   symbolList.append(QwtSymbol::Diamond);
   symbolList.append(QwtSymbol::Triangle);
   symbolList.append(QwtSymbol::DTriangle);
   symbolList.append(QwtSymbol::UTriangle);
   symbolList.append(QwtSymbol::LTriangle);
   symbolList.append(QwtSymbol::RTriangle);
   symbolList.append(QwtSymbol::Cross);
   symbolList.append(QwtSymbol::XCross);
   symbolList.append(QwtSymbol::HLine);
   symbolList.append(QwtSymbol::VLine);
   symbolList.append(QwtSymbol::Star1);
   symbolList.append(QwtSymbol::Star2);
   symbolList.append(QwtSymbol::Hexagon);
}

void Plot::connectSignalsSlots()
{
  connect(this, SIGNAL(legendChecked(QwtPlotItem *, bool)), this,
          SLOT(showCurve(QwtPlotItem *, bool)));
//  connect(sender, SIGNAL(signal), receiver, SLOT(method));
}

Plot::~Plot()
{
  delete[] curves;
}

void Plot::showCurve(QwtPlotItem *item, bool on)
{
    item->setVisible(on);
    QWidget *w = legend()->find(item);
    if ( w && w->inherits("QwtLegendItem") ) {
        ((QwtLegendItem *)w)->setChecked(on);
        ((QwtLegendItem *)w)->clearFocus();
    }
    
    replot();
}

//QList<QVector<double> > Plot::getDataList()
QList<vector<double> *> Plot::getDataList()
{
  return dataList;
}

//void Plot::setDataList(const QList<QVector<double> > & dataList)
void Plot::setDataList(const QList<vector<double> *> & dataList)
{
  this->dataList = dataList;
}

QStringList Plot::getCurveIdentifiers()
{
  return curveIdentifiers;
}

void Plot::setCurveIdentifiers(const QStringList & curveIdentifiers)
{
  this->curveIdentifiers = curveIdentifiers;
}

QList<QColor> Plot::getColorList()
{
  return colorList;
}

void Plot::setColorList(QList<QColor> colorList)
{
  this->colorList = colorList;
}

//QList<int> Plot::getSymbolList()
QList<QwtSymbol::Style> Plot::getSymbolList()
{
  return symbolList;
}

//void Plot::setSymbolList(QList<int> symbolList)
void Plot::setSymbolList(QList<QwtSymbol::Style> symbolList)
{
  this->symbolList = symbolList;
}
