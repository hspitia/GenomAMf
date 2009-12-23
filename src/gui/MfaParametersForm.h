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
    
    int getNCenters();
    
private:
    Ui::MfaParametersForm *ui;
    int cgrSelectedKey;
    
    QList<int> selectedSequencesKeys; /**< Lista de claves de las secuencias 
      seleccionadas por el usuario */
    
    int minQValue; /**< Valor q mínimo seleccionado en la interfaz como 
      parámetro para el análisis multifractal */
    int maxQValue; /**< Valor q máximoseleccionado en la interfaz como 
      parámetro para el análisis multifractal */
    
    int nCenters; /**< Número de centros para ejecución del análisis 
      multifractal */

};

#endif // MFAPARAMETERSFORM_H
