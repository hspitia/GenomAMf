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
}

CustomSequencesContainer::~CustomSequencesContainer()
{
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

VectorSequenceContainer * CustomSequencesContainer::getDnaSequences()
{
  return dnaSequences;
}

void CustomSequencesContainer::setDnaSequences(VectorSequenceContainer * 
                                               dnaSequences)
{
  this->dnaSequences = dnaSequences;
}

VectorSequenceContainer * CustomSequencesContainer::getProteinSequences()
{
  return proteinSequences;
}

void CustomSequencesContainer::setProteinSequences(VectorSequenceContainer * 
                                                   proteinSequences)
{
  this->proteinSequences = proteinSequences;
}

const Sequence * CustomSequencesContainer::getDnaSequence(const 
                                                          unsigned int & index)
  throw (IndexOutOfBoundsException)
{
  try
  {
    return dnaSequences->getSequence(index);
  }
  catch (IndexOutOfBoundsException e)
  { 
    throw e;
  }
}

const Sequence * CustomSequencesContainer::getProteinSequence(const 
                                                              unsigned int &
                                                              index) 
  throw (IndexOutOfBoundsException)
{
  try
  {
    return proteinSequences->getSequence(index);
  }
  catch (IndexOutOfBoundsException e)
  { 
    throw e;
  }
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

const Sequence * CustomSequencesContainer::getProteinSequence(const string & name) 
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
  }
  catch (Exception e)
  {
    throw e;
  }
}
