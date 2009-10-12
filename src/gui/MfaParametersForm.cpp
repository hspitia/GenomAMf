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
  ui->cgrTableView->setModel(model);
  ui->cgrTableView->selectRow(0);
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
  // TODO Verificar validación de existencia de modelo o index
  
  if (result == QDialog::Accepted) {
    QModelIndex index = ui->cgrTableView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->cgrTableView->model();

    if(model->rowCount() > 0){
      cgrSelectedKey = model->data(index,Qt::UserRole).toInt();
      minQValue = ui->qMinSpinBox->text().toInt();
      maxQValue = ui->qMaxSpinBox->text().toInt();
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
