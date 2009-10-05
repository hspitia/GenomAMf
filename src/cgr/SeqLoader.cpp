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
  this->sequences = 0;
}

SeqLoader::~SeqLoader()
{
  if (sequences != 0)
  {
    delete sequences;
    sequences = 0;
  }
}

VectorSequenceContainer * SeqLoader::load(const string & filePath)
{
  Fasta * seqReader = new Fasta();
  Alphabet * alphabet = new DNA();
  
  try
  {
    sequences = seqReader->read(filePath, alphabet);
  }
  catch (Exception e)
  {
//    cout << e.what() << endl << "Excepci�n en lectura." << endl;
    alphabet = new ProteicAlphabet();
    try
    {
      sequences = seqReader->read(filePath, alphabet);
    }
    catch (Exception e)
    { 
//      cout << e.what() << endl;
//      cout << "** Ultima excepcion **" << endl;
    }
  }
  delete seqReader;
  
  return sequences;
}

VectorSequenceContainer * SeqLoader::loadDnaSequences(const string & filePath)
{
  Fasta * seqReader = new Fasta();
  Alphabet * alphabet = new DNA();
  
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

VectorSequenceContainer * SeqLoader::loadProteinSequences(const string & filePath)
{
  Fasta * seqReader = new Fasta();
  Alphabet * alphabet = new ProteicAlphabet();
  
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
