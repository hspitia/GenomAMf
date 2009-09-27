/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

/*
    treeitem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include <QStringList>

#include "TreeItem.h"

//! [0]
TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
{
    parentItem = parent;
    itemData = data;
}
//! [0]

//! [1]
TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}
//! [1]

//! [2]
TreeItem *TreeItem::child(int number)
{
    return childItems.value(number);
}
//! [2]

//! [3]
int TreeItem::childCount() const
{
    return childItems.count();
}
//! [3]

//! [4]
int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
//! [4]

//! [5]
int TreeItem::columnCount() const
{
    return itemData.count();
}
//! [5]

//! [6]
QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}
//! [6]

//! [7]
bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}
//! [7]

bool TreeItem::insertChild(int position, TreeItem * child)
{
  if (position < 0 || position > childItems.size())
    return false;

  childItems.insert(position, child);
  
  return true;
}

//! [8]
bool TreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (TreeItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}
//! [8]

//! [9]
TreeItem *TreeItem::parent()
{
    return parentItem;
}
//! [9]

//! [10]
bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
//! [10]

bool TreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.remove(position);

    foreach (TreeItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

//! [11]
bool TreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}
//! [11]


///****************************************************************************
//**
//** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
//** Contact: Nokia Corporation (qt-info@nokia.com)
//**
//** This file is part of the examples of the Qt Toolkit.
//**
//** $QT_BEGIN_LICENSE:LGPL$
//** Commercial Usage
//** Licensees holding valid Qt Commercial licenses may use this file in
//** accordance with the Qt Commercial License Agreement provided with the
//** Software or, alternatively, in accordance with the terms contained in
//** a written agreement between you and Nokia.
//**
//** GNU Lesser General Public License Usage
//** Alternatively, this file may be used under the terms of the GNU Lesser
//** General Public License version 2.1 as published by the Free Software
//** Foundation and appearing in the file LICENSE.LGPL included in the
//** packaging of this file.  Please review the following information to
//** ensure the GNU Lesser General Public License version 2.1 requirements
//** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
//**
//** In addition, as a special exception, Nokia gives you certain
//** additional rights. These rights are described in the Nokia Qt LGPL
//** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
//** package.
//**
//** GNU General Public License Usage
//** Alternatively, this file may be used under the terms of the GNU
//** General Public License version 3.0 as published by the Free Software
//** Foundation and appearing in the file LICENSE.GPL included in the
//** packaging of this file.  Please review the following information to
//** ensure the GNU General Public License version 3.0 requirements will be
//** met: http://www.gnu.org/copyleft/gpl.html.
//**
//** If you are unsure which license is appropriate for your use, please
//** contact the sales department at http://www.qtsoftware.com/contact.
//** $QT_END_LICENSE$
//**
//****************************************************************************/
//
///*
//    treeitem.cpp
//
//    A container for items of data supplied by the simple tree model.
//*/
//
//#include <QStringList>
//
//#include "TreeItem.h"
//
////! [0]
//TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
//{
//    parentItem = parent;
//    itemData = data;
//}
////! [0]
//
////! [1]
//TreeItem::~TreeItem()
//{
//    qDeleteAll(childItems);
//}
////! [1]
//
////! [2]
//void TreeItem::appendChild(TreeItem *item)
//{
//    childItems.append(item);
//}
////! [2]
//
//bool TreeItem::insertChild(int position, TreeItem * child)
//{
//  if (position < 0 || position > childItems.size())
//    return false;
//  
//  childItems.insert(position, child);
//  
//  return true;
//}
//
////! [3]
//TreeItem *TreeItem::child(int row)
//{
//    return childItems.value(row);
//}
////! [3]
//
////! [4]
//int TreeItem::childCount() const
//{
//    return childItems.count();
//}
////! [4]
//
////! [5]
//int TreeItem::columnCount() const
//{
//    return itemData.count();
////    return 1;
//}
////! [5]
//
////! [6]
//QVariant TreeItem::data(int column) const
//{
//    return itemData.value(column);
//}
////QVariant TreeItem::data() const
////{
////    return itemData;
////}
////! [6]
//
////! [7]
//TreeItem *TreeItem::parent()
//{
//    return parentItem;
//}
////! [7]
//
////! [8]
//int TreeItem::row() const
//{
//    if (parentItem)
//        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
//
//    return 0;
//}
////! [8]
