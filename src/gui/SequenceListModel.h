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
#include <QAbstractItemModel>
#include <QList>
#include <QModelIndex>
#include <QStringList>
#include <QVariant>
#include <QIcon>

#include <gui/TreeItem.h>
#include <utils/Utils.h>


/**
 * 
 */
class SequenceListModel : public QAbstractTableModel
 {
     Q_OBJECT

 public:
//     SequenceListModel(const QStringList &data, QObject *parent = 0)
     SequenceListModel(const QList<QList<QVariant> > & data, 
                       QObject *parent = 0) 
     : QAbstractTableModel(parent), dataList(data) {}
//     : QAbstractItemModel(parent), dataList(data) {}
//     : QAbstractListModel(parent), dataList(data) {}

     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     int columnCount(const QModelIndex &parent) const;
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
     
//     QModelIndex index(int row, int column, 
//                       const QModelIndex & parent = QModelIndex()) const;
     
 private:
//     QStringList stringList;
     QList<QList<QVariant> > dataList;
//     QStringList dataList;
     
     QIcon getIcon(const int & type) const;
 }; 
    
#endif /* SEQUENCELISTMODEL_H_ */
