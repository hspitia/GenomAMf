/*
 * SequenceTreeItem.h
 *
 *  Created on: 24/09/2009
 *      Author: user
 */

#ifndef SEQUENCETREEITEM_H_
#define SEQUENCETREEITEM_H_

#include "TreeItem.h"
#include <Seq/Sequence.h>

using namespace bpp;


class SequenceTreeItem : public TreeItem
{
  public:
    SequenceTreeItem(const QVector<QVariant> &data, TreeItem *parent = 0);
    virtual ~SequenceTreeItem();
    
  private:
    Sequence * sequence; /**< Apuntador aun objeto <code> Sequence </code> 
        contenido el miembro <code> sequences </code> de la clase <code> 
        AppController </code>. */
    
    /**
     * Retorna 
     * @return 
     */
    Sequence * getSequence();
    
    /**
     * Asigna 
     */
    void setSequence(Sequence * sequence);
};

#endif /* SEQUENCETREEITEM_H_ */
