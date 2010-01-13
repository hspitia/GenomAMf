/**
 * @file MainWindow.h
 * @date 6/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de definiciones para la clase SeqLoader
 */

/* 
 *         File:  MainWindow.h
 *   Created on:  6/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de definiciones para la clase MainWindow
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt Libraries
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QStringList>
#include <QTime>


// Seqlib library 
#include <Seq/VectorSequenceContainer.h>

using namespace bpp;

// Project files includes
#include "ui_MainWindow.h"

#include <app/AppController.h>
#include <cgr/ChaosGameRepresentation.h>
#include <cra/CorrelationAnalysis.h>
//#include <cra/CorrelationElement.h>
#include <cra/CorrelationAnalysisResultsController.h>
#include <gui/CorrelationAnalysisResultsForm.h>
#include <gui/CgrParametersForm.h>
#include <gui/CgrResultsForm.h>
#include <gui/CorrelationAnalysisParametersForm.h>
#include <gui/CorrelationAnalysisResultsForm.h>
#include <mfa/MfaResultsController.h>
#include <gui/MfaParametersForm.h>
#include <gui/MfaResultsForm.h>
#include <gui/PreprocessingScriptParametersForm.h>
#include <gui/SequenceListModel.h>
#include <gui/TreeItem.h>
#include <gui/TreeModel.h>
#include <utils/SeqLoader.h>
#include <script/ScriptParametersSet.h>

// STD libraries
#include <iostream>

using namespace std;

class AppController;
/**
 * Ventana principal de la aplicacio-.n. Define toda la funcionalidad
 * relacionada con la ventana principal de la aplicacio-.n.
 */
class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
  
    enum ExplorerElementType
    {
      SequenceElement, CgrElement, MfaResultElement, CorrelationResultElement
    };
    
    MainWindow(AppController *parentApp = 0, QWidget *parent = 0);
    ~MainWindow();
    
    /**
     * Retorna 
     * @return 
     */
    TreeModel * getTreeModel();

    /**
     * Asigna 
     */
    void setTreeModel(TreeModel * treeModel);
    
    /**
     * Retorna 
     * @return 
     */
    SequenceListModel *  getSequenceListModel();
    
    
    SequenceListModel * getSequenceListModelForCgr();
    
    /**
     * Asigna 
     */
    void setSequenceListModel(SequenceListModel *  sequenceListModel);
    
    void addSequenceToModels(const Sequence * sequence, const int & key);
    
    void addCgrToModels(const int & key, const int & sequenceKey);
    
    QList<int> getCgrResultsFormsOnView();
    
    SequenceListModel * getModelForDnaCra();
    
    SequenceListModel * getModelForProteinCra();
     
    void insertMfaResultSetTotreeView(const int & resultSetKey);
    void insertCorrelationToTreeView(const int & craKey);
    
  private:
    // Atributos
    Ui::MainWindowClass *ui;
    AppController * parentApp;
    TreeModel * treeModel; /**< Modelo para el explorador de elementos */
    
    SequenceListModel * sequenceListModel; /**< Modelo para el formulario de 
      parámetros de CGR */
    
    SequenceListModel * sequenceListModelForCgr; /**< Modelo para el formulario 
      de parámetros de CGR */
    
    QList<int> cgrResultsFormsOnView; /**< Listado de formularios de resultados 
      de CGR que están actualmente visibles en la aplicación */
    
    SequenceListModel *  cgrListModel; /**< Modelo para el formulario de 
      parámetros de Análisis Multifractal */
    
    SequenceListModel * modelForDnaCra; /**< Modelo de secuencias ADN para el 
      formulario de parámetros de Análisis de Correlación */
    
    SequenceListModel * modelForProteinCra; /**<  Modelo de secuencias ADN para 
      el formulario de parámetros de Análisis de Correlación */
    
    // Metodos
    /**
     * Conecta signals y slots de la aplicacio-.n.
     */
    void connectSignalsSlots();
    
    /**
     * Inicializa el explorador de elementos.
     */
    void setUpExplorerTreeView();
    
    
    void insertTreeMainElements();
    
    
    void insertSequenceToTreeView(const Sequence * sequence, const int & key);
    
    void insertSequenceToSequenceListModel(const Sequence * sequence, 
                                           const int & key);
    void insertSequenceToModelsForCra(const Sequence * sequence,
                                      const int & key);
    
    void insertSequenceToSequenceListModelForCgr(const Sequence * sequence,
                                                 const int & key);
    
    void removeSequenceFromSequenceListModel(SequenceListModel * model,
                                             const int & sequenceKey);
    
    void insertCgrToTreeView(const int & cgrKey, const int & sequenceKey);
    
    void insertCgrToCgrListModel(const int & cgrKey);
    
    void displayCgrResults( const int & cgrKey );

    void displayMfaResults(const int & mfaResultSetKey);
    
    void displayCraResults(const int & craKey);
    
    void updateActionsState();

    
  private slots:
    
    void loadSequences();

    void makeCgr();

    void makeMultifractalAnalysis();
    
    void makeCorrelationAnalysis();
    
    void makePreprocessScript();
    
    void displayResultForm(QModelIndex index);
    
    void closeSubWindow();
    
//    void closeSubWindow();
    
    void testSlot();
        
};

#endif // MAINWINDOW_H
