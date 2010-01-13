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
//  this->outputDirectory = "";
//  this->dataBaseName         = "";
//  this->sequences            = QStringList();
//  this->forFragment          = false;
//  this->fragmentSize         = -1;
  
  this->parameters           = ScriptParametersSet();
  this->script               = "";
  this->bodyTemplateFilename = "";
  this->mainTemplateFilename = "";
  this->templateText         = "";

}

ScriptBuilder::ScriptBuilder(const ScriptParametersSet & parametersSet,
                             const QString & bodyTemplateFilename,
                             const QString & mainTemplateFilename)
{
//  this->outputDirectory      = "";
//  this->dataBaseName         = "";
//  this->sequences            = QStringList();
//  this->forFragment          = false;
//  this->fragmentSize         = -1;
  this->parameters           = parametersSet;
  this->script               = "";
  this->bodyTemplateFilename = bodyTemplateFilename;
  this->mainTemplateFilename = mainTemplateFilename;
  this->templateText         = "";

}

ScriptBuilder::ScriptBuilder(const ScriptBuilder & scriptBuilderObject)
{
//  this->outputDirectory      = scriptBuilderObject.outputDirectory;
//  this->dataBaseName         = scriptBuilderObject.dataBaseName;
//  this->sequences            = scriptBuilderObject.sequences;
//  this->forFragment          = scriptBuilderObject.forFragment;
//  this->fragmentSize         = scriptBuilderObject.fragmentSize;
//  
  this->parameters           = scriptBuilderObject.parameters;
  this->script               = scriptBuilderObject.script;
  this->bodyTemplateFilename = scriptBuilderObject.bodyTemplateFilename;
  this->mainTemplateFilename = scriptBuilderObject.mainTemplateFilename;
  this->templateText         = scriptBuilderObject.templateText;
}

ScriptBuilder & ScriptBuilder::operator=(const ScriptBuilder & 
                                         scriptBuilderObject)
{
//  this->outputDirectory      = scriptBuilderObject.outputDirectory;
//  this->dataBaseName         = scriptBuilderObject.dataBaseName;
//  this->sequences            = scriptBuilderObject.sequences;
//  this->forFragment          = scriptBuilderObject.forFragment;
//  this->fragmentSize         = scriptBuilderObject.fragmentSize;
  this->parameters           = scriptBuilderObject.parameters;
  this->script               = scriptBuilderObject.script;
  this->bodyTemplateFilename = scriptBuilderObject.bodyTemplateFilename;
  this->mainTemplateFilename = scriptBuilderObject.mainTemplateFilename;
  this->templateText         = scriptBuilderObject.templateText;
  
  return *this;
}

ScriptBuilder::~ScriptBuilder()
{
  // TODO Auto-generated destructor stub
}

QString ScriptBuilder::buildScript()
{
  script = getTextFromFile(bodyTemplateFilename);
  QString main = getTextFromFile(mainTemplateFilename);
  QString variables = makeVariablesBlock();
  
  main.replace("<variablesBlock>", variables);
  
  script += main;
  
  return script;
}

bool ScriptBuilder::saveScript(const QString & fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;
  
  QTextStream out(&file);
  out << script;
  
  return true;
}

QString ScriptBuilder::makeVariablesBlock()
{
  QString tab      = "\t";
  QString lineFeed = "\n";
  QString block    = "";
  
  block += tab + 
           QString("splitSize   = %1").arg(parameters.getFragmentSize()) +
           lineFeed;
  
  block += tab + 
           "inputDir    = os.path.abspath(\"" + parameters.getInputDirectory() + 
           "\")" + 
           lineFeed;

  block += tab + 
           "outputDir   = os.path.abspath(\"" + parameters.getOutputDirectory() + 
           "\")" + 
           lineFeed;
  
  QString origin = "local";
  
  if (parameters.getOriginType() == ScriptParametersSet::Remote_Type)
    origin = "remote";
  
  block += tab + 
           "originType  = \"" + origin + "\"" +
           lineFeed;
  
  block += tab + 
           "dbname      = \"" + parameters.getDataBaseName() + "\"" +
           lineFeed;
  
  block += tab + 
           "seqsIds     = " + makeSequenceList() + 
           lineFeed;
  
  block += tab + 
           "seqsIdsFile = \"" + sequenceListFilename + "\"" +
           lineFeed;
  
// splitSize   = <splitSize>
// inputDir    = os.path.abspath(<inputDir>)
// outputDir   = os.path.abspath(<outputDir>)
// originType  = <originType>
// dbName      = <dbName>
// seqsIdsFile = <seqsIdFile>
  
  return block;
}

bool ScriptBuilder::makeSequenceListFile()
{
  QString outString = "";
  
  for (int i = 0; i < parameters.getSequences().count(); ++i) {
    outString += parameters.getSequences().at(i); 
    if (i != parameters.getSequences().count() - 1)
      outString +=  "\n";
  }
  
  QFile file(sequenceListFilename);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;
  
  QTextStream out(&file);
  out << outString;
  
  return true;
}

QString ScriptBuilder::makeSequenceList()
{
  QString separator = ", ";
  QString outString = "[";
  
  for (int i = 0; i < parameters.getSequences().count(); ++i) {
    outString += "\"" + parameters.getSequences().at(i) + "\""; 
    if (i != parameters.getSequences().count() - 1)
      outString += separator;
  }
  outString += "]\n";
  
  return outString;
}

QString ScriptBuilder::getTextFromFile(const QString & fileName)
{
  QString text;
  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return text;
  
  QTextStream in(&file);
  
//  while (!in.atEnd()) {
//    text += in.readLine() + "\n";
//  }
  
  text = in.readAll();
  
  return text;
}

/*
QString ScriptBuilder::getInputDirectory()
{
  return inputDirectory;
}

void ScriptBuilder::setInputDirectory(QString inputDirectory)
{
  this->inputDirectory = inputDirectory;
}

QString ScriptBuilder::getOutputDirectory()
{
  return outputDirectory;
}

void ScriptBuilder::setOutputDirectory(QString outputDirectory)
{
  this->outputDirectory = outputDirectory;
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

bool ScriptBuilder::getForFragment()
{
  return forFragment;
}

void ScriptBuilder::setForFragment(const bool & forFragment)
{
  this->forFragment = forFragment;
}

long ScriptBuilder::getFragmentSize()
{
  return fragmentSize;
}

void ScriptBuilder::setFragmentSize(const long & fragmentSize)
{
  this->fragmentSize = fragmentSize;
}

QString ScriptBuilder::getScript()
{
  return script;
}

void ScriptBuilder::setScript(const QString & script)
{
  this->script = script;
}

QString ScriptBuilder::getTemplateText()
{
  return templateText;
}

void ScriptBuilder::setTemplateText(const QString & templateText)
{
  this->templateText = templateText;
}

QString ScriptBuilder::getBodyTemplateFilename()
{
  return bodyTemplateFilename;
}

void ScriptBuilder::setBodyTemplateFilename(QString bodyTemplateFilename)
{
  this->bodyTemplateFilename = bodyTemplateFilename;
}

QString ScriptBuilder::getmainTemplateFilename()
{
  return mainTemplateFilename;
}

void ScriptBuilder::setMainTemplateFilename(const QString & mainTemplateFilename)
{
  this->mainTemplateFilename = mainTemplateFilename;
}

int ScriptBuilder::getOriginType()
{
  return originType;
}

void ScriptBuilder::setOriginType(OriginType originType)
{
  this->originType = originType;
}
*/

QString ScriptBuilder::getSequenceListFilename()
{
  return sequenceListFilename;
}

void ScriptBuilder::setSequenceListFilename(QString sequenceListFilename)
{
  this->sequenceListFilename = sequenceListFilename;
}

ScriptParametersSet ScriptBuilder::getParameters()
{
  return parameters;
}

void ScriptBuilder::setParameters(ScriptParametersSet parameters)
{
  this->parameters = parameters;
}
