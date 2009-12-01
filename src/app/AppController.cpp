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

#include "AppController.h"

AppController::AppController(int & argc, char ** argv) :
  QApplication(argc, argv), mainWindow(new MainWindow(this))
{
//  seqLoader = new SeqLoader();
  sequences             = new CustomSequencesContainer();
  cgrHash               = new QHash<int, ChaosGameRepresentation *>();
//  mfaHash               = new QHash<int, MultifractalAnalysis *>();
  mfaHash               = new QHash<int, MultifractalAnalysis>();
  mfaResultSetHash      = new QHash<int, QList<int> >();
  cgrObjectsCounter     = 0;
  mfaObjectsCounter     = 0;
  mfaResultSetsCounter = 0;
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
int AppController::makeCgr(const int & sequenceKey) /*const*/
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
}

QList<const ChaosGameRepresentation *>
AppController::getCgrObjectsForAnalysis(const QList<int> sequenceKeys) 
{
  QList<const ChaosGameRepresentation *> cgrListForAnalysis;
  
  for (int i = 0; i < sequenceKeys.count(); ++i) {
    int sequenceKey = sequenceKeys.at(i);
    QHash<int, ChaosGameRepresentation *>::const_iterator i = 
            cgrHash->constBegin();
    
    cout << "buscado: " << sequences->getSequence(sequenceKey);
    cout << " - " << sequences->getSequence(sequenceKey)->getName() << endl << endl;
    
    bool cgrFound = false;
    while (i != cgrHash->constEnd() && !cgrFound) {
      cgrFound = 
              sequences->getSequence(sequenceKey) == i.value()->getSequence();
      
      if (cgrFound)
        cgrListForAnalysis.append(i.value());
      
      ++i;
    }
    
    if(!cgrFound){
      int newCgrKey = makeCgr(sequenceKey);
      cgrListForAnalysis.append(cgrHash->value(newCgrKey));
    }
  }
  return cgrListForAnalysis;
}

//QList<int> AppController::makeMultifractalAnalysis_(const QList<int> & sequenceKeys,
//MfaResultsForm * AppController::makeMultifractalAnalysis_(const QList<int> & 
int AppController::makeMultifractalAnalysis_(const QList<int> & sequenceKeys,
                                             const int & minQ,
                                             const int & maxQ)
{
  QList<int> mfaKeys;
  QList<const ChaosGameRepresentation *> cgrList =
          getCgrObjectsForAnalysis(sequenceKeys);
  
  int mfaKey = 0;
  
  for (int i = 0; i < cgrList.count(); ++i) {
//    MultifractalAnalysis * mfaObject = 
    MultifractalAnalysis mfaObject = MultifractalAnalysis(cgrList.at(i), minQ, 
                                                          maxQ);
    
//    mfaObject.performAnalysis(MultifractalAnalysis::CONTINOUS_ANALYSIS);
    cout << "DEBUG - AppController::174 - makeMultifractalAnalysis - antes performAnalysis()"<< endl;
    mfaObject.performAnalysis(MultifractalAnalysis::DISCRETE_ANALYSIS);
    
    mfaKey = mfaObjectsCounter;
    mfaHash->insert(mfaKey, mfaObject);
    mfaKeys.append(mfaKey);
    ++mfaObjectsCounter;
  }
    
  int mfaResultSetKey = mfaResultSetsCounter;
  mfaResultSetHash->insert(mfaResultSetKey, mfaKeys);
  ++mfaResultSetsCounter;
  
  return mfaResultSetKey;
}

QList<int> AppController::makeMultifractalAnalysis(const QList<int> & cgrKeys,
                                            const int & minQ,
                                            const int & maxQ)
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
  
  
  mfaObject = new MultifractalAnalysis(cgrListForAnalysis.at(0), minQ, maxQ);
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
