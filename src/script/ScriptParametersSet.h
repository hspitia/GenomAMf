/**
 * @file ScriptParametersSet.h
 * @date 13/01/2010
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  ScriptParametersSet.h
 *   Created on:  13/01/2010
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef SCRIPTPARAMETERSSET_H_
#define SCRIPTPARAMETERSSET_H_

#include <QtCore/QString>
#include <QtCore/QStringList>
//
//#include <script/ScriptBuilder.h>
//
//class ScriptBuilder;
/**
 * 
 */
class ScriptParametersSet
{
  public:
    enum OriginType{
      Local_Type, Remote_Type
    };
    
    ScriptParametersSet();
    ScriptParametersSet(const ScriptParametersSet & scriptParametersSetObject);
    ScriptParametersSet & operator=(const ScriptParametersSet & 
                                    scriptParametersSetObject);
    virtual ~ScriptParametersSet();
    
    // Access
    QString getInputDirectory();
    
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
    
    void setOriginType(OriginType originType);
    
  private:
    QString inputDirectory;
    
    QString outputDirectory;
    
    QString dataBaseName;
    
    QStringList sequences; 
    
    bool forFragment;
    
    long fragmentSize;
    
    OriginType originType;
};

#endif /* SCRIPTPARAMETERSSET_H_ */
