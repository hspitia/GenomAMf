/**
 * @file SandBoxMethod.cpp
 * @date 15/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  SandBoxMethod.cpp
 *   Created on:  15/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "SandBoxMethod.h"
#include <utils/Utils.h>


SandBoxMethod::SandBoxMethod()
{
  this->minQ = -70;
  this->maxQ =  70;
  this->minR = 0;
  this->maxR = 1;
  this->cgrMatrix = 0;
  this->nCenters = 150;
//  this->dqValues = new QList<vector<double> >();
  this->dqValues = new vector<double>();
//  this->linearRegressionValues = new QList<vector<double> >();
  this->linearRegressionValues = QList<vector<double> *>();
//  this->coordinatesOfPoints = new QList<QPointF>();
  this->coordinatesOfPoints = QList<QPointF>();
//  this->fractalSize = 1;
}

SandBoxMethod::SandBoxMethod(const SandBoxMethod & sandBoxObject)
{
  this->minQ = sandBoxObject.minQ;
  this->maxQ = sandBoxObject.maxQ;
  this->minR = sandBoxObject.minR;
  this->maxR = sandBoxObject.maxR;
  this->cgrMatrix = sandBoxObject.cgrMatrix;
  this->nCenters = sandBoxObject.nCenters;
//  this->dqValues = sandBoxObject.dqValues;
  this->dqValues = new vector<double>(*sandBoxObject.dqValues);
  this->linearRegressionValues = sandBoxObject.linearRegressionValues;
  this->coordinatesOfPoints = sandBoxObject.coordinatesOfPoints; 
//          new QList<QPointF>(*(sandBoxObject.coordinatesOfPoints));
//  this->fractalSize = sandBoxObject.fractalSize;
}

SandBoxMethod::SandBoxMethod(const RowMatrix<int> * cgrMatrix,
//                             const int & fractalSize,
                             const int & minQ,
                             const int & maxQ,
                             const int & nCenters)
{
  this->minQ = minQ;
  this->maxQ = maxQ;
  this->minR = 0;
//  this->maxR = cgrMatrix->nRows();
  this->maxR = cgrMatrix->getNumberOfRows();
  this->cgrMatrix = cgrMatrix;
  this->nCenters = nCenters;
//  this->dqValues = new QList<vector<double> >();
  this->dqValues = new vector<double>();
//  this->linearRegressionValues = new QList<vector<double> >();
  this->linearRegressionValues = QList<vector<double> *>();
//   this->coordinatesOfPoints = new QList<QPointF>();
  this->coordinatesOfPoints = QList<QPointF>();
//  this->fractalSize = fractalSize;
}

SandBoxMethod::SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                             const QList<QPointF> & coordinatesOfPoints,
                             const int & minQ,
                             const int & maxQ,
                             const int & nCenters)
{
  this->minQ = minQ;
  this->maxQ = maxQ;
  this->minR = 0;
//  this->maxR = cgrMatrix->nRows();
  this->maxR = cgrMatrix->getNumberOfRows();
  this->cgrMatrix = cgrMatrix;
  this->nCenters = nCenters;
//  this->dqValues = new QList<vector<double> >();
  this->dqValues = new vector<double>();
//  this->linearRegressionValues = new QList<vector<double> >();
  this->linearRegressionValues = QList<vector<double> *>();
//  this->coordinatesOfPoints = new QList<QPointF>(*coordinatesOfPoints);
  this->coordinatesOfPoints = QList<QPointF>(coordinatesOfPoints);
//  this->fractalSize = fractalSize;
}

SandBoxMethod & SandBoxMethod::operator=(const SandBoxMethod & sandBoxObject)
{
  this->minQ = sandBoxObject.minQ;
  this->maxQ = sandBoxObject.maxQ;
  this->minR = sandBoxObject.minR;
  this->maxR = sandBoxObject.maxR;
  this->cgrMatrix = sandBoxObject.cgrMatrix;
  this->nCenters = sandBoxObject.nCenters;
//  this->dqValues = sandBoxObject.dqValues;
  this->dqValues = new vector<double>(*sandBoxObject.dqValues);
  this->linearRegressionValues = sandBoxObject.linearRegressionValues;
  this->coordinatesOfPoints = QList<QPointF>(sandBoxObject.coordinatesOfPoints);
//          new QList<QPointF>(*(sandBoxObject.coordinatesOfPoints));
//  this->fractalSize = sandBoxObject.fractalSize;
  return *this;
}

SandBoxMethod::~SandBoxMethod()
{
  if (cgrMatrix != 0) 
    cgrMatrix = 0;
  
  delete cgrMatrix;
  
  if (dqValues != 0)
    delete dqValues;
  
  if (!linearRegressionValues.empty())
    linearRegressionValues.clear();
}

bool xCoordinateLessThan(const QPointF & x1, const QPointF & x2)
{
//  cout << "DEBUG - SandBoxMethod::452 - xCoordinatesLessThan"<< endl;
  return x1.x() < x2.x();
}

bool yCoordinateLessThan(const QPointF & y1, const QPointF & y2)
{
//  cout << "DEBUG - SandBoxMethod::458 - xCoordinatesLessThan"<< endl;
  return y1.y() < y2.y();
}

void SandBoxMethod::performAnalisys(int type)
{
  
  switch (type){
    case MultifractalAnalisys::CONTINOUS_ANALISYS:
      performContinousAnalisys();
      break;
    case MultifractalAnalisys::DISCRETE_ANALISYS:
      performDiscreteAnalisys();
      break;
    case MultifractalAnalisys::COMPARATIVE_ANALISYS:
      performComparativeAnalisys();
      break;
    default:
      return;
  }  
}

void SandBoxMethod::performComparativeAnalisys()
{
  
  int nIteraciones = 1;
  unsigned int nIteracionesInternas = 2;

  vector<double> * continousAverages = new vector<double>();
  vector<double> * discreteAverages = new vector<double>();
  vector<int> * nCentros = new vector<int>();
  
  qSort(coordinatesOfPoints.begin(), coordinatesOfPoints.end(), 
        xCoordinateLessThan);
  
  for (int genIt = 0; genIt < nIteraciones; ++genIt) {
    vector<int> xCoordinates(nCenters);
    vector<int> yCoordinates(nCenters);
    
    vector<double> xCoordinatesDouble(nCenters);
    vector<double> yCoordinatesDouble(nCenters);
    
    generateRandomCenters(&xCoordinatesDouble, &yCoordinatesDouble);
    
    for (unsigned int i = 0; i < xCoordinatesDouble.size(); ++i) {
      int x = static_cast<int> (utils::roundToInt(xCoordinatesDouble.at(i)));
      int y = static_cast<int> (utils::roundToInt(yCoordinatesDouble.at(i)));
      
      xCoordinates.at(i) = x;
      yCoordinates.at(i) = y;
    }

    int radio = 6;
    unsigned int initIndex = 0;
    double continousSum = 0.0;
    double discreteSum = 0.0;
    
    vector<double> * countsContinous = new vector<double>();
    vector<double> * countsDiscrete  = new vector<double>();
    
    /*debug_comparative*/cout << "No.;CONTEO CONTINUO;CONTEO DISCRETO;RADIO" << endl;
    
    for (unsigned int currentIt = 0; currentIt < nIteracionesInternas; ++currentIt) {
      unsigned int centers = 50;
      unsigned int endIndex = initIndex + centers;
      
      for (unsigned int i = initIndex; i < endIndex; ++i) {
        /*debug_comparative*/cout << (i + 1) << ";"; // No.
        countsContinous->push_back(
          countPointsOnTheContinousSquareSandbox(xCoordinatesDouble.at(i),
                                                 yCoordinatesDouble.at(i),
                                                 radio));
        
         countsDiscrete->push_back(
          countPointsOnTheDiscreteSquareSandbox(xCoordinates.at(i),
                                                yCoordinates.at(i),
                                                radio));
         
         
         
         continousSum += countsContinous->back();
         discreteSum  += countsDiscrete->back();
                 
         /*debug_comparative*/cout << countsContinous->back() << ";"; // conteo continuo
         /*debug_comparative*/cout << countsDiscrete->back()  << ";"; // conteo discreto
         /*debug_comparative*/cout << radio << endl; // radio
      }
      
      nCentros->push_back(centers + (currentIt * 50));
//      continousAverages->push_back(VectorTools::mean<double, double>(*countsContinous));
      continousAverages->push_back((double) continousSum / countsContinous->size());
//      discreteAverages->push_back(VectorTools::mean<double, double>(*countsDiscrete));
      discreteAverages->push_back((double) discreteSum / countsDiscrete->size());
      
      initIndex = endIndex;
    }

//    delete countsContinous;
//    delete countsDiscrete;
    cout << "\nNo.;CENTROS;PROMEDIO CONTINUO;PROMEDIO DISCRETO;RADIO" << endl; 
    for (unsigned int i = 0; i < continousAverages->size(); ++i) {
      cout << i << ";"
           << nCentros->at(i) << ";"
           << continousAverages->at(i) << ";"
           << discreteAverages->at(i) << ";"
           << radio
           << endl;
    }
    cout << endl << endl;;
  }
}

void SandBoxMethod::performContinousAnalisys()
{
//  int nMomentums = maxQ - minQ + 1;  // Longitud rango valores q
  int dataLenght = maxR - minR + 1;  // Longitud rango valores de radio
  
//  vector<double> qData(nMomentums);
//  vector<double> * dqData = new vector<double>(nMomentums);
  
  for (int q = minQ; q <= maxQ; ++q) {
    vector<double> * xData = new vector<double>(dataLenght);
    vector<double> * yData = new vector<double>(dataLenght);
    
//    dqData->at(i) = calculateContinousDqValue(q, *xData, *yData);
    double dqValue = calculateContinousDqValue(q, *xData, *yData);
    dqValues->push_back(dqValue);

    linearRegressionValues.append(xData);
    linearRegressionValues.append(yData);
  }
  
//  dqValues->push_back(dqData);
  
}

void SandBoxMethod::performDiscreteAnalisys()
{
  int dataLenght = maxR - minR + 1;  // Longitud rango valores de radio
  
  for (int q = minQ; q <= maxQ; ++q) {
    vector<double> * xData = new vector<double>(dataLenght);
    vector<double> * yData = new vector<double>(dataLenght);
    
    double dqValue = calculateDiscreteDqValue(q, *xData, *yData);
    dqValues->push_back(dqValue);

    linearRegressionValues.append(xData);
    linearRegressionValues.append(yData);
  }
  
  
  /*
  int nMomentums = maxQ - minQ + 1;
  int dataLenght = maxR - minR + 1;
  
  vector<double> qData(nMomentums);
  vector<double> dqData(nMomentums);
  
  for (int q = minQ, index = 0; q <= maxQ; ++q, ++index)
  {
    vector<double> xData(dataLenght);
    vector<double> yData(dataLenght);
    
    qData.at(index) = q;
    dqData.at(index) = calculateDqValue(q, xData, yData);
    
    linearRegressionValues->append(xData);
    linearRegressionValues->append(yData);
  }
  dqValues->append(qData);
  dqValues->append(dqData);
  */
  
}

double SandBoxMethod::calculateContinousDqValue(const int & q, 
                                                vector<double> & xData,
                                                vector<double> & yData)
{
  int dataLenght = maxR - minR + 1;
  
//  vector<double> xData(dataLenght);
//  vector<double> yData(dataLenght);
  
  double massAverage;
//  int fractalSize = cgrMatrix->nRows(); 
  int fractalSize = cgrMatrix->getNumberOfRows(); 
  
  for (int radius = minR, index = 0; radius <= maxR; ++radius, ++index) {
    // Sand box centers coordinates
    vector <int> xCoordinates(nCenters);
    vector <int> yCoordinates(nCenters);
    
    generateRandomCenters(&xCoordinates, &yCoordinates);
    
    vector <double> masses(nCenters);
    for (int i = 0; i < nCenters; ++i) {
      masses.at(i) = 
              pow(countPointsOnTheContinousSquareSandbox(xCoordinates.at(i),
                                                         yCoordinates.at(i),
                                                         radius),
                                                         static_cast<double>
                                                         (q - 1));
      /*
      masses.at(i) = 
              pow(countPointsOnTheDiscreteSquareSandbox(xCoordinates.at(i),
                                                        yCoordinates.at(i),
                                                        radius),
                                                        static_cast<double>
                                                        (q - 1));
    */
    }
    
    massAverage = VectorTools::mean<double,double>(masses);
    xData.at(index) = (q - 1) * log(radius / fractalSize);
    yData.at(index) = log(massAverage);
  }
  
  Linear * linear = new Linear(dataLenght, &xData, &yData);
  
  return linear->getSlope();
}

double SandBoxMethod::calculateDiscreteDqValue(const int & q, 
                                               vector<double> & xData,
                                               vector<double> & yData)
{
  int dataLenght = maxR - minR + 1;
  
//  vector<double> xData(dataLenght);
//  vector<double> yData(dataLenght);
  
  double massAverage;
//  int fractalSize = cgrMatrix->nRows(); 
  int fractalSize = cgrMatrix->getNumberOfRows(); 
  
  for (int radius = minR, index = 0; radius <= maxR; ++radius, ++index) {
    // Sand box centers coordinates
    vector <int> xCoordinates(nCenters);
    vector <int> yCoordinates(nCenters);
    
    generateRandomCenters(&xCoordinates, &yCoordinates);
    
    vector <double> masses(nCenters);
    for (int i = 0; i < nCenters; ++i) {
      masses.at(i) = 
              pow(countPointsOnTheDiscreteSquareSandbox(xCoordinates.at(i),
                                                         yCoordinates.at(i),
                                                         radius),
                                                         static_cast<double>
                                                         (q - 1));
      /*
      masses.at(i) = 
              pow(countPointsOnTheDiscreteSquareSandbox(xCoordinates.at(i),
                                                        yCoordinates.at(i),
                                                        radius),
                                                        static_cast<double>
                                                        (q - 1));
    */
    }
    
    massAverage = VectorTools::mean<double,double>(masses);
    xData.at(index) = (q - 1) * log(radius / fractalSize);
    yData.at(index) = log(massAverage);
  }
  
  Linear * linear = new Linear(dataLenght, &xData, &yData);
  
  return linear->getSlope();
}

void SandBoxMethod::generateRandomCenters(vector<int> * xCoordinates,
                                          vector<int> * yCoordinates)
{
////  int maxNumber = static_cast<int>(cgrMatrix->nRows()) + 1;
//  int maxNumber = static_cast<int>(cgrMatrix->getNumberOfRows());
//  for (int i = 0; i < nCenters; ++i)
//  {
//    xCoordinates->at(i) = RandomTools::
//            giveIntRandomNumberBetweenZeroAndEntry(maxNumber);
//    yCoordinates->at(i) = RandomTools::
//            giveIntRandomNumberBetweenZeroAndEntry(maxNumber);
////    cout << "x: " << xCoordinates->at(i) 
////         << "  y: " << yCoordinates->at(i) << endl;
//  }
  vector<double> * xCoordinatesDouble =  new vector<double>(nCenters);
  vector<double> * yCoordinatesDouble =  new vector<double>(nCenters);
  
//  generateRandomCenters(&xCoordinatesDouble, &yCoordinatesDouble);
  generateRandomCenters(&*xCoordinatesDouble, &*yCoordinatesDouble);
  
  for (unsigned int i = 0; i < xCoordinatesDouble->size(); ++i) {
    int x = static_cast<int> (utils::roundToInt(xCoordinatesDouble->at(i)));
    int y = static_cast<int> (utils::roundToInt(yCoordinatesDouble->at(i)));
    
    xCoordinates->at(i) = x;
    yCoordinates->at(i) = y;
  }
  
  delete xCoordinatesDouble;
  delete yCoordinatesDouble;
}

void SandBoxMethod::generateRandomCenters(vector<double> * xCoordinates,
                                          vector<double> * yCoordinates)
{
  int maxIndex = coordinatesOfPoints.size();
  int randomIndex = 0;
          
  for (int i = 0; i < nCenters; ++i){
    randomIndex = RandomTools::giveIntRandomNumberBetweenZeroAndEntry(maxIndex);
    xCoordinates->at(i) = coordinatesOfPoints.at(randomIndex).x();
    yCoordinates->at(i) = coordinatesOfPoints.at(randomIndex).y();
//    cout << "x: " << xCoordinates->at(i) 
//         << "  y: " << yCoordinates->at(i) << endl;
  }
} 

/*bool SandBoxMethod::xCoordinateLessThan(const QPointF & x1, const QPointF & x2)
{
  return x1.x() < x2.x();
}

bool SandBoxMethod::yCoordinateLessThan(const QPointF & y1, const QPointF & y2)
{
  return y1.y() < y2.y();
}*/
double SandBoxMethod::countPointsOnTheContinousSquareSandbox(const double & x,
                                                             const double & y,
                                                             const double & 
                                                             radius)
{
  double sum = 0.0;
  
  double minX = x - radius;
  double maxX = x + radius;
  double minY = y - radius;
  double maxY = y + radius;
  
  QPointF lowerBoundPoint = QPointF(minX, minY);
  QPointF upperBoundPoint = QPointF(maxX, maxY);
  
  QList<QPointF>::Iterator lowerBound = 
          qLowerBound(coordinatesOfPoints.begin(), coordinatesOfPoints.end(),
                      lowerBoundPoint, xCoordinateLessThan);
  
  QList<QPointF>::Iterator upperBound = 
          qUpperBound(coordinatesOfPoints.begin(), coordinatesOfPoints.end(),
                      upperBoundPoint, xCoordinateLessThan);
  
  int beginPosition = static_cast<int>(lowerBound - coordinatesOfPoints.begin());
  int endPosition   = static_cast<int>(upperBound - coordinatesOfPoints.begin());
  int length        = endPosition - beginPosition;
  
  QList<QPointF> subList = coordinatesOfPoints.mid(beginPosition, length);
  
  qSort(subList.begin(), subList.end(), yCoordinateLessThan);
  
  /*cout << "Sublista ordenada por y: " << endl;
  foreach(QPointF p, subList)
    cout << "(" << p.x() << ", " << p.y() << ") ";
  
  cout << endl;*/
  
  lowerBoundPoint = QPointF(minX, minY);
  upperBoundPoint = QPointF(maxX, maxY);

  lowerBound = qLowerBound(subList.begin(), subList.end(), lowerBoundPoint, 
                           yCoordinateLessThan);
  
  upperBound = qUpperBound(subList.begin(), subList.end(), upperBoundPoint,
                           yCoordinateLessThan);
  
  beginPosition = static_cast<int>(lowerBound - subList.begin());
  endPosition   = static_cast<int>(upperBound - subList.begin());
  length        = endPosition - beginPosition;
  sum           = static_cast<double>(endPosition - beginPosition);
  
  return sum;
}

double SandBoxMethod::countPointsOnTheDiscreteSquareSandbox(const int & x, // col
                                                            const int & y, // row
                                                            const int & radius)
{
  double sum   = 0.0;
   
  if (radius > 0) {
    int minIndex = 0;
    int maxIndex = cgrMatrix->getNumberOfRows() - 1;
    int initRow  = maxIndex - (y + radius);
    int initCol  = x - radius;
    int endRow   = maxIndex - (y - radius);
    int endCol   = x + radius;
    
    if (initRow < minIndex)
      initRow = 0;
    
    if (initCol < minIndex)
      initCol = 0;
    
    if (endCol > maxIndex)
      endCol = maxIndex;
    
    if (endRow > maxIndex)
      endRow = maxIndex;
    
    /*
    cout << "\n\nDEBUG -- SandBoxMethod::605" << endl;
    cout << "centro:  (" << x << ", " << y << ") " << "(" << maxRow - y << ", " << x << ")  "<< endl;
    cout << "inicial: (" << initRow << ", " << initCol << ")  "<< endl;
    cout << "final:   (" << endRow << ", " << endCol << ")  "<< endl;
    */
    for (int row = initRow; row <= endRow; ++row) {
      for (int col = initCol; col <= endCol; ++col) {
        sum = sum + (*cgrMatrix)(row, col);
      }
    }
  }
  else if (radius == 0) {
    sum += (*cgrMatrix)(y, x);
  }
  
  return sum;
}

// Accessors
int SandBoxMethod::getMinQ()
{
  return minQ;
}

void SandBoxMethod::setMinQ(int minQ)
{
  this->minQ = minQ;
}

int SandBoxMethod::getMaxQ()
{
  return maxQ;
}

void SandBoxMethod::setMaxQ(int maxQ)
{
  this->maxQ = maxQ;
}

int SandBoxMethod::getMinR()
{
  return minR;
}

void SandBoxMethod::setMinR(int minR)
{
  this->minR = minR;
}

int SandBoxMethod::getMaxR()
{
  return maxR;
}

void SandBoxMethod::setMaxR(int maxR)
{
  this->maxR = maxR;
}

const RowMatrix<int> * SandBoxMethod::getCgrMatrix() const
{
  return cgrMatrix;
}

void SandBoxMethod::setCgrMatrix(const RowMatrix<int> * cgrMatrix)
{
  this->cgrMatrix = cgrMatrix;
}

int SandBoxMethod::getNCenters()
{
  return nCenters;
}

void SandBoxMethod::setNCenters(int nCenters)
{
  this->nCenters = nCenters;
}

//QList<vector<double> > * SandBoxMethod::getDqValues()
vector<double> * SandBoxMethod::getDqValues()
{
  return dqValues;
}

/*
void SandBoxMethod::setDqValues(QList<vector<double> > * dqValues)
{
  this->dqValues = dqValues;
}
*/

//QList<vector<double> > * SandBoxMethod::getLinearRegressionValues()
QList<vector<double> *> SandBoxMethod::getLinearRegressionValues()
{
  return linearRegressionValues;
}

/*
void SandBoxMethod::setLinearRegressionValues(QList<vector<double> > * 
                                              linearRegressionValues)
{
  this->linearRegressionValues = linearRegressionValues;
}
*/

const QList<QPointF> SandBoxMethod::getCoordinatesOfPoints() const
{
  return coordinatesOfPoints;
}

void SandBoxMethod::setCoordinatesOfPoints(const QList<QPointF> & 
                                           coordinatesOfPoints)
{
  this->coordinatesOfPoints = coordinatesOfPoints;
}

