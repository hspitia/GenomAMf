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

//#define DEBUG_MODE

#include "utils/Trace.h"
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
  if (sequence != 0)
    delete sequence;

  sequence = 0;

  if (coordinatesOfPoints != 0)
    delete coordinatesOfPoints;
  
  coordinatesOfPoints = 0;

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
      // D, E  -> Negativo polar
      if (element == 3 || element == 6) {
        newElement = 1;
      }
      // R, H, K -> Positivo polar
      else if (element == 1 || element == 8 || element == 11) {
        newElement = 3;
      }
      // N. C, Q, G, S, T, Y, Polar no cargado
      else if (element == 2 || element == 4 || element == 5 || element == 7 ||
               element == 15 || element == 16 || element == 18) {
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
//  matrixOfPoints = RowMatrix<int>(matrixSize,matrixSize); // Matriz normal
  matrixOfPoints = RowMatrix<int>(matrixSize + 1, matrixSize + 1); // Matriz extendida
  
  int xImagePoints[4] = {0,       0, cgrSize, cgrSize};
  int yImagePoints[4] = {cgrSize, 0, 0,       cgrSize};
  
  // Para parejas de coordenadas reales (continuas)
//  int xPoints[4] = { 0, 0, 1, 1 };
//  int yPoints[4] = { 0, 1, 1, 0 };
  
  int xMatrixPoints[4] = {0, 0,          matrixSize, matrixSize};
  int yMatrixPoints[4] = {0, matrixSize, matrixSize, 0         };
  
  int xPoints[4] =       {0, 0,          matrixSize, matrixSize};
  int yPoints[4] =       {0, matrixSize, matrixSize, 0         };
  
  const vector<int> * ptrSequence;
  
  if (utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType())
          == GenomAMf::Proteic_Alphabet) {
    translateSequence();
    ptrSequence = &translatedSequence;
    cout << "Secuencia de Proteína clasificada" << endl;
  }
  else {
    ptrSequence = &sequence->getContent();
  }
  
  int xImage = utils::round((double)cgrSize/2);
  int yImage = xImage;
/*
  int xMatrix =  utils::round((double)matrixSize/2);
  int yMatrix = xMatrix;
*/
//  int xMatrix = matrixSize / 2;
//  int yMatrix = xMatrix;
  int xMatrix = 0;
  int yMatrix = 0;
  
  double x = matrixSize / 2;
  double y = x;
  
  if(generateImage){
    QImage * cgrImage = new QImage(cgrSize + (margin * 2), cgrSize + (margin
            * 3), QImage::Format_RGB32);
    QRgb backgroundColor = qRgb(255, 255, 255);
    cgrImage->fill(backgroundColor);
    
    QPainter * painter = new QPainter(cgrImage);
    painter->setPen(QColor(0, 0, 0));
    
    drawBoxAndLabels(painter, cgrSize, 
                     utils::getAlphabetType(sequence->getAlphabet()->
                                            getAlphabetType()));
    
    painter->translate(1, 1);
    
    for (unsigned int i = 0; i < sequenceSize; ++i) {
      int element = ptrSequence->at(i);
      // Los gaps y bases/aminoácidos no resueltos son ignorados
      if (element > -1 && element < 4) {
        xImage = (xImagePoints[element] + xImage) / 2;
        yImage = (yImagePoints[element] + yImage) / 2;
        painter->drawPoint(QPointF(xImage, yImage));
        
        x = (xPoints[element] + x) / 2;
        y = (yPoints[element] + y) / 2;
        coordinatesOfPoints->append(QPointF(x, y));
        
        // Redondeo a 0.5
        /*
        double xNuevo = utils::roundToHalf(x);
        double yNuevo = utils::roundToHalf(y);
        
        xMatrix = static_cast<int>(xNuevo - 0.5);
        yMatrix = static_cast<int>(yNuevo - 0.5);
        */
        
        // Redondeo a Piso
        xMatrix = utils::roundToInt(x);
        yMatrix = utils::roundToInt(y);

//        cout << x << ", " << y;
//        cout << "    "<< xMatrix << ", " << yMatrix << endl;
        
        // Transformación de la coordenada cartesiana a matricial
//        int row = matrixSize - 1 - yMatrix; // Tamaño normal de matriz
//        int row = matrixSize - yMatrix;     // Tamaño agrandado de matriz en una fila y columna
//        int col = xMatrix;

//        matrixOfPoints(row, col)++;
        TRACE (__LINE__ << "\n\t" << "(x, y): (" << x << ", " << y << ") "
               << "  (xMatrix, yMatrix): (" << xMatrix << ", " << yMatrix << ") ");
//        matrixOfPoints(xMatrix, yMatrix)++;
        
//        if (matrixOfPoints(xMatrix, yMatrix) == 0)
          matrixOfPoints(xMatrix, yMatrix)++;
        
      }
    }
    string sequenceType = utils::getAlphabetTypeString(sequence->getAlphabet()->
                                                       getAlphabetType());
    imagefilePath = "tmp/cgr_" +  
            sequenceType + "_" + sequence->getName() + ".png";
//    imagefilePath = "tmp/cgr_" + sequence->getName() + ".dat";
    
    // Si el directorio tmp no existe, entonces lo crea
    QDir currentDir = QDir::current();
    if (!currentDir.cd("tmp")) {
      currentDir.mkdir("tmp");
    }
    cgrImage->save(QString::fromStdString(imagefilePath), "PNG");
    
    delete painter;
    delete cgrImage;
    
  }
  else {
    for (unsigned int i = 0; i < sequenceSize; ++i) {
      int element = ptrSequence->at(i);
      if (element > -1) {
//        TODO - Implementar de igual forma al de la generación de la imagen
//        x = (xPoints[element] + x) / 2;
//        y = (yPoints[element] + y) / 2;
//        matrixOfPoints(floor(x), floor(y))++;
//        xMatrix = floor((xMatrixPoints[element] + xMatrix) / 2);
//        yMatrix = floor((yMatrixPoints[element] + yMatrix) / 2);
        xMatrix = utils::round((xMatrixPoints[element] + xMatrix) / 2);
        yMatrix = utils::round((yMatrixPoints[element] + yMatrix) / 2);
        matrixOfPoints(xMatrix, yMatrix)++;
        
        x = (xPoints[element] + x) / 2;
        y = (yPoints[element] + y) / 2;
        coordinatesOfPoints->append(QPointF(x, y));
      }
    }
  }
  
  /*
  MatrixTools::print(matrixOfPoints);
  cout << endl;
  
  foreach(QPointF p, *coordinatesOfPoints){
    int xcoor = floor(p.x()); 
    int ycoor = floor(p.y()); 
    cout << " (" << p.x() << ", " << p.y() << ");" << "(" << xcoor << ", " << ycoor << ");"<<"(" << matrixSize - 1 - ycoor << ", " << xcoor << ")" <<endl;
  }
  
  cout << endl;*/
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
  matrixOfPoints = RowMatrix<int>(cgrSize, cgrSize);
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
