/**
 * @file AppController.h
 * @date 6/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de implementacio-.n para la clase AppController.
 */

/* 
 *         File:  AppController.h
 *   Created on:  6/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de implementacio-.n para la clase AppController.
 */

#include "AppController.h"

AppController::AppController(int & argc, char ** argv) :
  QApplication(argc, argv), mainWindow(new MainWindow(this))
{
  seqLoader = new SeqLoader();
  sequences = new CustomSequencesContainer();
}

AppController::~AppController()
{
  if (sequences != 0)
  {
    delete sequences;
    sequences = 0;
  }
}

int AppController::loadSequences(const string & fileName, int & seqLoadedType)
{
  int loadedSequences = 0;
  
  VectorSequenceContainer * tmpSeqs = seqLoader->load(fileName);
  
  seqLoadedType = utils::getAlphabetType(tmpSeqs->getAlphabet()->
                                         getAlphabetType());
  
  for (unsigned int i = 0; i < tmpSeqs->getNumberOfSequences(); ++i)
  {
    try
    {
      sequences->addSequence((*(tmpSeqs->getSequence(i))));
      QVector<QVariant> data;
      data << QString::fromStdString(tmpSeqs->getSequence(i)->getName());
      data << sequences->getNumberOfSequences() - 1;
      mainWindow->insertSequenceToTreeView(data);
      loadedSequences++;
    }
    catch (Exception e)
    {
      cout << e.what() << endl;
      // La secuencia ya se encuentra cargada. Continua cargando el
      // resto de secuencias.
    }
  }
  
  return loadedSequences;
}

//int AppController::loadSequences(const string & fileName, int & seqLoadedType)
//{
//  int loadedSequences = 0;
//  
//  VectorSequenceContainer * tmpSeqs = seqLoader->load(fileName);
//  
//  if (utils::getAlphabetType(tmpSeqs->getAlphabet()->getAlphabetType())
//          == GenomAMf::DNA_Alphabet)
//  {
//    seqLoadedType = GenomAMf::DNA_Alphabet;
//    
//    for (unsigned int i = 0; i < tmpSeqs->getNumberOfSequences(); ++i)
//    {
//      try
//      {
//        sequences->addDnaSequence(*(tmpSeqs->getSequence(i)));
//        QVector<QVariant> data;
//        data << QString::fromStdString(tmpSeqs->getSequence(i)->getName());
//        data << sequences->getNumberOfSequences() - 1;
//        mainWindow->insertSequenceToTreeView(data);
//        cout << "Adicionada secuencia DNA - OK" << endl;
//        loadedSequences++;
//      }
//      catch (Exception e)
//      {
//        cout << "\tYa está!!" << endl;
//        // La secuencia ya se encuentra cargada. Continúa cargando el
//        // resto de secuencias.
//      }
//    }
//  }
//  else if (utils::getAlphabetType(tmpSeqs->getAlphabet()->getAlphabetType())
//          == GenomAMf::Proteic_Alphabet)
//  {
//    seqLoadedType = GenomAMf::Proteic_Alphabet;
//    
//    for (unsigned int i = 0; i < tmpSeqs->getNumberOfSequences(); ++i)
//    {
//      try
//      {
//        sequences->addProteinSequence((*(tmpSeqs->getSequence(i))));
//        QVector<QVariant> data;
//        data << QString::fromStdString(tmpSeqs->getSequence(i)->getName());
//        data << sequences->getNumberOfSequences() - 1;
//        mainWindow->insertSequenceToTreeView(data);
//        cout << "Adicionada secuencia proteína - OK" << endl;
//        loadedSequences++;
//      }
//      catch (Exception e)
//      {
//        cout << "\tYa está!!" << endl;
//        // La secuencia ya se encuentra cargada. Continúa cargando el
//        // resto de secuencias.
//      }
//    }
//  }
//  
//  return loadedSequences;
//}

MainWindow * AppController::getMainWindow()
{
  return mainWindow;
}

void AppController::setMainWindow(MainWindow *mainWindow)
{
  this->mainWindow = mainWindow;
}

SeqLoader * AppController::getSeqLoader() const
{
  return seqLoader;
}

void AppController::setSeqLoader(SeqLoader * seqLoader)
{
  this->seqLoader = seqLoader;
}

CustomSequencesContainer * AppController::getSequences()
{
  return sequences;
}

void AppController::setSequences(CustomSequencesContainer * sequences)
{
  this->sequences = sequences;
}
