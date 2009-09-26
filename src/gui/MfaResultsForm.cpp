#include "MfaResultsForm.h"

MfaResultsForm::MfaResultsForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::MfaResultsForm)
{
	ui->setupUi(this);
	connectSignalsSlots();
//  connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton *)), parent, SLOT(closeSubWindow()));
}

MfaResultsForm::~MfaResultsForm()
{
  delete ui;
}

void MfaResultsForm::connectSignalsSlots()
{
  connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton *)), this->parent(), SLOT(closeSubWindow()));
}
