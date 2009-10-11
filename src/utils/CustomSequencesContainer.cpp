/**
 * @file CustomSequencesContainer.cpp
 * @date 26/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  CustomSequencesContainer.cpp
 *   Created on:  26/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "CustomSequencesContainer.h"

CustomSequencesContainer::CustomSequencesContainer()
{
  this->dnaAlphabet = new DNA();
  this->proteicAlphabet = new ProteicAlphabet();
  this->dnaSequences = new VectorSequenceContainer(dnaAlphabet);
  this->proteinSequences = new VectorSequenceContainer(proteicAlphabet);
  this->counter = 0;
  this->sequencesHash = QHash<int, const Sequence *>();
}

CustomSequencesContainer::~CustomSequencesContainer()
{
  sequencesHash.clear();
  
  if (dnaSequences != 0)
  {
    dnaSequences->clear();
    delete dnaSequences;
    dnaSequences = 0;
  }
  
  if (proteinSequences != 0)
  {
    proteinSequences->clear();
    delete proteinSequences;
    proteinSequences = 0;
  }
  
}

DNA * CustomSequencesContainer::getDnaAlphabet()
{
  return dnaAlphabet;
}

ProteicAlphabet * CustomSequencesContainer::getProteicAlphabet()
{
  return proteicAlphabet;
}


const VectorSequenceContainer * CustomSequencesContainer::getDnaSequences() 
  const
{
  return dnaSequences;
}

const VectorSequenceContainer *  CustomSequencesContainer::getProteinSequences() 
  const
{
  return proteinSequences;
}

const Sequence * CustomSequencesContainer::getDnaSequence(const string & name) 
  throw (SequenceNotFoundException)
{
  try
  {
    return dnaSequences->getSequence(name);
  }
  catch (SequenceNotFoundException e)
  { 
    throw e;
  }
}

const Sequence * CustomSequencesContainer::getProteinSequence(const string & 
                                                              name) 
  throw (SequenceNotFoundException)
{
  try
  {
    return proteinSequences->getSequence(name);
  }
  catch (SequenceNotFoundException e)
  { 
    throw e;
  }
}

const QHash<int, const Sequence *> CustomSequencesContainer::getSequencesHash() 
  const
{
  return sequencesHash;
}

const Sequence * CustomSequencesContainer::getSequence(const int & key) const
{
  return sequencesHash.value(key);
}

int CustomSequencesContainer::getNumberOfSequences() const
{
  return sequencesHash.count();
}

void CustomSequencesContainer::addSequence(const Sequence & sequence) 
  throw (Exception)
{
  if(utils::getAlphabetType(sequence.getAlphabet()->getAlphabetType()) == 
          GenomAMf::DNA_Alphabet)
  {
    try
    {
      dnaSequences->addSequence(sequence, true);
      const Sequence * seq = dnaSequences->
              getSequence(dnaSequences->getNumberOfSequences()-1);
      sequencesHash.insert(counter, seq);
      ++counter;
      
    }
    catch (Exception e)
    {
      throw e;
    }
  }
  else if(utils::getAlphabetType(sequence.getAlphabet()-> getAlphabetType()) == 
          GenomAMf::Proteic_Alphabet)
  {
    try
    {
      proteinSequences->addSequence(sequence, true);
      const Sequence * seq = proteinSequences->
                    getSequence(proteinSequences->getNumberOfSequences()-1);
      sequencesHash.insert(counter, seq);
      ++counter;
    }
    catch (Exception e)
    {
      throw e;
    }
  }
  else {
    throw Exception("CustomSequencesContainer::addSequence : "
                    "Alphabets don't match: " + 
                    dnaSequences->getAlphabet()->getAlphabetType() + 
                    "or " + proteinSequences->getAlphabet()->getAlphabetType()
                    + ", with " + sequence.getAlphabet()->getAlphabetType());
  }
}

int CustomSequencesContainer::getCounter(){
  return counter;
}

int CustomSequencesContainer::getNumberOfDnaSequences()
{
  return (int)dnaSequences->getNumberOfSequences();
}

int CustomSequencesContainer::getNumberOfProteinSequences()
{
  return (int)proteinSequences->getNumberOfSequences();
}
