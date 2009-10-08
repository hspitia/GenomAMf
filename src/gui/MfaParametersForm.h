#ifndef MFAPARAMETERSFORM_H
#define MFAPARAMETERSFORM_H

#include <QtGui/QDialog>
#include <QtGui/QIcon>
#include <QtGui/QPushButton>

#include "ui_MfaParametersForm.h"

//namespace Ui {
//    class MfaParametersForm;
//}

class MfaParametersForm : public QDialog
{
    Q_OBJECT

public:
    MfaParametersForm(QWidget *parent = 0);
    ~MfaParametersForm();

private:
    Ui::MfaParametersForm *ui;
};

#endif // MFAPARAMETERSFORM_H
