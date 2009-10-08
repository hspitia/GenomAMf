#include "MfaParametersForm.h"
#include <utils/Utils.h>

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

