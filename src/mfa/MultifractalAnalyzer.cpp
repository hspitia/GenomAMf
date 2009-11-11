/**
 * @file MultifractalAnalyzer.cpp
 * @date 11/11/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MultifractalAnalyzer.cpp
 *   Created on:  11/11/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "MultifractalAnalyzer.h"

MultifractalAnalyzer::MultifractalAnalyzer()
{
  this->cgrObjects = QList<ChaosGameRepresentation *>;
  this->cgrObjects = QList<MultifractalAnalisys *>;
  this->minQ       = -70;
  this->maxQ       =  70;
  this->nCenters   =  50;
  this->minR       =   1.0;
  this->maxR       = 256.0; 
}

MultifractalAnalyzer::MultifractalAnalyzer(QList<ChaosGameRepresentation * >  
                                           cgrObjects,
                                           const int & minQ,
                                           const int & maxQ,
                                           const int & nCenters,
                                           const double & minR,
                                           const double & maxR)
{ 
  this->cgrObjects = cgrObjects;
  this->cgrObjects = QList<MultifractalAnalisys *>;
  this->minQ       = minQ;
  this->maxQ       = maxQ;
  this->nCenters   = nCenters;
  this->minR       = minR;
  this->maxR       = maxR;
}

MultifractalAnalyzer::MultifractalAnalyzer(const MultifractalAnalyzer & 
                                           multifractalAnalyzerObject)
{ 
  this->cgrObjects = multifractalAnalyzerObject.cgrObjects;
  this->cgrObjects = QList<MultifractalAnalisys *>;
  this->minQ       = multifractalAnalyzerObject.minQ;
  this->maxQ       = multifractalAnalyzerObject.maxQ;
  this->nCenters   = multifractalAnalyzerObject.nCenters;
  this->minR       = multifractalAnalyzerObject.minR;
  this->maxR       = multifractalAnalyzerObject.maxR;
}

MultifractalAnalyzer::~MultifractalAnalyzer()
{
  
}


QList<ChaosGameRepresentation *> MultifractalAnalyzer::getCgrObjects()
{
  return * cgrObjects;
}

void MultifractalAnalyzer::setCgrObjects(QList<ChaosGameRepresentation *>  
                                         cgrObjects)
{
  this->* cgrObjects = * cgrObjects;
}

int MultifractalAnalyzer::getMinQ()
{
  return minQ;
}

void MultifractalAnalyzer::setMinQ(int minQ)
{
  this->minQ = minQ;
}

int MultifractalAnalyzer::getMaxQ()
{
  return maxQ;
}

void MultifractalAnalyzer::setMaxQ(int maxQ)
{
  this->maxQ = maxQ;
}

int MultifractalAnalyzer::getNCenters()
{
  return nCenters;
}

void MultifractalAnalyzer::setNCenters(int nCenters)
{
  this->nCenters = nCenters;
}

double MultifractalAnalyzer::getMinR()
{
  return minR;
}

void MultifractalAnalyzer::setMinR(double minR)
{
  this->minR = minR;
}

QList<MultifractalAnalisys *>  MultifractalAnalyzer::getMfaObjects()
{
  return mfaObjects;
}

void MultifractalAnalyzer::setMfaObjects(QList<MultifractalAnalisys *> 
                                         mfaObjects)
{
  this->mfaObjects = mfaObjects;
}

double MultifractalAnalyzer::getMaxR()
{
  return maxR;
}

void MultifractalAnalyzer::setMaxR(double maxR)
{
  this->maxR = maxR;
}
