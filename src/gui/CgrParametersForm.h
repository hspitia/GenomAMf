#ifndef CGRPARAMETERSFORM_H
#define CGRPARAMETERSFORM_H

#include <QtGui/QDialog>
#include "ui_CgrParametersForm.h"

namespace Ui {
    class CgrParametersForm;
}

class CgrParametersForm : public QDialog 
{
    Q_OBJECT
    
public:
    CgrParametersForm(QWidget *parent = 0);
    ~CgrParametersForm();

private:
    Ui::CgrParametersForm *m_ui;
};

#endif // CGRPARAMETERSFORM_H
