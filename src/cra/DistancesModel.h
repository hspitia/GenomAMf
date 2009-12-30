/**
 * @file DistancesModel.h
 * @date 29/12/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  DistancesModel.h
 *   Created on:  29/12/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef DISTANCESMODEL_H_
#define DISTANCESMODEL_H_

#include <QAbstractTableModel>
#include <QStringList>
#include <QList>

/**
 * 
 */
class DistancesModel : public QAbstractTableModel
{
  Q_OBJECT

  public:
    DistancesModel(const QStringList & sequenceCodes,
                   const QList<double> & distances,
                   QObject *parent = 0);
    virtual ~DistancesModel();

//    void setSequences(const QStringList &sequenceNames);
//    void setDistances(const QList<int> & distances);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, 
                        int role) const;
//    Qt::ItemFlags flags(const QModelIndex &index) const;

  private:
    int offsetOf(int row, int column) const;

    QStringList sequences;
    QList<double> distances;
};

#endif /* DISTANCESMODEL_H_ */
