/**
 * @file AppController.h
 * @date Sep 5, 2009
 * @author H&eacute;ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de definiciones para la clase AppController.
 */

/* 
 *   Created on:  Sep 5, 2009
 *       Author:  HECTOR FABIO ESPITIA NAVARRO
 *  Institution:  UNIVERSIDAD DEL VALLE
 *                ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
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
#include <gui/MainWindow.h>
#include <cgr/SeqLoader.h>
#include <utils/Utils.h>
#include <utils/CustomSequencesContainer.h>


// LOCAL INCLUDES
// --

// Cyclic reference 
class Utils;
class MainWindow;
/**
 * 
 * @brief Clase controladora de la aplicaciÃ³n. 
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
     * Carga secuencias en la aplicacio-.n desde el archivo <code> fileName
     * </code> en formato FASTA.
     * @param fileName nombre de archivo de las secuencias.
     * @return número de nuevas cadenas cargadas.
     */
    int loadSequences(const string & fileName,
                      GenomAMf::AlphabetType & seqLoadedType);

    // Access
    

    /**
     * Retorna 
     * @return 
     */
    MainWindow * getMainWindow();

    /**
     * Asigna 
     */
    void setMainWindow(MainWindow * mainWindow);

    /**
     * 
     * @return
     */
    SeqLoader * getSeqLoader() const;

    /**
     *
     * @param seqLoader
     */
    void setSeqLoader(SeqLoader * seqLoader);

    /**
     * Retorna 
     * @return 
     */
    CustomSequencesContainer * getSequences();

    /**
     * Asigna 
     */
    void setSequences(CustomSequencesContainer * sequences);

  private:
    MainWindow * mainWindow; /**< Ventana principal de la aplicación. */
    SeqLoader * seqLoader; /**< Cargador de secuencias en al aplicación. */
    
//    QHash <GenomAMf::AlphabetType, VectorSequenceContainer *> * sequences; /**< 
//        Contenedor de primer nivel para las secuencias de nucléotidos y 
//        aminoácidos.  Contiene un objeto <code> VectorSequenceContainer </code> 
//        para cada tipo de secuencias. */

    CustomSequencesContainer * sequences; /**< Contenedor de secuencias de ADN y proteínas de la aplicación. */
    
//    /**
//     * Adiciona una secuencia de nucleótidos al contenedor de secuencias de 
//     * ADN de la aplicación.
//     * @param sequence La secuencia a ser adicionada  
//     */
//    void addDnaSequence(const Sequence & sequence) throw (bpp::Exception);
//
//    /**
//     * Adiciona una secuencia de aminoácidos al contenedor de secuencias de 
//     * proteínas de la aplicación.
//     * @param sequence La secuencia a ser adicionada
//     */
//    void addProteinSequence(const Sequence & sequence) throw (bpp::Exception);
    
};

#endif /* APPCONTROLLER_H_ */
