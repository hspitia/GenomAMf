/**
 * @file AppController.h
 * @date 6/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de implementacio-.n para la clase AppController.
 */

/* 
 *         File:  AppController.h
 *   Created on:  6/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de implementacio-.n para la clase AppController.
 */
#define DEBUG_MODE

#include "AppController.h"
#include "utils/Trace.h"


AppController::AppController(int & argc, char ** argv) :
  QApplication(argc, argv), mainWindow(new MainWindow(this))
{
  sequences             = new CustomSequencesContainer();
  cgrHash               = new QHash<int, ChaosGameRepresentation *>();
  mfaHash               = new QHash<int, MultifractalAnalysis>();
  mfaResultSetHash      = new QHash<int, QList<int> >();
  cgrObjectsCounter     = 0;
  mfaObjectsCounter     = 0;
  mfaResultSetsCounter  = 0;
  craHash               = 0;
  creHash               = 0;
}

AppController::~AppController()
{
  if (sequences != 0) {
    delete sequences;
    sequences = 0;
  }

  if (cgrHash != 0) {
    cgrHash->clear();
    delete cgrHash;
    cgrHash = 0;
  }
  
  if (mfaHash != 0) {
    mfaHash->clear();
    delete mfaHash;
    mfaHash = 0;
  }
  
  if (craHash != 0) {
    craHash->clear();
    delete craHash;
    craHash = 0;
  }
  
  if (creHash != 0) {
    creHash->clear();
    delete creHash;
    creHash = 0;
  }
}

QVector<int> AppController::loadSequences(const QStringList & fileName)
{
  SeqLoader * seqLoader = new SeqLoader();
  
  CustomSequencesContainer * tmpSeqs = new CustomSequencesContainer(); 
  seqLoader->load(fileName, tmpSeqs);
  int proteinSeqsAlreadyLoaded = 0;
  int dnaSeqsAlreadyLoaded = 0;
  bool isDna = true;
  
  for (int i = 0; i < tmpSeqs->getNumberOfSequences(); ++i) {
    try {
      isDna = utils::getAlphabetType(tmpSeqs->getSequence(i)->getAlphabet()->
                                 getAlphabetType()) == GenomAMf::DNA_Alphabet;
      
      sequences->addSequence(*(tmpSeqs->getSequence(i)));
      int key = sequences->getNumberOfSequences() - 1;
      mainWindow->addSequenceToModels(sequences->getSequence(key), key);
    }
    catch (Exception e) {
      if (isDna)
        dnaSeqsAlreadyLoaded++;
      else {
        proteinSeqsAlreadyLoaded++;
//        isDna = true;
      }
      cout << e.what() << endl;
      // La secuencia ya se encuentra cargada. Continua cargando el
      // resto de secuencias.
    }
  }

  QVector<int> loadedSequences;
  loadedSequences << tmpSeqs->getNumberOfDnaSequences() - dnaSeqsAlreadyLoaded;
  loadedSequences << tmpSeqs->getNumberOfProteinSequences()
          - proteinSeqsAlreadyLoaded;
  
  delete tmpSeqs;
  return loadedSequences;
}

//const ChaosGameRepresentation * AppController::makeCgr(const Sequence * 
//                                                       sequence) /*const*/
//const ChaosGameRepresentation * AppController::makeCgr(const int & sequenceKey) /*const*/
/*int AppController::makeCgr(const int & sequenceKey)
{
  const Sequence * sequence = sequences->getSequence(sequenceKey);
  ChaosGameRepresentation * cgrObject = 0;
  int cgrKey = cgrObjectsCounter;
  if(sequence){
//    cout << "AppController::99 - " << qPrintable(QString::
//            fromStdString(sequence->getName())) << endl;
    cgrObject = new ChaosGameRepresentation(sequence);
    cgrObject->performRepresentation(512,512,true);
//    cgrObject->performRepresentation(512,20,true);
    cgrHash->insert(cgrKey, cgrObject);
    
    mainWindow->addCgrToModels(cgrObjectsCounter, sequenceKey);
    
    ++cgrObjectsCounter;
  }
//  cout << "AppController::111  --  cgrKey " << cgrKey << endl; 
//  return cgrObject;
  return cgrKey;
}*/

QList<int> AppController::makeCgr(const QList<int> & sequenceKeys)
{
  const Sequence * sequence = 0;
  ChaosGameRepresentation * cgrObject = 0;
  QList<int> cgrKeys = QList<int>();
  
  for (int i = 0; i < sequenceKeys.count(); ++i) {
    int sequenceKey = sequenceKeys.at(i);
    int cgrKey = cgrObjectsCounter;
    
    sequence = sequences->getSequence(sequenceKey);
    if(sequence){
      cgrObject = new ChaosGameRepresentation(sequence);
      cgrObject->performRepresentation(512,512,true);
      //    cgrObject->performRepresentation(512,20,true);
      cgrHash->insert(cgrKey, cgrObject);
      cgrKeys.append(cgrKey);
      mainWindow->addCgrToModels(cgrObjectsCounter, sequenceKey);
      
      ++cgrObjectsCounter;
    }
    
  }
  return cgrKeys;
}


QList<const ChaosGameRepresentation *>
AppController::getCgrObjectsForAnalysis(const QList<int> sequenceKeys) 
{
  QList<const ChaosGameRepresentation *> cgrListForAnalysis;
  QList<int> sequenceKeysForCgr;
  
  for (int i = 0; i < sequenceKeys.count(); ++i) {
    int sequenceKey = sequenceKeys.at(i);
    QHash<int, ChaosGameRepresentation *>::const_iterator i = 
            cgrHash->constBegin();
    
//    cout << "buscado: " << sequences->getSequence(sequenceKey);
//    cout << " - " << sequences->getSequence(sequenceKey)->getName() << endl << endl;
    
    bool cgrFound = false;
    while (i != cgrHash->constEnd() && !cgrFound) {
      cgrFound = 
              sequences->getSequence(sequenceKey) == i.value()->getSequence();
      
      if (cgrFound)
        cgrListForAnalysis.append(i.value());
      
      ++i;
    }
    
    if (!cgrFound)
      sequenceKeysForCgr.append(sequenceKey);
  }
  
  QList<int> newsCgrKeys = makeCgr(sequenceKeysForCgr);
  
  for (int i = 0; i < newsCgrKeys.count(); ++i) {
    int newCgrKey = newsCgrKeys.at(i);
    cgrListForAnalysis.append(cgrHash->value(newCgrKey));
    //    mainWindow->addCgrToModels(newCgrKey, sequenceKeysForCgr.at(i));
  }
  return cgrListForAnalysis;
}

//QList<int> AppController::makeMultifractalAnalysis_(const QList<int> & sequenceKeys,
//MfaResultsForm * AppController::makeMultifractalAnalysis_(const QList<int> & 
int AppController::makeMultifractalAnalysis_(const QList<int> & sequenceKeys,
                                             const int & minQ,
                                             const int & maxQ,
                                             const int & nCenters)
{
  QList<int> mfaKeys;
  QList<const ChaosGameRepresentation *> cgrList =
          getCgrObjectsForAnalysis(sequenceKeys);
  
  int mfaKey = 0;
  
  for (int i = 0; i < cgrList.count(); ++i) {
    MultifractalAnalysis mfaObject = MultifractalAnalysis(cgrList.at(i), 
                                                          minQ, 
                                                          maxQ,
                                                          nCenters);
    
    mfaObject.performAnalysis(MultifractalAnalysis::DISCRETE_ANALYSIS);
//    mfaObject.performAnalysis(MultifractalAnalysis::CONTINOUS_ANALYSIS);
//    mfaObject.performAnalysis(MultifractalAnalysis::COMPARATIVE_ANALYSIS);
    
    mfaKey = mfaObjectsCounter;
    mfaHash->insert(mfaKey, mfaObject);
    mfaKeys.append(mfaKey);
    ++mfaObjectsCounter;
  }
    
  int mfaResultSetKey = mfaResultSetsCounter;
  mfaResultSetHash->insert(mfaResultSetKey, mfaKeys);
  mainWindow->insertMfaResultSetTotreeView(mfaResultSetKey);
  ++mfaResultSetsCounter;
  
  return mfaResultSetKey;
}

QList<int> AppController::makeMultifractalAnalysis(const QList<int> & cgrKeys,
                                            const int & minQ,
                                            const int & maxQ,
                                            const int & nCenters)
{
  MultifractalAnalysis * mfaObject = 0;
  QList<int> mfaKeys;
  QList<const ChaosGameRepresentation * > cgrListForAnalysis;
  
  for (int i = 0; i < cgrKeys.count(); ++i) {
    int cgrKey = cgrKeys.at(i);
    if (cgrKey != -1) {
      const ChaosGameRepresentation * cgrObject = cgrHash->value(cgrKey);
      if (cgrObject)
        cgrListForAnalysis.append(cgrObject);
    }
  }  
  //    cout << "AppController::125 - " << qPrintable(QString::
  //            fromStdString(sequence->getName())) << endl;
  
  
  mfaObject = new MultifractalAnalysis(cgrListForAnalysis.at(0), 
                                       minQ, 
                                       maxQ,
                                       nCenters);
  mfaObject->performAnalysis(MultifractalAnalysis::COMPARATIVE_ANALYSIS);

  return mfaKeys;
}

MainWindow * AppController::getMainWindow()
{
  return mainWindow;
}

void AppController::setMainWindow(MainWindow *mainWindow)
{
  this->mainWindow = mainWindow;
}

const CustomSequencesContainer * AppController::getSequences() const
{
  return sequences;
}

void AppController::setSequences(CustomSequencesContainer * sequences)
{
  this->sequences = sequences;
}

const QHash<int, ChaosGameRepresentation*> * AppController::getCgrHash() 
  const
{
  return cgrHash;
}

//const QHash<int, MultifractalAnalysis *> * AppController::getMfaHash() const
const QHash<int, MultifractalAnalysis> * AppController::getMfaHash() const
{
  return mfaHash;
}

//void AppController::setMfaHash(QHash<int, MultifractalAnalysis *> * mfaHash)
void AppController::setMfaHash(QHash<int, MultifractalAnalysis> * mfaHash)
{
  this->mfaHash = mfaHash;
} 

int AppController::getCgrObjectsCounter()
{
  return cgrObjectsCounter;
}
int AppController::getMfaObjectsCounter()
{
  return mfaObjectsCounter;
}

int AppController::getMfaResultSetsCounter()
{
  return mfaResultSetsCounter;
}

QHash<int, QList<int> > * AppController::getMfaResultSetHash()
{
  return mfaResultSetHash;
}

const QHash<int, CorrelationAnalysis> * AppController::getCraHash() const
{
  return craHash;
}

void AppController::setCraHash(QHash<int, CorrelationAnalysis> * craHash)
{
  this->craHash = craHash;
}

QHash<int, QList<int> > * AppController::getCraResultSetHash()
{
  return mfaResultSetHash;
}


QHash<int, CorrelationElement> * AppController::getCreHash()
{
  return creHash;
}

