#ifndef CGRPARAMETERSFORM_H
#define CGRPARAMETERSFORM_H

#include <QtGui/QDialog>
#include "ui_CgrParametersForm.h"
#include <gui/SequenceListModel.h>


namespace Ui {
    class CgrParametersForm;
}

class CgrParametersForm : public QDialog 
{
    Q_OBJECT
    
public:
    CgrParametersForm(SequenceListModel * model, QWidget *parent = 0);
    ~CgrParametersForm();
    
    /**
     * Retorna 
     * @return 
     */
    Ui::CgrParametersForm * getUi();
    
    /**
     * Asigna 
     */
    void setUi(Ui::CgrParametersForm * m_ui);
    
private:
    Ui::CgrParametersForm *m_ui;
};

#endif // CGRPARAMETERSFORM_H
