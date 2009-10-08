/*
 treeitem.cpp

 A container for items of data supplied by the simple tree model.
 */

#include <QStringList>

#include "TreeItem.h"
#include <gui/SequenceTreeItem.h>

class SequenceTreeItem;

//TreeItem::TreeItem(ItemType type, const QVector<QVariant> &data,
TreeItem::TreeItem(const QVector<QVariant> &data,
                   TreeItem *parent)
{
//  itemType = type;
  parentItem = parent;
  itemData = data;
  ptrCgr = 0;
  ptrSequence = 0;
}

TreeItem::~TreeItem()
{
  qDeleteAll(childItems);
  
  if (ptrCgr != 0) ptrCgr = 0;
  delete ptrCgr;
  
  if (ptrSequence != 0) ptrSequence = 0;
  delete ptrSequence;
}

TreeItem *TreeItem::child(int number)
{
  return childItems.value(number);
}

int TreeItem::childCount() const
{
  return childItems.count();
}

int TreeItem::childNumber() const
{
  if (parentItem) return parentItem->childItems.indexOf(
          const_cast<TreeItem*> (this));
  
  return 0;
}

int TreeItem::columnCount() const
{
  return itemData.count();
}

QVariant TreeItem::data(int column) const
{
  return itemData.value(column);
}

//bool TreeItem::insertChildrenSequences(int position, int count, int columns)
//{
//    if (position < 0 || position > childItems.size())
//        return false;
//
//    for (int row = 0; row < count; ++row) {
//        QVector<QVariant> data(columns);
//        SequenceTreeItem *item = new SequenceTreeItem(data, this);
//        childItems.insert(position, item);
//    }
//
//    return true;
//}

bool TreeItem::insertChildren(int position, int count, int columns)
{
  if (position < 0 || position > childItems.size()) return false;

  for (int row = 0; row < count; ++row)
  {
    QVector<QVariant> data(columns);
    TreeItem *item = new TreeItem(data, this);
    childItems.insert(position, item);
  }
  
  return true;
}

bool TreeItem::insertChild(int position, TreeItem * child)
{
  if (position < 0 || position > childItems.size()) return false;

  childItems.insert(position, child);
  
  return true;
}

bool TreeItem::insertColumns(int position, int columns)
{
  if (position < 0 || position > itemData.size()) return false;

  for (int column = 0; column < columns; ++column)
    itemData.insert(position, QVariant());
  
  foreach (TreeItem *child, childItems)
      child->insertColumns(position, columns);
  
  return true;
}

TreeItem *TreeItem::parent()
{
  return parentItem;
}

bool TreeItem::removeChildren(int position, int count)
{
  if (position < 0 || position + count > childItems.size()) return false;

  for (int row = 0; row < count; ++row)
    delete childItems.takeAt(position);
  
  return true;
}

bool TreeItem::removeColumns(int position, int columns)
{
  if (position < 0 || position + columns > itemData.size()) return false;

  for (int column = 0; column < columns; ++column)
    itemData.remove(position);
  
  foreach (TreeItem *child, childItems)
      child->removeColumns(position, columns);
  
  return true;
}

bool TreeItem::setData(int column, const QVariant &value)
{
  if (column < 0 || column >= itemData.size()) return false;

  itemData[column] = value;
  return true;
}

const Sequence * TreeItem::getPtrSequence()
{
  return ptrSequence;
}

void TreeItem::setPtrSequence(const Sequence * ptrSequence)
{
  this->ptrSequence = ptrSequence;
}

const ChaosGameRepresentation * TreeItem::getPtrCgr()
{
  return ptrCgr;
}

void TreeItem::setPtrCgr(const ChaosGameRepresentation * ptrCgr)
{
  this->ptrCgr = ptrCgr;
}

int TreeItem::getItemType()
{
  return itemType;
}
