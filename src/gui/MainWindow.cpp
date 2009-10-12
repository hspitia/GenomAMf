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
  this->sequenceListModel = new SequenceListModel(QList<QList<QVariant> > ());
  this->cgrListModel = new SequenceListModel(QList<QList<QVariant> > ());
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
  connect(ui->makeMultifractalAnalisysAction, SIGNAL(triggered()), this,
          SLOT(makeMultifractalAnalisys()));
  connect(ui->testAction, SIGNAL(triggered()), this, SLOT(testSlot()));
  connect(ui->explorerTreeView, SIGNAL(doubleClicked(QModelIndex)), this,
          SLOT(displayMfaResults()));
  
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
  
}

void MainWindow::addSequenceToModels(const Sequence * sequence, const int & key)
{
  insertSequenceToTreeView(sequence, key);
  insertSequenceToSequenceListModel(sequence, key);
}

void MainWindow::insertSequenceToTreeView(const Sequence * sequence,
                                          const int & key)
{
  int count = treeModel->rowCount();
  
  QModelIndex index = ui->explorerTreeView->model()->index(count - 1, 0);
  int type = utils::getAlphabetType(sequence->getAlphabet()->getAlphabetType());
  
  QVector<QVariant> data;
  data << QString::fromStdString(sequence->getName()); // Nombre secuencia

  // Tipo de item según el tipo de secuencia
  if (type == GenomAMf::DNA_Alphabet) data << TreeItem::DnaSequenceItem;
  else if (type == GenomAMf::Proteic_Alphabet) data
          << TreeItem::ProteinSequenceItem;
  
  // Key de Hash contenedor
  //  data << parentApp->getSequences()->getSequencesHash().key(sequence);
  data << key;
  
  if (!treeModel->insertRow(index.row() + 1, index.parent())) return;
  
  for (int column = 0; column < treeModel->columnCount(index.parent()); ++column)
  {
    QModelIndex child = treeModel->index(index.row() + 1, column,
            index.parent());
    treeModel->setData(child, data.at(column), Qt::EditRole);
  }
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

  // Tipo de item según tipo de secuencia 
  if (type == GenomAMf::DNA_Alphabet) data << TreeItem::DnaSequenceItem;
  else if (type == GenomAMf::Proteic_Alphabet) data
          << TreeItem::ProteinSequenceItem;
  
  data << key; // Key en hash

  sequenceListModel->setData(index, data);
}

void MainWindow::addCgrToModels(const int & cgrKey, const int & sequenceKey)
{
  insertCgrToTreeView(cgrKey, sequenceKey);
  insertCgrToCgrListModel(cgrKey);
}

void MainWindow::insertCgrToTreeView(const int & cgrKey,
                                     const int & sequenceKey)
{
  QModelIndex index = treeModel->index(sequenceKey, 0, QModelIndex());
  QAbstractItemModel *model = treeModel;
  
  if (model->columnCount(index) == 0)
  {
    if (!model->insertColumn(0, index)) return;
  }

  if (!model->insertRow(0, index)) return;

  QVector<QVariant> data;
  data << "Representación Juego del Caos";
  data << TreeItem::CgrItem;
  data << cgrKey;
  
  for (int column = 0; column < model->columnCount(index); ++column)
  {
    QModelIndex child = model->index(0, column, index);
    model->setData(child, data.at(column), Qt::EditRole);
    if (!model->headerData(column, Qt::Horizontal).isValid()) 
      model->setHeaderData( column, Qt::Horizontal, QVariant("[No header]"), 
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

/*      
 void insertMfaTotreeView(const MultyfractalAnalisys * mfa)
 {
 
 }
 
 void insertCorrelationToTreeView(const CorrelationAnalisys * correl)
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
  
  if (fileDialog->exec())
  {
    QStringList filesList = fileDialog->selectedFiles();
    if (!filesList.isEmpty())
    {
      loadedSequences = parentApp->loadSequences(filesList);
      int totalSequences = loadedSequences.at(0) + loadedSequences.at(1);
      
      QString infoText;
      QString text;
      QMessageBox::Icon icon = QMessageBox::NoIcon;
      
      if (totalSequences <= 0)
      {
        text = "No se cargaron nuevas secuencias.";
        infoText = "Esto se debe a una de las siguientes razones:\n - "
          "Las secuencias contenidas en los archivos ya fueron cargadas,"
          " o bien,\n - El formato de los archivos es incorrecto";
        icon = QMessageBox::Warning;
      }
      else
      {
        text = QString("Secuencias cargadas correctamente.");
        infoText
                = QString("Nuevas secuencias de ADN: %1\n"
                  "Nuevas secuencias de proteínas: %2") .arg(
                        loadedSequences.at(0)) .arg(loadedSequences.at(1));
        icon = QMessageBox::Information;
      }

      QMessageBox msgBox;
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
  if (sequenceListModel->rowCount() == 0)
  {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("GenomAMf - Representación del Juego del Caos");
    msgBox.setWindowIcon(QIcon(":/icons/cgr.png"));
    msgBox.setText("No hay secuencias cargadas en la aplicación.");
    msgBox.setInformativeText("Debe adicionar secuencias a la aplicación para "
      "realizar la Representación del Juego del Caos");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
  }
  else if (sequenceListModel->rowCount() > 0)
  {
    CgrParametersForm * cgrParametersForm = new CgrParametersForm(
            sequenceListModel, this);
    
    if (cgrParametersForm->exec() == QDialog::Accepted)
    {
      int key = cgrParametersForm->getSequenceSelectedKey();
      if (key != -1)
      {
        cout << "DEBUG - MainWindow::270 - " << "key: " << key << endl;
        const ChaosGameRepresentation * cgr = parentApp->makeCgr(key);
        cout << "DEBUG - Después de parentApp->makeCgr(key)" << endl;
        CgrResultsForm * cgrResultsForm = new CgrResultsForm(cgr, this);
        ui->mdiArea->addSubWindow(cgrResultsForm);
        cgrResultsForm->show();
        //        QMessageBox msgBox;
        //        msgBox.setText("Representación del Juego del Caos");
        //        msgBox.setInformativeText(QString("Key sequence: %1").arg(key));
        //        msgBox.setStandardButtons(QMessageBox::Ok);
        //        msgBox.setDefaultButton(QMessageBox::Ok);
        //        msgBox.setTextFormat(Qt::RichText);
        //        msgBox.exec();
        

      }
    }
  }
}

void MainWindow::makeMultifractalAnalisys()
{
  if (cgrListModel->rowCount() == 0)
  {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("GenomAMf - Análisis Multifractal");
    msgBox.setWindowIcon(QIcon(":/icons/mfa.png"));
    msgBox.setText("No existen Representaciones del Juego del Caos en la "
            "aplicación.");
    msgBox.setInformativeText("Debe realizar Representaciones del Juego del "
            "Caos en la aplicación para ejecutar el Análisis Multifractal");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();
  }
  else if (cgrListModel->rowCount() > 0)
  {
    cout << "MainWindow::350 - DEBUG" << endl;
    MfaParametersForm * mfaParametersForm = new MfaParametersForm(cgrListModel,
            this);
    if (mfaParametersForm->exec() == QDialog::Accepted)
    {
      int key = mfaParametersForm->getCgrSelectedKey();
      if (key != -1)
      {
        /*
        const MultifractalAnalisys * mfa = parentApp->makeMultifractalfAnalisys(key);
        cout << "DEBUG - Después de parentApp->makeCgr(key)" << endl;
        MfaResultsForm * mfaResultsForm = new MfaResultsForm(mfa, this);
        ui->mdiArea->addSubWindow(mfaResultsForm);
        mfaResultsForm->show();
         */
        QMessageBox msgBox;
        msgBox.setText("Análisis Multifractal");
        msgBox.setInformativeText(QString("Key cgr: %1\nq mínimo: %2"
                "\nq máximo: %3").arg(key)
                .arg(mfaParametersForm->getMinQValue())
                .arg(mfaParametersForm->getMaxQValue()));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setTextFormat(Qt::RichText);
        msgBox.exec();
      }
    }
  }
  
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

void MainWindow::testSlot()
{
  
}
