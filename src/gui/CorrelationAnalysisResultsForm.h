#ifndef CORRELATIONANALYSISRESULTSFORM_H
#define CORRELATIONANALYSISRESULTSFORM_H

#include <QtGui/QWidget>
#include "ui_CorrelationAnalysisResultsForm.h"

class CorrelationAnalysisResultsForm : public QWidget
{
    Q_OBJECT

public:
    CorrelationAnalysisResultsForm(QWidget *parent = 0);
    ~CorrelationAnalysisResultsForm();

private:
    Ui::CorrelationAnalysisResultsFormClass *ui;
};

#endif // CORRELATIONANALYSISRESULTSFORM_H
