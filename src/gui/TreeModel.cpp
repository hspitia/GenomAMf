
#include <QtGui>

#include "TreeItem.h"
#include "TreeModel.h"
#include <iostream>

using namespace std;


TreeModel::TreeModel(const QStringList &headers, const QString &data,
                     QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    rootItem = new TreeItem(rootData);
    setupModelData(data.split(QString("\n")), rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

//    if (role != Qt::DisplayRole && 
//            role != Qt::EditRole && 
//            role != Qt::DecorationRole)
//        return QVariant();
    
    TreeItem *item = getItem(index);
    if(!item)
      return QVariant();
    
    if (role == Qt::DisplayRole){
      if(index.column() == 0){
        switch (item->data(1).toInt()){
          case TreeItem::MainSequenceItem:
            return tr("Secuencias");
          case TreeItem::MainMfaItem:
            return tr("Análisis Multifractal");
          case TreeItem::MainCorrelationItem:
            return tr("Análisis de Correlación");
          case TreeItem::DnaSequenceItem: 
          case TreeItem::ProteinSequenceItem:
            return item->data(index.column());
          case TreeItem::CgrItem:
            return tr("Rep. Juego del Caos");
          case TreeItem::MfaItem:
            return tr("Análisis Multifractal");
          case TreeItem::CorrelItem:
            return tr("Análisis de Correlación");
          default:
            return tr("Desconocido");
        }
      }
      else{
        return item->data(index.column()).toInt();
      }
    }
    
    if(role == Qt::DecorationRole){
      if(index.column() == 0){
        return getIcon(item->data(1).toInt());
      }
    }
    
    if(role == Qt::FontRole){
      switch (item->data(1).toInt()){
        case TreeItem::MainSequenceItem:
        case TreeItem::MainMfaItem:
        case TreeItem::MainCorrelationItem:
          return QFont("Sans", 8, QFont::Bold);
        
        /*case TreeItem::DnaSequenceItem: 
        case TreeItem::ProteinSequenceItem:
          return item->data(index.column());
        case TreeItem::CgrItem:
          return tr("Rep. Juego del Caos");
        case TreeItem::MfaItem:
          return tr("Análisis Multifractal");
        case TreeItem::CorrelItem:
          return tr("Análisis de Correlación");*/
        default:
          return QVariant();
      }
    }
    
    if(role == Qt::BackgroundRole){
      switch (item->data(1).toInt()){
        case TreeItem::MainSequenceItem:
        case TreeItem::MainMfaItem:
        case TreeItem::MainCorrelationItem:
          return QBrush(QColor(240,240,240));
        
        case TreeItem::DnaSequenceItem: 
        case TreeItem::ProteinSequenceItem:
        case TreeItem::CgrItem:
          return QBrush(QColor("#EEECE1"));
        case TreeItem::MfaItem:
          return QBrush(QColor("#E5E0EC"));
        case TreeItem::CorrelItem:
          return QBrush(QColor("#FDEADA"));
        default:
          return QVariant();
      }
    }
    
    return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

TreeItem * TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}

//SequenceTreeItem * TreeModel::getSequenceTreeItem(const QModelIndex &index) const
//{
//    if (index.isValid()) {
//        SequenceTreeItem *item = static_cast<SequenceTreeItem*>(index.internalPointer());
//        if (item) return item;
//    }
//    return NULL;
//}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

//bool TreeModel::insertSequences(int position, int rows, const QModelIndex &parent)
//{
//  TreeItem *parentItem = getItem(parent);
//  bool success;
//  
//  beginInsertRows(parent, position, position + rows - 1);
//  success = parentItem->insertChildren(position, rows, rootItem->columnCount());
//  endInsertRows();
//  
//  return success;
//}


//bool TreeModel::insertSequence(int arow, const QModelIndex &aparent)
//{ 
//  return insertRows(arow, 1, aparent); 
//}


QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value,
                        int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
//    cout << "index.column(): " << index.column() << "value: " << qPrintable(value.toString()) << endl; 
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].mid(position, 1) != " ")
                break;
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            TreeItem *parent = parents.last();
            parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }

        number++;
    }
}

QIcon TreeModel::getIcon(const int & type) const
{
  switch (type){
    case TreeItem::MainSequenceItem:
          return QIcon(":/icons/seq.png");
    case TreeItem::MainMfaItem:
      return QIcon(":/icons/mfa.png");
    case TreeItem::MainCorrelationItem:
      return QIcon(":/icons/correl.png");
    case TreeItem::DnaSequenceItem:
      return QIcon(":/icons/seq_dna.png");
    case TreeItem::ProteinSequenceItem:
          return QIcon(":/icons/seq_protein.png");
    case TreeItem::CgrItem:
      return QIcon(":/icons/cgr_result.png");
    case TreeItem::MfaItem:
      return QIcon(":/icons/mfa_result.png");
    case TreeItem::CorrelItem:
      return QIcon(":/icons/correl_result.png");
    default:
      return QIcon();
  }
  return QIcon();
}
