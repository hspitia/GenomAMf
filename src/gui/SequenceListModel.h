/**
 * @file SequenceListModel.h
 * @date 3/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  SequenceListModel.h
 *   Created on:  3/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef SEQUENCELISTMODEL_H_
#define SEQUENCELISTMODEL_H_

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QStringList>
#include <QVariant>


/**
 * 
 */
class SequenceListModel : public QAbstractListModel
 {
     Q_OBJECT

 public:
//     SequenceListModel(const QList<QStringList> & data, QObject *parent = 0)
     SequenceListModel(const QStringList &data, QObject *parent = 0)
         : QAbstractListModel(parent), dataList(data) {}

     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     QVariant data(const QModelIndex &index, int role) const;
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
     
     Qt::ItemFlags flags(const QModelIndex &index) const;
     bool setData(const QModelIndex &index, const QVariant &value,
                  int role = Qt::EditRole);
     
     bool insertRows(int position, int rows, 
                     const QModelIndex &index = QModelIndex());
     bool removeRows(int position, int rows, 
                     const QModelIndex &index = QModelIndex());
     
 private:
//     QStringList stringList;
//     QList<QStringList> dataList;
     QStringList dataList;
 }; 
    
#endif /* SEQUENCELISTMODEL_H_ */
