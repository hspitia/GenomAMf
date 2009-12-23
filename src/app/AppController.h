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
#include <cra/CorrelationAnalysis.h>
#include <mfa/MultifractalAnalysis.h>
#include <mfa/MultifractalAnalyzer.h>
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
 * @brief Clase controladora de la aplicación. 
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
     * @return n�mero de nuevas cadenas cargadas.
     */
//    int loadSequences(const string & fileName,
//                      GenomAMf::AlphabetType & seqLoadedType);
//    int loadSequences(const string & fileName, int & seqLoadedType);
    QVector<int> loadSequences(const QStringList & fileName);
    
//    int  makeCgr(const int & sequenceKey);
    
    QList<int> makeCgr(const QList<int> & sequenceKeys);
    
    QList<int> makeMultifractalAnalysis(const QList<int> & cgrKeys,
                                        const int & minQ,
                                        const int & maxQ,
                                        const int & nCenters);
    
    int makeMultifractalAnalysis_(const QList<int> & sequenceKeys,
                                  const int & minQ,
                                  const int & maxQ,
                                  const int & nCenters);
    // Access
    MainWindow * getMainWindow();

    
    void setMainWindow(MainWindow * mainWindow);

    
    const CustomSequencesContainer * getSequences() const;

    
    void setSequences(CustomSequencesContainer * sequences);
    
    
    const QHash<int, ChaosGameRepresentation*> * getCgrHash() const;
    
    
//    const QHash<int, MultifractalAnalysis *> * getMfaHash() const;
    const QHash<int, MultifractalAnalysis> * getMfaHash() const;
    
    
//    void setMfaHash(QHash<int, MultifractalAnalysis *> * mfaHash);
    void setMfaHash(QHash<int, MultifractalAnalysis> * mfaHash);
      
    
    
    int getCgrObjectsCounter();
    
    
    int getMfaObjectsCounter();
    
    int getMfaResultSetsCounter();
    
    QHash<int, QList<int> > * getMfaResultSetHash();
    
    const QHash<int, CorrelationAnalysis> * getCraHash() const;
    
    void setCraHash(QHash<int, CorrelationAnalysis> * craHash);
    
    QHash<int, QList<int> > * getCraResultSetHash();
    
  private:
    MainWindow * mainWindow; /**< Ventana principal de la aplicaci�n. */
//    SeqLoader * seqLoader; /**< Cargador de secuencias en al aplicaci�n. */
    CustomSequencesContainer * sequences; /**< Contenedor de secuencias de ADN y
      prote�nas de la aplicaci�n. */
    
    int cgrObjectsCounter; /**< Contador de objetos de representaci�n del juego 
      del caos creados en la aplicaci�n para asignar valor clave al hash 
      contenedor */
    
    int mfaObjectsCounter;/**< Contador de objetos de an�lisis multifractal 
      creados en la aplicaci�n para asignar valor clave al hash 
      contenedor */
    
    int mfaResultSetsCounter; /**< Contador de conjuntos de resultados de an�lisis 
      multifractal creados en la aplicaci�n para asignar valor clave al hash 
      contenedor */
    
    QHash<int, ChaosGameRepresentation *> * cgrHash; /**< Hash de 
      apuntadores a los objetos CGR creados en la aplicaci�n. La clave 
      funciona como un identificador �nico del objeto */
    
//    QHash<int, MultifractalAnalysis *> * mfaHash; /**< Hash de 
    QHash<int, MultifractalAnalysis > * mfaHash; /**< Hash de 
      apuntadores a los objetos Mfa creados en la aplicaci�n. La clave 
      funciona como un identificador �nico del objeto*/
    
    QHash<int, QList<int> > * mfaResultSetHash; /**< Hash de 
      lista de claves de objetos Mfa que pertenecen a un an�lisis realizado. 
      La clave funciona como un identificador �nico de cada lista */
    
    QHash<int, CorrelationAnalysis> * craHash; /**< Hash de apuntadores a los 
      objetos Cra creados en la aplicaci�n.  La clave 
      funciona como un identificador �nico del objeto */
    
    QHash<int, QList<int> > * craResultSetHash; /**< Hash de 
      lista de claves de objetos Cra que pertenecen a un an�lisis realizado. 
      La clave funciona como un identificador �nico de cada lista */
    
    QList<const ChaosGameRepresentation *>
    getCgrObjectsForAnalysis(const QList<int> sequenceKeys);
    
};

#endif /* APPCONTROLLER_H_ */
