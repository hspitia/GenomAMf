#ifndef PREPROCESSINGINGSCRIPTPARAMETERSFORM_H
#define PREPROCESSINGINGSCRIPTPARAMETERSFORM_H

#include <QtGui/QWidget>
#include "ui_PreprocessingScriptParametersForm.h"

class PreprocessingScriptParametersForm : public QWidget
{
    Q_OBJECT

public:
    PreprocessingScriptParametersForm(QWidget *parent = 0);
    ~PreprocessingScriptParametersForm();

private:
    Ui::PreprocessingScriptParametersFormClass ui;
};

#endif // PREPROCESSINGINGSCRIPTPARAMETERSFORM_H
