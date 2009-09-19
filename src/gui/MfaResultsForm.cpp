#include "MfaResultsForm.h"

MfaResultsForm::MfaResultsForm(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::MfaResultsForm)
{
	ui->setupUi(this);
}

MfaResultsForm::~MfaResultsForm()
{
  delete ui;
}
