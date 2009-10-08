/**
 * @file SequenceListModel.cpp
 * @date 3/10/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  SequenceListModel.cpp
 *   Created on:  3/10/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "SequenceListModel.h"

int SequenceListModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return dataList.count();
}

QVariant SequenceListModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  
  if (index.row() >= dataList.size())
    return QVariant();
  
  if (role == Qt::DisplayRole)
    return dataList.at(index.row()).at(0); // Nombre de secuencia
  
  if (role == Qt::DecorationRole){
    return getIcon(dataList.at(index.row()).at(1).toInt());
  }
  else
    return QVariant();

}
QVariant SequenceListModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const
                                       {
  if (role != Qt::DisplayRole)
    return QVariant();
  
  if (orientation == Qt::Horizontal)
    return QString("Secuencias");
  else
    return QString("Secuencias");

}

Qt::ItemFlags SequenceListModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;
  
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool SequenceListModel::setData(const QModelIndex &index, 
                                const QVariant &value, int role)
{
  if (index.isValid() && role == Qt::EditRole) {
//    QStringList strings = value.toStringList();
//    dataList.replace(index.row(), value.toStringList());
    dataList.replace(index.row(), value.toList());
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

bool SequenceListModel::insertRows(int position, int rows, 
                                   const QModelIndex &parent)
{
  beginInsertRows(QModelIndex(), position, position+rows-1);
  
  for (int row = 0; row < rows; ++row) {
    dataList.insert(position, QList<QVariant>());
  }
  
  endInsertRows();
  return true;
}

bool SequenceListModel::removeRows(int position, int rows, 
                                   const QModelIndex &parent)
{
  beginRemoveRows(QModelIndex(), position, position+rows-1);
  
  for (int row = 0; row < rows; ++row) {
    dataList.removeAt(position);
  }
  
  endRemoveRows();
  return true;
}

QIcon SequenceListModel::getIcon(const int & type) const
{
  QIcon icon;
  if(type == GenomAMf::DNA_Alphabet){
    icon = QIcon(":/icons/icons/seq_dna.png");
  }
  else if(type == GenomAMf::Proteic_Alphabet){
    icon = QIcon(":/icons/icons/seq_protein.png");
  }
  return icon;
}
