#include "CorrelationAnalysisResultsForm.h"

CorrelationAnalysisResultsForm::
CorrelationAnalysisResultsForm(DistancesModel * distancesModel,
                               const QList<QStringList> & sequenceCodeList,
                               QWidget *parent)
    : QWidget(parent),
    ui(new Ui::CorrelationAnalysisResultsFormClass())
{
	ui->setupUi(this);
}

CorrelationAnalysisResultsForm::~CorrelationAnalysisResultsForm()
{
  
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
