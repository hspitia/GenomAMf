#include "CorrelationAnalysisResultsForm.h"

CorrelationAnalysisResultsForm::
CorrelationAnalysisResultsForm(const CorrelationAnalysis * craObject,
                               QWidget *parent)
    : QWidget(parent),
    ui(new Ui::CorrelationAnalysisResultsFormClass())
{
	ui->setupUi(this);
}

CorrelationAnalysisResultsForm::~CorrelationAnalysisResultsForm()
{

}
