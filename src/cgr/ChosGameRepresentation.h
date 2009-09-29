/**
 * @file ChosGameRepresentation.h
 * @date 28/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief
 */

/*
 *         File:  ChosGameRepresentation.h
 *   Created on:  28/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:
 */

#ifndef CHOSGAMEREPRESENTATION_H_
#define CHOSGAMEREPRESENTATION_H_

// SYSTEM INCLUDES
// Std libraries
#include <vector>

// Bio++ libraries
#include <Seq/Alphabet.h>
#include <Seq/AlphabetTools.h>
#include <Seq/DNA.h>
#include <Seq/ProteicAlphabet.h>
#include <Seq/VectorSequenceContainer.h>
#include <Utils/Exceptions.h>


using namespace bpp;

// PROJECT INCLUDES
#include <utils/Utils.h>

// LOCAL INCLUDES
// --

// Cyclic reference


/**
 *
 */
class ChosGameRepresentation
{
  public:
    ChosGameRepresentation();
    virtual ~ChosGameRepresentation();

  private:

};

#endif /* CHOSGAMEREPRESENTATION_H_ */
