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

//#include <QtGui>
//#include <QApplication>

#include <app/AppController.h>
#include <gui/MainWindow.h>

// The SeqLib library:
#include <Seq/Alphabet.h>
#include <Seq/DNA.h>
#include <Seq/Sequence.h>

#include <NumCalc/VectorTools.h>

//std library
#include <vector>


void pruebaSequences(){
  const Alphabet * alphabet = new DNA();
  Sequence seq("My first sequence", "ATGCGTGTAAC", alphabet);
  cout << seq.toString() << endl; 
//  seq.append("--GGGCCTTTA");
//  cout << seq.toString() << endl;
//  // Resizing on the right:
//  cout << "Before: " << seq.size() << "\t"; 
//  seq.setToSizeR(10);
//  cout << "After: " << seq.size() << "\t";
//  cout << seq.toString() << endl;
//  seq.setToSizeR(15);
//  cout << "And now: " << seq.size() << "\t";
//  cout << seq.toString() << endl;
//  // Resizing on the left:
//  seq. setToSizeL(10);
//  cout << "New size: " << seq.size() << "\t";
//  cout << seq.toString() << endl;
//  seq.setToSizeL(20);
//  cout << "And again: " << seq.size () << "\t";
//  cout << seq.toString() << endl;
//  cout << endl;
  
  vector<int> content(seq.getContent());
  
  VectorTools::print(content);
  
//  for (int i = 0; i < (int) content.size(); ++i)
//  {
//    cout << content[i] << "";
//  }
//  cout << endl;
  
}

int main(int argc, char *argv[])
{
//  AppController * app = new AppController(argc, argv);
//  app->getMainWindow()->show();

  pruebaSequences();
  return 0;
//  return app->exec();
}

