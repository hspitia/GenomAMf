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
#include <mfa/MfaParametersSet.h>
#include <gui/MainWindow.h>
#include <script/ScriptBuilder.h>
#include <script/ScriptParametersSet.h>
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
     * @return número de nuevas cadenas cargadas.
     */
//    int loadSequences(const string & fileName,
//                      GenomAMf::AlphabetType & seqLoadedType);
//    int loadSequences(const string & fileName, int & seqLoadedType);
    QVector<int> loadSequences(const QStringList & fileName);
    
    QList<int> makeCgr(const QList<int> & sequenceKeys);
    
    int makeMultifractalAnalysis(const QList<int> & sequenceKeys,
                                 const MfaParametersSet & mfaParametersSet);
    
    int makeMultifractalAnalysis(const QList<int> & sequenceKeys,
                                  const int & minQ,
                                  const int & maxQ,
                                  const int & nCenters,
                                  const int & radiusStep);
    
    int makeCorrelationAnalysis(const QList<int> & sequenceKeys, 
                                const int & nMeshFrames);
    
    bool makePreprocessingScript(const ScriptParametersSet & 
                                 scriptParametersSet,
                                 const QString & fileName);
    
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
    
    const QHash<int, QList<int> > * getCraResultSetHash() const;
    
    const QHash<int, CorrelationElement> * getCreHash() const;
    
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
    
    int mfaResultSetsCounter; /**< Contador de conjuntos de resultados de análisis 
      multifractal creados en la aplicación para asignar valor clave al hash 
      contenedor */

    int creObjectsCounter; /**< Contador de objetos de elementos de correlación
      (CorrelationElement) creados en la aplicación para asignar valor clave al 
      hash contenedor */
    
    int craObjectsCounter; /**< Contador de objetos de análisis de correlación
      (CorrelationAnalysis) creados en la aplicación para asignar valor clave al 
      hash contenedor */
    
    QHash<int, ChaosGameRepresentation *> * cgrHash; /**< Hash de 
      apuntadores a los objetos CGR creados en la aplicación. La clave 
      funciona como un identificador único del objeto */
    
//    QHash<int, MultifractalAnalysis *> * mfaHash; /**< Hash de 
    QHash<int, MultifractalAnalysis > * mfaHash; /**< Hash de 
      apuntadores a los objetos Mfa creados en la aplicación. La clave 
      funciona como un identificador único del objeto*/
    
    QHash<int, QList<int> > * mfaResultSetHash; /**< Hash de 
      lista de claves de objetos Mfa que pertenecen a un análisis realizado. 
      La clave funciona como un identificador único de cada lista */
    
    QHash<int, CorrelationAnalysis> * craHash; /**< Hash de apuntadores a los 
      objetos Cra creados en la aplicación.  La clave 
      funciona como un identificador único del objeto */
    
    QHash<int, CorrelationElement> * creHash; /**< Hash de apuntadores a los 
      objetos CorrelationElement creados en la aplicación. La clave 
      funciona como un identificador único del objeto */
    
    
    QHash<int, QList<int> > * craResultSetHash; /**< Hash de 
      lista de claves de objetos Cra que pertenecen a un análisis realizado. 
      La clave funciona como un identificador único de cada lista */
    
    
    
    QList<const ChaosGameRepresentation *>
    getCgrObjectsForAnalysis(const QList<int> & sequenceKeys);
    
    QList<const CorrelationElement *>
    getCreObjectsForAnalysis(const QList<int> & sequenceKeys,
                             const int & nMeshFrames);
    
};

#endif /* APPCONTROLLER_H_ */
