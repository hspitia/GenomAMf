/**
 * @file CustomSequencesContainer.h
 * @date 26/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  CustomSequencesContainer.h
 *   Created on:  26/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef CUSTOMSEQUENCESCONTAINER_H_
#define CUSTOMSEQUENCESCONTAINER_H_

#include <Seq/Alphabet.h>
#include <Seq/AlphabetTools.h>
#include <Seq/DNA.h>
#include <Seq/VectorSequenceContainer.h>
#include <Utils/Exceptions.h>


using namespace bpp;


/**
 * 
 */
class CustomSequencesContainer
{
  public:
    CustomSequencesContainer();
    virtual ~CustomSequencesContainer();
    
    /**
    * Retorna 
    * @return 
    */
    VectorSequenceContainer * getDnaSequences();
    
    /**
    * Asigna 
    */
    void setDnaSequences(VectorSequenceContainer * DnaSequences);
    
    /**
     * Retorna 
     * @return 
     */
    VectorSequenceContainer *  getProteinSequences();
    
    /**
     * Asigna 
     */
    void setProteinSequences(VectorSequenceContainer *  proteinSequences);
    
    /**
     * 
     */
    const Sequence * getDnaSequence(const unsigned int & index) 
      throw (IndexOutOfBoundsException);
    
    /**
     * 
     */
    const Sequence * getProteinSequence(const unsigned int & index) 
      throw (IndexOutOfBoundsException);
    
    /**
     * 
     */
    const Sequence * getDnaSequence(const string & name) throw 
      (SequenceNotFoundException);

    /**
     * 
     */
    const Sequence * getProteinSequence(const string & name) throw 
      (SequenceNotFoundException);
    
    /**
     * Adiciona una secuencia de nucleótidos al contenedor de secuencias de 
     * ADN de la aplicación.
     * @param sequence La secuencia a ser adicionada  
     */
    void addDnaSequence(const Sequence & sequence) throw (Exception);
    
    /**
     * Adiciona una secuencia de aminoácidos al contenedor de secuencias de 
     * proteínas de la aplicación.
     * @param sequence La secuencia a ser adicionada
     */
    void addProteinSequence(const Sequence & sequence) throw (Exception);
    
    
  private:
    VectorSequenceContainer * dnaSequences; /**< Contenedor de secuencias de nucleótidos (AND) */
    VectorSequenceContainer * proteinSequences; /**< comment */
    
    
    
    
    
    
    
    
};

#endif /* CUSTOMSEQUENCESCONTAINER_H_ */
