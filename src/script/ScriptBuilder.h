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

#include <QString>
#include <QStringList>

/**
 * 
 */
class ScriptBuilder
{
  public:
    enum OriginType{
      Local_Type, Remote_Type
    };
    
    ScriptBuilder();
    ScriptBuilder(const QString & destinationDirectory,
                                 const QStringList & sequences,
                                 const QString & dataBaseName);
    ScriptBuilder(const ScriptBuilder & scriptBuilderObject);
    ScriptBuilder & operator=(const ScriptBuilder & scriptBuilderObject);
    virtual ~ScriptBuilder();
    
    // Methods
    
    
    // Access
    QString getDestinationDirectory();
    
    void setDestinationDirectory(QString destinationDirectory);
    
    QString getDataBaseName();
    
    void setDataBaseName(QString dataBaseName);
    
    QStringList getSequences();
    
    void setSequences(QStringList sequences);
    
    bool getForSegment();
    
    void setForSegment(const bool & forSegment);
    
    long getSegmentSize();
    
    void setSegmentSize(const long & segmentSize);
    
    QString getScript();
    
    void setScript(const QString & script);
    
    QString getTemplatePath();
    
    void setTemplatePath(const QString & templatePath);
    
    QString getTemplateText();
    
    void setTemplateText(const QString & templateText);
    
    QString buildScript();
    
    QString getTextFromFile(const QString & fileName);
    
  private:
    QString destinationDirectory;
    
    QString dataBaseName;
    
    QStringList sequences; 
    
    bool forSegment;
    
    long segmentSize;
    
    QString script;
    
    QString templatePath;
    
    QString templateText;
    
};

#endif /* SCRIPTBUILDER_H_ */
