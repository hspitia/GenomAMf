#define DEBUG_MODE

#include <utils/Trace.h>

#include "CorrelationAnalysisResultsForm.h"

CorrelationAnalysisResultsForm::
CorrelationAnalysisResultsForm(DistancesModel * distancesModel,
                               Tree * tree,
                               const QList<QStringList> & sequenceCodeList,
                               CorrelationAnalysisResultsController *
                               parentController,
                               QWidget *parent)
    : QWidget(parent),
    ui(new Ui::CorrelationAnalysisResultsFormClass())
{
	ui->setupUi(this);
	this->tree = tree;
	this->parentController = parentController;
	connectSignalsSlots();
	setUpSequenceTable(sequenceCodeList);
	ui->distanceTable->setModel(distancesModel);
	initControls();
	setUpTree();
	setAttribute(Qt::WA_DeleteOnClose);
}

CorrelationAnalysisResultsForm::~CorrelationAnalysisResultsForm()
{
  if (tree)
    tree = 0;
  
  if (parentController)
    parentController = 0;
}

void CorrelationAnalysisResultsForm::connectSignalsSlots()
{
  connect(ui->buttonBox, SIGNAL(rejected()), this->parent(),
          SLOT(closeSubWindow()));
  connect(ui->exportToNewickFormatButton, SIGNAL(clicked()), this,
          SLOT(exportToNewickTree()));
  connect(ui->exportToCSVButton, SIGNAL(clicked()), this,
          SLOT(exportDistancesToCsv()));
}

void CorrelationAnalysisResultsForm::initControls()
{
//  controlPanel_ = new QWidget(ui->controlsFrame);
  controlPanel_ = new QWidget(ui->controlsItem);
  treeControlers_ = new TreeCanvasControlers();
  
  QGroupBox* drawingOptions = new QGroupBox;
  drawingOptions->setTitle(tr("Dibujo"));
  QFormLayout* drawingLayout = new QFormLayout;
  drawingLayout->addRow(tr("&Tipo:"),        
                        treeControlers_->getControlerById(TreeCanvasControlers::
                                         ID_DRAWING_CTRL));
  drawingLayout->addRow(trUtf8("&Orientación:"), 
                        treeControlers_->getControlerById(TreeCanvasControlers::
                                                          ID_ORIENTATION_CTRL));
  drawingLayout->addRow(tr("Ancho (px):"),   
                        treeControlers_->getControlerById(TreeCanvasControlers::
                                                          ID_WIDTH_CTRL));
  drawingLayout->addRow(tr("&Alto (px):"), 
                        treeControlers_->getControlerById(TreeCanvasControlers::
                                                          ID_HEIGHT_CTRL));
  drawingOptions->setLayout(drawingLayout);
  
  treeControlers_->
    getControlerById(TreeCanvasControlers::ID_WIDTH_CTRL)->
    setMaximumWidth(120);
  
  treeControlers_->
    getControlerById(TreeCanvasControlers::ID_HEIGHT_CTRL)->
    setMaximumWidth(120);

  treeControlers_->
    getControlerById(TreeCanvasControlers::ID_DRAWING_CTRL)->
    setMaximumWidth(120);
  
  
  
  QGroupBox* displayOptions = new QGroupBox;
  displayOptions->setTitle(trUtf8("Información"));
  QVBoxLayout* displayLayout = new QVBoxLayout;
  displayLayout->addWidget(treeControlers_->
                           getControlerById(TreeCanvasControlers::
                                            ID_DRAW_NODES_ID_CTRL));
  displayLayout->addWidget(treeControlers_->
                           getControlerById(TreeCanvasControlers::
                                            ID_DRAW_BRLEN_VALUES_CTRL));
//  displayLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_DRAW_BOOTSTRAP_VALUES_CTRL));
  displayOptions->setLayout(displayLayout);
  
  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(drawingOptions);
  layout->addWidget(displayOptions);
  layout->addStretch(1);
  controlPanel_->setLayout(layout);
//  layout->setContentsMargins(0,0,0,0);
 
//  statsPanel_ = new TreeStatisticsBox(ui->statsFrame);
  statsPanel_ = new TreeStatisticsBox(ui->statsItem);
  statsPanel_->setFlat(true);
//  ui->statsFrame->setContentsMargins(0,0,0,0);
//  ui->controlsFrame->setContentsMargins(0,0,0,0);
}

void CorrelationAnalysisResultsForm::
setUpSequenceTable(const QList<QStringList> & sequenceCodeList)
{
  QTableWidget * table =  ui->sequenceTable;
  table->setColumnCount(2);
  table->setRowCount(sequenceCodeList.count()); 
  QStringList headers;
  headers << QString::fromUtf8("Código")
          << QString::fromUtf8("Secuencia");
  
  table->setHorizontalHeaderLabels(headers);
  
  for (int row = 0; row < sequenceCodeList.count(); ++row) {
    QStringList contentRow = sequenceCodeList.at(row);
    QTableWidgetItem * codeItem = new QTableWidgetItem(contentRow.at(1));
    QTableWidgetItem * nameItem = new QTableWidgetItem(contentRow.at(2));
    table->setItem(row, 0, codeItem);
    table->setItem(row, 1, nameItem);
    
    int type = contentRow.at(0).toInt();
    int iconType = TreeItem::DnaSequenceItem; 
            
    if (type == GenomAMf::Proteic_Alphabet) 
      iconType = TreeItem::ProteinSequenceItem;
    
      table->item(row, 1)->setIcon(getIcon(iconType));
  }
}

void CorrelationAnalysisResultsForm::setUpTree()
{
  treeCanvas.setTree(tree);
  treeCanvas.setTreeDrawing(*(treeControlers_->getSelectedTreeDrawing()));
  treeCanvas.setMinimumSize(300,300);
  treeCanvas.setMaximumSize(1200,1200);
  treeCanvas.resize(400, 400);
  treeControlers_->applyOptions(&treeCanvas);
  ui->treePanelScrollArea->setWidget(&treeCanvas);
  updateTreeControls();
  
}

void CorrelationAnalysisResultsForm::updateTreeControls()
{
  statsPanel_->updateTree(*tree);
  treeControlers_->setTreeCanvas(&treeCanvas);
  treeControlers_->actualizeOptions();
}

void CorrelationAnalysisResultsForm::exportToNewickTree()
{
  QString filename = trUtf8("Arbol_filogenetico");
  filename += ".tree";
  
  QStringList filters;
  filters << "Newick tree format (*.tree)";
  
  QFileDialog * fileDialog = new QFileDialog(this);
  fileDialog->setNameFilters(filters);
  fileDialog->setAcceptMode(QFileDialog::AcceptSave);
  fileDialog->setDirectory(QDir::homePath());
  fileDialog->selectFile(filename);
  fileDialog->setDefaultSuffix("tree");
  
  if(fileDialog->exec()){
    QStringList list = fileDialog->selectedFiles();
    if(!list.isEmpty()){
      filename = list.at(0);
      bool succes;
      
      //      TRACE (__LINE__ << "\n\t" << "Dir tree en Form: " << tree);
      //      succes = parentController->exportTreeToNewickFormat(filename);
      try {
        Newick newick;
        newick.write(*tree, filename.toStdString());
        succes = true;
      }
      catch (Exception e) {
        succes = false;
      }
      
      if(!succes){
        QMessageBox::information(this,"Error", trUtf8("Ocurrió un "
                "error mientras se trataba de guardar el árbol.\n "
                "Verifique los permisos del directorio destino e intente "
                "exportar nuevamente."),
                QMessageBox::Ok);
      }
    }
  }
}

void CorrelationAnalysisResultsForm::exportDistancesToCsv()
{
  QString fileName = trUtf8("DistanceMatrix");
  QStringList filters;
  filters << trUtf8("Comma separated values (*.csv)");
  
  QFileDialog * fileDialog = new QFileDialog(this);
  fileDialog->setNameFilters(filters);
  fileDialog->setAcceptMode(QFileDialog::AcceptSave);
  fileDialog->setDirectory(QDir::homePath());
  fileDialog->selectFile(fileName);
  fileDialog->setDefaultSuffix("csv");
  
  if(fileDialog->exec()){
    QStringList list = fileDialog->selectedFiles();
    if(!list.isEmpty()){
      fileName = list.at(0);
      
      bool succes = parentController->exportDistanceMatrixToCsv(fileName);
      if (!succes)
        QMessageBox::critical(this, trUtf8("GenomAMf - Error"), 
                              trUtf8("Ha ocurrido un error al "
                                      "tratar de guardar el archivo:\n %1\n\n"
                                      "Verifique los permisos del directorio "
                                      "destino e intente guardar el archivo"
                                      "nuevamente.").arg(fileName),
                                      QMessageBox::Ok);
    }
  }
  delete fileDialog;
}

QIcon CorrelationAnalysisResultsForm::getIcon(const int & type) const
{
  QIcon icon;
  
  if(type == TreeItem::DnaSequenceItem)
    icon = QIcon(":/icons/seq_dna.png");
  else if(type == TreeItem::ProteinSequenceItem)
    icon = QIcon(":/icons/seq_protein.png");
  else if(type == TreeItem::CgrItem)
    icon = QIcon(":/icons/cgr.png");
  
  return icon;
}

CorrelationAnalysisResultsController * 
CorrelationAnalysisResultsForm::getParentController()
{
  return parentController;
}

void CorrelationAnalysisResultsForm::
setParentController(CorrelationAnalysisResultsController * parentController)
{
  this->parentController = parentController;
}

Tree * CorrelationAnalysisResultsForm::getTree()
{
  return tree;
}

void CorrelationAnalysisResultsForm::setTree(Tree * tree)
{
  this->tree = tree;
}

TreeCanvas & CorrelationAnalysisResultsForm::getTreeCanvas()
{
  return treeCanvas;
}

