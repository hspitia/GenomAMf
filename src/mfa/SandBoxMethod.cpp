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

SandBoxMethod::SandBoxMethod()
{
  this->minQ = -70;
  this->maxQ =  70;
  this->minR = 0;
  this->maxR = 1;
  this->cgrMatrix = 0;
  this->nCenters = 150;
  this->dqValues = new QList<vector<double> >();
  this->linearRegressionValues = new QList<vector<double> >();
//  this->coordinatesOfPoints = new QList<QPointF>();
  this->coordinatesOfPoints = QList<QPointF> ();
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
  this->dqValues = sandBoxObject.dqValues;
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
  this->dqValues = new QList<vector<double> >();
  this->linearRegressionValues = new QList<vector<double> >();
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
  this->dqValues = new QList<vector<double> >();
  this->linearRegressionValues = new QList<vector<double> >();
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
  this->dqValues = sandBoxObject.dqValues;
  this->linearRegressionValues = sandBoxObject.linearRegressionValues;
  this->coordinatesOfPoints = QList<QPointF>(sandBoxObject.coordinatesOfPoints);
//          new QList<QPointF>(*(sandBoxObject.coordinatesOfPoints));
//  this->fractalSize = sandBoxObject.fractalSize;
  return *this;
}

SandBoxMethod::~SandBoxMethod()
{
  if(cgrMatrix != 0) cgrMatrix = 0;
  delete cgrMatrix;
  dqValues->clear();
  linearRegressionValues->clear();
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
    default:
      return;
  }  
}

void SandBoxMethod::performContinousAnalisys()
{
  int nMomentums = maxQ - minQ + 1;
  int dataLenght = maxR - minR + 1;
  
  
  vector<double> qData(nMomentums);
  vector<double> dqData(nMomentums);

  vector<double> xData(dataLenght);
  vector<double> yData(dataLenght);
  
  for (int genIt = 0; genIt < 4; ++genIt)
  {
    vector<double> xCoordinates(nCenters);
    vector<double> yCoordinates(nCenters);
    
    generateRandomCenters(&xCoordinates, &yCoordinates);
    /* 
    cout << "Centros: x "<< endl;
    VectorTools::print(xCoordinates);
    cout << "Centros: y "<< endl;
    VectorTools::print(yCoordinates);
     */
    
    //  for (int i = 0; i < dataLenght; ++i)
    double radio = 3.0;
//    cout << "No.\tCENTROS\tPROMEDIO\tRADIO" << endl; 
    cout << "No.;CENTROS;PROMEDIO;RADIO" << endl; 
    for (unsigned int current = 0; current <= 10; ++current) {
      unsigned int centers = 20 + (current * 10);
//      cout << current + 1 << "\t" << centers;
      cout << current + 1 << ";" << centers;
      vector <double> * counts =  new vector<double>();
      for (unsigned int i = 0; i < centers; ++i) {
        counts->push_back(countPointsOnTheSquareSandbox(xCoordinates.at(i),
                                                        yCoordinates.at(i),
                                                        radio));
      }
      //    cout << "  \nConteos: ";
      //    VectorTools::print(*counts);
      //    cout << "Promedio: ";
//      cout << "\t\t" << VectorTools::mean<double, double>(*counts) 
      cout << ";" << VectorTools::mean<double, double>(*counts) 
//      << "\t\t" << radio << endl;
      << ";" << radio << endl;
      //    counts->clear();
      delete counts;
    }
    cout << endl;
  }
  /*
  for (int q = minQ, index = 0; q <= maxQ; ++q, ++index)
  {
    vector<double> xData(dataLenght);
    vector<double> yData(dataLenght);
    
    qData.at(index) = q;
    dqData.at(index) = calculateDqValue(q, xData, yData);
    
//    linearRegressionValues->append(xData);
//    linearRegressionValues->append(yData);
  }*/
//  dqValues->append(qData);
//  dqValues->append(dqData);
}

void SandBoxMethod::performDiscreteAnalisys()
{
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
}

double SandBoxMethod::calculateDqValue(const int & q, 
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
              pow(countPointsOnTheSquareSandbox(xCoordinates.at(i),
                                                yCoordinates.at(i),
                                                radius),
                                                static_cast<double>(q - 1));
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
//  int maxNumber = static_cast<int>(cgrMatrix->nRows()) + 1;
  int maxNumber = static_cast<int>(cgrMatrix->getNumberOfRows()) + 1;
//  int maxNumber = 1024;
  for (int i = 0; i < nCenters; ++i)
  {
    xCoordinates->at(i) = RandomTools::
            giveIntRandomNumberBetweenZeroAndEntry(maxNumber);
    yCoordinates->at(i) = RandomTools::
            giveIntRandomNumberBetweenZeroAndEntry(maxNumber);
//    cout << "x: " << xCoordinates->at(i) 
//         << "  y: " << yCoordinates->at(i) << endl;
  }
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
bool pointLessThan(const QPointF & x1, const QPointF & x2)
{
  return x1.x() < x2.x();
//  && x1.y() > x2.y();
}

bool xCoordinateLessThan(const QPointF & x1, const QPointF & x2)
{
  return x1.x() < x2.x();
}

bool yCoordinateLessThan(const QPointF & y1, const QPointF & y2)
{
  return y1.y() < y2.y();
}

double SandBoxMethod::countPointsOnTheSquareSandbox(const double & x,
                                                    const double & y,
                                                    const double & radius)
{
  double sum = 0.0;
  
  double minX = x - radius;
  double maxX = x + radius;
  double minY = y - radius;
  double maxY = y + radius;
  
  qSort(coordinatesOfPoints.begin(), coordinatesOfPoints.end(), 
        xCoordinateLessThan);
  /*cout << "Lista de puntos ordenada (por coordenada x): " << endl;
  int count = 0;
  foreach(QPointF p, coordinatesOfPoints){
    cout << count <<" (" << p.x() << ", " << p.y() << ")  ";
    ++count;
  }
  
  QPointF lookFor = QPointF(x,y);
  cout << "\n\nlookFor:    (" << lookFor.x() << ", " << lookFor.y() << ")" << endl;
  
  QList<QPointF>::Iterator center = 
          qBinaryFind(coordinatesOfPoints.begin(), coordinatesOfPoints.end(),
                      lookFor,
                      xCoordinateLessThan);
  
  if(center != coordinatesOfPoints.end())
    cout << "Encontrado: (" << center->x() << ", " << center->y() << ") " 
         << endl;
  else
    cout << "No" << endl;
  */
//  cout << "center: " << "(" << x << ", " << y << ") "<< endl;
  QPointF lowerBoundPoint = QPointF(minX, minY);
  QPointF upperBoundPoint = QPointF(maxX, maxY);
//  cout << "lowerBoundPoint: "; 
//  cout << "(" << lowerBoundPoint.x() << ", " << lowerBoundPoint.y() << ") " << endl;
//  cout << "upperBoundPoint: "; 
//  cout << "(" << upperBoundPoint.x() << ", " << upperBoundPoint.y() << ") " << endl;
  
  QList<QPointF>::Iterator lowerBound = 
          qLowerBound(coordinatesOfPoints.begin(), coordinatesOfPoints.end(),
                      lowerBoundPoint, xCoordinateLessThan);
  
  QList<QPointF>::Iterator upperBound = 
          qUpperBound(coordinatesOfPoints.begin(), coordinatesOfPoints.end(),
                      upperBoundPoint, xCoordinateLessThan);
  
  int beginPosition = (int)(lowerBound - coordinatesOfPoints.begin());
  int endPosition = (int)(upperBound - coordinatesOfPoints.begin());
  int length = endPosition - beginPosition;
  
//  cout << "beginPosition: " << beginPosition << endl;
//  cout << "endPosition: " << endPosition << endl;
  /*
  int beg = beginPosition;
  int en = endPosition;
  if(beginPosition > 0) 
    --beg;
  
  if(endPosition < coordinatesOfPoints.count() - 1)
    ++en;
  
  for (int i = beg; i < en; ++i)
  {
    cout << "(" << coordinatesOfPoints.at(i).x() << ", " << coordinatesOfPoints.at(i).y() << ") " << endl;
  }
  */
  QList<QPointF> subList = coordinatesOfPoints.mid(beginPosition, length);
  
  qSort(subList.begin(), subList.end(), yCoordinateLessThan);
  
  /*cout << "Sublista ordenada por y: " << endl;
  foreach(QPointF p, subList)
    cout << "(" << p.x() << ", " << p.y() << ") ";
  
  cout << endl;*/
  
  lowerBoundPoint = QPointF(minX, minY);
  upperBoundPoint = QPointF(maxX, maxY);
//  cout << "lowerBoundPoint: "; 
//  cout << "(" << lowerBoundPoint.x() << ", " << lowerBoundPoint.y() << ") " << endl;
//  cout << "upperBoundPoint: "; 
//  cout << "(" << upperBoundPoint.x() << ", " << upperBoundPoint.y() << ") " << endl;
  
  lowerBound = 
          qLowerBound(subList.begin(), subList.end(),
                      lowerBoundPoint, yCoordinateLessThan);
  
  upperBound = 
          qUpperBound(subList.begin(), subList.end(),
                      upperBoundPoint, yCoordinateLessThan);
  
  beginPosition = (int)(lowerBound - subList.begin());
  endPosition = (int)(upperBound - subList.begin());
  length = endPosition - beginPosition;
  sum = static_cast<double>(endPosition - beginPosition);
  
//  cout << "beginPosition: " << beginPosition << endl;
//  cout << "endPosition: " << endPosition << endl;
  /*
  beg = beginPosition;
  en = endPosition;
  
  
  for (int i = beg; i < en; ++i)
  {
    cout << "(" << subList.at(i).x() << ", " << subList.at(i).y() << ") " << endl;
  }
  cout << "DEBUG " << endl;
  */
//  cout << "\n\nTotal puntos: " << length << endl;
  
  /*subList = subList.mid(beginPosition, length);
  foreach(QPointF p, subList)
    cout << "(" << p.x() << ", " << p.y() << ") ";
  */
  return sum;
}

double SandBoxMethod::countPointsOnTheSquareSandbox(const int & x, // col
                                                    const int & y, // row
                                                    const int & radius)
{
  double sum = 0.0;
  
  if (radius > 0) 
  {
    int minValue = 0;
//    int maxValue = cgrMatrix->nRows() - 1;
    int maxValue = cgrMatrix->getNumberOfRows() - 1;
//    int half = floor(radius / 2);
    int initRow = y - radius;
    int initCol = x - radius;
    int endRow = initRow + radius;
    int endCol = initCol + radius;
    
    if (initRow < minValue) initRow = 0;
    if (initCol < minValue) initCol = 0;
    
    if (endCol > maxValue) endCol = maxValue;
    if (endRow > maxValue) endRow = maxValue;
    
    for (int row = initRow; row <= endRow; ++row)
    {
      for (int col = initCol; col <= endCol; ++col)
      {
        sum = sum + (*cgrMatrix)(row, col);
      }
    }
  }
  else if (radius == 0){
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

QList<vector<double> > * SandBoxMethod::getDqValues()
{
  return dqValues;
}

void SandBoxMethod::setDqValues(QList<vector<double> > * dqValues)
{
  this->dqValues = dqValues;
}


//int SandBoxMethod::getFractalSize()
//{
//  return fractalSize;
//}

//void SandBoxMethod::setFractalSize(int fractalSize)
//{
//  this->fractalSize = fractalSize;
//}

QList<vector<double> > * SandBoxMethod::getLinearRegressionValues()
{
  return linearRegressionValues;
}

void SandBoxMethod::setLinearRegressionValues(QList<vector<double> > * 
                                              linearRegressionValues)
{
  this->linearRegressionValues = linearRegressionValues;
}


const QList<QPointF> SandBoxMethod::getCoordinatesOfPoints() const
{
  return coordinatesOfPoints;
}

void SandBoxMethod::setCoordinatesOfPoints(const QList<QPointF> & 
                                           coordinatesOfPoints)
{
  this->coordinatesOfPoints = coordinatesOfPoints;
}

