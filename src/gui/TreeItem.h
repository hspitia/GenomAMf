#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QVector>
#include <Seq/Sequence.h>
#include <cgr/ChaosGameRepresentation.h>

using namespace bpp;

//class TreeModel;
class TreeItem
{
public:
    enum ItemType{
      DnaSequenceItem,
      ProteinSequenceItem,
      CgrItem,
      MfaItem,
      CorrelItem
    };
    
//    TreeItem(ItemType type, const QVector<QVariant> &data, 
    TreeItem(const QVector<QVariant> &data, 
             TreeItem *parent = 0);
    ~TreeItem();

    TreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertChild(int position, TreeItem * child);
    bool insertColumns(int position, int columns);
    TreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);
    
//    bool insertChildrenSequences(int position, int count, int columns);
    
private:
    QList<TreeItem*> childItems;
    QVector<QVariant> itemData;
    TreeItem * parentItem;
     
};

#endif
