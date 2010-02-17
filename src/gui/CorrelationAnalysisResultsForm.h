#ifndef CORRELATIONANALYSISRESULTSFORM_H
#define CORRELATIONANALYSISRESULTSFORM_H
// Qt
#include <QtGui/QWidget>
#include <QtGui/QFormLayout>
#include <QtGui/QDockWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>

// Bio++
#include <Bpp/Qt/TreeCanvas.h>
#include <Bpp/Qt/TreeCanvasControlers.h>
#include <Bpp/Qt/TreeStatisticsBox.h>
#include <Phyl/Tree.h>
#include <Phyl/TreeDrawing.h>
// Project
#include <cra/CorrelationAnalysis.h>
#include <cra/DistancesModel.h>
#include <cra/CorrelationAnalysisResultsController.h>
#include <gui/TreeItem.h>
#include "ui_CorrelationAnalysisResultsForm.h"

class CorrelationAnalysisResultsController;


class CorrelationAnalysisResultsForm : public QWidget
{
  Q_OBJECT

  public:
    CorrelationAnalysisResultsForm(DistancesModel * distancesModel,
                                   Tree * tree,
                                   const QList<QStringList> & sequenceCodeList,
                                   CorrelationAnalysisResultsController *
                                   parentController,
                                   QWidget *parent = 0);

    ~CorrelationAnalysisResultsForm();
    
    CorrelationAnalysisResultsController * getParentController();
    
    void setParentController(CorrelationAnalysisResultsController * 
                             parentController);
    
    Tree * getTree();

    void setTree(Tree * tree);

    TreeCanvas & getTreeCanvas();

  private:
    CorrelationAnalysisResultsController * parentController;
    Ui::CorrelationAnalysisResultsFormClass *ui;
    Tree * tree;
    TreeCanvas treeCanvas;

    TreeCanvasControlers * treeControlers_;
    QWidget * controlPanel_;
    TreeStatisticsBox * statsPanel_;

    //    QDockWidget* statsDockWidget_; 
    //    QDockWidget* controlsDockWidget_;

    void connectSignalsSlots();
    void setUpSequenceTable(const QList<QStringList> & sequenceCodeList);
    void setUpTree();
    QIcon getIcon(const int & type) const;

    void initControls();
    void updateTreeControls();
    
  private slots:
    void exportToNewickTree();
};

#endif // CORRELATIONANALYSISRESULTSFORM_H
