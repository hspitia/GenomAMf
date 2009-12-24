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
#include <QtGui/QMdiSubWindow>

// Project
#include "ui_MfaResultsForm.h"
#include <mfa/Plotter.h>
#include <gui/TreeItem.h>


// MathGl Library
//#include <mgl/mgl_data.h>
//#include <mgl/mgl_zb.h>
//#include <mgl/mgl_font.h>
#include <mgl/mgl_qt.h>

namespace Ui
{
  class MfaResultsForm;
}

class MfaResultsForm : public QWidget
{
  Q_OBJECT

  public:
    MfaResultsForm(QWidget *parent = 0);
    ~MfaResultsForm();
    
    void setUpDqGraphic(Plotter * plotter);
    void setUpCqGraphic(Plotter * plotter);
    void setUpLinearRegressionGraphic(Plotter * plotter);
    void setUpSequenceTable(const QList<QStringList> & contentList);
    
    Ui::MfaResultsForm * getUi();
    
    QMathGL * getDqGraphicWidget();
    
    void setDqGraphicWidget(QMathGL * dqGraphicWidget);
    
    QMathGL * getCqGraphicWidget();
    
    void setCqGraphicWidget(QMathGL * cqGraphicWidget);
    
    QMathGL * getLinearRegressionGraphicWidget();
    
    void setLinearRegressionGraphicWidget(QMathGL * 
                                          linearRegressionGraphicWidget);
    
  private:
    Ui::MfaResultsForm *ui;
    QMathGL * dqGraphicWidget;
    QMathGL * cqGraphicWidget;
    QMathGL * linearRegressionGraphicWidget;
    
    
    /**
     * Realiza conexiones entre signals y slots.
     */
    void connectSignalsSlots();
    void setupGraphicWidgets();
    QIcon getIcon(const int & type) const;
    
  private slots:
    void exportImage();
    
};

#endif // MFARESULTSFORM_H
