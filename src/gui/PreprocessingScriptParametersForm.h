#ifndef PREPROCESSINGINGSCRIPTPARAMETERSFORM_H
#define PREPROCESSINGINGSCRIPTPARAMETERSFORM_H

#include <QtCore/QDir>
#include <QtGui/QDialog>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QTableWidgetItem>

#include <iostream>

#include <script/ScriptBuilder.h>
#include <script/ScriptParametersSet.h>
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
    
//    int getOriginType();
    ScriptParametersSet::OriginType getOriginType();
    
    QStringList getSequencesToDownload();
    
    QString getDataBaseName();
    
  private:
    Ui::PreprocessingScriptParametersForm * ui;
    
    QString inputDirectoryPath;
    
    QString outputDirectoryPath;
     
    bool isForFragment;
    
    int fragmentSize;
    
    QStringList sequencesToDownload;
    
    ScriptParametersSet::OriginType originType;
    
    QString dataBaseName;
    
    void connectSignalsSlots();
    
    QString validateFields();
    
    void initControls();
    
    QStringList takeSequencesToDownload();
    
  private slots:
    void addItemToSequenceList();

    void removeItemFromSequenceList();
       
    void updateFragmentControls(int checkState);
    
    void updateOriginControls(bool checked);
    
    QString findDirectory();
    
    void updateInputDirectoryLineEdit();
    
    void updateOutputDirectoryLineEdit();
    
};

#endif // PREPROCESSINGINGSCRIPTPARAMETERSFORM_H
