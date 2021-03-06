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
#include <cmath>

// PROJECT INCLUDES

// LOCAL INCLUDES
#include <utils/Definitions.h>
#include <utils/Matrix.h>


//class AppController;

namespace utils 
{
  
  
  inline int getAlphabetType(const string & alphabetTypeString)
  {
    if(alphabetTypeString.compare("DNA alphabet") == 0) {
      return GenomAMf::DNA_Alphabet;
    }
    else if(alphabetTypeString.compare("Proteic alphabet") == 0){
      return GenomAMf::Proteic_Alphabet;
    }
    return GenomAMf::Undefined_Alphabet;
  }
  
  inline string getAlphabetTypeString(const string & alphabetTypeString)
  {
    if(alphabetTypeString.compare("DNA alphabet") == 0) {
      return string("DNA");
    }
    else if(alphabetTypeString.compare("Proteic alphabet") == 0){
      return string("Protein");
    }
    return string("Undefined");
  }
  
  inline double round(double number) {
    return floor(number + 0.5);
  }
   
  inline float round(float number) {
    return floor(number + 0.5);
  }
  
}
#endif /* UTILS_H_ */
