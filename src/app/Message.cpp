/**
 * @file Message.cpp
 * @date 18/09/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  Message.cpp
 *   Created on:  18/09/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#include "Message.h"

Message::Message() :
  parameters(QList <QVariant>())

{
  this->name = "";
  this->title = "";
  this->informationText = "";
  this->contentText = "";
  //  this->parameters = QList<QVariant>();
  this->type = GenomAMf::Undefined;
}

Message::Message(const QString & name, const QString & contentText) :
  parameters(QList <QVariant>())
{
  this->name = name;
  this->title = "";
  this->informationText = contentText;
  this->contentText = "";
  //  this->parameters = "";
  this->type = GenomAMf::Undefined;
}

Message::~Message()
{
  // TODO Auto-generated destructor stub
}

QString Message::getName()
{
  return name;
}

void Message::setName(QString name)
{
  this->name = name;
}

QString Message::getTitle()
{
  return title;
}

void Message::setTitle(QString title)
{
  this->title = title;
}

QString Message::getInformationText()
{
  return informationText;
}

void Message::setInformationText(QString informationText)
{
  this->informationText = informationText;
}

QString Message::getContentText()
{
  return contentText;
}

void Message::setContentText(QString contentText)
{
  this->contentText = contentText;
}

QList <QVariant> Message::getParameters()
{
  return parameters;
}

void Message::setParameters(QList <QVariant> parameters)
{
  this->parameters = parameters;
}

GenomAMf::MessageType Message::getType()
{
  return type;
}

void Message::setType(GenomAMf::MessageType type)
{
  this->type = type;
}
