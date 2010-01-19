/**
 * @file MfaResultsController.cpp
 * @date 13/11/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MfaResultsController.cpp
 *   Created on:  13/11/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#define DEBUG_MODE
 
#include "MfaResultsController.h"

#include "utils/Trace.h"


MfaResultsController::MfaResultsController()
{
//  this->mfaObjects     = QList<MultifractalAnalysis *>();
  this->mfaObjects           = QList<MultifractalAnalysis>();
  this->mfaResultsForm       = 0;
  this->dqPlot               = 0;
  this->cqPlot               = 0;
  this->linearRegressionPlot = 0;
  this->separator            = ";";
  this->lineFeed             = "\n";
}

//MfaResultsController::MfaResultsController(const QList<MultifractalAnalysis * > & 
MfaResultsController::MfaResultsController(const QList<MultifractalAnalysis> & 
                                           mfaObjects)
{
  this->mfaObjects     = mfaObjects;//QList<MultifractalAnalysis *>(mfaObjects);
  this->mfaResultsForm       = 0;
  this->dqPlot               = 0;
  this->cqPlot               = 0;
  this->linearRegressionPlot = 0;
  this->separator            = ";";
  this->lineFeed             = "\n";
}

MfaResultsController::~MfaResultsController()
{
  if (mfaResultsForm != 0)
    delete mfaResultsForm;
  
  mfaResultsForm = 0;
  
  if (dqPlot != 0)
    delete dqPlot;
  
  dqPlot = 0;
  
  if (cqPlot != 0)
    delete cqPlot;
  
  cqPlot = 0;
  
  if (linearRegressionPlot != 0)
    delete linearRegressionPlot;
  
  linearRegressionPlot = 0;
  
}


MfaResultsForm * MfaResultsController::contructTheResultsForm(QWidget *parent)
{
  QList<QStringList> dqValuesContent = prepareContentDqValuesTable();
  QList<QStringList> sequenceList = prepareContentSequenceTable();
  
  MfaResultsForm * mfaResultsForm = new MfaResultsForm(dqValuesContent,
                                                       sequenceList, this, 
                                                       parent);
  QList<Plotter *> plots = plotResults();
  
  mfaResultsForm->setUpDqGraphic(dqPlot); // Dq graphic
  mfaResultsForm->setUpCqGraphic(cqPlot); // Cq graphic
  mfaResultsForm->setUpLinearRegressionGraphic(linearRegressionPlot); // Linear reg.
  mfaResultsForm->setUpSequenceTable();
  mfaResultsForm->setUpDqValuesTable();
//  prepareContentSequenceTable();
//  TRACE (__LINE__ << "\n\t" << "Después setUpDqGraphic()");
  
   
  return mfaResultsForm;
}

QList<Plotter *> MfaResultsController::plotResults()
{
  QList<Plotter *> plots;
  QList<vector<double> *> dqDataSet;
  QList<vector<double> *> cqDataSet;
  QList<QList<vector<double> *> > linearRegressionsDataSet;
  
//  vector<double> * qValues = mfaObjects.at(0)->getQValues();
  vector<double> * qValues = mfaObjects.at(0).getQValues();
  
  dqDataSet.append(qValues);
  cqDataSet.append(qValues);
  
  for (int i = 0; i < mfaObjects.count(); ++i) {
//     dqDataSet.append(mfaObjects.at(i)->getDqValues());
     dqDataSet.append(mfaObjects.at(i).getDqValues());
//     cqDataSet.append(mfaObjects.at(i)->getCqValues());
     cqDataSet.append(mfaObjects.at(i).getCqValues());
//     linearRegressionsDataSet.append(mfaObjects.at(i)->
     linearRegressionsDataSet.append(mfaObjects.at(i).
                                     getLinearRegressionValues());
  }
  
  /*Plotter * */dqPlot = new Plotter(dqDataSet,Plotter::Dq_Plot);
  /*Plotter * */cqPlot = new Plotter(cqDataSet,Plotter::Cq_Plot);
//  Plotter * cqPlot = new Plotter(Plotter::Test_Plot);
  /*Plotter * */linearRegressionPlot = new Plotter(linearRegressionsDataSet,
                                                   Plotter::Linear_Plot);
  
  
  dqPlot->setXLabel("q");
  dqPlot->setYLabel("\\D_q");
  dqPlot->setTitle("Espectro \\D_q");
  
  cqPlot->setXLabel("q");
  cqPlot->setYLabel("\\C_q");
  cqPlot->setTitle("Calor específico análogo \\C_q");
  
//  plots.append(dqPlot);
//  plots.append(cqPlot);
//  plots.append(linearRegressionPlot);
  
  return plots;
}
/*QString MfaResultsController::convertDqValuesToCsv()
{

  QList<QStringList> dqTableContent = prepareContentDqValuesTable();
  
  int nCols = dqTableContent.at(0).count();
  int nRows = dqTableContent.count();
  
  QString informationBlock = getSequenceCodeAndNames();
  
  QString headers;
  QString outString;
  QString rows;
  QString lineFeed  = "\n";
  headers += "\"q\"";
  headers += separator;
  
  for (int i = 1; i < nCols; ++i) {
    headers += QString::fromUtf8("\"Dq Seq_%1\"").arg(i);
    if (i < nCols - 1) 
        headers += separator;
  }
  
  for (int row = 0; row < nRows; ++row) {
    QStringList contentRow = dqTableContent.at(row);
    rows += contentRow.at(0); // q value
    rows += separator;
    for (int j = 1; j < nCols; ++j) {
      rows += contentRow.at(j); // Dq value
      
      if (j < nCols - 1) 
        rows += separator;
    }
    rows += lineFeed;
  }
  headers += lineFeed;
  outString = informationBlock + lineFeed + headers + rows;
  
  return outString;
}*/

QString MfaResultsController::convertDqValuesToCsv()
{

  QList<QStringList> dqTableContent = prepareContentDqValuesTable();
  int nCols = dqTableContent.at(0).count();
  int nRows = dqTableContent.count();
  
  QString informationBlock = getSequenceCodeAndNames();
  
  QString headers;
  QString outString;
  QString rows;
  QString lineFeed  = "\n";
  
  QStringList headersList = dqTableContent.at(0);
  for (int i = 0; i < nCols; ++i) {
    headers += QString::fromUtf8("\"") + 
               headersList.at(i) + 
               QObject::trUtf8("\"");
    
    if (i < nCols - 1) 
        headers += separator;
  }
  
  for (int row = 1; row < nRows; ++row) {
    QStringList contentRow = dqTableContent.at(row);
//    rows += QString("Seq_%1").arg(row + 1);
//    rows += separator;
    for (int j = 0; j < nCols; ++j) {
      rows += contentRow.at(j); // Dq value
      
      if (j < nCols - 1) 
        rows += separator;
    }
    rows += lineFeed;
  }
  headers += lineFeed;
  outString = informationBlock + lineFeed + headers + rows;
  
  return outString;
}
/*QString MfaResultsController::convertDqValuesToCsv()
{

  QList<QStringList> dqTableContent = prepareContentDqValuesTable();
  
  int nCols = dqTableContent.at(0).count();
  int nRows = dqTableContent.count();
  
  QString informationBlock = getSequenceCodeAndNames();
  
  QString headers;
  QString outString;
  QString rows;
  QString lineFeed  = "\n";
  headers += "\"q\"";
  headers += separator;
  
  for (int i = 1; i < nCols; ++i) {
    headers += QString::fromUtf8("\"Dq Seq_%1\"").arg(i);
    if (i < nCols - 1) 
        headers += separator;
  }
  
  for (int row = 0; row < nRows; ++row) {
    QStringList contentRow = dqTableContent.at(row);
    rows += contentRow.at(0); // q value
    rows += separator;
    for (int j = 1; j < nCols; ++j) {
      rows += contentRow.at(j); // Dq value
      
      if (j < nCols - 1) 
        rows += separator;
    }
    rows += lineFeed;
  }
  headers += lineFeed;
  outString = informationBlock + lineFeed + headers + rows;
  
  return outString;
}*/

bool MfaResultsController::exportDqValuesToCsv(const QString & fileName)
{
  QString outString = convertDqValuesToCsv();
  
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;
  
  QTextStream out(&file);
  out << outString;
  
  return true;
}

//bool MfaResultsController::exportPlotToImageFile(Plotter::plotType ploType,
//                                                 const QString & filename,
//                                                 GenomAMf::ImageFormat imageFormat)
//{
//  Plotter * currentPlot = 0;
//  switch (ploType) {
//    case Plotter::Dq_Plot:
//      currentPlot = dqPlot;
//      break;
//      
//    case Plotter::Cq_Plot:
//      currentPlot = cqPlot;
//      break;
//      
//    case Plotter::Linear_Plot:
//      currentPlot = linearRegressionPlot;
//      break;
//      
//    default:
//      return false;
//  }
//  
//  currentPlot->exportToImage(filename, imageFormat);
//  
//    
//  return true;
//}

QString MfaResultsController::getSequenceCodeAndNames()
{
  QList<QStringList> sequenceList = prepareContentSequenceTable();
  QString outString;
  QString headers;
//  QString separator = ";";
  QString lineFeed = "\n";
  headers += QObject::trUtf8("\"No.\"");
  headers += separator;
  headers += QObject::trUtf8("\"Tipo\"");
  headers += separator;
  headers += QObject::trUtf8("\"Código\"");
  headers += separator;
  headers += QObject::trUtf8("\"Secuencia\"");
  headers += lineFeed;
  
  QString rows;
  
  QStringList types;
  types << QObject::trUtf8("\"ADN\"")
        << QObject::trUtf8("\"Proteína\"")
        << QObject::trUtf8("\"No definido\"");
  
  for (int row = 0; row < sequenceList.count(); ++row) {
    QStringList contentRow = sequenceList.at(row);
    rows += QString::number(row + 1); // No.
    rows += separator;

    int type = contentRow.at(0).toInt();
    rows += types.at(type);  // Tipo
    rows += separator;
    rows += contentRow.at(1); // Código
    rows += separator;
    rows += contentRow.at(2); // Nombre
    rows += lineFeed;
  }
  
  outString += headers + rows;
  return outString;
}

QList<QStringList > MfaResultsController::prepareContentSequenceTable()
{
  QList<QStringList > contentList;
  
  for (int i = 0; i < mfaObjects.count(); ++i) {
    const Sequence * sequence = mfaObjects.at(i).getCgrObject()->getSequence();
    
    int type = 
            utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType());
    
    QString code = QString("\"Seq_%1\"").arg(i + 1);
    
    QString name = "\"" + QString::fromStdString(sequence->getName()) + "\"";
    
    QStringList row;
    row << QString::number(type)
        << code
        << name;
    
    contentList << row;
  }
  return contentList;
}

// Horizontal
QList<QStringList > MfaResultsController::prepareContentDqValuesTable()
{
  QList<QStringList > contentList;
  int minQ = mfaObjects.at(0).getMfaParametersSet().getMinQ();
  int maxQ = mfaObjects.at(0).getMfaParametersSet().getMaxQ();
  int nRows = mfaObjects.count();
  int nCols = maxQ - minQ + 1;
  QStringList row;
  QList<vector<double> * > dqValues;
  int q = minQ;
  double dqValue = 0.0;
  /*
  for (int i = 0; i < mfaObjects.count(); ++i) {
    dqValues.append(mfaObjects.at(i).getDqValues());
  }*/
  
  QStringList headers;
  headers << QObject::trUtf8("Secuencias");
  for (int i = 0; i < nCols; ++i) {
    headers << QString::fromUtf8("D(q=%1)").arg(q);
    ++q;
  }
  contentList << headers;
  
  for (int i = 0; i < nRows; ++i) {
    row = QStringList();
    row << QString("seq_%1").arg(i + 1);
    for (int j = 0; j < nCols; ++j) {
      dqValue = mfaObjects.at(i).getDqValues()->at(j);
      row << QString("%L1").arg(dqValue, 0, 'g', 9);
    }
    contentList << row;
    ++q;
  }
//  
//  for (int i = 0; i < contentList.count(); ++i) {
//    for (int j = 0; j < contentList.at(i).count(); ++j) {
//      cout << qPrintable(contentList.at(i).at(j)) << " ";
//    }
//    cout << endl;
//  }
  
  return contentList;
}

// Vertical
/*QList<QStringList > MfaResultsController::prepareContentDqValuesTable()
{
  QList<QStringList > contentList;
  int minQ = mfaObjects.at(0).getMinQ();
  int maxQ = mfaObjects.at(0).getMaxQ();
  int nRows = maxQ - minQ + 1;
  int nCols = mfaObjects.count();
  QStringList row;
  QList<vector<double> * > dqValues;
  int q = minQ;
  double dqValue = 0.0;
  
  for (int i = 0; i < mfaObjects.count(); ++i) {
    dqValues.append(mfaObjects.at(i).getDqValues());
  }
  
  for (int i = 0; i < nRows; ++i) {
    row = QStringList();
    row << QString::number(q);
    
    for (int j = 0; j < nCols; ++j) {
      dqValue = dqValues.at(j)->at(i);
      row << QString::number(dqValue);
    }
    contentList << row;
    ++q;
  }
  
  return contentList;
}*/

void MfaResultsController::setMfaObjects(QList <MultifractalAnalysis> 
                                         mfaObjects)
{
  this->mfaObjects = mfaObjects;
}

MfaResultsForm * MfaResultsController::getMfaResultsForm()
{
  return mfaResultsForm;
}


Plotter * MfaResultsController::getDqPlot()
{
  return dqPlot;
}

Plotter * MfaResultsController::getCqPlot()
{
  return cqPlot;
}

Plotter * MfaResultsController::getLinearRegressionPlot()
{
  return linearRegressionPlot;
}