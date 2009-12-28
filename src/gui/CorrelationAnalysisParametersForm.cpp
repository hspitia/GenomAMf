#include "CorrelationAnalysisParametersForm.h"

CorrelationAnalysisParametersForm::CorrelationAnalysisParametersForm(
        SequenceListModel * modelDnaSequences,
        SequenceListModel * modelProteinSequences,
        QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CorrelationAnalysisParametersFormClass())
{
	ui->setupUi(this);
	
	this->modelDnaSequences = modelDnaSequences;
	this->modelProteinSequences = modelProteinSequences;
	
	ui->sequenceTableView->setModel(modelDnaSequences);
	connectSignalsSlots();
}

CorrelationAnalysisParametersForm::~CorrelationAnalysisParametersForm()
{

}

void CorrelationAnalysisParametersForm::connectSignalsSlots()
{
  connect(ui->dnaRadio,     SIGNAL(toggled(bool /*checked*/)), this, 
          SLOT(changeTableModelToDna(bool /*checked*/)));
  
  connect(ui->proteinRadio, SIGNAL(toggled(bool /*checked*/)), this, 
          SLOT(changeTableModelToProtein(bool /*checked*/)));
}

void CorrelationAnalysisParametersForm::changeTableModelToDna(bool checked)
{
  if (checked)
    ui->sequenceTableView->setModel(modelDnaSequences);
}

void CorrelationAnalysisParametersForm::changeTableModelToProtein(bool checked)
{
  if (checked)
    ui->sequenceTableView->setModel(modelProteinSequences);
}

void CorrelationAnalysisParametersForm::done(int result)
{
  if (result == QDialog::Accepted) {
    QList<QModelIndex> selectedIndexes = ui->sequenceTableView->
            selectionModel()->selectedRows();
    
    if (!selectedIndexes.isEmpty()) {
      for (int i = 0; i < selectedIndexes.count(); ++i) {
        QModelIndex index = selectedIndexes.at(i);
        QAbstractItemModel *model = ui->sequenceTableView->model();
        
        selectedSequencesKeys << model->data(index,Qt::UserRole).toInt();
      }
      // TODO - Crear campo de entrada en el formulario para este parámetro
      nMeshFrames = 512;
    }
  }
  QDialog::done(result);
  
}

QList<int> CorrelationAnalysisParametersForm::getSelectedSequencesKeys()
{
  return selectedSequencesKeys;
}
    
int CorrelationAnalysisParametersForm::getNMeshFrames()
{
  return nMeshFrames;
}
