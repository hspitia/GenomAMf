#include "CorrelationAnalysisResultsForm.h"

CorrelationAnalysisResultsForm::
CorrelationAnalysisResultsForm(DistancesModel * distancesModel,
                               const QList<QStringList> & sequenceCodeList,
                               QWidget *parent)
    : QWidget(parent),
    ui(new Ui::CorrelationAnalysisResultsFormClass())
{
	ui->setupUi(this);
	setUpSequenceTable(sequenceCodeList);
	ui->distanceTable->setModel(distancesModel);
	
}

CorrelationAnalysisResultsForm::~CorrelationAnalysisResultsForm()
{
  
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
