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
#include <QPainter>
#include <QImage>
#include <QRgb>


#include <app/AppController.h>
#include <gui/MainWindow.h>
#include <cgr/ChaosGameRepresentation.h>
#include <utils/Utils.h>

// The SeqLib library:
#include <Seq/Alphabet.h>
#include <Seq/AlphabetTools.h>
#include <Seq/DNA.h>
#include <Seq/Sequence.h>
#include <Seq/VectorSequenceContainer.h>


#include <NumCalc/VectorTools.h>
#include <NumCalc/Matrix.h>
#include <NumCalc/MatrixTools.h>

//STL library
#include <vector>

//MathGl Library
#include <mgl/mgl_data.h>
#include <mgl/mgl_zb.h>
#include <mgl/mgl_font.h>

using namespace utils;

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
  cout << endl;
  vector<double> nuevo = m.row(0);
  VectorTools::print(nuevo);
  mglData test(3);
  test.Set(nuevo);
  
  test.Modify("sin(pi*(2*x-1))");
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
  gr->Surf(a);      
  gr->Box();
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

int plot(mglGraph *gr, void *)
{
//  mglData data(41);
  vector<double> x(41);
  vector<double> y(41);
  for (unsigned int i = 0; i < x.size(); ++i)
  {
    x.at(i) = i;
  }
  for (unsigned int i = 0; i < y.size(); ++i)
  {
    y.at(i) = i;
  }
  
  gr->SetRanges(-20,20,0,41,0,0);
  mglData * data = new mglData();
  data->Set(x);
//  data->Modify("x");
  
  for (unsigned int i = 0; i < x.size(); ++i)
  {
    cout<< (data->a[i]) << " " << endl;
  }
  mglFont * font = new mglFont("Bonum");
  gr->SetFont(font);
//  gr->Axis(mglPoint(0,0,0),mglPoint(1,1,1));
  gr->Plot(*data);
//  gr->Box();
  gr->Axis(mglPoint(-20,20),mglPoint(0,41));
  gr->Axis();
  gr->AddLegend("x","b");
  gr->Legend();
//  gr->Grid();
  return 0;
}

int runSample(){
  /*mglGraphZB gr;
  gr.Alpha(false);
  gr.Light(true);             
  gr.Light(0,mglPoint(1,0,-1));
  sample1(&gr,NULL);           // The same drawing function.
  gr.WritePNG("tmp/sample1.png");    // Don't forget to save the result!
  gr.WriteJPEG("tmp/sample1.jpg");    // Don't forget to save the result!
  
  mglGraphZB gr2;
  gr2.Alpha(false);
  gr2.Light(true);             
  gr2.Light(0,mglPoint(1,0,-1));
  sample2(&gr2,NULL);           // The same drawing function.
  gr2.WritePNG("tmp/sample2.png");    // Don't forget to save the result!
  gr2.WriteJPEG("tmp/sample2.jpg");    // Don't forget to save the result!
  
  mglGraphZB gr3;
  gr3.Alpha(false);
  gr3.Light(true);             
  gr3.Light(0,mglPoint(1,0,-1));
  sample3(&gr3,NULL);           // The same drawing function.
  gr3.WritePNG("tmp/sample3.png");    // Don't forget to save the result!
  gr3.WriteJPEG("tmp/sample3.jpg");    // Don't forget to save the result!
  */
  mglGraphZB grPlot;
  
  plot(&grPlot, NULL);
  grPlot.WritePNG("tmp/plot.png");
//  grPlot.WriteJPEG("tmp/plot.jpg");
  return 0;
}

void performCgr(){
  SeqLoader * sl = new SeqLoader(); 
  VectorSequenceContainer *vec =  sl->load("data/sequences/bacteria/"
          "buchnera_protein_frame_1.fasta",
          new DNA(),
          new ProteicAlphabet());
  Sequence * seq = const_cast<Sequence* >(vec->getSequence(0));
  ChaosGameRepresentation * cgr = new ChaosGameRepresentation(seq);
  cgr->performRepresentation(512);
  delete cgr;
}

void testPaint(){
  QImage * img = new QImage(200,200, QImage::Format_RGB32);
  QRgb backgroudColor = qRgb(230,230,230);
  img->fill(backgroudColor);
  QPainter * p = new QPainter(img);
  p->translate(100,100);
  p->drawPoint(10,20);
  img->save("tmp/test.png" , "PNG");
}

void linkProteinSequence(){
  SeqLoader * sl = new SeqLoader(); 
  VectorSequenceContainer *vec =  sl->load("/home/hector/Escritorio/"
          "buchnera.fasta",
          new DNA(),
          new ProteicAlphabet());
  
  Sequence * newSeq = new Sequence("Buchnera sp APS","", new ProteicAlphabet());
  for (unsigned int i = 0; i < vec->getNumberOfSequences(); ++i)
  {
    newSeq->append(vec->getContent(1));
  }
  cout << newSeq->toString() << endl;
  VectorSequenceContainer * newVec = 
          new VectorSequenceContainer(new ProteicAlphabet());
  newVec->addSequence(*newSeq, true);
  Fasta * f = new Fasta();
  string name = "data/sequences/bacteria/Buchnera_protein.fasta"; 
  f->write(name, *newVec);
  
}

int main(int argc, char *argv[])
{
 /* 
  // NORMAL
  AppController * app = new AppController(argc, argv);
//  app->getMainWindow()->showMaximized();
  app->getMainWindow()->show();
  return app->exec();*/
  
//  Q_UNUSED(argc);
//  Q_UNUSED(argv);

  QApplication app(argc, argv);
//  pruebaSequences();
  runSample(); // MathGl samples
//  performCgr();
//  linkProteinSequence();
//  testPaint();
  return 0;
  
}

