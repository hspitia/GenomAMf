/**
 * @file DistancesModel.cpp
 * @date 29/12/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  DistancesModel.cpp
 *   Created on:  29/12/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "DistancesModel.h"

DistancesModel::DistancesModel(const QStringList & sequenceCodes,
                               const QList<double> & distances,
                               QObject *parent)
    : QAbstractTableModel(parent)
{
  this->sequenceCodes = sequenceCodes;
  this->distances = distances; 
}

DistancesModel::~DistancesModel()
{
  // TODO Auto-generated destructor stub
}

//void CityModel::setSequences(const QStringList &cityNames)
//{
//    cities = cityNames;
////    distances.resize(cities.count() * (cities.count() - 1) / 2);
////    distances.fill(0);
//    reset();
//}

int DistancesModel::rowCount(const QModelIndex & /* parent */) const
{
    return sequenceCodes.count();
}

int DistancesModel::columnCount(const QModelIndex & /* parent */) const
{
    return sequenceCodes.count();
}

QVariant DistancesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } 
    else if (role == Qt::DisplayRole) {
        if (index.row() == index.column())
            return 0;
        int offset = offsetOf(index.row(), index.column());
        return distances.at(offset);
    }
    return QVariant();
}

/*bool DistancesModel::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
    if (index.isValid() && index.row() != index.column()
            && role == Qt::EditRole) {
        int offset = offsetOf(index.row(), index.column());
        distances[offset] = value.toInt();

        QModelIndex transposedIndex = createIndex(index.column(),
                                                  index.row());
        emit dataChanged(index, index);
        emit dataChanged(transposedIndex, transposedIndex);
        return true;
    }
    return false;
}*/

QVariant DistancesModel::headerData(int section,
                               Qt::Orientation /* orientation */,
                               int role) const
{
    if (role == Qt::DisplayRole)
        return sequenceCodes.at(section);
    return QVariant();
}

/*Qt::ItemFlags DistancesModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.row() != index.column())
        flags |= Qt::ItemIsEditable;
    return flags;
}*/

int DistancesModel::offsetOf(int row, int column) const
{
    if (row < column)
        qSwap(row, column);
    return (row * (row - 1) / 2) + column;
}
