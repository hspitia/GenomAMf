#ifndef PREPROCESSINGINGSCRIPTPARAMETERSFORM_H
#define PREPROCESSINGINGSCRIPTPARAMETERSFORM_H

#include <QtGui/QDialog>
#include "ui_PreprocessingScriptParametersForm.h"

namespace Ui {
    class PreprocessingScriptParametersForm;
}

class PreprocessingScriptParametersForm : public QDialog
{
  Q_OBJECT

  public:
    PreprocessingScriptParametersForm(QWidget *parent = 0);
    ~PreprocessingScriptParametersForm();
    
    void done(int result);
    
    bool getIsForFragment();
    
    void setIsForFragment(const bool & isForFragment);
    
    QString getInputDirectoryPath();
    
    void setInputDirectoryPath(const QString & inputDirectoryPath);

    QString getOutputDirectoryPath();
    
    void setOutputDirectoryPath(const QString & outputDirectoryPath);
    
    int getFragmentSize();
    
    void setFragmentSize(const int & fragmentSize);
    
  private:
    Ui::PreprocessingScriptParametersForm * ui;
    
    QString inputDirectoryPath;
    
    QString outputDirectoryPath;
     
    bool isForFragment;
    
    int fragmentSize;
    
    
    void connectSignalsSlots();
    
  private slots:
       
    void updateFragmentControls();
    
};

#endif // PREPROCESSINGINGSCRIPTPARAMETERSFORM_H
