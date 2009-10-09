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
    void setUi(Ui::CgrParametersForm * ui);
    
    /**
     * Retorna 
     * @return 
     */
    int getSequenceSelectedKey();
    
    void done(int result);
    
private:
    Ui::CgrParametersForm *ui;
    int sequenceSelectedKey; /**< Clave de la secuencia seleccionada por el 
      usuario */
    
    
    
};

#endif // CGRPARAMETERSFORM_H
