/**
 * @file MainWindow.h
 * @date 6/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de definiciones para la clase MfaResultsForm
 */

/* 
 *         File:  MfaResultsForm.h
 *   Created on:  6/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de definiciones para la clase MfaResultsForm
 */

#ifndef MFARESULTSFORM_H
#define MFARESULTSFORM_H

// QT Library
#include <QtGui/QWidget>
#include <QtCore/QSignalMapper>
#include <QtGui/QMdiSubWindow>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QGridLayout>
#include <QtCore/QTextStream>
#include <QtSvg/QSvgGenerator>

// Project
#include "ui_MfaResultsForm.h"
#include <mfa/Plotter.h>
#include <mfa/MfaResultsController.h>
#include <gui/TreeItem.h>
#include <utils/NormalPlot.h>
#include <utils/LinearPlot.h>
#include <utils/Definitions.h>

class MfaResultsController;

// MathGl Library
//#include <mgl/mgl_data.h>
//#include <mgl/mgl_zb.h>
//#include <mgl/mgl_font.h>
#include <mgl/mgl_qt.h>

//Qwt Library
//#include <qwt_plot.h>

using namespace GenomAMf;


namespace Ui
{
  class MfaResultsForm;
}

class MfaResultsForm : public QWidget
{
  Q_OBJECT

  public:
    MfaResultsForm(const QList<QStringList> & dqTableContent,
                   const QList<QStringList> & contentList,
                   MfaResultsController * parentCotroller,
                   QWidget *parent = 0);
    ~MfaResultsForm();
    
    void setUpDqGraphic(Plotter * plotter);
    void setUpCqGraphic(Plotter * plotter);
    void setUpLinearRegressionGraphic(Plotter * plotter);
    
    void setUpDqPlot(NormalPlot * dqPlot);
    void setUpCqPlot(NormalPlot * cqPlot);
    void setUpLinearRegressionPlot(QList<LinearPlot *> linearPlotList);
    
    void setupPlotWidgets();
    
    void setUpSequenceTable(/*const QList<QStringList> & contentList*/);
    void setUpDqValuesTable(/*const QList<QStringList> & contentList*/);
    
    Ui::MfaResultsForm * getUi();
    
    QMathGL * getDqGraphicWidget();
    
    void setDqGraphicWidget(QMathGL * dqGraphicWidget);
    
    QMathGL * getCqGraphicWidget();
    
    void setCqGraphicWidget(QMathGL * cqGraphicWidget);
    
    QMathGL * getLinearRegressionGraphicWidget();
    
    void setLinearRegressionGraphicWidget(QMathGL * 
                                          linearRegressionGraphicWidget);
    
    MfaResultsController * getParentController();
    
    NormalPlot * getDqPlotWidget();
    
    void setDqPlotWidget(NormalPlot * dqPlotWidget);
    
    NormalPlot * getCqPlotWidget();
    
    void setCqPlotWidget(NormalPlot * cqPlotWidget);
    
    QList<LinearPlot *> getLinearPlotWidgetList();
    
    void setLinearPlotWidgetList(QList<LinearPlot *> linearPlotWidgetList);
    
    QFrame * getlinearPlotFrame();
    
    void setlinearPlotFrame(QFrame * linearPlotFrame);
    
  private:
    MfaResultsController * parentController;
    Ui::MfaResultsForm *ui;
    QMathGL * dqGraphicWidget;
    QMathGL * cqGraphicWidget;
    QMathGL * linearRegressionGraphicWidget;
    QList<QStringList> dqTableContent;
    QList<QStringList> sequenceList;
    NormalPlot * dqPlotWidget;
    NormalPlot * cqPlotWidget;
    QList<LinearPlot *> linearPlotWidgetList;
    QFrame * linearPlotFrame;
    
    /**
     * Realiza conexiones entre signals y slots.
     */
    void connectSignalsSlots();
    void setupGraphicWidgets();
    QIcon getIcon(const int & type) const;
    
  private slots:
    void exportImage(int plotType);
    bool exportNormalPlot(NormalPlot * plotWidget, 
                          const QString & fileName,
                          const QString & format);
    bool exportLinearPlot(const QList<LinearPlot* > & linearPlotList, 
                          const QString & fileName,
                          const QString & format);
    void exportDqValuesTableToCsv();
    
};

#endif // MFARESULTSFORM_H
