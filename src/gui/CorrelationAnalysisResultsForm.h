#ifndef CORRELATIONANALYSISRESULTSFORM_H
#define CORRELATIONANALYSISRESULTSFORM_H
// Qt
#include <QtGui/QWidget>

// Bio++
#include <Bpp/Qt/TreeCanvas.h>
#include <Phyl/Tree.h>
#include <Phyl/TreeDrawing.h>

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
                                   Tree * tree,
                                   const QList<QStringList> & sequenceCodeList,
                                   QWidget *parent = 0);
    
    ~CorrelationAnalysisResultsForm();
    
    Tree * getTree();
    
    void setTree(Tree * tree);
    
    TreeCanvas & getTreeCanvas();
    
private:
    Ui::CorrelationAnalysisResultsFormClass *ui;
    Tree * tree;
    TreeCanvas treeCanvas;
   
    void connectSignalsSlots();
    void setUpSequenceTable(const QList<QStringList> & sequenceCodeList);
    void setUpTree();
    QIcon getIcon(const int & type) const;
};

#endif // CORRELATIONANALYSISRESULTSFORM_H
