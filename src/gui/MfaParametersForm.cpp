#include "MfaParametersForm.h"

MfaParametersForm::MfaParametersForm(QWidget *parent)
  : QDialog(parent),
  ui(new Ui::MfaParametersForm())
{
  ui->setupUi(this);
}

MfaParametersForm::~MfaParametersForm()
{
  delete ui;
}
