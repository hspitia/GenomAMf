/**
 * @file ScriptBuilder.cpp
 * @date 16/12/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  ScriptBuilder.cpp
 *   Created on:  16/12/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "ScriptBuilder.h"

ScriptBuilder::ScriptBuilder()
{
  this->destinationDirectory = "";
  this->dataBaseName         = "";
  this->sequences            = QStringList();
  this->forSegment           = true;
  this->segmentSize          = 100000;
  this->script               = "";
  this->templatePath         = "";
  this->templateText         = "";

}

ScriptBuilder::ScriptBuilder(const QString & destinationDirectory,
                             const QStringList & sequences,
                             const QString & dataBaseName)
{
  this->destinationDirectory = destinationDirectory;
  this->dataBaseName         = dataBaseName;
  this->sequences            = sequences;
  this->forSegment           = true;
  this->segmentSize          = 100000;
  this->script               = "";
  this->templatePath         = "templates/template01.tpl";
  this->templateText         = "";

}

ScriptBuilder::ScriptBuilder(const ScriptBuilder & scriptBuilderObject)
{
  this->destinationDirectory = scriptBuilderObject.destinationDirectory;
  this->dataBaseName         = scriptBuilderObject.dataBaseName;
  this->sequences            = scriptBuilderObject.sequences;
  this->forSegment           = scriptBuilderObject.forSegment;
  this->segmentSize          = scriptBuilderObject.segmentSize;
  this->script               = scriptBuilderObject.script;
  this->templatePath         = scriptBuilderObject.templatePath;
  this->templateText         = scriptBuilderObject.templateText;
}

ScriptBuilder & ScriptBuilder::operator=(const ScriptBuilder & 
                                         scriptBuilderObject)
{
  this->destinationDirectory = scriptBuilderObject.destinationDirectory;
  this->dataBaseName         = scriptBuilderObject.dataBaseName;
  this->sequences            = scriptBuilderObject.sequences;
  this->forSegment           = scriptBuilderObject.forSegment;
  this->segmentSize          = scriptBuilderObject.segmentSize;
  this->script               = scriptBuilderObject.script;
  this->templatePath         = scriptBuilderObject.templatePath;
  this->templateText         = scriptBuilderObject.templateText;
  
  return *this;
}

ScriptBuilder::~ScriptBuilder()
{
  // TODO Auto-generated destructor stub
}

QString ScriptBuilder::buildScript()
{
  
}


QString ScriptBuilder::getTextFromFile(const QString & fileName)
{
  
}

QString ScriptBuilder::getDestinationDirectory()
{
  return destinationDirectory;
}

void ScriptBuilder::setDestinationDirectory(QString destinationDirectory)
{
  this->destinationDirectory = destinationDirectory;
}

QString ScriptBuilder::getDataBaseName()
{
  return dataBaseName;
}

void ScriptBuilder::setDataBaseName(QString dataBaseName)
{
  this->dataBaseName = dataBaseName;
}

QStringList ScriptBuilder::getSequences()
{
  return sequences;
}

void ScriptBuilder::setSequences(QStringList sequences)
{
  this->sequences = sequences;
}

bool ScriptBuilder::getForSegment()
{
  return forSegment;
}

void ScriptBuilder::setForSegment(const bool & forSegment)
{
  this->forSegment = forSegment;
}

long ScriptBuilder::getSegmentSize()
{
  return segmentSize;
}

void ScriptBuilder::setSegmentSize(const long & segmentSize)
{
  this->segmentSize = segmentSize;
}

QString ScriptBuilder::getScript()
{
  return script;
}

void ScriptBuilder::setScript(const QString & script)
{
  this->script = script;
}

QString ScriptBuilder::getTemplatePath()
{
  return templatePath;
}

void ScriptBuilder::setTemplatePath(const QString & templatePath)
{
  this->templatePath = templatePath;
}

QString ScriptBuilder::getTemplateText()
{
  return templateText;
}

void ScriptBuilder::setTemplateText(const QString & templateText)
{
  this->templateText = templateText;
}
