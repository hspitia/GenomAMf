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
  this->sequence = 0;
  this->matrixOfPoints = RowMatrix<int> ();
  this->imagefilePath = "";
  this->translatedSequence = vector<int> ();
}

ChaosGameRepresentation::ChaosGameRepresentation(const Sequence * sequence)
{
  this->sequence = sequence;
  this->matrixOfPoints = RowMatrix<int> ();
  this->imagefilePath = "";
  this->translatedSequence = vector<int> ();
}

ChaosGameRepresentation::~ChaosGameRepresentation()
{
  if (sequence != 0)
  {
    sequence = 0;
    delete sequence;
  }
}

void ChaosGameRepresentation::translateSequence()
{
  unsigned int size = (unsigned int)sequence->size();
  translatedSequence = vector<int>(size);
  int newElement = -1;
  
  for (unsigned int i = 0; i < size; ++i) {
    string elementChar = sequence->getChar(i);
    int element = sequence->getValue(i);
    if (element == 3 || element == 6) { // Negativo polar
      newElement = 1;
    } 
    else if(element == 1 || element == 8 || element == 11){ // Positivo polar
      newElement = 3;
    }
    else if (element == 2 || element == 4 || element == 5 || element == 7 || 
            element == 15 || element == 16 || element == 18) { // Polar no 
                                                               // cargado
      newElement = 2;
    }
    else{  // No polar
     newElement = 0; 
    }
    
    translatedSequence[i] = newElement; 
  }
}

bool ChaosGameRepresentation::performRepresentation(int cgrSize, bool generateImage)
{
  int sequenceSize = (int) sequence->size();
//  if(sequence->size() > 1000000) size = 1024;
//  if(sequence->size() > 100000) size = 512;
  
  matrixOfPoints = RowMatrix<int>(cgrSize,cgrSize);
  cout << "DEBUG" << endl;
  if(generateImage){
    QImage * cgrImage = new QImage (cgrSize,cgrSize, QImage::Format_RGB32);
    QRgb pixelColor = qRgb(0,0,0);
    QRgb backgroudColor = qRgb(255,255,255);
    cgrImage->fill(backgroudColor);
    
    int x =  utils::round((double)cgrSize/2); 
    int y = x;
    
    for (unsigned int i = 0; i < sequenceSize; ++i)
    {
      int element = sequence->getValue(i);
      if (element == 0)
      {
        x -= x / 2;
        y += (cgrSize - y) / 2;
      }
      else if (element == 1)
      {
        x -= x / 2;
        y -= y / 2;
      }
      else if (element == 2)
      {
        x += (cgrSize - x) / 2;
        y += (cgrSize - y) / 2;
      }
      else if (element == 3)
      {
        x += (cgrSize - x) / 2;
        y -= y / 2;
      }
      
      int x2 = floor(x);
      int y2 = floor(y);
      
      cgrImage->setPixel(x2, y2, pixelColor);
      matrixOfPoints(y2,x2)++;
    }
    
    cgrImage->save("data/cgr.png", "PNG");
    MatrixTools::print(matrixOfPoints);
  }
  

}

const Sequence * ChaosGameRepresentation::getSequence()
{
  return sequence;
}

void ChaosGameRepresentation::setSequence(const Sequence * sequence)
{
  this->sequence = sequence;
}

RowMatrix<int> ChaosGameRepresentation::getMatrixOfPoints()
{
  return matrixOfPoints;
}

void ChaosGameRepresentation::setMatrixOfPoints(RowMatrix<int> matrixOfPoints)
{
  this->matrixOfPoints = matrixOfPoints;
}

string ChaosGameRepresentation::getImageFilePath()
{
  return imagefilePath;
}

void ChaosGameRepresentation::setImageFilePath(string imagefilePath)
{
  this->imagefilePath = imagefilePath;
}

vector<int> ChaosGameRepresentation::getTranslatedSequence()
{
  return translatedSequence;
}

void ChaosGameRepresentation::setTranslatedSequence(
                                                    vector<int> translatedSequence)
{
  this->translatedSequence = translatedSequence;
}
