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

// Qt
#include <QtCore/QObject>

//#include <app/AppController.h>
#include <gui/MfaResultsForm.h>
#include <mfa/MultifractalAnalysis.h>
#include <mfa/Plotter.h>
#include <utils/Definitions.h>

class MfaResultsForm;

class MfaResultsController
{
  public:
    MfaResultsController();
    
//    MfaResultsController(QList<MultifractalAnalysis * > mfaObjects);
//    MfaResultsController(const QList<MultifractalAnalysis * > & mfaObjects);
    MfaResultsController(const QList<MultifractalAnalysis> & mfaObjects);
    
    virtual ~MfaResultsController();
    
//    void setMfaObjects(QList <MultifractalAnalysis *> mfaObjects);
    void setMfaObjects(QList <MultifractalAnalysis> mfaObjects);
    
    MfaResultsForm * getMfaResultsForm();
    
    MfaResultsForm * contructTheResultsForm(QWidget *parent);
    
    QList<Plotter *> plotResults();
    
    QString convertDqValuesToCsv();
    bool exportDqValuesToCsv(const QString & fileName);
//    bool exportPlotToImageFile(Plotter::plotType,
//                               const QString & filename,
//                               GenomAMf::ImageFormat imageFormat);
    
    Plotter * getDqPlot();
    
    Plotter * getCqPlot();
    
    Plotter * getLinearRegressionPlot();
    
  private:
//    QList<MultifractalAnalysis * > mfaObjects; /**< Lista de apuntadores a los 
    QList<MultifractalAnalysis> mfaObjects; /**< Lista de apuntadores a los 
      objetos Mfa cuyos resultados se desplegarán por pantalla */
    
    MfaResultsForm * mfaResultsForm; /**< Ventana para desplegar resultados 
      de los objetos Mfa*/
    
    Plotter * dqPlot;
    
    Plotter * cqPlot; 
    
    Plotter * linearRegressionPlot; 
    
    QString separator;
    QString lineFeed;
    
    QList<QStringList > prepareContentSequenceTable();
    
    QList<QStringList > prepareContentDqValuesTable();
    
    QString getSequenceCodeAndNames();
    
    
};

#endif /* MFARESULTSCONTROLLER_H_ */
