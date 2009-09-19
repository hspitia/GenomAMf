/**
 * @file Message.h
 * @date 18/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  Message.h
 *   Created on:  18/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <QList>
#include <QVariant>

typedef enum
{
  INFORMATION,
  WARNING,
  ERROR
} messageType;

/**
 * 
 */
class Message
{
  public:
    
    Message();
    virtual ~Message();

    /**
     * Retorna 
     * @return 
     */
    QString getName();

    /**
     * Asigna 
     */
    void setName(QString name);

    /**
     * Retorna 
     * @return 
     */
    QString getTitle();

    /**
     * Asigna 
     */
    void setTitle(QString title);

    /**
     * Retorna 
     * @return 
     */
    QString getInformationText();

    /**
     * Asigna 
     */
    void setInformationText(QString informationText);

    /**
     * Retorna 
     * @return 
     */
    QString getContentText();

    /**
     * Asigna 
     */
    void setContentText(QString contentText);
    /**
     * Retorna 
     * @return 
     */
    QList <QVariant> getParameters();

    /**
     * Asigna 
     */
    void setParameters(QList <QVariant> parameters);

    /**
     * Retorna 
     * @return 
     */
    messageType getType();

    /**
     * Asigna 
     */
    void setType(messageType type);

  private:
    QString name; /**< Nombre del mensaje */
    QString title; /**< Título de la ventana del diálogo del mensaje */
    QString informationText; /**< Texto de información del diálogo del mensaje */
    QString contentText; /**< Texto del mensaje */
    QList <QVariant> parameters; /**< Parámetros a ser desplegados en el mensaje */
    messageType type; /**< Tipo del mensaje */
    
};

#endif /* MESSAGE_H_ */
