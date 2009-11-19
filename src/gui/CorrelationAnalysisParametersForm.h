#ifndef CORRELATIONANALYSISPARAMETERSFORM_H
#define CORRELATIONANALYSISPARAMETERSFORM_H

//#include <QtGui/QWidget>
#include <QtGui/QDialog>
#include "ui_CorrelationAnalysisParametersForm.h"

//class CorrelationAnalysisParametersForm : public QWidget
class CorrelationAnalysisParametersForm : public QDialog
{
    Q_OBJECT

public:
    CorrelationAnalysisParametersForm(QWidget *parent = 0);
    ~CorrelationAnalysisParametersForm();

private:
    Ui::CorrelationAnalysisParametersFormClass *ui;
};

#endif // CORRELATIONANALYSISPARAMETERSFORM_H
