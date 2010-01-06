#include "PreprocessingScriptParametersForm.h"

PreprocessingScriptParametersForm::
PreprocessingScriptParametersForm(QWidget *parent) :
  QDialog(parent), ui(new Ui::PreprocessingScriptParametersForm())
{
  ui->setupUi(this);
  
  this->inputDirectoryPath = "";
  this->outputDirectoryPath = "";
  this->isForFragment       = true;
  this->fragmentSize        = 100000;
}

PreprocessingScriptParametersForm::~PreprocessingScriptParametersForm()
{
  delete ui;
}

void PreprocessingScriptParametersForm::done(int result)
{
  if (result == QDialog::Accepted) {
    inputDirectoryPath  = ui->inputDirectoryLineEdit->text();
    outputDirectoryPath = ui->outputDirectoryLineEdit->text();
    isForFragment       = true;
    fragmentSize        = 100000;
    
    /*if (!selectedIndexes.isEmpty()) {
      for (int i = 0; i < selectedIndexes.count(); ++i) {
        QModelIndex index = selectedIndexes.at(i);
        QAbstractItemModel *model = ui->sequenceTableView->model();
        
        selectedSequencesKeys << model->data(index, Qt::UserRole).toInt();

      }
    }*/
  }
  QDialog::done(result);
}

void PreprocessingScriptParametersForm::connectSignalsSlots()
{
//  connect(ui->, SIGNAL(signal), receiver, SLOT(method));
}
    
void PreprocessingScriptParametersForm::updateFragmentControls()
{
  
}


QString PreprocessingScriptParametersForm::getInputDirectoryPath()
{
  return inputDirectoryPath;
}

void PreprocessingScriptParametersForm::
setInputDirectoryPath(const QString & inputDirectoryPath)
{
  this->inputDirectoryPath = inputDirectoryPath;
}



QString PreprocessingScriptParametersForm::getOutputDirectoryPath()
{
  return outputDirectoryPath;
}

void PreprocessingScriptParametersForm::
setOutputDirectoryPath(const QString & outputDirectoryPath)
{
  this->outputDirectoryPath = outputDirectoryPath;
}

bool PreprocessingScriptParametersForm::getIsForFragment()
{
  return isForFragment;
}

void PreprocessingScriptParametersForm::
setIsForFragment(const bool & isForFragment)
{
  this->isForFragment = isForFragment;
}

int PreprocessingScriptParametersForm::getFragmentSize()
{
  return fragmentSize;
}

void PreprocessingScriptParametersForm::
setFragmentSize(const int & fragmentSize)
{
  this->fragmentSize = fragmentSize;
}
