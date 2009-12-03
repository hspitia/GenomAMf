#ifndef CORRELATIONANALYSISPARAMETERSFORM_H
#define CORRELATIONANALYSISPARAMETERSFORM_H

//#include <QtGui/QWidget>
#include <QtGui/QDialog>
#include "ui_CorrelationAnalysisParametersForm.h"
#include <gui/SequenceListModel.h>

//class CorrelationAnalysisParametersForm : public QWidget
class CorrelationAnalysisParametersForm : public QDialog
{
  Q_OBJECT

  public:
   CorrelationAnalysisParametersForm(SequenceListModel * modelDnaSequences,
                                     SequenceListModel * modelProteinSequences,
                                     QWidget *parent = 0);
   
    ~CorrelationAnalysisParametersForm();

    QList<int> getSelectedSequencesKeys();
    
    void done(int result);

  private:
    Ui::CorrelationAnalysisParametersFormClass *ui;
    
    SequenceListModel * modelDnaSequences;
    
    SequenceListModel * modelProteinSequences;
    
    QList<int> selectedSequencesKeys; /**< Lista de claves de las secuencias 
     seleccionadas por el usuario */
    
    void connectSignalsSlots();
    
    
  private slots:
    void changeTableModelToDna(bool checked);
    void changeTableModelToProtein(bool checked);
    
};

#endif // CORRELATIONANALYSISPARAMETERSFORM_H
