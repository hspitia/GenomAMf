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

#include <QtCore/QHash>

#include <Seq/Alphabet.h>
#include <Seq/AlphabetTools.h>
#include <Seq/DNA.h>
#include <Seq/VectorSequenceContainer.h>
#include <Utils/Exceptions.h>
#include <utils/Utils.h>

using namespace bpp;

#include <string>

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
    DNA * getDnaAlphabet();

    /**
     * Retorna 
     * @return 
     */
    ProteicAlphabet * getProteicAlphabet();
    
    /**
     * Retorna 
     * @return 
     */
    const VectorSequenceContainer * getDnaSequences() const;

    /**
     * Retorna 
     * @return 
     */
    const VectorSequenceContainer * getProteinSequences() const;

    /**
     * 
     */
    const Sequence
            * getDnaSequence(const string & name)
                                                  throw (SequenceNotFoundException);

    /**
     * 
     */
    const Sequence
            * getProteinSequence(const string & name)
                                                      throw (SequenceNotFoundException);

    /**
     * Retorna 
     * @return 
     */
    const QHash<int, const Sequence *> getSequencesHash() const;

    /**
     * Retorna 
     * @return 
     */
    const Sequence * getSequence(const int & key) const; 

    /**
     * Asigna 
     */
    void setSequence(const Sequence * sequence);

    /**
     * 
     */
    int getNumberOfSequences() const;

    /**
     * 
     */
    void addSequence(const Sequence & sequence) throw (Exception);

    /**
     * Retorna 
     * @return 
     */
    int getCounter();
    
    int getNumberOfDnaSequences();
    int getNumberOfProteinSequences();
    

  private:
    DNA * dnaAlphabet; /**< Alfabeto DNA para el contenedor de 
      secuencias ADN */

    ProteicAlphabet * proteicAlphabet; /**< Alfabeto Proteic para el contenedor de 
      secuencias de proteínas */

    VectorSequenceContainer * dnaSequences; /**< Contenedor de secuencias de 
     nucleótidos (ADN) */
    VectorSequenceContainer * proteinSequences; /**< Contenedor de secuencias 
     aminoácidos (proteínas) */
    //    QList<const Sequence *> sequencesList; /**< Lista de apuntadores a las 
    //      secuencias de ADN y proteínas. */

    QHash<int, const Sequence *> sequencesHash; /**< Hash de apuntadores a las 
     secuencias de ADN y proteínas. La clave funciona como un identificador 
     único de cada secuencia*/
    int counter; /**< Conteo de secuencias adicionadas al contenedor */
};

#endif /* CUSTOMSEQUENCESCONTAINER_H_ */
