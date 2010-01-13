#include "PreprocessingScriptParametersForm.h"

PreprocessingScriptParametersForm::
PreprocessingScriptParametersForm(QWidget *parent) :
  QDialog(parent), ui(new Ui::PreprocessingScriptParametersForm())
{
  ui->setupUi(this);
  
  this->inputDirectoryPath  = "";
  this->outputDirectoryPath = "";
  this->isForFragment       = true;
  this->fragmentSize        = 100000;
  this->originType          = ScriptParametersSet::Local_Type;
  this->sequencesToDownload = QStringList();
  this->dataBaseName        = "";
  connectSignalsSlots();
  initControls();
  updateOriginControls(false);
  updateFragmentControls(Qt::Checked);
}

PreprocessingScriptParametersForm::~PreprocessingScriptParametersForm()
{
  delete ui;
}

void PreprocessingScriptParametersForm::done(int result)
{
  if (result == QDialog::Accepted) {
    QString message = validateFields();
    if (message.isEmpty()) {
      inputDirectoryPath  = ui->inputDirectoryLineEdit->text();
      outputDirectoryPath = ui->outputDirectoryLineEdit->text();
      
      if (!isForFragment)
        fragmentSize = -1;
      else
        fragmentSize = ui->fragmentSizeSpinBox->text().toInt();
      
      if(originType == ScriptParametersSet::Remote_Type)
        sequencesToDownload = takeSequencesToDownload();
      
      dataBaseName = ui->dataBaseComboBox->currentText();
      
      QDialog::done(result);
    }
    else {
      QMessageBox::warning(this, trUtf8("GenomAMf - Error"),
                           trUtf8("Se presentaron los "
                                  "siguientes problemas:\n\n") + message,
                           QMessageBox::Ok);
    }
  }
  else 
    QDialog::done(result);
}

void PreprocessingScriptParametersForm::connectSignalsSlots()
{
  connect(ui->remoteRadioButton, SIGNAL(toggled(bool /*checked*/)), this, 
          SLOT(updateOriginControls(bool /*checked*/)));
  
  connect(ui->fragmentCheckBox, SIGNAL(stateChanged(int /*checkState*/)), this, 
          SLOT(updateFragmentControls(int /*checkState*/)));
  
  connect(ui->findInputDirPushButton, SIGNAL(clicked()), this, 
          SLOT(updateInputDirectoryLineEdit()));

  connect(ui->findOutputDirPushButton, SIGNAL(clicked()), this, 
          SLOT(updateOutputDirectoryLineEdit()));
  
  connect(ui->addSequencePushButton, SIGNAL(clicked()), this, 
          SLOT(addItemToSequenceList()));
  
  connect(ui->removeSequencePushButton, SIGNAL(clicked()), this, 
          SLOT(removeItemFromSequenceList()));
  
}

QString PreprocessingScriptParametersForm::validateFields()
{
  QString message = "";
  
  if (ui->inputDirectoryLineEdit->text().isEmpty())
    message += trUtf8("- El campo \"Directorio de trabajo\" no "
                      "puede estar en blanco.\n");
  else {
    QDir dir = ui->inputDirectoryLineEdit->text();
    if (!dir.exists())
      message += trUtf8("- El campo \"Directorio de trabajo\" no "
                      "contiene un directorio válido.\n");
  }
  
  if (ui->outputDirectoryLineEdit->text().isEmpty())
    message += trUtf8("- El campo \"Directorio de destino\" no "
                      "puede estar en blanco.\n");
  else {
    QDir dir = ui->outputDirectoryLineEdit->text();
    if (!dir.exists())
      message += trUtf8("- El campo \"Directorio de destino\" no "
                      "contiene un directorio válido.\n");
  }

  if (originType == ScriptParametersSet::Remote_Type && 
      ui->sequenceTable->rowCount() == 0)
  {
     message += trUtf8("- El origen de las secuencias es remoto y no se han "
                       "  especificado secuencias para descarga.\n");
  }
  
  return message;
}

void PreprocessingScriptParametersForm::initControls()
{
  QStringList items;
  items << "Nucleotide";
  items << "Protein";
  
  ui->dataBaseComboBox->insertItems(0, items);
  
  ui->sequenceTable->setColumnCount(1);
  QStringList tableHeaders;
  tableHeaders << trUtf8("Secuencias");
//  tableHeaders << trUtf8("No.") << trUtf8("Secuencias");
  
  ui->sequenceTable->setHorizontalHeaderLabels(tableHeaders);
}

QStringList PreprocessingScriptParametersForm::takeSequencesToDownload()
{
  QStringList sequenceList;
  for (int i = 0; i < ui->sequenceTable->rowCount(); ++i) {
    sequenceList << ui->sequenceTable->itemAt(i, 0)->text();
  }
  return sequenceList;
}

void PreprocessingScriptParametersForm::addItemToSequenceList() 
{
  QString item = ui->sequenceIdLineEdit->text();
  
  if (!item.isEmpty()) {
    int nRows = ui->sequenceTable->rowCount();
    ui->sequenceTable->setRowCount(nRows + 1);
    QTableWidgetItem *newItem = new QTableWidgetItem(item);
    ui->sequenceTable->setItem(nRows, 0, newItem);
    ui->sequenceIdLineEdit->setText("");
  }
}

void PreprocessingScriptParametersForm::removeItemFromSequenceList()
{
  QList<QTableWidgetItem *> selectedItems = ui->sequenceTable->selectedItems();
  
  if (selectedItems.count() > 0){
    ui->sequenceTable->removeRow(selectedItems.at(0)->row());
  }
  
}

void PreprocessingScriptParametersForm::updateFragmentControls(int checkState)
{
//  bool flag = false;
  
  if (checkState == Qt::Checked)
    isForFragment = true;
  
  else if (checkState == Qt::Unchecked)
    isForFragment = false;

  ui->fragmentSizeSpinBox->setEnabled(isForFragment);
  ui->fragmentSizeLabel->setEnabled(isForFragment);
  ui->fragmentUnitsLabel->setEnabled(isForFragment);
}

void PreprocessingScriptParametersForm::updateOriginControls(bool checked)
{
  ui->dataBaseLabel->setEnabled(checked);
  ui->dataBaseComboBox->setEnabled(checked);
  ui->sequenceGroupBox->setEnabled(checked);
  
  if (checked) {
    originType = ScriptParametersSet::Remote_Type;
    ui->inputDirectoryLabel->setText(trUtf8("Directorio de descarga "
            "de las secuencias:"));
  }
  else { 
    originType = ScriptParametersSet::Local_Type;
    ui->inputDirectoryLabel->setText(trUtf8("Directorio de entrada "
            "de las secuencias:"));
  }
}

QString PreprocessingScriptParametersForm::findDirectory()
{
  QString path = "";

  path = QFileDialog::getExistingDirectory(this, 
                                           trUtf8("Selección de directorio"),
                                           QDir::homePath(), 
                                           QFileDialog::ShowDirsOnly | 
                                           QFileDialog::DontResolveSymlinks);
  return path;
}

void PreprocessingScriptParametersForm::updateInputDirectoryLineEdit()
{
  QString path = findDirectory();
  ui->inputDirectoryLineEdit->setText(path);
}
    
void PreprocessingScriptParametersForm::updateOutputDirectoryLineEdit()
{
  QString path = findDirectory();
  ui->outputDirectoryLineEdit->setText(path);
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

//int PreprocessingScriptParametersForm::getOriginType()
ScriptParametersSet::OriginType 
PreprocessingScriptParametersForm::getOriginType()
{
  return originType;
}

QStringList PreprocessingScriptParametersForm::getSequencesToDownload()
{
  return sequencesToDownload;
}

QString PreprocessingScriptParametersForm::getDataBaseName()
{
  return dataBaseName;
}
