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
#define DEBUG_MODE

#include "MainWindow.h"

#include "utils/Trace.h"

MainWindow::MainWindow(AppController *parentApp, QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindowClass)
{
  this->parentApp = parentApp;
  this->treeModel = 0;
  this->sequenceListModel = new SequenceListModel(QList<QList<QVariant> > ());
  this->sequenceListModelForCgr = 
          new SequenceListModel(QList<QList<QVariant> > ());
  this->modelForDnaCra = 
          new SequenceListModel(QList<QList<QVariant> > ());
  this->modelForProteinCra = 
          new SequenceListModel(QList<QList<QVariant> > ());
  this->cgrListModel = new SequenceListModel(QList<QList<QVariant> > ());
  ui->setupUi(this);
  connectSignalsSlots();
  setUpExplorerTreeView();
  updateActionsState();
}

MainWindow::~MainWindow()
{
  parentApp = 0;
  delete ui;
  delete sequenceListModel;
  delete sequenceListModelForCgr;
  delete treeModel;
  delete modelForDnaCra;
  delete modelForProteinCra;
}

TreeModel * MainWindow::getTreeModel()
{
  return treeModel;
}

void MainWindow::setTreeModel(TreeModel * treeModel)
{
  this->treeModel = treeModel;
}

SequenceListModel * MainWindow::getSequenceListModel()
{
  return sequenceListModel;
}

void MainWindow::setSequenceListModel(SequenceListModel * sequenceListModel)
{
  this->sequenceListModel = sequenceListModel;
}

void MainWindow::connectSignalsSlots()
{
  connect(ui->loadSequencesAction, SIGNAL(triggered()), this,
          SLOT(loadSequences()));
  connect(ui->makeCgrAction, SIGNAL(triggered()), this, SLOT(makeCgr()));
  connect(ui->makeMultifractalAnalysisAction, SIGNAL(triggered()), this,
          SLOT(makeMultifractalAnalysis()));
  connect(ui->makeCorrelationAnalysisAction, SIGNAL(triggered()), this,
          SLOT(makeCorrelationAnalysis()));
  connect(ui->testAction, SIGNAL(triggered()), this, SLOT(testSlot()));
  connect(ui->explorerTreeView, SIGNAL(doubleClicked(QModelIndex /*index*/)), 
          this, SLOT(displayResultForm(QModelIndex /*index*/)));
  
}

void MainWindow::setUpExplorerTreeView()
{
  QStringList headers;
  headers << "Elementos" << "ItemType" << "Key";
  treeModel = new TreeModel(headers, QString(""));
  
  ui->explorerTreeView->setModel(treeModel);
  for (int column = 0; column < treeModel->columnCount(); ++column)
    ui->explorerTreeView->resizeColumnToContents(column);
  
  bool isHidden = false;
  ui->explorerTreeView->setColumnHidden(1, isHidden);
  ui->explorerTreeView->setColumnHidden(2, isHidden);
  
  // Insert main elements
  insertTreeMainElements();
  
}

void MainWindow::insertTreeMainElements()
{
  QVector<QVariant> mainSeqElementData;
  QVector<QVariant> mainMfaElementData;
  QVector<QVariant> mainCorrelElementData;
  
  mainSeqElementData << "Secuencias";
  mainSeqElementData << TreeItem::MainSequenceItem;
  mainSeqElementData << -1;
  mainMfaElementData << "Análisis Multifractal";
  mainMfaElementData << TreeItem::MainMfaItem;
  mainMfaElementData << -1;
  mainCorrelElementData << "Análisis de Correlación";
  mainCorrelElementData << TreeItem::MainCorrelationItem;
  mainCorrelElementData << -1;
  
  QList<QVector<QVariant> > dataList;
  
  dataList << mainSeqElementData;
  dataList << mainMfaElementData;
  dataList << mainCorrelElementData;
  
  QModelIndex index = ui->explorerTreeView->model()->index(0, 0);
  
  for (int i = 0; i < 3; ++i) {
    if (!treeModel->insertRow(index.row() + i + 1, index.parent()))
      return;
    
    for (int column = 0; column < treeModel->columnCount(index.parent()); ++column) {
      QModelIndex child = treeModel->index(index.row() + i + 1, column,
                                           index.parent());
      treeModel->setData(child, dataList.at(i).at(column), Qt::EditRole);
    }
  }
}

void MainWindow::addSequenceToModels(const Sequence * sequence, const int & key)
{
  insertSequenceToTreeView(sequence, key);
  insertSequenceToSequenceListModel(sequence, key);
  insertSequenceToSequenceListModelForCgr(sequence, key);
  insertSequenceToModelsForCra(sequence, key);
}

void MainWindow::insertSequenceToTreeView(const Sequence * sequence,
                                          const int & key)
{
  QVector<QVariant> data;
  data << QString::fromStdString(sequence->getName()); // Nombre secuencia
  
  // Tipo de item seg�n el tipo de secuencia
  int type = utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType());
  if (type == GenomAMf::DNA_Alphabet) data << TreeItem::DnaSequenceItem;
  else if (type == GenomAMf::Proteic_Alphabet) data
  << TreeItem::ProteinSequenceItem;
  
  // Key de Hash contenedor
  //  data << parentApp->getSequences()->getSequencesHash().key(sequence);
  data << key;
  
  QAbstractItemModel *model = treeModel;
  QModelIndex mainSeqElementIndex = model->index(0, 0);
  int count = treeModel->getItem(mainSeqElementIndex)->childCount();
  int row = 0;
  QModelIndex index;
  QModelIndex parentIndex;
  if (count == 0) {
    index = mainSeqElementIndex;
    parentIndex = index;
    if (!model->insertRow(0, mainSeqElementIndex))
      return;
  }
  else {
    row = count;
    index = model->index(row - 1, 0, mainSeqElementIndex);
    parentIndex = mainSeqElementIndex;
    if (!model->insertRow(row, mainSeqElementIndex))
      return;
  }

  for (int column = 0; column < model->columnCount(index); ++column) {
    QModelIndex child = model->index(row, column, parentIndex);
    model->setData(child, data.at(column), Qt::EditRole);
    if (!model->headerData(column, Qt::Horizontal).isValid())
      model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"),
                           Qt::EditRole);
  }
  
  ui->explorerTreeView->selectionModel()->
      setCurrentIndex(model->index(row, 0,parentIndex),
                      QItemSelectionModel::ClearAndSelect);
}

void MainWindow::insertSequenceToSequenceListModel(const Sequence * sequence,
                                                   const int & key)
{
  int position = sequenceListModel->rowCount();
  sequenceListModel->insertRows(position, 1);
  QModelIndex index = sequenceListModel->index(position, 0, QModelIndex());
  int type = utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType());
  
  QList<QVariant> data;
  data << QString::fromStdString(sequence->getName()); // Nombre secuencia

  // Tipo de item seg�n tipo de secuencia 
  if (type == GenomAMf::DNA_Alphabet) 
    data << TreeItem::DnaSequenceItem;
  else if (type == GenomAMf::Proteic_Alphabet) 
    data << TreeItem::ProteinSequenceItem;
  
  data << key; // Key en hash

  sequenceListModel->setData(index, data);
}

void MainWindow::insertSequenceToModelsForCra(const Sequence * sequence,
                                              const int & key)
{
  int type = utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType());
  
  QList<QVariant> data;
  data << QString::fromStdString(sequence->getName()); // Nombre secuencia

  // Tipo de item seg�n tipo de secuencia 
  if (type == GenomAMf::DNA_Alphabet){ 
    data << TreeItem::DnaSequenceItem;
    data << key; // Key en hash
    
    int position = modelForDnaCra->rowCount();
    modelForDnaCra->insertRows(position, 1);
    QModelIndex index = modelForDnaCra->index(position, 0, QModelIndex());
    modelForDnaCra->setData(index, data);
  }
  else if (type == GenomAMf::Proteic_Alphabet){
    data << TreeItem::ProteinSequenceItem;
    data << key; // Key en hash
    
    int position = modelForProteinCra->rowCount();
    modelForProteinCra->insertRows(position, 1);
    QModelIndex index = modelForProteinCra->index(position, 0, QModelIndex());
    modelForProteinCra->setData(index, data);
  }
}

void 
MainWindow::insertSequenceToSequenceListModelForCgr(const Sequence * sequence,
                                                    const int & key)
{
  int position = sequenceListModelForCgr->rowCount();
  sequenceListModelForCgr->insertRows(position, 1);
  QModelIndex index = sequenceListModelForCgr->index(position, 0, QModelIndex());
  int type = utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType());
  
  QList<QVariant> data;
  data << QString::fromStdString(sequence->getName()); // Nombre secuencia

  // Tipo de item seg�n tipo de secuencia 
  if (type == GenomAMf::DNA_Alphabet) 
    data << TreeItem::DnaSequenceItem;
  else if (type == GenomAMf::Proteic_Alphabet) 
    data << TreeItem::ProteinSequenceItem;
  
  data << key; // Key en hash

  sequenceListModelForCgr->setData(index, data);
}

void MainWindow::removeSequenceFromSequenceListModel(SequenceListModel * model,
                                         const int & sequenceKey)
{
  bool keyFound = false;
  int position = -1;
  while (position < model->rowCount() && !keyFound){
    ++position;
    QModelIndex keyIndex = model->index(position, 0, QModelIndex());
    int key = model->data(keyIndex, Qt::UserRole).toInt();
    keyFound = key == sequenceKey;
  }
  if (keyFound){
    model->removeRows(position, 1);
    updateActionsState();
  }
}

void MainWindow::addCgrToModels(const int & cgrKey, const int & sequenceKey)
{
  insertCgrToTreeView(cgrKey, sequenceKey);
  removeSequenceFromSequenceListModel(sequenceListModelForCgr, sequenceKey);
//  insertCgrToCgrListModel(cgrKey);
}

void MainWindow::insertCgrToTreeView(const int & cgrKey,
                                     const int & sequenceKey)
{
  QModelIndex mainSeqElementIndex = treeModel->index(0, 0, QModelIndex());
  QModelIndex index = treeModel->index(sequenceKey, 0, mainSeqElementIndex);
  QAbstractItemModel *model = treeModel;
  
  if (model->columnCount(index) == 0) {
    if (!model->insertColumn(0, index))
      return;
  }

  if (!model->insertRow(0, index)) return;

  QVector<QVariant> data;
  data << "Representación Juego del Caos";
  data << TreeItem::CgrItem;
  data << cgrKey;
  
  for (int column = 0; column < model->columnCount(index); ++column) {
    QModelIndex child = model->index(0, column, index);
    model->setData(child, data.at(column), Qt::EditRole);
    if (!model->headerData(column, Qt::Horizontal).isValid())
      model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"),
                           Qt::EditRole);
  }
  
  ui->explorerTreeView->selectionModel()->setCurrentIndex(model->index(0, 0,
          index), QItemSelectionModel::ClearAndSelect);
}

void MainWindow::insertCgrToCgrListModel(const int & cgrKey)
{
  int position = cgrListModel->rowCount();
  cgrListModel->insertRows(position, 1);
  QModelIndex index = cgrListModel->index(position, 0, QModelIndex());
  
  const Sequence * sequence = parentApp->getCgrHash()->value(cgrKey)->
          getSequence();
  
  QList<QVariant> data;
  data << QString::fromStdString(sequence->getName()); // Nombre secuencia
  data << TreeItem::CgrItem;  // Tipo de elemento
  data << cgrKey; // Key en hash

  cgrListModel->setData(index, data);
}

     
 void MainWindow::insertMfaResultSetTotreeView(const int & resultSetKey)
 {
   QAbstractItemModel *model = treeModel;
   QModelIndex mainMfaElementIndex = model->index(1, 0);
   int count = treeModel->getItem(mainMfaElementIndex)->childCount();
   int row = 0;
   QModelIndex index;
   QModelIndex parentIndex;
   
   if (count == 0) {
     index = mainMfaElementIndex;
     parentIndex = index;
     if (!model->insertRow(0, mainMfaElementIndex))
       return;
   }
   else {
     row = count;
     index = model->index(row - 1, 0, mainMfaElementIndex);
     parentIndex = mainMfaElementIndex;
     if (!model->insertRow(row, mainMfaElementIndex))
       return;
   }
   
   QVector<QVariant> data;
   // Nombre
   data << QString("Resultado %1").arg(count + 1);
   // Tipo
   data << TreeItem::MfaResultItem;
   // Key de Hash contenedor
   data << resultSetKey;
   
   for (int column = 0; column < model->columnCount(index); ++column) {
     QModelIndex child = model->index(row, column, parentIndex);
     model->setData(child, data.at(column), Qt::EditRole);
     if (!model->headerData(column, Qt::Horizontal).isValid())
       model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"),
                            Qt::EditRole);
   }
   
   ui->explorerTreeView->selectionModel()->
           setCurrentIndex(model->index(row, 0,parentIndex),
                           QItemSelectionModel::ClearAndSelect);
 }
 /* 
 void insertCorrelationToTreeView(const CorrelationAnalysis * correl)
 {
 
 }
 */

void MainWindow::loadSequences()
{
  QVector<int> loadedSequences;
  QFileDialog * fileDialog = new QFileDialog(this);
  QStringList filters;
  filters << tr("Archivos en formato FASTA (*.fna *.fas *.fasta)");
  
  fileDialog->setNameFilters(filters);
  fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
  fileDialog->setFileMode(QFileDialog::ExistingFiles);
  fileDialog->setDirectory("./data/sequences");
  
  if (fileDialog->exec()) {
    QStringList filesList = fileDialog->selectedFiles();
    if (!filesList.isEmpty()) {
      loadedSequences = parentApp->loadSequences(filesList);
      int totalSequences = loadedSequences.at(0) + loadedSequences.at(1);
      
      QString infoText;
      QString text;
      QMessageBox::Icon icon = QMessageBox::NoIcon;
      
      if (totalSequences <= 0) {
        text = "No se cargaron nuevas secuencias.";
        infoText = "Esto se debe a una de las siguientes razones:\n - "
          "Las secuencias contenidas en los archivos ya fueron cargadas,"
          " o bien,\n - El formato de los archivos es incorrecto";
        icon = QMessageBox::Warning;
      }
      else {
        text = QString("Secuencias cargadas correctamente.");
        infoText = QString("Nuevas secuencias de ADN: %1\n"
                  "Nuevas secuencias de proteínas: %2") .arg(
                        loadedSequences.at(0)) .arg(loadedSequences.at(1));
        icon = QMessageBox::Information;
        updateActionsState();
      }

      QMessageBox msgBox(this);
      msgBox.setText(text);
      msgBox.setInformativeText(infoText);
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.setDefaultButton(QMessageBox::Ok);
      msgBox.setIcon(icon);
      msgBox.setTextFormat(Qt::RichText);
      msgBox.exec();
      
      //    QHashIterator<int, const Sequence *> i(parentApp->getSequences()->getSequences());
      //    cout <<"MainWindow::232: Contenido CustomSecuenceContainer: " << endl;;
      //    while (i.hasNext()) {
      //        i.next();
      //        cout << i.key() << " : "
      //              << qPrintable(QString::fromStdString(i.value()->getName()))
      //              << " key: "
      //              << parentApp->getSequences()->getSequences().key(i.value())
      //              << endl;
      //    }
      

    }
  }
}

void MainWindow::makeCgr()
{
  CgrParametersForm * cgrParametersForm = new CgrParametersForm(
          sequenceListModelForCgr, this);
  
  if (cgrParametersForm->exec() == QDialog::Accepted) {
    QList<int> sequenceKeysForCgr = 
            cgrParametersForm->getSelectedSequencesKeys();
    QList<int> cgrKeys = parentApp->makeCgr(sequenceKeysForCgr);
    
    for (int i = 0; i < cgrKeys.count(); ++i) {
      int cgrKey = cgrKeys.at(i);
      displayCgrResults(cgrKey);
    }
    
    for (int i = 0; i < sequenceKeysForCgr.count(); ++i) {
      int sequenceKey = sequenceKeysForCgr.at(i);
      removeSequenceFromSequenceListModel(sequenceListModelForCgr, 
                                          sequenceKey);
    }
  }
}

void MainWindow::makeMultifractalAnalysis()
{
  QList<int> sequencesKeysList = QList<int>();
  int minQ = 0;
  int maxQ = 0;
  int nCenters = 0;
  MfaParametersForm * mfaParametersForm = 
          new MfaParametersForm(sequenceListModel, this);
  if (mfaParametersForm->exec() == QDialog::Accepted) {
    minQ     = mfaParametersForm->getMinQValue();
    maxQ     = mfaParametersForm->getMaxQValue();
    nCenters = mfaParametersForm->getNCenters();
    sequencesKeysList = mfaParametersForm->getSelectedSequencesKeys();
    
    int mfaResultSetKey = 
            //          parentApp->makeMultifractalAnalysis_(sequencesKeysList, -2, 2);
            parentApp->makeMultifractalAnalysis(sequencesKeysList, 
                                                minQ, 
                                                maxQ,
                                                nCenters);
    
    displayMfaResults(mfaResultSetKey);
  }
}

void MainWindow::makeCorrelationAnalysis()
{
//  int nMeshFrames = 0;
  CorrelationAnalysisParametersForm * correlationParametersForm = 
          new CorrelationAnalysisParametersForm(modelForDnaCra,
                                                modelForProteinCra,
                                                this);
  
  if (correlationParametersForm->exec() == QDialog::Accepted) {
    QList<int> sequencesKeysList = 
            correlationParametersForm->getSelectedSequencesKeys();
//    int nMeshFrames = correlationParametersForm->getNMeshFrames();
    int craKey = parentApp->makeCorrelationAnalysis(sequencesKeysList, 512);
//    displayCraResults(craKey);
  }
}

void MainWindow::displayResultForm(QModelIndex index)
{
  QModelIndex typeIndex = treeModel->index(index.row(), 1, index.parent());
  QModelIndex keyIndex = treeModel->index(index.row(), 2, index.parent());
  int elementType = treeModel->data(typeIndex, Qt::DisplayRole).toInt();
  int key = treeModel->data(keyIndex, Qt::DisplayRole).toInt();
//  cout << "Type: "<< elementType << "  Key: "<< key << endl;
  
  switch (elementType)
  {
    case TreeItem::CgrItem:
      displayCgrResults(key);
      return;
      
    case TreeItem::MfaResultItem:
      displayMfaResults(key);
      return;
      
    case TreeItem::CorrelResultItem:
      
      return;
      
  }
}

void MainWindow::displayCgrResults(const int & cgrKey)
{
  const ChaosGameRepresentation * cgr = parentApp->getCgrHash()->value(cgrKey);

  if (cgr != 0) {
    CgrResultsForm * cgrResultsForm = new CgrResultsForm(cgr, this);
    ui->mdiArea->addSubWindow(cgrResultsForm);
    cgrResultsForm->show();
  }
}

void MainWindow::displayMfaResults(const int & mfaResultSetKey)
{
  QList<int> mfaKeys = parentApp->getMfaResultSetHash()->value(mfaResultSetKey);
//  QList<MultifractalAnalysis *> mfaListFromAnalysis;
  QList<MultifractalAnalysis> mfaListFromAnalysis;
  
  for (int i = 0; i < mfaKeys.count(); ++i) {
//    MultifractalAnalysis * mfaObject = 
    MultifractalAnalysis mfaObject = 
            parentApp->getMfaHash()->value(mfaKeys.at(i));
    mfaListFromAnalysis.append(mfaObject);
  }
  
  MfaResultsController * mfaResultsController = 
          new MfaResultsController(mfaListFromAnalysis);
  MfaResultsForm * mfaResultsForm = 
          mfaResultsController->contructTheResultsForm();
  ui->mdiArea->addSubWindow(mfaResultsForm);
  mfaResultsForm->show();
}

void MainWindow::displayCraResults(const int & craKey)
{
  CorrelationAnalysis craObject = parentApp->getCraHash()->value(craKey);
  
  if (!craObject.isEmpty()) {
    CorrelationAnalysisResultsForm * craResultsForm = 
            new CorrelationAnalysisResultsForm(&craObject, this);
    ui->mdiArea->addSubWindow(craResultsForm);
    craResultsForm->show();
  }
}

void MainWindow::updateActionsState()
{
  bool active = sequenceListModel->rowCount() > 0;
  ui->makeCorrelationAnalysisAction->setEnabled(active);
  ui->makeMultifractalAnalysisAction->setEnabled(active);
  
  active = sequenceListModelForCgr->rowCount() > 0;
  ui->makeCgrAction->setEnabled(active);
}

void MainWindow::closeSubWindow()
{
  ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::testSlot()
{
  
}

SequenceListModel * MainWindow::getSequenceListModelForCgr()
{
  return sequenceListModelForCgr;
}

QList<int> MainWindow::getCgrResultsFormsOnView()
{
  return cgrResultsFormsOnView;
}

SequenceListModel * MainWindow::getModelForDnaCra()
{
  return modelForDnaCra;
}

SequenceListModel * MainWindow::getModelForProteinCra()
{
  return modelForProteinCra;
}

