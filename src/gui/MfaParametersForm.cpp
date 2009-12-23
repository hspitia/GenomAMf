#include "MfaParametersForm.h"
#include <utils/Utils.h>

MfaParametersForm::MfaParametersForm(SequenceListModel * model, QWidget *parent)
  : QDialog(parent),
  ui(new Ui::MfaParametersForm())
{
  cgrSelectedKey = -1;
  minQValue = 0;
  maxQValue = 0;
  ui->setupUi(this);
  ui->sequenceTableView->setModel(model);
  ui->sequenceTableView->selectRow(0);
}

MfaParametersForm::~MfaParametersForm()
{
  delete ui;
}

int MfaParametersForm::getCgrSelectedKey(){
  return cgrSelectedKey;
}

void MfaParametersForm::done(int result)
{
  // TODO Verificar validaci�n de existencia de modelo o index
  
//  if (result == QDialog::Accepted) {
//    QModelIndex index = ui->sequenceTableView->selectionModel()->currentIndex();
//    QAbstractItemModel *model = ui->sequenceTableView->model();
//
//    if(model->rowCount() > 0){
//      cgrSelectedKey = model->data(index,Qt::UserRole).toInt();
//      minQValue = ui->qMinSpinBox->text().toInt();
//      maxQValue = ui->qMaxSpinBox->text().toInt();
//    }
//  }
//  QDialog::done(result);
  
  
  if (result == QDialog::Accepted) {
    QList<QModelIndex> selectedIndexes = ui->sequenceTableView->
            selectionModel()->selectedRows();
    
    if (!selectedIndexes.isEmpty()) {
      for (int i = 0; i < selectedIndexes.count(); ++i) {
        QModelIndex index = selectedIndexes.at(i);
        QAbstractItemModel *model = ui->sequenceTableView->model();
        
        selectedSequencesKeys << model->data(index,Qt::UserRole).toInt();
      }
      minQValue = ui->qMinSpinBox->text().toInt();
      maxQValue = ui->qMaxSpinBox->text().toInt();
      nCenters  = ui->nCentersSpinBox->text().toInt();
    }
  }
  QDialog::done(result);
  
}

int MfaParametersForm::getMinQValue()
{
  return minQValue;
}

int MfaParametersForm::getMaxQValue()
{
  return maxQValue;
}

QList<int> MfaParametersForm::getSelectedSequencesKeys()
{
  return selectedSequencesKeys;
}

int MfaParametersForm::getNCenters()
{
  return nCenters;
}
