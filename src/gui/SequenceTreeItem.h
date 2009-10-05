/*
 * SequenceTreeItem.h
 *
 *  Created on: 24/09/2009
 *      Author: user
 */

#ifndef SEQUENCETREEITEM_H_
#define SEQUENCETREEITEM_H_

#include <gui/TreeItem.h>
#include <Seq/Sequence.h>

//class TreeItem;

using namespace bpp;


class SequenceTreeItem : public TreeItem
{
  public:
    SequenceTreeItem(const QVector<QVariant> &data, TreeItem *parent = 0);
    virtual ~SequenceTreeItem();
    
    /**
     * Retorna 
     * @return 
     */
    const Sequence * getSequence();
    
    /**
     * Asigna 
     */
    void setSequence(const Sequence * sequence);
    
  private:
    const Sequence * sequence; /**< Apuntador aun objeto <code> Sequence </code> 
        contenido el miembro <code> sequences </code> de la clase <code> 
        AppController </code>. */
    
};

#endif /* SEQUENCETREEITEM_H_ */
