#ifndef MFAPARAMETERSFORM_H
#define MFAPARAMETERSFORM_H

#include <QtGui/QDialog>
#include <QtGui/QIcon>
#include <QtGui/QPushButton>

#include "ui_MfaParametersForm.h"

#include <gui/SequenceListModel.h>


//namespace Ui {
//    class MfaParametersForm;
//}

class MfaParametersForm : public QDialog
{
    Q_OBJECT

public:
    MfaParametersForm(SequenceListModel * model, QWidget *parent = 0);
    ~MfaParametersForm();
    
    int getCgrSelectedKey();
    
    QList<int> getSelectedSequencesKeys();
    
    void done(int result);
    
    /**
     * Retorna 
     * @return 
     */
    int getMinQValue();

    /**
     * Retorna 
     * @return 
     */
    int getMaxQValue();
    
private:
    Ui::MfaParametersForm *ui;
    int cgrSelectedKey;
    
    QList<int> selectedSequencesKeys; /**< Lista de claves de las secuencias 
      seleccionadas por el usuario */
    
    int minQValue; /**< Valor q m�nimo seleccionado en la interfaz como 
      par�metro para el an�lisis multifractal */
    int maxQValue; /**< Valor q m�ximo seleccionado en la interfaz como 
      par�metro para el an�lisis multifractal */
    
};

#endif // MFAPARAMETERSFORM_H
