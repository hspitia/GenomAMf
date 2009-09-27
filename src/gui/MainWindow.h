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


// Seqlib library 
#include <Seq/VectorSequenceContainer.h>

using namespace bpp;

// Project files includes
#include "ui_MainWindow.h"
#include <app/AppController.h>
#include <cgr/SeqLoader.h>
#include <gui/CgrParametersForm.h>
#include <gui/MfaParametersForm.h>
#include <gui/MfaResultsForm.h>
#include <gui/TreeModel.h>
#include <gui/TreeItem.h>


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

  private:
    // Atributos
    Ui::MainWindowClass *ui;
    AppController * parentApp;
    TreeModel * treeModel; /**< Modelo para el explorador de elementos */

    // Metodos
    /**
     * Conecta signals y slots de la aplicacio-.n.
     */
    void connectSignalsSlots();
    
    /**
     * Inicializa el explorador de elementos.
     */
    void setUpExplorerTreeView();
    
    /**
     * 
     */
    void insertSequenceToTreeView(const Sequence * sequence);
    
    /*
    void insertCgrToTreeView();
    void insertMfaTotreeView();
    void insertCorrelationToTreeView();
    */

  private slots:
    /**
     * 
     */
    void loadSequences();

    /**
     * 
     */
    void makeCgr();

    /**
     * 
     */
    void makeMultifractalAnalisys();

    /**
     * 
     */
    void displayMfaResults();
    
    /**
     * 
     */
    void closeSubWindow();
    
    void testSlot();
        
};

#endif // MAINWINDOW_H
