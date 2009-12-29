#ifndef CORRELATIONANALYSISPARAMETERSFORM_H
#define CORRELATIONANALYSISPARAMETERSFORM_H

//#include <QtGui/QWidget>
#include <QtGui/QDialog>
#include <QtGui/QMessageBox>

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
    
    int getNMeshFrames();
    
    void done(int result);

  private:
    Ui::CorrelationAnalysisParametersFormClass *ui;
    
    SequenceListModel * modelDnaSequences;
    
    SequenceListModel * modelProteinSequences;
    
    QList<int> selectedSequencesKeys; /**< Lista de claves de las secuencias 
     seleccionadas por el usuario */
    
    int nMeshFrames; /**< Número de cuadros o subconjuntos para determinar las 
      medidas mu de cada CGR del análisis. */
    
    void connectSignalsSlots();
    
    
  private slots:
    void changeTableModelToDna(bool checked);
    void changeTableModelToProtein(bool checked);
    
};

#endif // CORRELATIONANALYSISPARAMETERSFORM_H
