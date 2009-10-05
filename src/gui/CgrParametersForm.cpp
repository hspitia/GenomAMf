#include "CgrParametersForm.h"

CgrParametersForm::CgrParametersForm(SequenceListModel * model, 
                                     QWidget *parent) :
  QDialog(parent), m_ui(new Ui::CgrParametersForm())
{
  m_ui->setupUi(this);
  m_ui->sequenceListView->setModel(model);
//  m_ui->sequenceListView->
}

CgrParametersForm::~CgrParametersForm()
{
  delete m_ui;
}

Ui::CgrParametersForm * CgrParametersForm::getUi()
{
  return m_ui;
}

void CgrParametersForm::setUi(Ui::CgrParametersForm * m_ui)
{
  this->m_ui = m_ui;
}
