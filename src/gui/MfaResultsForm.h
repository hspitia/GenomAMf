#ifndef MFARESULTSFORM_H
#define MFARESULTSFORM_H

#include <QtGui/QWidget>
#include "ui_MfaResultsForm.h"

namespace Ui {
    class MfaResultsForm;
}

class MfaResultsForm : public QWidget
{
    Q_OBJECT

public:
    MfaResultsForm(QWidget *parent = 0);
    ~MfaResultsForm();

private:
    Ui::MfaResultsForm *ui;
};

#endif // MFARESULTSFORM_H
