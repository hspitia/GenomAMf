/**
 * @file Definitions.h
 * @date 21/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  Definitions.h
 *   Created on:  21/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

namespace GenomAMf
{
  
  enum AlphabetType
  {
      DNA_Alphabet, Proteic_Alphabet, Undefined_Alphabet
  };  
  
  typedef enum
  {
    Information, Warning, Error, Undefined
  } MessageType;
}

#endif /* DEFINITIONS_H_ */
