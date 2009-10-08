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
  this->dnaSequences = new VectorSequenceContainer(new DNA());
  this->proteinSequences = new VectorSequenceContainer(new ProteicAlphabet());
  this->counter = 0;
}

CustomSequencesContainer::~CustomSequencesContainer()
{
  sequences.clear();
  
  if (dnaSequences != 0)
  {
    delete dnaSequences;
    dnaSequences = 0;
  }
  
  if (proteinSequences != 0)
  {
    delete proteinSequences;
    proteinSequences = 0;
  }
  
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

//const Sequence * CustomSequencesContainer::getDnaSequence(const 
//                                                          unsigned int & index)
//  throw (IndexOutOfBoundsException)
//{
//  try
//  {
//    return dnaSequences->getSequence(index);
//  }
//  catch (IndexOutOfBoundsException e)
//  { 
//    throw e;
//  }
//}
//
//const Sequence * CustomSequencesContainer::getProteinSequence(const 
//                                                              unsigned int &
//                                                              index) 
//  throw (IndexOutOfBoundsException)
//{
//  try
//  {
//    return proteinSequences->getSequence(index);
//  }
//  catch (IndexOutOfBoundsException e)
//  { 
//    throw e;
//  }
//}

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


void CustomSequencesContainer::addDnaSequence(const Sequence & sequence)
  throw (Exception)
{
  try
  {
    dnaSequences->addSequence(sequence, true);
//    const Sequence * seq = &sequence;
    sequences.insert(counter, &sequence);
    ++counter;
  }
  catch (Exception e)
  {
    throw e;
  }
}

void CustomSequencesContainer::addProteinSequence(const Sequence & sequence)
  throw (Exception)
{
  try
  {
    proteinSequences->addSequence(sequence, true);
//    const Sequence * seq = &sequence;
    sequences.insert(counter, &sequence);
    ++counter;
  }
  catch (Exception e)
  {
    throw e;
  }
}

QHash<int, const Sequence *> CustomSequencesContainer::getSequences(){
  return sequences;
}

const Sequence * CustomSequencesContainer::getSequence(const int & key)
{
  return sequences.value(key);
}

int CustomSequencesContainer::getNumberOfSequences()
{
  return sequences.count();
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
//      const Sequence * seq = &sequence;
      sequences.insert(counter, &sequence);
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
//      const Sequence * seq = &sequence;
      sequences.insert(counter, &sequence);
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
