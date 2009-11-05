/**
 * @file ChaosGameRepresentation.cpp
 * @date 28/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief
 */

/*
 *         File:  ChaosGameRepresentation.cpp
 *   Created on:  28/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION
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
  this->coordinatesOfPoints = new QList<QPointF> ();
}

ChaosGameRepresentation::ChaosGameRepresentation(const 
                                                 ChaosGameRepresentation & 
                                                 cgrObject) 
{
//  sequence = new Sequence(*cgrObject.getSequence());
  sequence = cgrObject.getSequence();
  matrixOfPoints = RowMatrix<int>(cgrObject.matrixOfPoints);
  imagefilePath = cgrObject.imagefilePath;
  translatedSequence = vector<int>(cgrObject.translatedSequence);
  coordinatesOfPoints = new QList<QPointF> (*(cgrObject.coordinatesOfPoints));
}

ChaosGameRepresentation::ChaosGameRepresentation(const Sequence * sequence)
{
  this->sequence = sequence;
  this->matrixOfPoints = RowMatrix<int> ();
  this->imagefilePath = "";
  this->translatedSequence = vector<int> ();
  this->coordinatesOfPoints = new QList<QPointF> ();
}

ChaosGameRepresentation::~ChaosGameRepresentation()
{
  if (sequence != 0) {
    sequence = 0;
    delete sequence;
  }

  if (coordinatesOfPoints != 0) {
    delete coordinatesOfPoints;
    coordinatesOfPoints = 0;
  }

  translatedSequence.clear();
//  matrixOfPoints.clear();
  
}

ChaosGameRepresentation & ChaosGameRepresentation::
operator=(const ChaosGameRepresentation & cgrObject)
{
//  sequence = new Sequence(*cgrObject.getSequence());
  sequence = cgrObject.getSequence();
  matrixOfPoints = RowMatrix<int>(cgrObject.matrixOfPoints);
  imagefilePath = cgrObject.imagefilePath;
  translatedSequence = vector<int>(cgrObject.translatedSequence);
  return *this;
}

void ChaosGameRepresentation::translateSequence()
{
  unsigned int size = (unsigned int)sequence->size();
  translatedSequence = vector<int>(size);
  int newElement = -1;

  for (unsigned int i = 0; i < size; ++i) {
    string elementChar = sequence->getChar(i);
    int element = sequence->getValue(i);
    newElement = -1;
    // Los gaps y aminoácidos no resueltos son ignorados 
    if (element > -1 && element < 20) {
      if (element == 3 || element == 6) { // Negativo polar
        newElement = 1;
      }
      else if (element == 1 || element == 8 || element == 11) { // Positivo polar
        newElement = 3;
      }
      else if (element == 2 || element == 4 || element == 5 || element == 7
              || element == 15 || element == 16 || element == 18) { // Polar no
        // cargado
        newElement = 2;
      }
      else { // No polar
        newElement = 0;
      }
      
      translatedSequence[i] = newElement;
    }
  }
}

void ChaosGameRepresentation::performRepresentation(const int & cgrSize,
                                                    const int & matrixSize,
                                                    const bool & generateImage)
{
  unsigned int sequenceSize = sequence->size();
  int margin = 20; // pixeles
  matrixOfPoints = RowMatrix<int>(matrixSize,matrixSize);
  
  int xImagePoints[4]  = {0,       0, cgrSize, cgrSize};
  int yImagePoints[4]  = {cgrSize, 0, 0,       cgrSize};
  
  int xMatrixPoints[4] = {0, 0,          matrixSize, 0         }; // { 0, 0, matrixSize, matrixSize };
  int yMatrixPoints[4] = {0, matrixSize, matrixSize, matrixSize}; // { matrixSize, 0, 0, matrixSize };
  
  // Para parejas de coordenadas reales (continuas)
//  int xPoints[4] = { 0, 0, 1, 1 };
//  int yPoints[4] = { 1, 0, 0, 1 };
  
  int xPoints[4] = {0, 0,          matrixSize, 0         };
  int yPoints[4] = {0, matrixSize, matrixSize, matrixSize};
  
  const vector<int> * ptrSequence;
  
  if (utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType()) == 
          GenomAMf::Proteic_Alphabet)
  {
    translateSequence();
    ptrSequence = &translatedSequence; 
    cout << "Secuencia de Proteína clasificada" << endl;
  }
  else
  { 
    ptrSequence = &sequence->getContent();
  }
  double x = matrixSize / 2;
  double y = x;
  
  int xImage = utils::round((double)cgrSize/2);
  int yImage = xImage;
  
  int xMatrix =  utils::round((double)matrixSize/2);
  int yMatrix = xMatrix;
  
  
  if(generateImage){
    QImage * cgrImage = new QImage(cgrSize + (margin * 2), 
            cgrSize + (margin * 3), QImage::Format_RGB32);
    QRgb backgroundColor = qRgb(255,255,255);
    cgrImage->fill(backgroundColor);
    
    QPainter * painter = new QPainter(cgrImage);
    painter->setPen(QColor(0, 0, 0));
    
    drawBoxAndLabels(painter, cgrSize,
            utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType()));
                    
    painter->translate(1,1);
   
//    cout << "DEBUG CGR::153 - sequenceSize: " << sequenceSize << endl;
    for (unsigned int i = 0; i < sequenceSize; ++i)
    {
      int element = ptrSequence->at(i);
      // Los gaps y bases/aminoácidos no resueltos son ignorados
      if(element > -1 && element < 4 ) 
      { 
//        xImage = floor(((xPoints[element] * cgrSize) + xImage) / 2);
//        yImage = floor(((yPoints[element] * cgrSize) + yImage) / 2);
//        
//        xMatrix = floor(((xPoints[element] * matrixSize) + xMatrix) / 2);
//        yMatrix = floor(((yPoints[element] * matrixSize) + yMatrix) / 2);
        xImage = (xImagePoints[element] + xImage) / 2;
        yImage = (yImagePoints[element] + yImage) / 2;
        
        xMatrix = (xMatrixPoints[element] + xMatrix) / 2;
        yMatrix = (yMatrixPoints[element] + yMatrix) / 2;
        
        x = (xPoints[element] + x) / 2;
        y = (yPoints[element] + y) / 2;
        coordinatesOfPoints->append(QPointF(x,y));
        cout << "(" << x << ", "<< y << ")";
        
        int x1 = floor(xImage);
        int y1 = floor(yImage);
        
        painter->drawPoint(QPointF(x1,y1));
        
        x1 = floor(xMatrix);
        y1 = floor(yMatrix);
        
//        cout << "   DEBUG CGR::170 -  i: " << i << "  element: " << element
//        << "  x: " << x 
//        << "  y: " << y << endl;
        matrixOfPoints(x1,y1)++;
      }
    }
    cout << endl;
    string sequenceType = utils::getAlphabetTypeString(sequence->getAlphabet()->
                                                       getAlphabetType());
    imagefilePath = "tmp/cgr_" + 
            sequenceType + "_" + sequence->getName() + ".png";
//    imagefilePath = "tmp/cgr_" + sequence->getName() + ".dat";
    cgrImage->save(QString::fromStdString(imagefilePath) , "PNG");
    
    delete painter;
    delete cgrImage;
    
  }
  else{
    for (unsigned int i = 0; i < sequenceSize; ++i)
    {
      int element = ptrSequence->at(i);
      if(element > -1){
//        x = (xPoints[element] + x) / 2;
//        y = (yPoints[element] + y) / 2;
//        matrixOfPoints(floor(x), floor(y))++;
        xMatrix = floor((xMatrixPoints[element] + xMatrix) / 2);
        yMatrix = floor((yMatrixPoints[element] + yMatrix) / 2);
        matrixOfPoints(xMatrix,yMatrix)++;
        
        x = (xPoints[element] + x) / 2;
        y = (yPoints[element] + y) / 2;
        coordinatesOfPoints->append(QPointF(x,y));
      }
    }
  }
}

void ChaosGameRepresentation::drawBoxAndLabels(QPainter * painter, 
                                              const int & cgrSize,
                                              int alphabetType)
{
  int margin = (painter->device()->width() - cgrSize) / 2;
  int bottomMargin = margin * 2;
  int bottomTextMargin = margin * 1.5;
  int spacer = 2;
  
  painter->setFont(QFont(QString("Arial"), 10, QFont::Normal));
  painter->setLayoutDirection(Qt::LeftToRight);
  
  // Labels
  painter->drawText(QRectF(spacer, 
          painter->device()->height() - spacer - 1 - bottomMargin,
          margin, margin), Qt::AlignCenter, "0");
  painter->drawText(QRectF(spacer, spacer, margin, margin), Qt::AlignCenter,
          "1");
  painter->drawText(QRectF(painter->device()->width() - spacer - 1 - margin, 
          spacer, margin, margin), Qt::AlignCenter, "2");
  painter->drawText(QRectF(painter->device()->width() - spacer - 1 - margin,
          painter->device()->height() - spacer - 1 - bottomMargin, 
          margin, margin), Qt::AlignCenter, "3");
  
  // Nombre y tamanho de la secuencia
  painter->setFont(QFont(QString("Arial"), 8, QFont::Normal));
  QRectF rect(margin * 1.5, painter->device()->height() - bottomTextMargin,
          cgrSize - margin, bottomTextMargin - spacer);
  
  QString text = QString::fromStdString(sequence->getName());
  text += " (";
  text += QString::number(sequence->size());
  if(alphabetType == GenomAMf::DNA_Alphabet) text += " bp)";
  if(alphabetType == GenomAMf::Proteic_Alphabet) text += " aa)";
  
  painter->drawText(rect, Qt::AlignHCenter | Qt::TextWordWrap, text);
  
  // Box
  painter->setBrush(QColor(250, 250, 250));
  painter->translate(margin - 2, margin - 2);
  QRectF box(0, 0, cgrSize + 1, cgrSize + 1);
  painter->drawRect(box);
  
}

void ChaosGameRepresentation::performRepresentation1(int cgrSize, 
                                                    bool generateImage)
{
  unsigned int sequenceSize = sequence->size();
  int margin = 20;
  matrixOfPoints = RowMatrix<int>(cgrSize,cgrSize);
  if(generateImage){
    QImage * cgrImage = new QImage(cgrSize + (margin * 2), cgrSize + 
            (margin * 2), QImage::Format_RGB32);
    QRgb pixelColor = qRgb(0,0,0);
    QRgb backgroundColor = qRgb(255,255,255);
    cgrImage->fill(backgroundColor);
    
    QPainter * painter = new QPainter(cgrImage);
    drawBoxAndLabels(painter, cgrSize, margin);
    
    const vector<int> * ptrSequence;

    int x =  utils::round((double)cgrSize/2);
    int y = x;
    
    if (utils::getAlphabetType((sequence->getAlphabet()->getAlphabetType())) == 
            GenomAMf::Proteic_Alphabet)
    {
      translateSequence();
      ptrSequence = &translatedSequence; 
    }
    else
    { 
      ptrSequence = &sequence->getContent();
    }

    for (unsigned int i = 0; i < sequenceSize; ++i)
    {
      int element = ptrSequence->at(i);
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
        y -= y / 2;
      }
      else if (element == 3)
      {
        x += (cgrSize - x) / 2;
        y += (cgrSize - y) / 2;
      }

      int x2 = floor(x);
      int y2 = floor(y);

      cgrImage->setPixel(x2 + margin - 1 , y2 + margin - 1, pixelColor);
      matrixOfPoints(x2,y2)++;
    }
    QString sequenceType;
    sequenceType = QString::fromStdString(utils::
           getAlphabetTypeString((sequence->getAlphabet()->getAlphabetType())));
    
    QString fileName = "tmp/cgr_";
    fileName += sequenceType;
    fileName += "_";
    fileName += QString::fromStdString(sequence->getName());
    fileName += ".png";
    cgrImage->save(fileName , "PNG");
  }
  
}

const Sequence * ChaosGameRepresentation::getSequence() const
{
  return sequence;
}

void ChaosGameRepresentation::setSequence(const Sequence * sequence)
{
  this->sequence = sequence;
}

const RowMatrix<int> * ChaosGameRepresentation::getMatrixOfPoints() const
{
  return &matrixOfPoints;
}

void ChaosGameRepresentation::setMatrixOfPoints(RowMatrix<int> matrixOfPoints)
{
  this->matrixOfPoints = matrixOfPoints;
}

string ChaosGameRepresentation::getImageFilePath() const
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

void ChaosGameRepresentation::setTranslatedSequence(vector<int> 
  translatedSequence)
{
  this->translatedSequence = translatedSequence;
}

const QList<QPointF> * ChaosGameRepresentation::getCoordinatesOfPoints() const 
{
  return coordinatesOfPoints;
}
