/**
 * @file MainWindow.cpp
 * @date 6/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo de definiciones para la clase MfaResultsForm
 */

/* 
 *         File:  MfaResultsForm.cpp
 *   Created on:  6/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE
 *                ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo de implementacio-.n para la clase MfaResultsForm
 */

#include "MfaResultsForm.h"

MfaResultsForm::MfaResultsForm(QWidget *parent) :
  QWidget(parent), ui(new Ui::MfaResultsForm)
{
  ui->setupUi(this);
  connectSignalsSlots();
}

MfaResultsForm::~MfaResultsForm()
{
  delete ui;
}

void MfaResultsForm::connectSignalsSlots()
{
  connect(ui->buttonBox, SIGNAL(rejected()), this->parent(),
          SLOT(closeSubWindow()));
  connect(ui->buttonBox, SIGNAL(rejected()), this,
            SLOT(exportImage()));
}

void MfaResultsForm::exportImage()
{
  
}
