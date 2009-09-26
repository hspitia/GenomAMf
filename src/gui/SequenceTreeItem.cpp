/*
 * SequenceTreeItem.cpp
 *
 *  Created on: 24/09/2009
 *      Author: user
 */

#include "SequenceTreeItem.h"

SequenceTreeItem::SequenceTreeItem(const QVector<QVariant> &data, TreeItem *parent) :
  TreeItem(data, parent)
{
  sequence = 0;
}

SequenceTreeItem::~SequenceTreeItem()
{
  if (sequence != 0)
  {
    sequence = 0;
    delete sequence;
  }
}

Sequence * SequenceTreeItem::getSequence()
{
  return sequence;
}

void SequenceTreeItem::setSequence(Sequence * sequence)
{
  this->sequence = sequence;
}
