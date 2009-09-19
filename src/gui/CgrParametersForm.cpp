#include "CgrParametersForm.h"

CgrParametersForm::CgrParametersForm(QWidget *parent) 
  : QDialog(parent),
  m_ui(new Ui::CgrParametersForm())
{
  m_ui->setupUi(this);
}

CgrParametersForm::~CgrParametersForm()
{
  delete m_ui;
}
