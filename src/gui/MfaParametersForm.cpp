#include "MfaParametersForm.h"
#include <utils/Utils.h>

MfaParametersForm::MfaParametersForm(SequenceListModel * model, QWidget *parent)
  : QDialog(parent),
  ui(new Ui::MfaParametersForm())
{
  mfaParametersSet = MfaParametersSet();
  ui->setupUi(this);
  connectSignalsSlots();
  ui->totalRadii->setEnabled(false);
  updateTotalRadii();
  ui->sequenceTableView->setModel(model);
  ui->sequenceTableView->selectRow(0);
}

MfaParametersForm::~MfaParametersForm()
{
  delete ui;
}

void MfaParametersForm::connectSignalsSlots()
{
  connect(ui->minRSpinBox, SIGNAL(valueChanged(int /*value*/)), this, 
          SLOT(updateTotalRadii()));
  connect(ui->maxRSpinBox, SIGNAL(valueChanged(int /*value*/)), this, 
          SLOT(updateTotalRadii()));
  connect(ui->radiusStepSpinBox, SIGNAL(valueChanged(int /*value*/)), this, 
          SLOT(updateTotalRadii()));
}

MfaParametersSet MfaParametersForm::getMfaParametersSet() const
{
  return mfaParametersSet;
}

void MfaParametersForm::setMfaParametersSet(const MfaParametersSet & mfaParametersSet)
{
  this->mfaParametersSet = mfaParametersSet;
}


void MfaParametersForm::done(int result)
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
      
      mfaParametersSet.setMinQ(ui->minQSpinBox->text().toInt());
      mfaParametersSet.setMaxQ(ui->maxQSpinBox->text().toInt());
      mfaParametersSet.setMinR(ui->minRSpinBox->text().toInt());
      mfaParametersSet.setMaxR(ui->maxRSpinBox->text().toInt());
      mfaParametersSet.setRadiusStep(ui->radiusStepSpinBox->text().toInt());
      mfaParametersSet.setNCenters(ui->nCentersSpinBox->text().toInt());
      mfaParametersSet.setNIterations(ui->nIterationsSpinBox->text().toInt());
    }
  }
  QDialog::done(result);
  
}

void MfaParametersForm::updateTotalRadii()
{
  int minR = ui->minRSpinBox->text().toInt();
  int maxR = ui->maxRSpinBox->text().toInt();
  int radiusStep = ui->radiusStepSpinBox->text().toInt();
  
  int totalRadii = static_cast<int>( 
          ceil(((double)maxR - (double)minR + 1)/ (double)radiusStep));
  
  ui->totalRadii->setText(QString("%1").arg(totalRadii));
  
}

QList<int> MfaParametersForm::getSelectedSequencesKeys()
{
  return selectedSequencesKeys;
}
