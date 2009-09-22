/**
 * @file TypesDefinitions.h
 * @date 21/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  TypesDefinitions.h
 *   Created on:  21/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef TYPESDEFINITIONS_H_
#define TYPESDEFINITIONS_H_

namespace GenomAMf
{
  
  typedef enum
  {
    DNA_Alphabet, Proteic_Alphabet, Undefined_Alphabet
  } AlphabetType;
  
  typedef enum
  {
    Information, Warning, Error, Undefined
  } MessageType;
}

#endif /* TYPESDEFINITIONS_H_ */
