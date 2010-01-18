/**
 * @file MfaParametersSet.cpp
 * @date 18/01/2010
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MfaParametersSet.cpp
 *   Created on:  18/01/2010
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "MfaParametersSet.h"

MfaParametersSet::MfaParametersSet()
{
  this->minQ        = 0;
  this->maxQ        = 0;
  this->minR        = 0;
  this->maxR        = 0;
  this->radiusStep  = 0;
  this->nCenters    = 0;
  this->nIterations = 0;
}

MfaParametersSet::MfaParametersSet(const MfaParametersSet & 
                                   mfaParametersSetObject)
{
  this->minQ        = mfaParametersSetObject.minQ;
  this->maxQ        = mfaParametersSetObject.maxQ;
  this->minR        = mfaParametersSetObject.minR;
  this->maxR        = mfaParametersSetObject.maxR;
  this->radiusStep  = mfaParametersSetObject.radiusStep;
  this->nCenters    = mfaParametersSetObject.nCenters;
  this->nIterations = mfaParametersSetObject.nIterations;
}

MfaParametersSet & MfaParametersSet::operator=(const MfaParametersSet &
                                               mfaParametersSetObject)
{
  this->minQ        = mfaParametersSetObject.minQ;
  this->maxQ        = mfaParametersSetObject.maxQ;
  this->minR        = mfaParametersSetObject.minR;
  this->maxR        = mfaParametersSetObject.maxR;
  this->radiusStep  = mfaParametersSetObject.radiusStep;
  this->nCenters    = mfaParametersSetObject.nCenters;
  this->nIterations = mfaParametersSetObject.nIterations;
  
  return *this;
}

MfaParametersSet::~MfaParametersSet()
{
  // TODO Auto-generated destructor stub
}

// Accessors
int MfaParametersSet::getMinQ() const
{
  return minQ;
}

void MfaParametersSet::setMinQ(const int & minQ)
{
  this->minQ = minQ;
}

int MfaParametersSet::getMaxQ() const
{
  return maxQ;
}

void MfaParametersSet::setMaxQ(const int & maxQ)
{
  this->maxQ = maxQ;
}

int MfaParametersSet::getMinR() const
{
  return minR;
}

void MfaParametersSet::setMinR(const int & minR)
{
  this->minR = minR;
}

int MfaParametersSet::getMaxR() const
{
  return maxR;
}

void MfaParametersSet::setMaxR(const int & maxR)
{
  this->maxR = maxR;
}

int MfaParametersSet::getNCenters() const
{
  return nCenters;
}

void MfaParametersSet::setNCenters(const int & nCenters)
{
  this->nCenters = nCenters;
}

int MfaParametersSet::getRadiusStep() const
{
  return radiusStep;
}

void MfaParametersSet::setRadiusStep(const int & radiusStep)
{
  this->radiusStep = radiusStep;
}

int MfaParametersSet::getNIterations() const
{
  return nIterations;
}

void MfaParametersSet::setNIterations(const int & nIterations)
{
  this->nIterations = nIterations;
}

QString MfaParametersSet::toString() const
{
  QString outString = "";
  outString += QObject::trUtf8("-- Parámetros Análisis Multifractal --\n");
  outString += QObject::trUtf8("    minQ:  %1").arg(minQ);
  outString += QObject::trUtf8("  maxQ:  %1\n").arg(maxQ);
  outString += QObject::trUtf8("    minR:  %1").arg(minR);
  outString += QObject::trUtf8("  maxR:  %1\n").arg(maxR);
  outString += QObject::trUtf8("    radiusStep :  %1\n").arg(radiusStep);
  outString += QObject::trUtf8("    nCenters   :  %1\n").arg(nCenters);
  outString += QObject::trUtf8("    nIterations:  %1\n").arg(nIterations);
  outString += QObject::trUtf8("--------------------------------------\n");
  return outString;
}
