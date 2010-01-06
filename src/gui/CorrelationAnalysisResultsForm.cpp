#define DEBUG_MODE

#include <utils/Trace.h>

#include "CorrelationAnalysisResultsForm.h"

CorrelationAnalysisResultsForm::
CorrelationAnalysisResultsForm(DistancesModel * distancesModel,
                               Tree * tree,
                               const QList<QStringList> & sequenceCodeList,
                               QWidget *parent)
    : QWidget(parent),
    ui(new Ui::CorrelationAnalysisResultsFormClass())
{
	ui->setupUi(this);
	this->tree = tree;
	setUpSequenceTable(sequenceCodeList);
	ui->distanceTable->setModel(distancesModel);
	initControls();
	setUpTree();
	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_QuitOnClose);
}

CorrelationAnalysisResultsForm::~CorrelationAnalysisResultsForm()
{
  if (tree)
    tree = 0;
}

void CorrelationAnalysisResultsForm::connectSignalsSlots()
{
  connect(ui->buttonBox, SIGNAL(rejected()), this->parent(),
          SLOT(closeSubWindow()));
}

void CorrelationAnalysisResultsForm::initControls()
{
  //treePanel_ = new TreeCanvas;
  //treePanel_->setTreeDrawing(new PhylogramPlot());
  //treePanel_->setMinimumSize(400,400);
  //treePanelScrollArea_ = new QScrollArea;
  //treePanelScrollArea_->setWidget(treePanel_);

//  controlPanel_ = new QWidget(this);
  controlPanel_ = new QWidget(ui->controlsFrame);
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
  
//  treeControlers_->
//    getControlerById(TreeCanvasControlers::ID_ORIENTATION_CTRL)->
//    setMaximumWidth(120); 
  
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
  displayLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_DRAW_NODES_ID_CTRL));
  displayLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_DRAW_BRLEN_VALUES_CTRL));
  displayLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_DRAW_BOOTSTRAP_VALUES_CTRL));
  displayOptions->setLayout(displayLayout);
  
  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(drawingOptions);
  layout->addWidget(displayOptions);
  layout->addStretch(1);
  controlPanel_->setLayout(layout);

 
  statsPanel_ = new TreeStatisticsBox(ui->statsFrame);
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
