/**
 * @file MfaResultsController.h
 * @date 13/11/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MfaResultsController.h
 *   Created on:  13/11/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef MFARESULTSCONTROLLER_H_
#define MFARESULTSCONTROLLER_H_

#include <app/AppController.h>
#include <gui/MfaResultsForm.h>
#include <mfa/MultifractalAnalisys.h>
#include <mfa/Plotter.h>




class MfaResultsController
{
  public:
    MfaResultsController();
    
    MfaResultsController(QList<MultifractalAnalisys * > mfaObjects);
    MfaResultsController(const QList<MultifractalAnalisys * > & 
                                           mfaObjects);
    
    virtual ~MfaResultsController();
    
    void setMfaObjects(QList <MultifractalAnalisys *> mfaObjects);
    
    MfaResultsForm * getMfaResultsForm();
    
    MfaResultsForm * contructTheResultsForm();
    
  private:
    QList<MultifractalAnalisys * > mfaObjects; /**< Lista de apuntadores a los 
      objetos Mfa cuyos resultados se desplegarán por pantalla */
    
    MfaResultsForm * mfaResultsForm; /**< Ventana para desplegar resultados 
      de los objetos Mfa*/
    
    QList<Plotter *> plotResults();
};

#endif /* MFARESULTSCONTROLLER_H_ */
