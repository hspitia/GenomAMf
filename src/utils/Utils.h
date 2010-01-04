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

// Qt
#include <QString>

// SYSTEM INCLUDES
#include <string>
#include <cmath>

// PROJECT INCLUDES

// LOCAL INCLUDES
#include <utils/Definitions.h>
//#include <utils/Matrix.h>


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
  
  inline double roundToHalf(double number) {
    return floor(number + 1.0) - 0.5;
  }
   
  inline float round(float number) {
    return floor(number + 0.5);
  }
  
  inline int roundToInt(double number) {
    return static_cast<int> (floor(number + 0.5));
//    return static_cast<int> (floor(number));
//    return static_cast<int> (floor(number));
  }
  
//  QString ApplicationController::getTimeElapsed(const int & milliseconds)
  inline string getTimeElapsed(const int & milliseconds)
  {
    QString outText = "";
    double min  = 0;
    double sec  = 0;
    
    if (milliseconds >= 1000) {
      sec  = ((double)milliseconds) / 1000.0;
      if(sec >= 60.0){
        min = sec / 60.0;
        sec = min / 60.0;
        outText += QString("%1 min, ").arg((int)floor(min));
      }
      outText += QString("%1 seg\n").arg(sec);
    }
    else 
      outText += QString("%1 ms\n").arg(milliseconds);
    
    return outText.toStdString();
  }
  
  inline int offsetOf(int row, int column)
  {
    if (row < column)
      qSwap(row, column);
    return (row * (row - 1) / 2) + column;
  }
}
#endif /* UTILS_H_ */
