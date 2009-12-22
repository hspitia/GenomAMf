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
#define DEBUG_MODE

#include "SandBoxMethod.h"
#include "utils/Trace.h"

SandBoxMethod::SandBoxMethod()
{
  this->minQ                   =  -70;
  this->maxQ                   =   70;
  this->minR                   =    0;
  this->maxR                   =  256;
  this->totalPoints            =    0;                 
  this->cgrMatrix              =    0;
  this->nCenters               = 1000;
  this->indexesOfCenters       = QList<int>();
  this->dqValues               = new vector<double>();
  this->linearRegressionValues = QList<vector<double> *>();
  this->fractalPoints          = QList<QPointF>();
}

SandBoxMethod::SandBoxMethod(const SandBoxMethod & sandBoxObject)
{
  this->minQ                   = sandBoxObject.minQ;
  this->maxQ                   = sandBoxObject.maxQ;
  this->minR                   = sandBoxObject.minR;
  this->maxR                   = sandBoxObject.maxR;
  this->totalPoints            = sandBoxObject.totalPoints;
  this->cgrMatrix              = sandBoxObject.cgrMatrix;
  this->nCenters               = sandBoxObject.nCenters;
  this->indexesOfCenters       = sandBoxObject.indexesOfCenters;
  this->dqValues               = new vector<double>(*sandBoxObject.dqValues);
  this->linearRegressionValues = sandBoxObject.linearRegressionValues;
  this->fractalPoints          = sandBoxObject.fractalPoints; 
}

SandBoxMethod::SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                             const int & totalPoints,
                             const int & minQ,
                             const int & maxQ,
                             const int & nCenters)
{
  this->minQ                   = minQ;
  this->maxQ                   = maxQ;
  this->minR                   = 0;
  this->maxR                   = 256;
  this->totalPoints            = totalPoints;
  this->cgrMatrix              = cgrMatrix;
  this->nCenters               = nCenters;
  this->indexesOfCenters       = QList<int>();
  this->dqValues               = new vector<double>();
  this->linearRegressionValues = QList<vector<double> *>();
  this->fractalPoints    = QList<QPointF>();
}

SandBoxMethod::SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                             const QList<QPointF> & fractalPoints,
                             const int & minQ,
                             const int & maxQ,
                             const int & nCenters)
{
  this->minQ                   = minQ;
  this->maxQ                   = maxQ;
  this->minR                   = 0;
  this->maxR                   = 256;
  this->totalPoints            = fractalPoints.count();
  this->cgrMatrix              = cgrMatrix;
  this->nCenters               = nCenters;
  this->indexesOfCenters       = QList<int>();
  this->dqValues               = new vector<double>();
  this->linearRegressionValues = QList<vector<double> *>();
  this->fractalPoints    = QList<QPointF>(fractalPoints);
  
  generateRandomCenters();
}

SandBoxMethod & SandBoxMethod::operator=(const SandBoxMethod & sandBoxObject)
{
  this->minQ                   = sandBoxObject.minQ;
  this->maxQ                   = sandBoxObject.maxQ;
  this->minR                   = sandBoxObject.minR;
  this->maxR                   = sandBoxObject.maxR;
  this->totalPoints            = sandBoxObject.totalPoints;
  this->cgrMatrix              = sandBoxObject.cgrMatrix;
  this->nCenters               = sandBoxObject.nCenters;
  this->indexesOfCenters       = sandBoxObject.indexesOfCenters;
  this->dqValues               = new vector<double>(*sandBoxObject.dqValues);
  this->linearRegressionValues = sandBoxObject.linearRegressionValues;
  this->fractalPoints    = sandBoxObject.fractalPoints;
  
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
  return x1.x() < x2.x();
}

bool yCoordinateLessThan(const QPointF & y1, const QPointF & y2)
{
  return y1.y() < y2.y();
}

void SandBoxMethod::performAnalysis(int type)
{
  
  switch (type){
    case MultifractalAnalysis::CONTINOUS_ANALYSIS:
      performContinousAnalysis();
      break;
    case MultifractalAnalysis::DISCRETE_ANALYSIS:
      performDiscreteAnalysis();
      break;
    case MultifractalAnalysis::COMPARATIVE_ANALYSIS:
      performComparativeAnalysis();
      break;
    default:
      return;
  }  
}

void SandBoxMethod::performComparativeAnalysis()
{
  
  int nIteraciones = 3;
  unsigned int nIteracionesInternas = 3;
  int radio = 6;

  vector<double> * continousAverages = new vector<double>();
  vector<double> * discreteAverages = new vector<double>();
  
  vector<double> * countsContinous = new vector<double>();
  vector<double> * countsDiscrete  = new vector<double>();
  
  vector<int> * nCentros = new vector<int>();
  
  qSort(fractalPoints.begin(), fractalPoints.end(), 
        xCoordinateLessThan);
  
  for (int genIt = 0; genIt < nIteraciones; ++genIt) {
    vector<int> xCoordinates(nCenters);
    vector<int> yCoordinates(nCenters);
    
    vector<double> xCoordinatesDouble(nCenters);
    vector<double> yCoordinatesDouble(nCenters);
    
    generateRandomCenters(&xCoordinatesDouble, &yCoordinatesDouble);
    
    for (unsigned int i = 0; i < xCoordinatesDouble.size(); ++i) {
//      double  xTmp = utils::roundToHalf(xCoordinatesDouble.at(i));
//      double  yTmp = utils::roundToHalf(yCoordinatesDouble.at(i));
      double  xTmp = utils::roundToInt(xCoordinatesDouble.at(i));
      double  yTmp = utils::roundToInt(yCoordinatesDouble.at(i));
      
//      int x = static_cast<int> (xTmp - 0.5);
//      int y = static_cast<int> (yTmp - 0.5);
      int x = xTmp;
      int y = yTmp;
      
      xCoordinates.at(i) = x;
      yCoordinates.at(i) = y;
    }

    unsigned int initIndex = 0;
    double continousSum    = 0.0;
    double discreteSum     = 0.0;
    
    for (unsigned int currentIt = 0; currentIt < nIteracionesInternas; ++currentIt) {
      unsigned int centers = 50;
      unsigned int endIndex = initIndex + centers;
      
      for (unsigned int i = initIndex; i < endIndex; ++i) {
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
  }
  cout << "\nNo.;CENTROS;PROMEDIO CONTINUO;PROMEDIO DISCRETO;RADIO" << endl; 
  for (unsigned int i = 0; i < continousAverages->size(); ++i) {
    cout << i << ";"
            << nCentros->at(i) << ";"
            << continousAverages->at(i) << ";"
            << discreteAverages->at(i) << ";"
            << radio
            << endl;
  }
  cout << endl << endl;
  
  /*debug_comparative*/cout << "No.;CONTEO CONTINUO;CONTEO DISCRETO;RADIO" << endl;
  for (unsigned int i = 0; i < countsDiscrete->size(); ++i) {
    cout << i << ";"
            << countsContinous->at(i) << ";"
            << countsDiscrete->at(i) << ";"
            << radio
            << endl;
  }
}

void SandBoxMethod::performContinousAnalysis()
{
//  int nMomentums = maxQ - minQ + 1;  // Longitud rango valores q
  int dataLenght = maxR - minR + 1;  // Longitud rango valores de radio
  
//  vector<double> qData(nMomentums);
//  vector<double> * dqData = new vector<double>(nMomentums);
  
  for (int q = minQ; q <= maxQ; ++q) {
    if (q != 1) {
      vector<double> * xData = new vector<double> (dataLenght);
      vector<double> * yData = new vector<double> (dataLenght);
      
      //    dqData->at(i) = calculateContinousDqValue(q, *xData, *yData);
      double dqValue = calculateContinousDqValue(q, *xData, *yData);
      dqValues->push_back(dqValue);
      
      linearRegressionValues.append(xData);
      linearRegressionValues.append(yData);
    }
  }
  
//  dqValues->push_back(dqData);
  
}

void SandBoxMethod::performDiscreteAnalysis()
{
  int dataLenght = maxR - minR + 1;  // Longitud rango valores de radio
  
  for (int q = minQ; q <= maxQ; ++q) {
//    if (q != 1) {
      TRACE (__LINE__ << "\n\t" << "q: " << q);
      vector<double> * xData = new vector<double> (dataLenght);
      vector<double> * yData = new vector<double> (dataLenght);
      
      double dqValue = calculateDiscreteDqValue(q, *xData, *yData);
      dqValues->push_back(dqValue);
      TRACE (__LINE__ << "\n\t" << "dqValue: " << dqValue );
      linearRegressionValues.append(xData);
      linearRegressionValues.append(yData);
//    }
  }
}

double SandBoxMethod::calculateContinousDqValue(const double & q, 
                                                vector<double> & xData,
                                                vector<double> & yData)
{
  int dataLenght = maxR - minR + 1;
  
  double massAverage;
  int fractalSize = cgrMatrix->getNumberOfRows(); 
  int index = 0;
  
  for (int radius = minR; radius <= maxR; ++radius) {
    // Sand box centers coordinates
    vector<int> xCoordinates(nCenters);
    vector<int> yCoordinates(nCenters);
    
    generateRandomCenters(&xCoordinates, &yCoordinates);
    vector <double> masses(nCenters);
    
    for (int i = 0; i < nCenters; ++i) {
      double count = countPointsOnTheContinousSquareSandbox(xCoordinates.at(i),
                                                            yCoordinates.at(i),
                                                            radius);
      
      masses.at(i) = pow(count, (q - 1.0));
    }
    
    massAverage = VectorTools::mean<double,double>(masses);
    double quotient = 
            (static_cast<double>(radius) / static_cast<double>(fractalSize));
    double tmpQ = (q - 1.0);

    xData.at(index) = tmpQ * log(quotient);
    yData.at(index) = log(massAverage);
    ++index;
    /*cout << "      DEBUG - SandBoxMethod::calculateDiscreteDqValue::401\n"
            "                      massAverage: " << massAverage << endl
         << "                            (q-1): " << tmpQ << endl
         << "                           radius: " << radius  << endl
         << "                      fractalSize: " << fractalSize << endl
         << "           (radius / fractalSize): " << quotient << endl
         << "          log(radius/fractalSize): " << log(quotient) << endl;*/
  }
  /*cout << "\n           Valores x e y:" << endl;
  for (unsigned int i = 0; i < xData.size(); ++i) {
    cout << "            "<< xData.at(i)<< ";" <<yData.at(i)<<endl;
  }*/
  
  Linear * linear = new Linear(dataLenght, &xData, &yData);
  double slope = linear->getSlope();
  delete linear;
  
  return slope;
}

double SandBoxMethod::calculateDiscreteDqValue(const double & q, 
                                               vector<double> & xData,
                                               vector<double> & yData)
{
  double DqValue = 0.0;
  if (q != 1) {
    int dataLenght = maxR - minR + 1;
    
    double massAverage;
    int fractalSize = cgrMatrix->getNumberOfRows(); 
    int index = 0;
    double qMinusOne = (q - 1.0);
    double probabilityDistribution = 0.0;
    double count = 0.0;
    
    /*// Sandbox centers coordinates
    vector<int> xCoordinates(nCenters);
    vector<int> yCoordinates(nCenters);
    generateRandomCenters(&xCoordinates, &yCoordinates);*/
    for (int radius = minR; radius <= maxR; ++radius) {
      vector <double> masses(nCenters);
      
      for (int i = 0; i < nCenters; ++i) {
        QPointF center = fractalPoints.at(indexesOfCenters.at(i));
        int xCenterCoordinate = utils::roundToInt(center.x());
        int yCenterCoordinate = utils::roundToInt(center.y());
        
        count = countPointsOnTheDiscreteSquareSandbox(xCenterCoordinate,
                                                      yCenterCoordinate,
                                                      radius);
        probabilityDistribution = count / totalPoints;
        masses.at(i) = pow(probabilityDistribution, qMinusOne);
        cout << "radius: " << radius << "   ->  count : " << count << endl;
      }
      
      massAverage = VectorTools::mean<double, double>(masses);
      double sizeRelation = 
              (static_cast<double>(radius) / static_cast<double>(fractalSize));
      
      //    xData.at(index) = qMinusOne * log(sizeRelation);
      xData.at(index) = log(sizeRelation);
      yData.at(index) = log(massAverage) / qMinusOne;
     /* TRACE (__LINE__ << "\n\t"  
         << "                      massAverage: " << massAverage << endl
         << "                            (q-1): " << qMinusOne << endl
         << "                           radius: " << radius  << endl
         << "           (radius / fractalSize): " << sizeRelation << endl
         << "          log(radius/fractalSize): " << log(sizeRelation) << endl
         << "                  xData.at(index): " << xData.at(index) << endl
         << "                  yData.at(index): " << yData.at(index) << endl
                 );*/
      ++index;
    }
    /*cout << "\n           Valores x e y:" << endl;
  for (unsigned int i = 0; i < xData.size(); ++i) {
    cout << "            "<< xData.at(i)<< ";" <<yData.at(i)<<endl;
  }*/
    
    Linear * linear = new Linear(dataLenght, &xData, &yData);
    DqValue = linear->getSlope();
    delete linear;
  }
  else if (q == 1) {
//    vector<double> xDataPlusEpsilon(xData.size());
//    vector<double> yDataPlusEpsilon(yData.size());
    vector<double> xDataMinusEpsilon(xData.size());
    vector<double> yDataMinusEpsilon(yData.size());
    double epsilon = 0.001;
    double DqPlusEpsilon = calculateDiscreteDqValue(q + epsilon, 
                                                    xData,
                                                    yData);
    
    double DqMinusEpsilon = calculateDiscreteDqValue(q + epsilon, 
                                                    xDataMinusEpsilon,
                                                    yDataMinusEpsilon);
    
    DqValue = (DqPlusEpsilon + DqMinusEpsilon) / 2;
  }
  
  return DqValue;
}

void SandBoxMethod::generateRandomCenters()
{
  int maxIndex = fractalPoints.size();
  int randomIndex = 0;
  
  for (int i = 0; i < nCenters; ++i) {
    randomIndex = RandomTools::giveIntRandomNumberBetweenZeroAndEntry(maxIndex);
    indexesOfCenters.append(randomIndex);
  }
} 

void SandBoxMethod::generateRandomCenters(vector<int> * xCoordinates,
                                          vector<int> * yCoordinates)
{
  vector<double> * xCoordinatesDouble =  new vector<double>(nCenters);
  vector<double> * yCoordinatesDouble =  new vector<double>(nCenters);
  
//  generateRandomCenters(&xCoordinatesDouble, &yCoordinatesDouble);
  generateRandomCenters(&*xCoordinatesDouble, &*yCoordinatesDouble);
  
  for (unsigned int i = 0; i < xCoordinatesDouble->size(); ++i) {
    int x = utils::roundToInt(xCoordinatesDouble->at(i));
    int y = utils::roundToInt(yCoordinatesDouble->at(i));
    
    xCoordinates->at(i) = x;
    yCoordinates->at(i) = y;
  }
  
  delete xCoordinatesDouble;
  delete yCoordinatesDouble;
}



void SandBoxMethod::generateRandomCenters(vector<double> * xCoordinates,
                                          vector<double> * yCoordinates)
{
  int maxIndex = fractalPoints.size();
  int randomIndex = 0;
          
  for (int i = 0; i < nCenters; ++i){
    randomIndex = RandomTools::giveIntRandomNumberBetweenZeroAndEntry(maxIndex);
    xCoordinates->at(i) = fractalPoints.at(randomIndex).x();
    yCoordinates->at(i) = fractalPoints.at(randomIndex).y();
//    cout << xCoordinates->at(i) << "," << yCoordinates->at(i) << endl;
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
          qLowerBound(fractalPoints.begin(), fractalPoints.end(),
                      lowerBoundPoint, xCoordinateLessThan);
  
  QList<QPointF>::Iterator upperBound = 
          qUpperBound(fractalPoints.begin(), fractalPoints.end(),
                      upperBoundPoint, xCoordinateLessThan);
  
  int beginPosition = static_cast<int>(lowerBound - fractalPoints.begin());
  int endPosition   = static_cast<int>(upperBound - fractalPoints.begin());
  int length        = endPosition - beginPosition;
  
  QList<QPointF> subList = fractalPoints.mid(beginPosition, length);
  
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

double SandBoxMethod::countPointsOnTheDiscreteSquareSandbox(const int & x, 
                                                            const int & y, 
                                                            const int & radius)
{
  /*double sum   = 0.0;
   
  if (radius > 0) {
    int minIndex = 0;
    int maxIndex = cgrMatrix->getNumberOfRows() - 1;
    int initRow  = maxIndex - (y + radius);
    int initCol  = x - radius;
//    int endRow   = maxIndex - (y - radius);
    int endRow   = maxIndex - (y - radius) - 1;
//    int endCol   = x + radius;
    int endCol   = x + radius - 1;
    
    if (initRow < minIndex)
      initRow = 0;
    
    if (initCol < minIndex)
      initCol = 0;
    
    if (endCol > maxIndex)
      endCol = maxIndex;
    
    if (endRow > maxIndex)
      endRow = maxIndex;
    
    
    cout << "\n\nDEBUG -- SandBoxMethod::605" << endl;
    cout << "centro:  (" << x << ", " << y << ") " << "(" << maxRow - y << ", " << x << ")  "<< endl;
    cout << "inicial: (" << initRow << ", " << initCol << ")  "<< endl;
    cout << "final:   (" << endRow << ", " << endCol << ")  "<< endl;
    
    for (int row = initRow; row <= endRow; ++row) {
      for (int col = initCol; col <= endCol; ++col) {
        sum = sum + (*cgrMatrix)(row, col);
      }
    }
  }
  else if (radius == 0) {
    sum += (*cgrMatrix)(y, x);
  }*/
  
  double sum = 0.0;
  
  if (radius > 0) {
    int minIndex = 0;
    int maxIndex = cgrMatrix->getNumberOfRows() - 1;
    int initX = x - radius;
    int initY = y - radius;
    int endX  = x + radius - 1; 
    int endY  = y + radius - 1;
    
    if (initX < minIndex)
      initX = 0;
    
    if (initY < minIndex)
      initY = 0;
    
    if (endX > maxIndex)
      endX = maxIndex;
    
    if (endY > maxIndex)
      endY = maxIndex;
    for (int i = initX; i <= endX; ++i) {
      for (int j = initY; j <= endY; ++j) {
        sum = sum + (*cgrMatrix)(i, j);
      }
    }
  }
  else if (radius == 0) {
    sum += (*cgrMatrix)(x, y);
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

int SandBoxMethod::getTotalPoints()
{
  return totalPoints;
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

const QList<QPointF> SandBoxMethod::getFractalPoints() const
{
  return fractalPoints;
}

void SandBoxMethod::setFractalPoints(const QList<QPointF> & fractalPoints)
{
  this->fractalPoints = fractalPoints;
}

QList<int> SandBoxMethod::getIndexesOfCenters()
{
  return indexesOfCenters;
}

void SandBoxMethod::setIndexesOfCenters(QList<int> indexesOfCenters)
{
  this->indexesOfCenters = indexesOfCenters;
}
