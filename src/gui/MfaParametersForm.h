#ifndef MFAPARAMETERSFORM_H
#define MFAPARAMETERSFORM_H

#include <QtGui/QDialog>
#include <QtGui/QIcon>
#include <QtGui/QPushButton>

#include "ui_MfaParametersForm.h"
#include <gui/SequenceListModel.h>
#include <mfa/MfaParametersSet.h>

//namespace Ui {
//    class MfaParametersForm;
//}

class MfaParametersForm : public QDialog
{
  Q_OBJECT

  public:
    MfaParametersForm(SequenceListModel * model, QWidget *parent = 0);
    ~MfaParametersForm();

    QList<int> getSelectedSequencesKeys();

    MfaParametersSet mfaParametersSet;

    MfaParametersSet getMfaParametersSet() const;

    void done(int result);

  private:
    Ui::MfaParametersForm *ui;

    QList<int> selectedSequencesKeys; /**< Lista de claves de las secuencias 
     seleccionadas por el usuario */
    
    void setMfaParametersSet(const MfaParametersSet & mfaParametersSet);

    void connectSignalsSlots();

  private slots:
    void updateTotalRadii();
};

#endif // MFAPARAMETERSFORM_H
