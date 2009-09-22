/**
 * @file AppController.h
 * @date Sep 5, 2009
 * @author H&eacute;ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de definiciones para la clase AppController.
 */

/* 
 *   Created on:  Sep 5, 2009
 *       Author:  HECTOR FABIO ESPITIA NAVARRO
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de definiciones para la clase AppController.
 */


#ifndef APPCONTROLLER_H_
#define APPCONTROLLER_H_

// SYSTEM INCLUDES
// Qt libraries
#include <QtGui>
#include <QApplication>
#include <QHash>

// Bio++ libraries
#include <Seq/Alphabet.h>
#include <Seq/AlphabetTools.h>
#include <Seq/DNA.h>
#include <Seq/VectorSequenceContainer.h>

using namespace bpp;

// PROJECT INCLUDES
#include <cgr/SeqLoader.h>
#include <utils/Utils.h>


// LOCAL INCLUDES
// --

// Cyclic reference 
class Utils;

/**
 * 
 * @brief Clase controladora de la aplicaci√≥n. 
 */
class AppController : public QApplication
{
  Q_OBJECT
  
  public:

    // METHODS
    // Life cycle
    /**
     * Crea un nuevo objeto AppController.
     * @param argc Nu-.mero de para_metros de la aplicacio-.n. 
     * @param argv Para-.metros de la apliacio-.n.
     */
    AppController(int & argc, char ** argv);
    
    /**
     * Destructor de clase.
     */
    virtual ~AppController();
    
    // Operations
    /**
     * Carga secuencias en la aplicacio-.n desde el archivo <code> fileName </code>
     * en formato FASTA.
     * @param fileName nombre de archivo de las secuencias.
     * @return n√∫mero de nuevas cadenas cargadas.
     */
    int loadSequences(const string & fileName);
    
    // Access
    /**
     * 
     * @return
     */
    SeqLoader * getSeqLoader() const;
    
    /**
     *
     * @param seqLoader
     */
    void setSeqLoader(SeqLoader *seqLoader);
    
    /**
     * Retorna 
     * @return 
     */
    QHash <GenomAMf::AlphabetType, VectorSequenceContainer> * getSequences();

    /**
     * Asigna 
     */
    void setSequences(
        QHash <GenomAMf::AlphabetType, VectorSequenceContainer> * sequences);
    
    /**
     * Retorna 
     * @return 
     */
    VectorSequenceContainer * getDNASequences();
    
    /**
     * Asigna 
     */
    void setDNASequences(VectorSequenceContainer *DNASequences);
    
    /**
     * Retorna
     * @return
     */
    VectorSequenceContainer * getProteinSequences();
    
    /**
     * Asigna 
     */
    void setProteinSequences(VectorSequenceContainer *proteinSequences);
    
  private:
//    MainWindow * mainWindow; /**< Ventana principal de la aplicaciÛn. */
    SeqLoader * seqLoader; /**< Cargador de secuencias en al aplicaciÛn. */
    VectorSequenceContainer * DNASequences; /**< Contenedor de las secuencias de AND cargadas en la aplicaci&oacute;n */
    VectorSequenceContainer * proteinSequences; /**< Contenedor de las secuencias de proteÌnas cargada en la aplicaci&oacute;n */  
    QHash<GenomAMf::AlphabetType, VectorSequenceContainer> *sequences; /**< Contenedor de primer nivel para las secuencias de nuclÈotidos y amino·cidos.  Contiene un objeto <code> VectorSequenceContainer </code>  para cada tipo de secuencias. */
};

#endif /* APPCONTROLLER_H_ */
