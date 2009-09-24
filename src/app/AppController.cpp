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
  sequences = new QHash <GenomAMf::AlphabetType, VectorSequenceContainer *> ();
  DNASequences = NULL;
  proteinSequences = NULL;
}

AppController::~AppController()
{
  if (sequences != 0)
  {
    delete sequences;
    sequences = 0;
  }
  if (DNASequences != 0)
  {
    delete DNASequences;
    DNASequences = 0;
    
  }
  if (proteinSequences != 0)
  {
    delete proteinSequences;
    proteinSequences = 0;
  }
}

int AppController::loadSequences(const string & fileName,
                                 GenomAMf::AlphabetType & seqLoadedType)
{
  int loadedSequences = 0;
  
  VectorSequenceContainer * tmpSeqs = seqLoader->load(fileName);
  
  if (utils::Utils::getAlphabetType(tmpSeqs->getAlphabet()->getAlphabetType())
          == GenomAMf::DNA_Alphabet)
  {
    seqLoadedType = GenomAMf::DNA_Alphabet;
    if (DNASequences == NULL)
    {
      DNASequences = new VectorSequenceContainer(tmpSeqs->getAlphabet());
    }
    for (unsigned int i = 0; i < tmpSeqs->getNumberOfSequences(); ++i)
    {
      try
      {
        addDnaSequence(*(tmpSeqs->getSequence(i)));
        cout << "Adicionada secuencia DNA - OK" << endl;
        
        DNASequences->addSequence((*(tmpSeqs->getSequence(i))), true);
        loadedSequences++;
      }
      catch (Exception e)
      {
        cout << "\tYa está!!" << endl;
        // La secuencia ya se encuentra cargada. Continúa cargando el
        // resto de secuencias.
      }
    }
  }
  else if (utils::Utils::getAlphabetType(tmpSeqs->getAlphabet()->getAlphabetType())
          == GenomAMf::Proteic_Alphabet)
  {
    seqLoadedType = GenomAMf::Proteic_Alphabet;
    if (proteinSequences == NULL) proteinSequences = new VectorSequenceContainer(
            tmpSeqs->getAlphabet());
    for (unsigned int i = 0; i < tmpSeqs->getNumberOfSequences(); ++i)
    {
      try
      {
        addProteinSequence((*(tmpSeqs->getSequence(i))));
        cout << "Adicionada secuencia proteína - OK" << endl;
        proteinSequences->addSequence((*(tmpSeqs->getSequence(i))), true);
        loadedSequences++;
      }
      catch (Exception e)
      {
        cout << "\tYa está!!" << endl;
        // La secuencia ya se encuentra cargada. Continúa cargando el
        // resto de secuencias.
      }
    }
  }

  QHashIterator <GenomAMf::AlphabetType, VectorSequenceContainer *> i(*sequences);
  while (i.hasNext())
  {
    i.next();
    cout << i.key() << endl;
    for (unsigned int j = 0; j < i.value()->getNumberOfSequences(); ++j)
    {
      cout << i.value()->getSequence(j)->getName() << endl;
    }
  }
  return loadedSequences;
}

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

QHash <GenomAMf::AlphabetType, VectorSequenceContainer *> * AppController::getSequences()
{
  return sequences;
}

void AppController::setSequences(QHash <GenomAMf::AlphabetType,
        VectorSequenceContainer *> * sequences)
{
  this->sequences = sequences;
}

VectorSequenceContainer * AppController::getDNASequences()
{
  //  return DNASequences;
  return sequences->value(GenomAMf::DNA_Alphabet);
}

void AppController::setDNASequences(VectorSequenceContainer * DNASequences)
{
  this->DNASequences = DNASequences;
}

VectorSequenceContainer * AppController::getProteinSequences()
{
  //  return proteinSequences;
  return sequences->value(GenomAMf::Proteic_Alphabet);
}

void AppController::setProteinSequences(VectorSequenceContainer * proteinSequences)
{
  this->proteinSequences = proteinSequences;
}

void AppController::addDnaSequence(const Sequence & sequence) throw (bpp::Exception)
{
  if (!sequences->contains(GenomAMf::DNA_Alphabet))
  {
    cout << "Creando VectorSequenceContainer para DNA" << endl;
    sequences->insert(GenomAMf::DNA_Alphabet, new VectorSequenceContainer(new DNA()));
  }
  
  try
  {
    sequences->value(GenomAMf::DNA_Alphabet)->addSequence(sequence, true);
  }
  catch (bpp::Exception e)
  {
    throw e;
  }
}

void AppController::addProteinSequence(const Sequence & sequence)
                                                                  throw (bpp::Exception)
{
  if (!sequences->contains(GenomAMf::Proteic_Alphabet))
  {
    cout << "Creando VectorSequenceContainer para Proteínas" << endl;
    sequences ->insert(GenomAMf::Proteic_Alphabet, new VectorSequenceContainer(
            new ProteicAlphabet()));
  }
  
  try
  {
    sequences->value(GenomAMf::Proteic_Alphabet)->addSequence(sequence, true);
  }
  catch (bpp::Exception e)
  {
    throw e;
  }
}
