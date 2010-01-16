/**
 * @file ScriptParametersSet.cpp
 * @date 13/01/2010
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  ScriptParametersSet.cpp
 *   Created on:  13/01/2010
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "ScriptParametersSet.h"

ScriptParametersSet::ScriptParametersSet()
{
  this->inputDirectory  = "";
  this->outputDirectory = "";
  this->dataBaseName    = "";
  this->sequences       = QStringList();
  this->forFragment     = false;
  this->fragmentSize    = -1;
  this->originType      = Local_Type;
}

ScriptParametersSet::ScriptParametersSet(const ScriptParametersSet & 
                                         scriptParametersSetObject)
{
  this->inputDirectory  = scriptParametersSetObject.inputDirectory;;
  this->outputDirectory = scriptParametersSetObject.outputDirectory;
  this->dataBaseName    = scriptParametersSetObject.dataBaseName;
  this->sequences       = scriptParametersSetObject.sequences;
  this->forFragment     = scriptParametersSetObject.forFragment;
  this->fragmentSize    = scriptParametersSetObject.fragmentSize;
  this->originType      = scriptParametersSetObject.originType;
}

ScriptParametersSet & ScriptParametersSet::operator=(const ScriptParametersSet & 
                                                     scriptParametersSetObject)
{
  this->inputDirectory  = scriptParametersSetObject.inputDirectory;;
  this->outputDirectory = scriptParametersSetObject.outputDirectory;
  this->dataBaseName    = scriptParametersSetObject.dataBaseName;
  this->sequences       = scriptParametersSetObject.sequences;
  this->forFragment     = scriptParametersSetObject.forFragment;
  this->fragmentSize    = scriptParametersSetObject.fragmentSize;
  this->originType      = scriptParametersSetObject.originType;
  
  return *this;
}

ScriptParametersSet::~ScriptParametersSet()
{
  // TODO Auto-generated destructor stub
}


QString ScriptParametersSet::getInputDirectory()
{
  return inputDirectory;
}

void ScriptParametersSet::setInputDirectory(QString inputDirectory)
{
  this->inputDirectory = inputDirectory;
}

QString ScriptParametersSet::getOutputDirectory()
{
  return outputDirectory;
}

void ScriptParametersSet::setOutputDirectory(QString outputDirectory)
{
  this->outputDirectory = outputDirectory;
}

QString ScriptParametersSet::getDataBaseName()
{
  return dataBaseName;
}

void ScriptParametersSet::setDataBaseName(QString dataBaseName)
{
  this->dataBaseName = dataBaseName;
}

QStringList ScriptParametersSet::getSequences()
{
  return sequences;
}

void ScriptParametersSet::setSequences(QStringList sequences)
{
  this->sequences = sequences;
}

bool ScriptParametersSet::getForFragment()
{
  return forFragment;
}

void ScriptParametersSet::setForFragment(const bool & forFragment)
{
  this->forFragment = forFragment;
}

long ScriptParametersSet::getFragmentSize()
{
  return fragmentSize;
}

void ScriptParametersSet::setFragmentSize(const long & fragmentSize)
{
  this->fragmentSize = fragmentSize;
}

int ScriptParametersSet::getOriginType()
{
  return originType;
}

void ScriptParametersSet::setOriginType(OriginType originType)
{
  this->originType = originType;
}
