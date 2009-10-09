#include "CgrParametersForm.h"

CgrParametersForm::CgrParametersForm(SequenceListModel * model, 
                                     QWidget *parent) :
  QDialog(parent), ui(new Ui::CgrParametersForm())
{
  sequenceSelectedKey = -1;
  ui->setupUi(this);
  ui->sequenceTableView->setModel(model);
  ui->sequenceTableView->selectRow(0);
}

CgrParametersForm::~CgrParametersForm()
{
  delete ui;
}

Ui::CgrParametersForm * CgrParametersForm::getUi()
{
  return ui;
}

void CgrParametersForm::setUi(Ui::CgrParametersForm * ui)
{
  this->ui = ui;
}

int CgrParametersForm::getSequenceSelectedKey(){
  return sequenceSelectedKey;
}

void CgrParametersForm::done(int result)
{
  // TODO Verificar validación de existencia de modelo o index
  
  if (result == QDialog::Accepted) {
    QModelIndex index = ui->sequenceTableView->selectionModel()->currentIndex();
    QAbstractItemModel *model = ui->sequenceTableView->model();

    if(model->rowCount() > 0)
      sequenceSelectedKey = model->data(index,Qt::UserRole).toInt();
//    QListWidgetItem *item = listWidget->currentItem();
//    if (item)
//      id = item->data(Qt::UserRole).toInt();
  }
  QDialog::done(result);
}

