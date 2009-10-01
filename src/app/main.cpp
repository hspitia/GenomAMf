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
#include <NumCalc/Matrix.h>
#include <NumCalc/MatrixTools.h>

//STL library
#include <vector>

//MathGl Library
#include <mgl/mgl_data.h>
#include <mgl/mgl_zb.h>
#include <mgl/mgl_font.h>


void pruebaSequences(){
  const Alphabet * alphabet = new DNA();
  Sequence seq("My first sequence", "ATGCGTGTAAC", alphabet);
  cout << seq.toString() << endl;
  seq.append("--GGGCCTTTA");
  cout << seq.toString() << endl;
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

//  VectorTools::print(content);
  
  RowMatrix<double> m (3,3);
  RowMatrix<double> n (3,3);
  MatrixTools::fill(m,4.6);
  m(0,0) = 2790;
  m(0,1) = m(0,0) + 1;
  m(0,2) = m(0,1) + 1;
  m(0,2)++;
  
  MatrixTools::print(m);
  m(0,2)--;
  MatrixTools::print(m);
  unsigned int a = 2;
  MatrixTools::pow(m,a,n);
  MatrixTools::print(n);
}


int sample1(mglGraph *gr, const void *)
{
  gr->Rotate(60,40);
  gr->Box();
  return 0;
}

int sample2(mglGraph *gr, void *)
{
  mglData a(30,40);   
  a.Modify("x*y");
  gr->SetFont(new mglFont("MGL_FONT_ITAL"));
  gr->SetFontSizePT(24,96);
  gr->Axis(mglPoint(0,0,0),mglPoint(1,1,1));
  gr->SubPlot(2,2,0); 
  gr->Rotate(60,40);
  gr->Surf(a);        
  gr->Box();
  gr->Puts(mglPoint(0.7,1,1.2),"a(x,y)");
  gr->SubPlot(2,2,1); 
  gr->Rotate(60,40);
  a.Diff("x");        
  gr->Surf(a);      
  gr->Box();
  gr->Puts(mglPoint(0.7,1,1.2),"da/dx");
  gr->SubPlot(2,2,2); 
  gr->Rotate(60,40);
  a.Integral("xy");   
  gr->Surf(a);      
  gr->Box();
  gr->Puts(mglPoint(0.7,1,1.2),"\\int da/dx dxdy");
  gr->SubPlot(2,2,3); 
  gr->Rotate(60,40);
  a.Diff2("y");       
  gr->Surf(a);      gr->Box();
  gr->Puts(mglPoint(0.7,1,1.2),"\\int {d^2}a/dxdy dx");
  return 0;
}

int sample3(mglGraph *gr, void *)
{
  mglData y0(50);   
  y0.Modify("sin(pi*(2*x-1))");
//  gr->SubPlot(2,2,0);
  gr->Rotate(70,40);
  gr->Plot(y0);
  gr->Box();
  return 0;
}
//  ./configure --enable-jpeg --enable-gif --enable-qt --with-qt
int runSample(){
  mglGraphZB gr;
  gr.Alpha(false);
  gr.Light(true);             
  gr.Light(0,mglPoint(1,0,-1));
  sample1(&gr,NULL);           // The same drawing function.
//  gr.WritePNG("data/sample1.png");    // Don't forget to save the result!
  gr.WriteJPEG("data/sample1.jpg");    // Don't forget to save the result!
  
  mglGraphZB gr2;
  gr2.Alpha(false);
  gr2.Light(true);             
  gr2.Light(0,mglPoint(1,0,-1));
  sample2(&gr2,NULL);           // The same drawing function.
  gr2.WritePNG("data/sample2.png");    // Don't forget to save the result!
  gr2.WriteJPEG("data/sample2.jpg");    // Don't forget to save the result!
  
  
  mglGraphZB gr3;
  gr3.Alpha(false);
  gr3.Light(true);             
  gr3.Light(0,mglPoint(1,0,-1));
  sample3(&gr3,NULL);           // The same drawing function.
//  gr3.WritePNG("data/sample3.png");    // Don't forget to save the result!
  gr3.WriteJPEG("data/sample3.jpg");    // Don't forget to save the result!
  return 0;
}

int main(int argc, char *argv[])
{
  Q_UNUSED(argc);
  Q_UNUSED(argv);
//  AppController * app = new AppController(argc, argv);
//  app->getMainWindow()->show();

//  pruebaSequences();
  runSample();
  return 0;
//  return app->exec();
}

