/**
 * @file utils.h
 * @date 14/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Utilidades varias.
 */

/* 
 *         File:  utils.h
 *   Created on:  14/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Utilidades varias.
 */


#ifndef UTILS_H_
#define UTILS_H_

// SYSTEM INCLUDES
#include <string>

// PROJECT INCLUDES
#include "src/app/AppController.h"

// LOCAL INCLUDES


class AppController;

namespace utils 
{
  
  typedef enum {
      DNA_Alphabet,
      Proteic_Alphabet,
      Undefined_Alphabet
  } AlphabetType;


  class Utils 
  {
  
    public:
      static AlphabetType getAlphabetType(const string & alphabetTypeString)
      {
        if(alphabetTypeString.compare("DNA alphabet") == 0) {
          return DNA_Alphabet;
        }
        else if(alphabetTypeString.compare("Proteic alphabet") == 0){
          return Proteic_Alphabet;
        }
        return Undefined_Alphabet;
      }
  };

}
#endif /* UTILS_H_ */
