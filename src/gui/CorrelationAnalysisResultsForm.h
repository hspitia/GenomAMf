#ifndef CORRELATIONANALYSISRESULTSFORM_H
#define CORRELATIONANALYSISRESULTSFORM_H

#include <QtGui/QWidget>
#include <cra/CorrelationAnalysis.h>
#include "ui_CorrelationAnalysisResultsForm.h"

class CorrelationAnalysisResultsForm : public QWidget
{
    Q_OBJECT

public:
    CorrelationAnalysisResultsForm(const CorrelationAnalysis * craObject,
                                   QWidget *parent = 0);
    ~CorrelationAnalysisResultsForm();

private:
    Ui::CorrelationAnalysisResultsFormClass *ui;
};

#endif // CORRELATIONANALYSISRESULTSFORM_H
