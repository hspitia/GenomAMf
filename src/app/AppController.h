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
//#include <QtGui>
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
#include <cgr/ChaosGameRepresentation.h>
#include <mfa/MultifractalAnalyzer.h>
#include <mfa/MultifractalAnalisys.h>
#include <gui/MainWindow.h>
#include <utils/CustomSequencesContainer.h>
#include <utils/SeqLoader.h>
#include <utils/Utils.h>


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
//    int loadSequences(const string & fileName, int & seqLoadedType);
    QVector<int> loadSequences(const QStringList & fileName);
    /**
     * 
     */
//    const ChaosGameRepresentation *  makeCgr(const Sequence * sequence) /*const*/;
//    const ChaosGameRepresentation *  makeCgr(const int & sequenceKey) /*const*/;
    int  makeCgr(const int & sequenceKey) /*const*/;
    // Access
    
    /**
     * 
     */
    QList<int> makeMultifractalAnalisys(const QList<int> & cgrKeys, 
                                 const int & minQ,
                                 const int & maxQ);

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
     * Retorna 
     * @return 
     */
    const CustomSequencesContainer * getSequences() const;

    /**
     * Asigna 
     */
    void setSequences(CustomSequencesContainer * sequences);
    
    /**
     * Retorna 
     * @return 
     */
    const QHash<int, ChaosGameRepresentation*> * getCgrHash() const;
    
    /**
     * Retorna 
     * @return 
     */
    const QHash<int, MultifractalAnalisys *> * getMfaHash() const;
    
    /**
     * Asigna 
     */
    void setMfaHash(QHash<int, MultifractalAnalisys *> * mfaHash);
      
    
    /**
     * Retorna 
     * @return 
     */
    int getCgrObjectsCounter();
    
    /**
     * Retorna 
     * @return 
     */
    int getMfaObjectsCounter();
    
  private:
    MainWindow * mainWindow; /**< Ventana principal de la aplicación. */
//    SeqLoader * seqLoader; /**< Cargador de secuencias en al aplicación. */
    CustomSequencesContainer * sequences; /**< Contenedor de secuencias de ADN y
      proteínas de la aplicación. */
    int cgrObjectsCounter; /**< Contador de objetos de representación del juego 
      del caos creados en la aplicación para asignar valor clave al hash 
      contenedor */
    
    
    int mfaObjectsCounter;/**< Contador de objetos de análisis multifractal 
      creados en la aplicación para asignar valor clave al hash 
      contenedor */
    
    QHash<int, ChaosGameRepresentation *> * cgrHash; /**< Hash de 
      apuntadores a los objetos CGR creados en la aplicación. La clave 
      funciona como un identificador único del objeto */
    
    QHash<int, MultifractalAnalisys *> * mfaHash; /**< Hash de 
      apuntadores a los objetos Mfa creados en la aplicación. La clave 
      funciona como un identificador único del objeto*/
    
};

#endif /* APPCONTROLLER_H_ */
