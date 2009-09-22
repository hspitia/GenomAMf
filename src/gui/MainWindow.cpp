/**
 * @file MainWindow.cpp
 * @date 6/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de definiciones para la clase SeqLoader
 */

/* 
 *         File:  MainWindow.cpp
 *   Created on:  6/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de implementacio-.n para la clase MainWindow
 */

#include "MainWindow.h"

MainWindow::MainWindow(AppController *parentApp, QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindowClass)
{
  this->parentApp = parentApp;
  ui->setupUi(this);
  connectSignalsSlots();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::connectSignalsSlots()
{
  connect(ui->loadSequencesAction, SIGNAL(triggered()), this, SLOT(loadSequences()));
  connect(ui->makeCgrAction, SIGNAL(triggered()), this, SLOT(makeCgr()));
  connect(ui->makeMultifractalAnalisysAction, SIGNAL(triggered()), this,
          SLOT(makeMultifractalAnalisys()));
  connect(ui->testAction, SIGNAL(triggered()), this, SLOT(displayMfaResults()));
}

void MainWindow::loadSequences()
{
  int loadedSequences = 0;
  GenomAMf::AlphabetType seqLoadedType = GenomAMf::Undefined_Alphabet;
  QString fileName = QFileDialog::getOpenFileName(this, tr("Carga de secuencias"),
          ".", tr("Archivos de secuencias (*.fasta *.fas)"));
  
  if (!fileName.isEmpty()) {
    loadedSequences
            = parentApp->loadSequences(fileName.toStdString(), seqLoadedType);
    
    QString infoString;
    QString alphabetType = "No definido";
    
    if (seqLoadedType == GenomAMf::DNA_Alphabet) {
      alphabetType = "ADN";
      for (unsigned int i = 0; i
              < parentApp->getDNASequences()->getNumberOfSequences(); ++i) {
        infoString += QString::fromStdString(
                parentApp->getDNASequences()->getSequence(i)->getName());
        infoString += "\n";
      }
    }
    else if (seqLoadedType == GenomAMf::Proteic_Alphabet) {
      alphabetType = "Prote�na";
      for (unsigned int i = 0; i
              < parentApp->getProteinSequences()->getNumberOfSequences(); ++i) {
        infoString += QString::fromStdString(
                parentApp->getProteinSequences()->getSequence(i)->getName());
        infoString += "\n";
      }
    }

    QMessageBox msgBox;
    msgBox.setText("Informaci�n de secuencias cargadas:");
    msgBox.setInformativeText(
            QString("Tipo: %1\nN�mero de nuevas secuencias: %2\n\n%3").arg(
                    alphabetType).arg(loadedSequences).arg(infoString));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
  }
  
}

void MainWindow::makeCgr()
{
  CgrParametersForm *cgrParametersForm = new CgrParametersForm(this);
  cgrParametersForm->exec();
}

void MainWindow::makeMultifractalAnalisys()
{
  MfaParametersForm *mfaParametersForm = new MfaParametersForm(this);
  mfaParametersForm->exec();
}

void MainWindow::displayMfaResults()
{
  MfaResultsForm *mfaResultsForm = new MfaResultsForm(this);
  ui->mdiArea->addSubWindow(mfaResultsForm);
  mfaResultsForm->show();
}
