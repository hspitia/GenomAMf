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
  this->mfaParametersSet          = MfaParametersSet();
  this->cgrMatrix                 =    0;
  this->cumulativeFrequencyMatrix =    0;                                 
  this->indexesOfCenters          = QVector<int>();
  this->dqValues                  = new vector<double>();
  this->linearRegressionValues    = QList<vector<double> *>();
  this->fractalPoints             = QList<QPointF>();
}

/*SandBoxMethod::SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                             const RowMatrix<int> * cumulativeFrequencyMatrix,
                             const int & totalPoints,
                             const int & minQ,
                             const int & maxQ,
                             const int & nCenters,
                             const int & radiusStep)
{
  this->mfaParametersSet          = MfaParametersSet(); 
  this->totalPoints               = totalPoints;
  this->cgrMatrix                 = cgrMatrix;
  this->cumulativeFrequencyMatrix = cumulativeFrequencyMatrix;
  this->indexesOfCenters          = QVector<int>();
  this->dqValues                  = new vector<double>();
  this->linearRegressionValues    = QList<vector<double> *>();
  this->fractalPoints             = QList<QPointF>();
}

SandBoxMethod::SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                             const RowMatrix<int> * cumulativeFrequencyMatrix,
                             const QList<QPointF> & fractalPoints,
                             const int & minQ,
                             const int & maxQ,
                             const int & nCenters,
                             const int & radiusStep)
{
  this->mfaParametersSet          = MfaParametersSet();
  this->totalPoints               = fractalPoints.count();
  this->cgrMatrix                 = cgrMatrix;
  this->cumulativeFrequencyMatrix = cumulativeFrequencyMatrix;
  this->indexesOfCenters          = QVector<int>();
  this->dqValues                  = new vector<double>();
  this->linearRegressionValues    = QList<vector<double> *>();
  this->fractalPoints             = QList<QPointF>(fractalPoints);
}*/

SandBoxMethod::SandBoxMethod(const RowMatrix<int> * cgrMatrix,
                             const RowMatrix<int> * cumulativeFrequencyMatrix,
                             const QList<QPointF> & fractalPoints,
                             const int & totalPoints,
                             const MfaParametersSet & mfaParametersSet)
{
  this->mfaParametersSet          = mfaParametersSet;
  this->totalPoints               = totalPoints;
  this->cgrMatrix                 = cgrMatrix;
  this->cumulativeFrequencyMatrix = cumulativeFrequencyMatrix;
  this->indexesOfCenters          = QVector<int>();
  this->dqValues                  = new vector<double>();
  this->linearRegressionValues    = QList<vector<double> *>();
  this->fractalPoints             = QList<QPointF>(fractalPoints);
  this->qValuesForRegressionPlot  = vector<int>();
}

SandBoxMethod::SandBoxMethod(const SandBoxMethod & sandBoxObject)
{
  this->mfaParametersSet          = sandBoxObject.mfaParametersSet;
  this->totalPoints               = sandBoxObject.totalPoints;
  this->cgrMatrix                 = sandBoxObject.cgrMatrix;
  this->cumulativeFrequencyMatrix = sandBoxObject.cumulativeFrequencyMatrix;
  this->indexesOfCenters          = sandBoxObject.indexesOfCenters;
  this->dqValues                  = new vector<double>(*sandBoxObject.dqValues);
  this->linearRegressionValues    = sandBoxObject.linearRegressionValues;
  this->fractalPoints             = sandBoxObject.fractalPoints; 
  this->qValuesForRegressionPlot  = sandBoxObject.qValuesForRegressionPlot;
}

SandBoxMethod & SandBoxMethod::operator=(const SandBoxMethod & sandBoxObject)
{
  this->mfaParametersSet          = sandBoxObject.mfaParametersSet;
  this->totalPoints               = sandBoxObject.totalPoints;
  this->cgrMatrix                 = sandBoxObject.cgrMatrix;
  this->cumulativeFrequencyMatrix = sandBoxObject.cumulativeFrequencyMatrix;
  this->indexesOfCenters          = sandBoxObject.indexesOfCenters;
  this->dqValues                  = new vector<double>(*sandBoxObject.dqValues);
  this->linearRegressionValues    = sandBoxObject.linearRegressionValues;
  this->fractalPoints             = sandBoxObject.fractalPoints;
  this->qValuesForRegressionPlot  = sandBoxObject.qValuesForRegressionPlot;
  
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
  
  int nIteraciones = mfaParametersSet.getNIterations();
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
    vector<int> xCoordinates(mfaParametersSet.getNCenters());
    vector<int> yCoordinates(mfaParametersSet.getNCenters());
    
    vector<double> xCoordinatesDouble(mfaParametersSet.getNCenters());
    vector<double> yCoordinatesDouble(mfaParametersSet.getNCenters());
    
    generateRandomCenters(&xCoordinatesDouble, &yCoordinatesDouble);
    
    for (unsigned int i = 0; i < xCoordinatesDouble.size(); ++i) {
//      double  xTmp = utils::roundToHalf(xCoordinatesDouble.at(i));
//      double  yTmp = utils::roundToHalf(yCoordinatesDouble.at(i));
      double  xTmp = utils::roundToInt(xCoordinatesDouble.at(i));
      double  yTmp = utils::roundToInt(yCoordinatesDouble.at(i));
      
//      int x = static_cast<int> (xTmp - 0.5);
//      int y = static_cast<int> (yTmp - 0.5);
      int x = static_cast<int> (xTmp);
      int y = static_cast<int> (yTmp);
      
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
  int dataLenght = mfaParametersSet.getMaxR() - mfaParametersSet.getMinR() + 1;  // Longitud rango valores de radio
  
//  vector<double> qData(nMomentums);
//  vector<double> * dqData = new vector<double>(nMomentums);
  
  for (int q = mfaParametersSet.getMinQ(); q <= mfaParametersSet.getMaxQ(); ++q) 
  {
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
  // Longitud rango valores de radio
  int dataLenght = static_cast<int>(ceil((mfaParametersSet.getMaxR() - 
          mfaParametersSet.getMinR()+ 1) / mfaParametersSet.getRadiusStep()));
  
  int iterations = mfaParametersSet.getNIterations(); // TODO - cambio - iteraciones
  
  int numberOfQ = 
          mfaParametersSet.getMaxQ() - mfaParametersSet.getMinQ() + 1;
  
  
  vector<double> * sizeRelations;
  QList<vector<double> *> tmpDqList; //  Para promedio de los Dq de las iteraciones
  
  QList<QList<vector<double> > > linearRegressionList; //  Para archivo CSV de análisis
  QList<vector<double> > regressionSubList; //  Para archivo CSV de análisis
  
  QList<vector<double> *> regressionSumations; // Para promedio de regresiones
  int indexOfQRegValues = 0;
  
  for (int i = 0; i < numberOfQ; ++i) {
    tmpDqList.append(new vector<double>(iterations));
//    tmpYDataLinearRegresionList.append(new vector<double>(iterations));
  }
  
  for (int i = 0; i < static_cast<int>(qValuesForRegressionPlot.size()); ++i) {
    regressionSumations.append(new vector<double>(dataLenght, 0.0)); // sumas datos x
    regressionSumations.append(new vector<double>(dataLenght, 0.0)); // sumas datos y
  }
  
  vector<double> * xDataLinearRegression = 0; // Datos x regresión lineal
  vector<double> * yDataLinearRegression = 0; // Datos y regresión lineal
  
  vector<int> * xCenterCoordinates = 
          new vector<int>(mfaParametersSet.getNCenters());
  vector<int> * yCenterCoordinates = 
          new vector<int>(mfaParametersSet.getNCenters());
  
  for (int i = 0; i < iterations; ++i) {
    // Generación centros aleatorios
    generateRandomCenters(xCenterCoordinates, yCenterCoordinates);
    
    sizeRelations = new vector<double>(dataLenght); // vector que contiene los valores ln(R/L)
    // Cálculo distribuciones de probabilidad (conteo en sand boxes)
    QList<vector<double> > * distributionsList = 
            calculateDistributionProbabilities(*sizeRelations, 
                                               xCenterCoordinates,
                                               yCenterCoordinates);
    // Cálculo de valores Dq
//    double q = static_cast<double>(minQ);
    double q = static_cast<double>(mfaParametersSet.getMinQ());
    
    regressionSubList = QList<vector<double> >();
    
    indexOfQRegValues = 0;
    
    // Iteracion a través de los valores q en el rango [Qmin, Qmax]
    for (int qIndex = 0; qIndex < numberOfQ; ++qIndex) {
      xDataLinearRegression = new vector<double>(dataLenght);
      yDataLinearRegression = new vector<double>(dataLenght);
      
      double dqValue = calculateDiscreteDqValue(q, 
                                                distributionsList,
                                                *sizeRelations,
                                                *xDataLinearRegression,
                                                *yDataLinearRegression);
      
      tmpDqList.at(qIndex)->at(i) = dqValue; // 

      regressionSubList.append(*xDataLinearRegression); // Para Archivo CSV de análisis
      regressionSubList.append(*yDataLinearRegression); // Para Archivo CSV de análisis
      
      // Suma de valores de regresión para los q especificados en qValuesForregressionPlot
      int tmpQ = static_cast<int>(q);
      if (tmpQ == qValuesForRegressionPlot.at(indexOfQRegValues)) {
        for (int k = 0; k < dataLenght; ++k) {
          int listIndex = indexOfQRegValues * 2;
          regressionSumations.at(listIndex)->at(k) += 
                  xDataLinearRegression->at(k);
          
          regressionSumations.at(listIndex + 1)->at(k) += 
                  yDataLinearRegression->at(k);
        }
        if (indexOfQRegValues < 
                static_cast<int>(qValuesForRegressionPlot.size() - 1)) 
          ++indexOfQRegValues;
      }
      q += 1;
    }
    
    delete distributionsList;
    linearRegressionList.append(regressionSubList);
  }
  
  delete xCenterCoordinates;
  delete yCenterCoordinates;
  
  // Promedio de valores Dq
  double average = 0.0;
  for (int i = 0; i < tmpDqList.count(); ++i) {
    average = VectorTools::mean<double, double>(*(tmpDqList.at(i)));
    dqValues->push_back(average);
  }
  
  // Promedio de regresiones
  for (int i = 0; i < regressionSumations.count(); ++i) {
    for (int j = 0; j < dataLenght; ++j) {
      regressionSumations.at(i)->at(j) /= iterations;
    }
  }
  linearRegressionValues.append(regressionSumations);
  
  
  
  exportToCsv(tmpDqList);
  exportRegressionsToCsv(regressionSumations);
//  exportRegressionsToCsv(linearRegressionList);
  
//  linearRegressionValues.append(xDataLinearRegression);
//  linearRegressionValues.append(yDataLinearRegression);
 // ---------------------------------------------------------------------------
  
 
  
}

bool SandBoxMethod::exportToCsv(const QList<vector<double> *> & dqList)
{
  QString outString = "";
  int q = mfaParametersSet.getMinQ();// minQ;
  /*for (int i = 0; i < dqList.count(); ++i) {
    outString += QString::number(q) + ";";
    for (unsigned int j = 0; j < dqList.at(i)->size(); ++j) {
      outString += QString::number(dqList.at(i)->at(j));
      
      if (j != dqList.at(i)->size() - 1)
        outString += ";";
      
    }
    outString += "\n";
    ++q;
  }*/
  for (unsigned int j = 0; j < dqList.count(); ++j) {
    outString += QString("%1").arg(q) + ";";
    ++q;
  }
  outString += "\n";
  
  for (unsigned int i = 0; i < dqList.at(0)->size(); ++i) {
    for (int j = 0; j < dqList.count(); ++j) {
      outString += QString("%1").arg(dqList.at(j)->at(i), 0, 'g', 9);
      
      if (j != dqList.count() - 1)
        outString += ";";
      
    }
    outString += "\n";
    ++q;
  }
  
  QFile file("data/dq_iteration_values.csv");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;
  
  QTextStream out(&file);
  out << outString;
  
  return true;
}

bool SandBoxMethod::
exportRegressionsToCsv(const QList<QList<vector<double> > > &
                       linearRegressionsList)
{
  int nIterations = linearRegressionsList.count();
  int nRadii      = linearRegressionsList.at(0).at(0).size();
  int nVectorData = linearRegressionsList.at(0).count();
  QString outString = "";
  QString separator = ";";
  QString linefeed  = "\n";

  for (int i = 0; i < nIterations; ++i) {
    QList<vector<double> > current = linearRegressionsList.at(i);
    
    // headers
    for (int k = 0; k < nVectorData; k += 2) {
      outString += "x" + separator + "y";
      if (k != nVectorData - 2) 
        outString += separator;
    }
    outString += linefeed;
    
    // Content
    for (int j = 0; j < nRadii; ++j) {
      for (int k = 0; k < nVectorData; k += 2) {
        outString += QString::number(current.at(k).at(j)) +     // dato x 
                     separator + 
                     QString::number(current.at(k + 1).at(j));  // dato y
        if (k != nVectorData - 2) 
          outString += separator;
      }
      outString += linefeed;
    }
    outString += linefeed;
    outString += linefeed;
  }
  
  QFile file("data/regression_values.csv");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;
  
  QTextStream out(&file);
  out << outString;
  
  return true;
}

bool SandBoxMethod::
exportRegressionsToCsv(const QList<vector<double> * > &
                       linearRegressionsList)
{
  int nVectorData = linearRegressionsList.count();
  int dataLength =  linearRegressionsList.at(0)->size();
  QString outString = "";
  QString separator = ";";
  QString linefeed  = "\n";
  
   // headers
  for (int k = 0; k < nVectorData; k += 2) {
    outString += "x" + separator + "y";
    if (k != nVectorData - 2) 
      outString += separator;
  }
  outString += linefeed;
    
  for (int i = 0; i < dataLength; ++i) {
    // Content
    for (int j = 0; j < nVectorData; ++j) {
      outString += QString::number(linearRegressionsList.at(j)->at(i));     // dato x 
      if (j != nVectorData - 1) 
        outString += separator;
    }
    outString += linefeed;
  }
  
  QFile file("data/regression_values_for_plot.csv");
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;
  
  QTextStream out(&file);
  out << outString;
  
  return true;
}

/*void SandBoxMethod::performDiscreteAnalysis_()
{
  int dataLenght = maxR - minR + 1;  // Longitud rango valores de radio
  
  DEBUG ("Coeficiente regresión;q;Dq");
  for (int q = minQ; q <= maxQ; ++q) {
    vector<double> * xData = new vector<double> (dataLenght);
    vector<double> * yData = new vector<double> (dataLenght);
    
    double dqValue = calculateDiscreteDqValue((double) q, *xData, *yData);
    dqValues->push_back(dqValue);
    linearRegressionValues.append(xData);
    linearRegressionValues.append(yData);
  }
}*/

double SandBoxMethod::calculateContinousDqValue(const double & q, 
                                                vector<double> & xData,
                                                vector<double> & yData)
{
//  int dataLenght = maxR - minR + 1;
  int dataLenght = mfaParametersSet.getMaxR() - mfaParametersSet.getMinR() + 1;
  
  double massAverage;
  int fractalSize = cgrMatrix->getNumberOfRows(); 
  int index = 0;
  
//  for (int radius = minR; radius <= maxR; ++radius) {
  for (int radius = mfaParametersSet.getMinR(); 
       radius <= mfaParametersSet.getMaxR(); ++radius) {
    // Sand box centers coordinates
//    vector<int> xCoordinates(nCenters);
//    vector<int> yCoordinates(nCenters);
    vector<int> xCoordinates(mfaParametersSet.getNCenters());
    vector<int> yCoordinates(mfaParametersSet.getNCenters());
    
    generateRandomCenters(&xCoordinates, &yCoordinates);
    vector <double> masses(mfaParametersSet.getNCenters());
    
    for (int i = 0; i < mfaParametersSet.getNCenters(); ++i) {
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
  }
  
  Linear * linear = new Linear(dataLenght, &xData, &yData);
  double slope = linear->getSlope();
  delete linear;
  
  return slope;
}

double SandBoxMethod::calculateDiscreteDqValue(const double & q,
                                               QList<vector<double> > * 
                                               distributionsList,
                                               vector<double> & 
                                               sizeRelations,
                                               vector<double> & 
                                               xDataLinearRegression,
                                               vector<double> & 
                                               yDataLinearRegression)
{
  int dataLenght = distributionsList->count(); // Número de radios en el rango
  double qMinusOne = 0.0;
  double dqValue = 0.0;
  
  if (q != 1) {
    qMinusOne = q - 1.0;
    
    for (int j = 0; j < dataLenght; ++j) {
      // [M(R)/Mo]^(q-1) 
//      vector<double> tmpDistributions = 
//              VectorTools::pow<double>(distributionsList->at(j), qMinusOne);
//      
//      // <[M(R)/Mo]^(q-1)>  promedio
//      double probDistributionsAverage = 
//              VectorTools::mean<double, double>(tmpDistributions);
      
      double sum = 0.0;
      int nElements =  static_cast<int>(distributionsList->at(j).size());
      for (int k = 0; k < nElements; ++k) {
        sum += std::pow(distributionsList->at(j).at(k), qMinusOne);
      }
      
      double probDistributionsAverage = sum / static_cast<double>(nElements);
              
//      yDataLinearRegression.at(j) = log(probDistributionsAverage); // Yu - TODO - cambio - Formula ProbDistibution
      yDataLinearRegression.at(j) = log(probDistributionsAverage) / qMinusOne; // Otro - TODO - cambio - Formula ProbDistibution
      
        double sizeRelation = sizeRelations.at(j);
//        xDataLinearRegression.at(j) = sizeRelation * qMinusOne; // Yu - TODO - cambio - Formula SizeRelation
        xDataLinearRegression.at(j) = sizeRelation; // Otro - TODO - cambio - Formula SizeRelation
    }
    
//    MatrixTools::print(xDataLinearRegression);
//    MatrixTools::print(yDataLinearRegression);
    
    Linear * linear = new Linear(dataLenght, &xDataLinearRegression, 
                                 &yDataLinearRegression);
    
    dqValue = linear->getSlope();
    delete linear;
  }
  
  else if (q == 1) {
    vector<double> xDataPlusEpsilon(xDataLinearRegression.size());
    vector<double> yDataPlusEpsilon(yDataLinearRegression.size());
//    vector<double> xDataMinusEpsilon(xDataLinearRegression.size());
//    vector<double> yDataMinusEpsilon(yDataLinearRegression.size());
    double epsilon = 0.001;
    double dqMinusEpsilon = calculateDiscreteDqValue(q - epsilon,
                                                     distributionsList,
                                                     sizeRelations,
                                                     xDataLinearRegression,
                                                     yDataLinearRegression);
    
    double dqPlusEpsilon = calculateDiscreteDqValue(q + epsilon,
                                                    distributionsList,
                                                    sizeRelations,
                                                    xDataPlusEpsilon,
                                                    yDataPlusEpsilon);
    
    dqValue = (dqMinusEpsilon + dqPlusEpsilon) / 2;
    
    for (int i = 0; i < dataLenght; ++i) {
      xDataLinearRegression.at(i) = 
              (xDataLinearRegression.at(i) + xDataPlusEpsilon.at(i)) / 2;
    }
    
  }
  
  return dqValue;
}

QList<vector<double> > * 
SandBoxMethod::calculateDistributionProbabilities(vector<double> & 
                                                  xDataLinearRegression,
                                                  vector<int> *
                                                  xCenterCoordinates,
                                                  vector<int> *
                                                  yCenterCoordinates)
{
  QList<vector<double> > * distributionList = new QList<vector<double> >();
  int fractalSize = cgrMatrix->getNumberOfRows();// - 1; // Menos 1 por ser matriz ampliada ??
  double count = 0.0;
  double probabilityDistributionValue = 0.0;
  int dataLenght = xDataLinearRegression.size(); 
  int radius = mfaParametersSet.getMinR();
  
  for (int radiusIndex = 0; radiusIndex < dataLenght; ++radiusIndex) {
    vector<double> probabilityDistributions(mfaParametersSet.getNCenters());
    
    for (int i = 0; i < mfaParametersSet.getNCenters(); ++i) {
//      QPointF center = fractalPoints.at(indexesOfCenters.at(i));
//      int xCenterCoordinate = utils::roundToInt(center.x());
//      int yCenterCoordinate = utils::roundToInt(center.y());
      int xCenterCoordinate = xCenterCoordinates->at(i);
      int yCenterCoordinate = yCenterCoordinates->at(i);
      
      count = countPointsOnTheDiscreteSquareSandbox(xCenterCoordinate,
                                                    yCenterCoordinate,
                                                    radius);
//      probabilityDistributionValue = count; // Yu -> M(R) TODO - cambio - Formula masas M(R)
      probabilityDistributionValue = count / totalPoints; // Vicsek - Stosic -> M(R)/Mo TODO - cambio - Formula masas M(R)
      probabilityDistributions.at(i) = probabilityDistributionValue;
    }
    // Probabilidades de distribución
    distributionList->append(probabilityDistributions);
    
    // Dato x para regresión lineal -> ln(R/L)
//    double rad = static_cast<double>(radius); // cambio - Fórmula - Yu? - Dimension del radio
    double rad = (static_cast<double>(radius) * 2.0) + 1.0; // cambio - Fórmula - Vicsek - Dimension del radio
    double sizeRelation = 
              (static_cast<double>(rad) / static_cast<double>(fractalSize));
    
    xDataLinearRegression.at(radiusIndex) = log(sizeRelation);
    radius += mfaParametersSet.getRadiusStep();
  }
  return distributionList;
}

void SandBoxMethod::generateRandomCenters()
{
  int maxIndex = fractalPoints.size();
  int randomIndex = 0;
//  indexesOfCenters = QList<int>();
//  indexesOfCenters = QVector<int>(nCenters);
  indexesOfCenters = QVector<int>(mfaParametersSet.getNCenters());
          
  for (int i = 0; i < mfaParametersSet.getNCenters(); ++i) {
    randomIndex = RandomTools::giveIntRandomNumberBetweenZeroAndEntry(maxIndex);
    indexesOfCenters[i] = randomIndex;
  }
} 

// SIN usar la lista de puntos con precisión real  
void SandBoxMethod::generateRandomCenters(vector<int> * xCoordinates,
                                          vector<int> * yCoordinates)
{
//  vector<double> * xCoordinatesDouble =  new vector<double>(nCenters);
//  vector<double> * yCoordinatesDouble =  new vector<double>(nCenters);
  
  int x = 0;
  int y = 0;
  
//  for (int i = 0; i < nCenters; ++i) {
  for (int i = 0; i < mfaParametersSet.getNCenters(); ++i) {
    bool found = false;
    while (!found) {
      x = RandomTools::
          giveIntRandomNumberBetweenZeroAndEntry(cgrMatrix->getNumberOfRows());
      y = RandomTools::
              giveIntRandomNumberBetweenZeroAndEntry(cgrMatrix->getNumberOfRows());
      
      if ((*cgrMatrix)(x, y) > 0)
        found = true;
    }
    xCoordinates->at(i) = x;
    yCoordinates->at(i) = y;
  }
  
//  delete xCoordinatesDouble;
//  delete yCoordinatesDouble;
}


/*
// Utilizando la lista de puntos con precisión real  
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
*/



void SandBoxMethod::generateRandomCenters(vector<double> * xCoordinates,
                                          vector<double> * yCoordinates)
{
  int maxIndex = fractalPoints.size();
  int randomIndex = 0;
          
//  for (int i = 0; i < nCenters; ++i){
  for (int i = 0; i < mfaParametersSet.getNCenters(); ++i){
    randomIndex = RandomTools::giveIntRandomNumberBetweenZeroAndEntry(maxIndex);
    xCoordinates->at(i) = fractalPoints.at(randomIndex).x();
    yCoordinates->at(i) = fractalPoints.at(randomIndex).y();
//    cout << xCoordinates->at(i) << "," << yCoordinates->at(i) << endl;
  }
} 

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
  double sum = 0.0;
  if (radius > 0) {
    int minIndex = 0;
    int maxIndex = cgrMatrix->getNumberOfRows() - 1;
    int initX = x - radius;
    int initY = y - radius;
    int endX  = x + radius - 1; // TODO - cambio - tamaño caja conteo
    int endY  = y + radius - 1; // TODO - cambio - tamaño caja conteo
//    int endX  = x + radius; 
//    int endY  = y + radius;
    
    if (initX < minIndex)
      initX = 0;
    
    if (initY < minIndex)
      initY = 0;
    
    if (endX > maxIndex)
      endX = maxIndex;
    
    if (endY > maxIndex)
      endY = maxIndex;
    
    for (int j = initY; j <= endY; ++j) {
      sum += (*cumulativeFrequencyMatrix)(endX + 1, j) - 
             (*cumulativeFrequencyMatrix)(initX   , j);
    }
  }
  else if (radius == 0) {
    sum += (*cgrMatrix)(x, y);
  }
  
  return sum;
}

// Accessors
MfaParametersSet SandBoxMethod::getMfaParametersSet() const
{
  return mfaParametersSet;
}

void SandBoxMethod::setMfaParametersSet(const MfaParametersSet & mfaParametersSet)
{
  this->mfaParametersSet = mfaParametersSet;
}

const RowMatrix<int> * SandBoxMethod::getCgrMatrix() const
{
  return cgrMatrix;
}

void SandBoxMethod::setCgrMatrix(const RowMatrix<int> * cgrMatrix)
{
  this->cgrMatrix = cgrMatrix;
}

vector<double> * SandBoxMethod::getDqValues()
{
  return dqValues;
}

QList<vector<double> *> SandBoxMethod::getLinearRegressionValues()
{
  return linearRegressionValues;
}

const QList<QPointF> SandBoxMethod::getFractalPoints() const
{
  return fractalPoints;
}

void SandBoxMethod::setFractalPoints(const QList<QPointF> & fractalPoints)
{
  this->fractalPoints = fractalPoints;
}

QVector<int> SandBoxMethod::getIndexesOfCenters()
{
  return indexesOfCenters;
}

void SandBoxMethod::setIndexesOfCenters(QVector<int> indexesOfCenters)
{
  this->indexesOfCenters = indexesOfCenters;
}

vector<int> SandBoxMethod::getQValuesForRegressionPlot()
{
  return qValuesForRegressionPlot;
}

void SandBoxMethod::setQValuesForRegressionPlot(const vector<int> & qValuesForRegressionPlot)
{
  this->qValuesForRegressionPlot = qValuesForRegressionPlot;
}
