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

#include <QtGui/QWidget>
#include <QtGui/QMdiSubWindow>
#include "ui_MfaResultsForm.h"

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

  private:
    Ui::MfaResultsForm *ui;
    
    /**
     * Realiza conexiones entre signals y slots.
     */
    void connectSignalsSlots();
    
};

#endif // MFARESULTSFORM_H
