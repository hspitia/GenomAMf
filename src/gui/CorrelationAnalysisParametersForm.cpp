#include "CorrelationAnalysisParametersForm.h"

CorrelationAnalysisParametersForm::CorrelationAnalysisParametersForm(QWidget *parent)
//    : QWidget(parent)
    : QDialog(parent),
    ui(new Ui::CorrelationAnalysisParametersFormClass())
{
	ui->setupUi(this);
}

CorrelationAnalysisParametersForm::~CorrelationAnalysisParametersForm()
{

}
