#ifndef PREPROCESSROUTINEPARAMETERSFORM_H
#define PREPROCESSROUTINEPARAMETERSFORM_H

#include <QtGui/QWidget>
#include "ui_PreprocessRoutineParametersForm.h"

class PreprocessRoutineParametersForm : public QWidget
{
    Q_OBJECT

public:
    PreprocessRoutineParametersForm(QWidget *parent = 0);
    ~PreprocessRoutineParametersForm();

private:
    Ui::PreprocessRoutineParametersFormClass ui;
};

#endif // PREPROCESSROUTINEPARAMETERSFORM_H
