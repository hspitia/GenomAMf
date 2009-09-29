/**
 * @file ChaosGameRepresentation.cpp
 * @date 28/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  ChaosGameRepresentation.cpp
 *   Created on:  28/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "ChaosGameRepresentation.h"

ChaosGameRepresentation::ChaosGameRepresentation()
{
  // TODO Auto-generated constructor stub

}

ChaosGameRepresentation::~ChaosGameRepresentation()
{
  // TODO Auto-generated destructor stub
}

RowMatrix<int> ChaosGameRepresentation::getMatrixOfPoints(){
  return matrixOfPoints;
}

void ChaosGameRepresentation::setMatrixOfPoints(RowMatrix<int> matrixOfPoints){
  this->matrixOfPoints = matrixOfPoints;
}

string ChaosGameRepresentation::getImageFilePath(){
  return imagefilePath;
}

void ChaosGameRepresentation::setImageFilePath(string imagefilePath){
  this->imagefilePath = imagefilePath;
}
