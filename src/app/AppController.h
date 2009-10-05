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
#include <Utils/Exceptions.h>


using namespace bpp;

// PROJECT INCLUDES
#include <gui/MainWindow.h>
#include <cgr/SeqLoader.h>
#include <cgr/ChaosGameRepresentation.h>
#include <utils/Utils.h>
#include <utils/CustomSequencesContainer.h>

// LOCAL INCLUDES
// --

// Cyclic reference 
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
//    int loadSequences(const string & fileName,
//                      GenomAMf::AlphabetType & seqLoadedType);
    int loadSequences(const string & fileName, int & seqLoadedType);
    
    /**
     * 
     */
    const ChaosGameRepresentation *  makeCgr(const Sequence * sequence);
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
    
    /**
     * Retorna 
     * @return 
     */
    QList<ChaosGameRepresentation *> * getCgrList();

    /**
     * Asigna 
     */
    void setCgrList(QList<ChaosGameRepresentation *> * cgrList);
    
  private:
    MainWindow * mainWindow; /**< Ventana principal de la aplicación. */
    SeqLoader * seqLoader; /**< Cargador de secuencias en al aplicación. */
    CustomSequencesContainer * sequences; /**< Contenedor de secuencias de ADN y
      proteínas de la aplicación. */
    QList<ChaosGameRepresentation *> * cgrList; /**< Lista de apuntadores a los objetos CGR creados en la aplicación */
};

#endif /* APPCONTROLLER_H_ */
