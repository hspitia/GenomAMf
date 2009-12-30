#ifndef CORRELATIONANALYSISRESULTSFORM_H
#define CORRELATIONANALYSISRESULTSFORM_H

#include <QtGui/QWidget>

// Project
#include <cra/CorrelationAnalysis.h>
#include <cra/DistancesModel.h>
#include <gui/TreeItem.h>
#include "ui_CorrelationAnalysisResultsForm.h"

class CorrelationAnalysisResultsForm : public QWidget
{
    Q_OBJECT

public:
    CorrelationAnalysisResultsForm(DistancesModel * distancesModel,
                                   const QList<QStringList> & sequenceCodeList,
                                   QWidget *parent = 0);
    ~CorrelationAnalysisResultsForm();

private:
    Ui::CorrelationAnalysisResultsFormClass *ui;
    
    QIcon getIcon(const int & type) const;
};

#endif // CORRELATIONANALYSISRESULTSFORM_H
