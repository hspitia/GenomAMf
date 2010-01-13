/**
 * @file ScriptBuilder.h
 * @date 16/12/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  ScriptBuilder.h
 *   Created on:  16/12/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef SCRIPTBUILDER_H_
#define SCRIPTBUILDER_H_

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <script/ScriptParametersSet.h>

/**
 * 
 */
class ScriptBuilder
{
  public:
    ScriptBuilder();
    ScriptBuilder(const ScriptParametersSet & parametersSet,
                  const QString & bodyTemplateFilename,
                  const QString & mainTemplateFilename);
    ScriptBuilder(const ScriptBuilder & scriptBuilderObject);
    ScriptBuilder & operator=(const ScriptBuilder & scriptBuilderObject);
    virtual ~ScriptBuilder();
    
    // Methods
    bool saveScript(const QString & fileName);
    
    // Access
    /*QString getInputDirectory();
    
    void setInputDirectory(QString inputDirectory);
    
    QString getOutputDirectory();
    
    void setOutputDirectory(QString outputDirectory);
    
    QString getDataBaseName();
    
    void setDataBaseName(QString dataBaseName);
    
    QStringList getSequences();
    
    void setSequences(QStringList sequences);
    
    bool getForFragment();
    
    void setForFragment(const bool & forFragment);
    
    long getFragmentSize();
    
    void setFragmentSize(const long & fragmentSize);
    
    int getOriginType();
    
    void setOriginType(OriginType originType);*/
    
    QString getScript();
    
    void setScript(const QString & script);
    
    QString getTemplateText();
    
    void setTemplateText(const QString & templateText);
    
    QString buildScript();
    
    QString getSequenceListFilename();
    
    void setSequenceListFilename(QString sequenceListFilename);
    
    QString getBodyTemplateFilename();
    
    void setBodyTemplateFilename(QString bodyTemplateFilename);
    
    QString getmainTemplateFilename();
    
    void setMainTemplateFilename(const QString & mainTemplateFilename);
    
    ScriptParametersSet getParameters();
    
    void setParameters(ScriptParametersSet parameters);
    
  private:
    ScriptParametersSet parameters;
    
    /*QString inputDirectory;
    
    QString outputDirectory;
    
    QString dataBaseName;
    
    QStringList sequences; 
    
    bool forFragment;
    
    long fragmentSize;
    
    OriginType originType;
    */
    QString script;
    
    QString bodyTemplateFilename;
    
    QString mainTemplateFilename;
    
    QString templateText;
    
    QString sequenceListFilename;
    
    QString makeVariablesBlock();
    
    bool makeSequenceListFile();
    
    QString makeSequenceList();
    
    QString getTextFromFile(const QString & fileName);
    
    
    
};

#endif /* SCRIPTBUILDER_H_ */
