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
	setUpTree();
	setAttribute(Qt::WA_DeleteOnClose);
}

CorrelationAnalysisResultsForm::~CorrelationAnalysisResultsForm()
{
  if (tree)
    tree = 0;
}

void CorrelationAnalysisResultsForm::connectSignalsSlots()
{
  connect(ui->buttonBox, SIGNAL(rejected()), this,
          SLOT(close()));
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
  
//  setWindowFilePath(filePath);
  treeCanvas.setTree(tree);
//  treeCanvas.setTreeDrawing(*td);
//  treeCanvas.setMinimumSize(400,400);
//  setMinimumSize(400,400);
//  QScrollArea* treePanelScrollArea = new QScrollArea;
  ui->treePanelScrollArea->setWidget(&treeCanvas);
//  setWidget(treePanelScrollArea);
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
