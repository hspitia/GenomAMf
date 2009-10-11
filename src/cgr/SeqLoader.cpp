/**
 * @file SeqLoader.cpp
 * @date 6/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de implementacio-.n para la clase SeqLoader.
 */

/* 
 *         File:  SeqLoader.cpp
 *   Created on:  6/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de implementacio-.n para la clase SeqLoader.
 */

#include "SeqLoader.h"
//#include <Utils/Exceptions.h>


SeqLoader::SeqLoader()
{
//  this->sequences = 0;
}

SeqLoader::~SeqLoader()
{
//  if (sequences != 0)
//  {
//    delete sequences;
//    sequences = 0;
//  }
}

VectorSequenceContainer * SeqLoader::load(const string & filePath,
                                          const DNA * dnaAlphabet,
                                          const ProteicAlphabet *
                                          proteicAlphabet)
{
  Fasta * seqReader = new Fasta();
  Alphabet * alphabet = new DNA();
  VectorSequenceContainer * sequences;
   
  try
  {
    sequences = seqReader->read(filePath, dnaAlphabet);
  }
  catch (Exception e)
  {
// cout << e.what() << endl << "Excepción en lectura." << endl;
    alphabet = new ProteicAlphabet();
    try
    {
      sequences = seqReader->read(filePath, proteicAlphabet);
    }
    catch (Exception e)
    {
// cout << e.what() << endl;
// cout << "** Ultima excepcion **" << endl;
    }
  }
  delete seqReader;
  
  return sequences;
}

void SeqLoader::load(const QStringList & filePath, 
                     CustomSequencesContainer * container)
{
  Fasta * seqReader = new Fasta();
  Alphabet * alphabet = new DNA();
  VectorSequenceContainer * sequences = 0;
  
  for (int i = 0; i < filePath.count(); ++i)
  {
    try
    {
      sequences = seqReader->read(filePath.at(i).toStdString(), alphabet);
    }
    catch (Exception e)
    {
      alphabet = new ProteicAlphabet();
      try
      {
        sequences = seqReader->read(filePath.at(i).toStdString(), alphabet);
      }
      catch (Exception e)
      { 
  //      cout << e.what() << endl;
  //      cout << "** Ultima excepcion **" << endl;
      }
    }
    
    if(sequences != 0){
      for (unsigned int i = 0; i < sequences->getNumberOfSequences(); ++i)
      {
        container->addSequence(*(sequences->getSequence(i)));
      }
      sequences->clear();
      sequences = 0;
    }
  }
  
  delete seqReader;
  
//  return allSequences;
}

// TODO cambiar implementación incluyendo alfabetos tal como en el método load
VectorSequenceContainer * SeqLoader::loadDnaSequences(const string & filePath)
{
  Fasta * seqReader = new Fasta();
  Alphabet * alphabet = new DNA();
  VectorSequenceContainer * sequences;
  
  try
  {
    sequences = seqReader->read(filePath, alphabet);
  }
  catch (Exception e)
  {
    cout << e.what() << endl;
  }
  delete seqReader;
  
  return sequences;
}

// TODO cambiar implementación incluyendo alfabetos tal como en el método load
VectorSequenceContainer * SeqLoader::loadProteinSequences(const string & filePath)
{
  Fasta * seqReader = new Fasta();
  Alphabet * alphabet = new ProteicAlphabet();
  VectorSequenceContainer * sequences;
  
  try
  {
    sequences = seqReader->read(filePath, alphabet);
  }
  catch (Exception e)
  {
    cout << e.what() << endl;
  }
  delete seqReader;
  
  return sequences;
}
