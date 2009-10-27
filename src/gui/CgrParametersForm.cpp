#include "CgrParametersForm.h"

CgrParametersForm::CgrParametersForm(SequenceListModel * model, 
                                     QWidget *parent) :
  QDialog(parent), ui(new Ui::CgrParametersForm())
{
  sequenceSelectedKey = -1;
  selectedSequencesKeys = QList<int>();
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

QList<int> CgrParametersForm::getSelectedSequencesKeys()
{
  return selectedSequencesKeys;
}

void CgrParametersForm::done(int result)
{
  if (result == QDialog::Accepted) {
    QList<QModelIndex> selectedIndexes = ui->sequenceTableView->
            selectionModel()->selectedRows();
    
    if (!selectedIndexes.isEmpty()) {
      for (int i = 0; i < selectedIndexes.count(); ++i)
      {
        QModelIndex index = selectedIndexes.at(i);
        QAbstractItemModel *model = ui->sequenceTableView->model();
        
//        if(model->rowCount() > 0)
        selectedSequencesKeys << model->data(index,Qt::UserRole).toInt();
//          sequenceSelectedKey = model->data(index,Qt::UserRole).toInt();
        //    QListWidgetItem *item = listWidget->currentItem();
        //    if (item)
        //      id = item->data(Qt::UserRole).toInt();
        
      }
    }
  }
  QDialog::done(result);
}

