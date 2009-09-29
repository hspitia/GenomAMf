/**
 * @file SeqLoader.h
 * @date 6/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de definiciones para la clase SeqLoader
 */

/* 
 *         File:  SeqLoader.h
 *   Created on:  6/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de definiciones para la clase SeqLoader
 */

#ifndef SEQLOADER_H_
#define SEQLOADER_H_

// Qt Libraries
#include <QString>

// SeqLib library
#include <Seq/Alphabet.h>
#include <Seq/AlphabetTools.h>
#include <Seq/ProteicAlphabet.h>
#include <Seq/DNA.h>
#include <Seq/SequenceContainer.h>
#include <Seq/Fasta.h>

// UtilsLib library
#include <Utils/Exceptions.h>

using namespace bpp;

// STL Library
#include <iostream>
#include <string>

using namespace std;

/**
 * Clase para carga de secuencias de ADN y protei-.nas.
 * 
 * Provee toda la funcionalidad para cargar en al aplicacio-.n 
 * los archivos de secuencias de ADN y protei-.nas en formato FASTA. 
 */
class SeqLoader {
  public:
    // Atributos
    
    // Metodos
    SeqLoader();
    virtual ~SeqLoader();
    
    /**
     * 
     */
    VectorSequenceContainer * load(const string & filePath);
    
    /**
     * 
     */
    VectorSequenceContainer * loadDnaSequences(const string & filePath);
    
    /**
     * 
     */
    VectorSequenceContainer * loadProteinSequences(const string & filePath);
    
  private:
    // Atributos
//    Alphabet * alphabet; /**< Alfabeto de las secuencias de entrada. */
    VectorSequenceContainer * sequences; /**< Contenedor de las secuencias cargadas. */
    
    
    // Metodos
    
};

#endif /* SEQLOADER_H_ */
