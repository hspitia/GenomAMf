#ifndef CORRELATIONANALYSISPARAMETERSFORM_H
#define CORRELATIONANALYSISPARAMETERSFORM_H

#include <QtGui/QWidget>
#include "ui_CorrelationAnalysisParametersForm.h"

class CorrelationAnalysisParametersForm : public QWidget
{
    Q_OBJECT

public:
    CorrelationAnalysisParametersForm(QWidget *parent = 0);
    ~CorrelationAnalysisParametersForm();

private:
    Ui::CorrelationAnalysisParametersFormClass ui;
};

#endif // CORRELATIONANALYSISPARAMETERSFORM_H
