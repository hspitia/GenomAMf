/**
 * @file CorrelationAnalysisResultsController.h
 * @date 29/12/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  CorrelationAnalysisResultsController.h
 *   Created on:  29/12/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef CORRELATIONANALYSISRESULTSCONTROLLER_H_
#define CORRELATIONANALYSISRESULTSCONTROLLER_H_

// Qt
#include <QtCore/QList>
#include <QtCore/QTextStream>

// Bio++
#include <Seq/Sequence.h>
#include <NumCalc/Matrix.h>
#include <Phyl/Newick.h>
#include <Phyl/Tree.h>

using namespace bpp;

// Project
#include <cra/CorrelationAnalysis.h>
#include <cra/CorrelationElement.h>
#include <cra/DistancesModel.h>
#include <gui/CorrelationAnalysisResultsForm.h>
#include <mfa/Plotter.h>

class CorrelationAnalysisResultsForm;
/**
 * 
 */
class CorrelationAnalysisResultsController
{
  public:
    CorrelationAnalysisResultsController();
    CorrelationAnalysisResultsController(const CorrelationAnalysis * craObject); 
    CorrelationAnalysisResultsController(const 
                                         CorrelationAnalysisResultsController &
                                         creResultsControllerObject);
    CorrelationAnalysisResultsController &
    operator=(const CorrelationAnalysisResultsController
              & creResultsControllerObject);
    
    virtual ~CorrelationAnalysisResultsController();
    
    CorrelationAnalysisResultsForm * contructTheResultsForm(QWidget *parent);
    
    bool exportTreeToNewickFormat(const QString & fileName);
    
    bool exportDistanceMatrixToCsv(const QString & fileName);
    
    // Access
    const CorrelationAnalysis * getCraObject();
    
    void setCraObject(const CorrelationAnalysis * craObject);
    
    
    DistancesModel * getDistanceModel();
    
  private:
    const CorrelationAnalysis * craObject;
    DistancesModel * distanceModel;
    
    // Methods
    Plotter * plotMuMeasures();
    QList<QStringList> prepareContentSequenceTable();
    DistancesModel * prepareDistancesModel();
    QString getSequenceCodeAndNames();
    QString convertDistanceMatrixToCsv();
};

#endif /* CORRELATIONANALYSISRESULTSCONTROLLER_H_ */
