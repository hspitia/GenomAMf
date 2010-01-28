/**
 * @file main.cpp
 * @date Sep 5, 2009
 * @author H&eacute;ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief Archivo main de la apliacacio-.n.
 */

/*
 *   Created on:  Sep 5, 2009
 *       Author:  HECTOR FABIO ESPITIA NAVARRO
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y COMPUTACION
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  Archivo main de la apliacacio-.n.
 */

#include <QApplication>
#include <app/AppController.h>

int appNormal(int argc, char *argv[])
{
  AppController * app = new AppController(argc, argv);
//    app->getMainWindow()->showMaximized();
  app->getMainWindow()->resize(1024, 762);
  app->getMainWindow()->show();
  return app->exec();
}

int main(int argc, char *argv[])
{
  appNormal(argc, argv);
  return 0;
}
