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

AppController::AppController(int & argc, char ** argv)
  : QApplication(argc, argv)
{
  seqLoader = new SeqLoader();
  sequences = NULL;
  DNASequences = NULL;
  proteinSequences = NULL;
}

AppController::~AppController()
{
  if(sequences != 0){
    delete sequences;
    sequences = 0;
  }
  if(DNASequences != 0){
    delete DNASequences;
    DNASequences = 0;
    
  }
  if(proteinSequences != 0){
    delete proteinSequences;
    proteinSequences = 0;
  }
}

int AppController::loadSequences(const string & fileName)
{
  int loadedSequences = 0;
  
  VectorSequenceContainer * tmpSeqs = seqLoader->load(fileName);
  
  cout << "AlphabetType from file: " << utils::Utils::getAlphabetType(tmpSeqs->getAlphabet()->getAlphabetType())<<endl;
  cout << "AlphabetType: " << AlphabetTools::PROTEIN_ALPHABET.getAlphabetType() << endl;
  
  if (utils::Utils::getAlphabetType(tmpSeqs->getAlphabet()->getAlphabetType()) == utils::DNA_Alphabet){
    if (DNASequences == NULL) {
      DNASequences = new VectorSequenceContainer(tmpSeqs->getAlphabet());
    }
    for (unsigned int i = 0; i < tmpSeqs->getNumberOfSequences(); ++i) {
      try {
        DNASequences->addSequence((*(tmpSeqs->getSequence(i))), true);
        loadedSequences++;
      } 
      catch (Exception e) {
        // La secuencia ya se encuentra cargada. Continúa cargando el
        // resto de secuencias.
      }
    }
  }
  else if (utils::Utils::getAlphabetType(tmpSeqs->getAlphabet()->getAlphabetType()) == utils::Proteic_Alphabet){
    if (proteinSequences == 0) proteinSequences = new VectorSequenceContainer(tmpSeqs->getAlphabet());
    for (unsigned int i = 0; i < tmpSeqs->getNumberOfSequences(); ++i) {
      try {
        proteinSequences->addSequence((*(tmpSeqs->getSequence(i))), true);
        loadedSequences++;
      } 
      catch (Exception e) {
        // La secuencia ya se encuentra cargada. Continúa cargando el
        // resto de secuencias.
      }
    }
  }
  
  
  return loadedSequences;
}

SeqLoader * AppController::getSeqLoader() const 
{
  return seqLoader;
}

void AppController::setSeqLoader(SeqLoader * seqLoader)
{
  this->seqLoader = seqLoader;
}

VectorSequenceContainer * AppController::getSequences()
{
  return sequences;
}

void AppController::setSequences(VectorSequenceContainer * sequences)
{
  this->sequences = sequences;
}

VectorSequenceContainer * AppController::getDNASequences()
{
  return DNASequences;
}

void AppController::setDNASequences(VectorSequenceContainer * DNASequences)
{
  this->DNASequences = DNASequences;
}

VectorSequenceContainer * AppController::getProteinSequences()
{
  return proteinSequences;
}

void AppController::setProteinSequences(VectorSequenceContainer * proteinSequences)
{
  this->proteinSequences = proteinSequences;
}
