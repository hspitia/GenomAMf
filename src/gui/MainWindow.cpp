/**
 * @file MainWindow.cpp
 * @date 6/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de definiciones para la clase MainWindow
 */

/* 
 *         File:  MainWindow.cpp
 *   Created on:  6/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE
 *                ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de implementacio-.n para la clase MainWindow
 */

#include "MainWindow.h"

MainWindow::MainWindow(AppController *parentApp, QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindowClass)
{
  this->parentApp = parentApp;
  this->treeModel = 0;
  ui->setupUi(this);
  connectSignalsSlots();
  setUpExplorerTreeView();
}

MainWindow::~MainWindow()
{
  delete ui;
}

TreeModel * MainWindow::getTreeModel()
{
  return treeModel;
}

void MainWindow::setTreeModel(TreeModel * treeModel)
{
  this->treeModel = treeModel;
}

void MainWindow::connectSignalsSlots()
{
  connect(ui->loadSequencesAction, SIGNAL(triggered()), this,
          SLOT(loadSequences()));
  connect(ui->makeCgrAction, SIGNAL(triggered()), this, SLOT(makeCgr()));
  connect(ui->makeMultifractalAnalisysAction, SIGNAL(triggered()), this,
          SLOT(makeMultifractalAnalisys()));
  connect(ui->testAction, SIGNAL(triggered()), this, 
          SLOT(testSlot()));
  connect(ui->explorerTreeView, SIGNAL(doubleClicked(QModelIndex)), this,
          SLOT(displayMfaResults()));
  
}

void MainWindow::setUpExplorerTreeView()
{
  QFile file("data/default.txt");
//  QFile file("data/default.txt.bak");
  file.open(QIODevice::ReadOnly);
  QStringList headers;
  headers << "Secuencias" << "type" << "index";
  treeModel = new TreeModel(headers, file.readAll());
  file.close();
  
  ui->explorerTreeView->setModel(treeModel);
  for (int column = 0; column < treeModel->columnCount(); ++column)
    ui->explorerTreeView->resizeColumnToContents(column);
  
  ui->explorerTreeView->setColumnHidden(1,true);
  ui->explorerTreeView->setColumnHidden(2,true);
  
}

void MainWindow::insertSequenceToTreeView(const Sequence * sequence)
{
  int count = treeModel->rowCount();
  cout << "Rowcount: " << count <<endl;
  
  QModelIndex index = ui->explorerTreeView->model()->index(count-1, 0);
  
  
  TreeItem * parentItem = treeModel->getItem(index.parent());
  cout << "Data parentItem :"<< qPrintable(parentItem->data(0).toString()) << endl;
  QVariant data = QString::fromStdString(sequence->getName());
  
  if (!treeModel->insertRow(index.row()+1, index.parent()))
    return;
  
  for (int column = 0; column < treeModel->columnCount(index.parent()); ++column) {
    QModelIndex child = treeModel->index(index.row()+1, column, index.parent());
    treeModel->setData(child, data, Qt::EditRole);
  }
  
  cout<< "Data: " << qPrintable(treeModel->index(index.row()+1, 0, index.parent()).data().toString())  << endl;
  
}
/*    
    void insertCgrToTreeView(const CGR * cgr)
    {
      
    }
    
    void insertMfaTotreeView(const MultyfractalAnalisys * mfa)
    {
      
    }
    
    void insertCorrelationToTreeView(const CorrelationAnalisys * correl)
    {
      
    }
 */

void MainWindow::loadSequences()
{
  int loadedSequences = 0;
  int loadedSequencesType = GenomAMf::Undefined_Alphabet;
  QString fileName = QFileDialog::getOpenFileName(this, 
                                                  tr("Carga de secuencias"),
                                                  ".",
                                                  tr("Archivos de secuencias "
                                                          "(*.fasta *.fas)"));
  
  if (!fileName.isEmpty())
  {
    loadedSequences = parentApp->loadSequences(fileName.toStdString(),
                                               loadedSequencesType);
    
    QString infoString;
    QString alphabetType = "No definido";
    
//    if (seqLoadedType == GenomAMf::DNA_Alphabet)
    if (loadedSequencesType == GenomAMf::DNA_Alphabet)
    {
      alphabetType = "ADN";
      for (unsigned int i = 0; i < parentApp->getSequences()->
        getDnaSequences()->getNumberOfSequences(); ++i)
      {
        infoString += QString::fromStdString(parentApp->getSequences()->
                                             getDnaSequences()->
                                             getSequence(i)->getName());
        infoString += "\n";
      }
    }
//    else if (seqLoadedType == GenomAMf::Proteic_Alphabet)
    else if (loadedSequencesType == GenomAMf::Proteic_Alphabet)
    {
      alphabetType = "Proteína";
      for (unsigned int i = 0; 
              i < parentApp->
              getSequences()->getProteinSequences()->getNumberOfSequences();
              ++i)
      {
        infoString += QString::fromStdString(parentApp->getSequences()->
                                             getProteinSequences()->
                                             getSequence(i)->getName());
        infoString += "\n";
      }
    }
    
    cout << "Todas las Secuencias: "<< endl;
    for (int i = 0; i < parentApp->getSequences()->getNumberOfSequences(); ++i)
    {
      cout << qPrintable(QString::fromStdString(parentApp->getSequences()->
                                                getSequence(i)->
                                                getName()))<<endl;
    }
    
    QMessageBox msgBox;
    msgBox.setText("Información de secuencias cargadas:");
    msgBox.setInformativeText(QString("Tipo: %1\nNúmero de nuevas secuencias: "
      "%2\n\n%3").arg(alphabetType).arg(loadedSequences).arg(infoString));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
  }
  
}

void MainWindow::makeCgr()
{
  CgrParametersForm * cgrParametersForm = new CgrParametersForm(this);
  cgrParametersForm->exec();
}

void MainWindow::makeMultifractalAnalisys()
{
  MfaParametersForm * mfaParametersForm = new MfaParametersForm(this);
  mfaParametersForm->exec();
}

void MainWindow::displayMfaResults()
{
  MfaResultsForm * mfaResultsForm = new MfaResultsForm(this);
  ui->mdiArea->addSubWindow(mfaResultsForm);
  mfaResultsForm->show();
  
}

void MainWindow::closeSubWindow()
{
  ui->mdiArea->closeActiveSubWindow();
}


void MainWindow::testSlot(){
  const Sequence * seq = parentApp->getSequences()->getDnaSequence(0);
  insertSequenceToTreeView(seq);
}
