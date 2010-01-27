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
#include <QFileDialog>
#include <QPixmap>
#include <QDir>
#include <QString>
#include <QImage>


#include <app/AppController.h>
#include <gui/MainWindow.h>
#include <cgr/ChaosGameRepresentation.h>
#include <mfa/SandBoxMethod.h>
#include <mfa/Plotter.h>
#include <utils/Utils.h>
#include <utils/Plot.h>
#include <utils/NormalPlot.h>
#include <utils/LinearPlot.h>

// The SeqLib library:
#include <Seq/Alphabet.h>
#include <Seq/AlphabetTools.h>
#include <Seq/DNA.h>
#include <Seq/DistanceMatrix.h>
#include <Seq/Sequence.h>
#include <Seq/VectorSequenceContainer.h>
#include <NumCalc/RandomTools.h>
//#include <Bpp/Raa/RAA.h>
#include <NumCalc/VectorTools.h>
#include <NumCalc/Matrix.h>
#include <NumCalc/MatrixTools.h>
#include <Phyl/NeighborJoining.h>
#include <Phyl/Newick.h>

//STL library
#include <vector>
#include <string>

using namespace std;

//MathGl Library
#include <mgl/mgl_data.h>
#include <mgl/mgl_zb.h>
#include <mgl/mgl_font.h>
#include <mgl/mgl_qt.h>

using namespace utils;

//int offsetOf(int row, int column)
//{
//    if (row < column)
//        qSwap(row, column);
//    return (row * (row - 1) / 2) + column;
//}

void treeTest()
{
  int nElements = 5;
  vector<string> names(nElements);
  
  for (int i = 0; i < nElements; ++i) {
    names.at(i) = QString("Seq_%1").arg(i+1).toStdString();  
  }
  
  DistanceMatrix * matrix = new DistanceMatrix(names);
  
  int nDistances = (nElements * (nElements - 1)) / 2;
  
  vector<double> distances(nDistances);
  
  distances.at(0) = 0.23548;
  distances.at(1) = 0.1865;
  distances.at(2) = 0.87645;
  distances.at(3) = 0.063;
  distances.at(4) = 0.00122;
  distances.at(5) = 0.349;
  distances.at(6) = 0.21212;
  distances.at(7) = 0.9865;
  distances.at(8) = 1.87645;
  distances.at(9) = 3.87645;
  
  for (int i = 0; i < nElements; ++i) {
    for (int j = 0; j < nElements; ++j) {
      int index = offsetOf(i,j);
      double distance = 0.0;
      
      if (i != j) 
        distance = distances.at(index);
      
      (*matrix)(i, j) = distance;
    }
    cout << endl;
  }
  cout << endl;
  
  MatrixTools::print(*matrix);
  
  NeighborJoining nj(*matrix, false, true);
  
  Tree * tree = nj.getTree();
  
  Newick newick;
  newick.write(*tree,"tree.dnd");
  
  delete tree;
  delete matrix;
}

void pruebaSequences()
{
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
  
  RowMatrix<double> m(3, 3);
  RowMatrix<double> n(3, 3);
  MatrixTools::fill(m, 4.6);
  m(0, 0) = 2790;
  m(0, 1) = m(0, 0) + 1;
  m(0, 2) = m(0, 1) + 1;
  m(0, 2)++;
  
  MatrixTools::print(m);
  m(0, 2)--;
  MatrixTools::print(m);
  unsigned int a = 2;
  MatrixTools::pow(m, a, n);
  MatrixTools::print(n);
  cout << endl;
  vector<double> nuevo = m.row(0);
  VectorTools::print(nuevo);
  mglData test(3);
  test.Set(nuevo);
  
  test.Modify("sin(pi*(2*x-1))");
}

void performCgr()
{
  SeqLoader * sl = new SeqLoader();
  VectorSequenceContainer *vec = sl->load("data/sequences/bacteria/"
    "buchnera_protein_frame_1.fasta", new DNA(), new ProteicAlphabet());
//  Sequence * seq = const_cast<Sequence*> (vec->getSequence(0));
  Sequence * seq = const_cast<Sequence*> (&vec->getSequence(0));
  ChaosGameRepresentation * cgr = new ChaosGameRepresentation(seq);
  cgr->performRepresentation(512);
  delete cgr;
}

void testPaint()
{
  QImage * img = new QImage(200, 200, QImage::Format_RGB32);
  QRgb backgroudColor = qRgb(230, 230, 230);
  img->fill(backgroudColor);
  QPainter * p = new QPainter(img);
  p->translate(100, 100);
  p->drawPoint(10, 20);
  img->save("tmp/test.png", "PNG");
}

void linkProteinSequence()
{
  SeqLoader * sl = new SeqLoader();
  VectorSequenceContainer *vec = sl->load("/home/hector/Escritorio/"
    "buchnera.fasta", new DNA(), new ProteicAlphabet());
  
  Sequence * newSeq =
          new Sequence("Buchnera sp APS", "", new ProteicAlphabet());
  for (unsigned int i = 0; i < vec->getNumberOfSequences(); ++i) {
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

void testRandomGenerarion()
{
  SandBoxMethod * sb = new SandBoxMethod();
  vector<int> x(300);
  vector<int> y(300);
  
  sb->generateRandomCenters(&x, &y);
  /* cout<<"Vector x: "<< endl;
   VectorTools::print(x);
   cout<<"Vector y: "<< endl;
   VectorTools::print(y);*/

}

int sample1(mglGraph *gr, const void *)
{
  gr->Rotate(60, 40);
  gr->Box();
  return 0;
}

int sample2(mglGraph *gr, void *)
{
  mglData a(30, 40);
  a.Modify("x*y");
  gr->SetFont(new mglFont("MGL_FONT_ITAL"));
  gr->SetFontSizePT(24, 96);
  gr->Axis(mglPoint(0, 0, 0), mglPoint(1, 1, 1));
  gr->SubPlot(2, 2, 0);
  gr->Rotate(60, 40);
  gr->Surf(a);
  gr->Box();
  gr->Puts(mglPoint(0.7, 1, 1.2), "a(x,y)");
  gr->SubPlot(2, 2, 1);
  gr->Rotate(60, 40);
  a.Diff("x");
  gr->Surf(a);
  gr->Box();
  gr->Puts(mglPoint(0.7, 1, 1.2), "da/dx");
  gr->SubPlot(2, 2, 2);
  gr->Rotate(60, 40);
  a.Integral("xy");
  gr->Surf(a);
  gr->Box();
  gr->Puts(mglPoint(0.7, 1, 1.2), "\\int da/dx dxdy");
  gr->SubPlot(2, 2, 3);
  gr->Rotate(60, 40);
  a.Diff2("y");
  gr->Surf(a);
  gr->Box();
  gr->Puts(mglPoint(0.7, 1, 1.2), "\\int {d^2}a/dxdy dx");
  return 0;
}

int sample3(mglGraph *gr, void *)
{
  mglData y0(50);
  y0.Modify("sin(pi*(2*x-1))");
  //  gr->SubPlot(2,2,0);
  gr->Rotate(70, 40);
  gr->Plot(y0);
  gr->Box();
  
  return 0;
}

int plot(mglGraph *gr, void *)
{
  //  mglData data(41);
  vector<double> x(41);
  vector<double> y(41);
  //  vector<double> z(41);
  int datum = -20;
  for (unsigned int i = 0; i < x.size(); ++i) {
    x.at(i) = datum;
    datum++;
  }
  for (unsigned int i = 0; i < y.size(); ++i) {
    y.at(i) = i;
  }
  //  for (unsigned int i = 0; i < z.size() / 2; ++i)
  //  {
  //    z.at(i) = i*0.5 ;

  //  for (unsigned int i = z.size() / 2; i < z.size(); ++i)
  //    {
  //      z.at(i) = i*0.8 ;
  //    }

  gr->SetRanges(-20, 20, 0, 41, 0, 41);
  mglData * xData = new mglData();
  xData->Set(x);
  mglData * yData = new mglData(41, 3);
  yData->Set(y);
  //  yData->Modify("x*4",0);
  //  yData->Modify("x*4",0);
  //  mglData * zData = new mglData();
  //  zData->Set(z);
  //  grPlot.SetFontSizePT(10);
  //  mglData z(30,40);
  //  z.Modify("sin(pi*x)*cos(pi*y)");
  gr->SetFont(new mglFont("CURSOR", "/usr/local/share/mathgl/fonts/"));
  //  gr->Rotate(60,40);
  //  gr->Box();
  gr->Plot(*xData, *yData, "b");
  //  gr->Plot(z,"b");
  gr->Axis(mglPoint(-20, 20), mglPoint(0, 41));
  gr->Axis();
  gr->AddLegend("lectura para x", "b");
  gr->Legend();
  //  gr->Grid();
  return 0;
}

int log(mglGraph *gr, void *)
{
//  gr->GetFont()->Load("adventor", "/usr/local/share/mathgl/fonts");
//  gr->GetFont()->Load("bonum", "/usr/local/share/mathgl/fonts");
//  gr->GetFont()->Load("chorus", "/usr/local/share/mathgl/fonts");
//  gr->GetFont()->Load("cursor", "/usr/local/share/mathgl/fonts");
//  gr->GetFont()->Load("heros", "/usr/local/share/mathgl/fonts");
//  gr->GetFont()->Load("heroscn", "/usr/local/share/mathgl/fonts");
//  gr->GetFont()->Load("pagella", "/usr/local/share/mathgl/fonts");
//  gr->GetFont()->Load("schola", "/usr/local/share/mathgl/fonts");
//  gr->GetFont()->Load("termes", "/usr/local/share/mathgl/fonts");

  mglData x(100), y(100);
  x.Modify("pow(10,6*x-3)");
  y.Modify("sqrt(1+v^2)", x);
  
  gr->Axis(mglPoint(0.001, 0.1), mglPoint(1000, 1000), mglPoint(0.001, 0.1));
  gr->Axis("lg(x)", "lg(y)", 0);
  gr->SetTicks('x', 0);
  gr->SetTicks('y', 0);
  
  gr->Box();
  gr->Plot(x, y, "b2");
  gr->Axis();
  gr->Grid("xy", "g;");
  gr->Label('x', "x", 0);
  gr->Label('y', "y=\\sqrt{1+x^2}", 0);
  return 0;
}

Plotter * sinSample()
{
  QList<vector<double> *> data = QList<vector<double> *> ();
  vector<double> * q  = new vector<double>(50);
  vector<double> * y1 = new vector<double>(50);
  vector<double> * y2 = new vector<double>(50);
  vector<double> * y3 = new vector<double>(50);
  
  double pi = 3.141593;
  for (unsigned int i = 0; i < q->size(); ++i) {
    q->at(i) = i;
  }
  //  double size = y1.size() - 1;
  double size = 1;
  for (unsigned int i = 0; i < y1->size(); ++i) {
    //    0.7*sin(2*pi*x) + 0.5*cos(3*pi*x) + 0.2*sin(pi*x)
    y1->at(i) = (0.7 * sin(2 * pi * (i / size))) + (0.5 * cos(3 * pi
            * (i / size)) + (0.2 * sin(pi * (i / size))));
  }
  cout << endl;
  for (unsigned int i = 0; i < y2->size(); ++i) {
    //    sin(2*pi*x)
    y2->at(i) = sin(2 * pi * (i / size));
  }
  cout << endl;
  
  for (unsigned int i = 0; i < y3->size(); ++i) {
    //    cos(2*pi*x)
    y3->at(i) = cos(2 * pi * (i / size));
  }
  cout << endl;
  
  data.append(q);
  data.append(y1);
  data.append(y2);
  data.append(y3);
  
  Plotter * plotter = new Plotter(data, Plotter::Dq_Plot);
  return plotter;
}

int freqSample(mglGraph *gr, void *)
{
  int maxX = 512;
  int maxY = 512;
  mglData a(maxX, maxY);
  
  srand((unsigned) time(0));
  
  for (int i = 0; i < maxX; ++i) {
    for (int j = 0; j < maxY; ++j) {
      int index = i + (maxX * j);
      //      a.a[index] = RandomTools::giveIntRandomNumberBetweenZeroAndEntry(100);
      a.a[index] = (rand() % 100);
    }
  }
  gr->SetRanges(maxX, 0, maxY, 0, 0, 100);
  gr->SetFontSizePT(9);
  gr->SetTicks('x', 128, 4);
  gr->SetTicks('y', 128, 4);
  gr->SetTicks('z', 20, 4);
  gr->Rotate(40, 60);
  gr->Light(true);
  //  gr->Box();
  gr->Axis();
  gr->Boxs(a, "bcyr");
  //  gr->Boxs(a,"bcyr|");
  //  gr->Boxs(a,"Bbcyr|");
  //  gr->Boxs(a,"Bbcyr");
  //  gr->Boxs(a,"kw");
  //  gr->Boxs(a,"kRryw");
  //  gr->Fall(a);
  //  gr->Boxs(a);
  //  gr->Surf(a,"bcyr");
  //  gr->Mesh(a,"bcyr");
  return 0;
}

Plotter * measuresSample()
{
  QList<const RowMatrix<int> *> dataList = QList<const RowMatrix<int> *>();
  for (int mainIndex = 0; mainIndex < 5; ++mainIndex) {
    int maxX = 60;
    int maxY = 60;
    RowMatrix<int> * matrix = new RowMatrix<int> (maxX, maxY);
    
    srand((unsigned) time(0));
    
    for (int i = 0; i < maxX; ++i) {
      for (int j = 0; j < maxY; ++j) {
        (*matrix)(i, j)
                = RandomTools::giveIntRandomNumberBetweenZeroAndEntry(101);
        //      (*matrix)(i,j) =  (rand()%100);
      }
    }
    
    const RowMatrix<int> * mat = matrix;
    
    dataList.append(mat);
    
  }
  Plotter * plotter = new Plotter(dataList, Plotter::Measures_Plot);
  plotter->setTitle("Medidas \\mu");
  plotter->setXLabel("Eje x");
  plotter->setYLabel("Eje y");
  plotter->setZLabel("Eje z");
  return plotter;
}

Plotter * rectSample()
{
  QList<vector<double> *> data = QList<vector<double> *>();
  vector<double> * q  = new vector<double>(50);
  vector<double> * y1 = new vector<double>(50);
//  vector<double> * y2 = new vector<double>(50);
//  vector<double> * y3 = new vector<double>(50);
  
  int datum = -20;
  for (unsigned int i = 0; i < q->size(); ++i, datum++) {
    q->at(i) = datum;
  }
  for (unsigned int i = 0; i < y1->size(); ++i) {
    y1->at(i) = i * 0.5;
  }
//  cout << endl;
//  for (unsigned int i = 0; i < y2->size(); ++i) {
//    y2->at(i) = i * 0.8;
//  }
//  cout << endl;
//  
//  for (unsigned int i = 0; i < y3->size(); ++i) {
//    y3->at(i) = i;
//  }
  cout << endl;
  
  data.append(q);
  data.append(y1);
//  data.append(y2);
//  data.append(y3);
  
  Plotter * plotter = new Plotter(data, Plotter::Dq_Plot);
  plotter->setTitle("Rectas");
  plotter->setXLabel("Eje x");
  plotter->setYLabel("Eje y");
  return plotter;
}

Plotter * multiRectSample()
{
  QList<QList<vector<double> *> > data = QList<QList<vector<double> *> >();
  
  for (int n = 0; n < 5; ++n) {
    QList<vector<double> *> subData = QList<vector<double> *> ();
    vector<double> * q  = new vector<double>(50);
    vector<double> * y1 = new vector<double>(50);
    vector<double> * y2 = new vector<double>(50);
    vector<double> * y3 = new vector<double>(50);
    
    int datum = -20;
    for (unsigned int i = 0; i < q->size(); ++i, datum++) {
      q->at(i) = datum;
    }
    for (unsigned int i = 0; i < y1->size(); ++i) {
      y1->at(i) = i * 0.5;
    }
    cout << endl;
    for (unsigned int i = 0; i < y2->size(); ++i) {
      y2->at(i) = i * 0.8;
    }
    cout << endl;
    
    for (unsigned int i = 0; i < y3->size(); ++i) {
      y3->at(i) = i;
    }
    cout << endl;
    
    subData.append(q);
    subData.append(y1);
    subData.append(y2);
    subData.append(y3);
    data.append(subData);
  }
  Plotter * plotter = new Plotter(data, Plotter::Linear_Plot);
  plotter->setTitle("Multi Rectas");
  plotter->setXLabel("Eje x");
  plotter->setYLabel("Eje y");
  
  return plotter;
}

int appNormal(int argc, char *argv[])
{
  AppController * app = new AppController(argc, argv);
//    app->getMainWindow()->showMaximized();
  app->getMainWindow()->resize(1024, 762);
  app->getMainWindow()->show();
  return app->exec();
}

int appPlot(int argc, char *argv[])
{
//    Plotter * plotter = sinSample();
    Plotter * plotter = rectSample();
//    Plotter * plotter = multiRectSample();
//  Plotter * plotter = measuresSample();
  
  QApplication a(argc, argv);
  QMainWindow *Wnd = new QMainWindow;
  Wnd->resize(800, 600); // for fill up the QMGL, menu and toolbars
  Wnd->setWindowTitle("Ventana");
  // here I allow to scroll QMathGL -- the case 
  // then user want to prepare huge picture
  QScrollArea *scroll = new QScrollArea(Wnd);
  
  // Create and setup QMathGL
  QMathGL *QMGL = new QMathGL(Wnd);
  //  QMGL->setPopup(popup); // if you want to setup popup menu for QMGL
  int nPlotRows = 2;
  //  QMGL->setSize(580, 260 * nPlotRows); // Linear regression
  QMGL->setSize(620, 280 * nPlotRows); // Measures
  QMGL->setDraw(plotter);
  // or use QMGL->setDraw(foo); for instance of class Foo:public mglDraw
  QMGL->update();
  
  // continue other setup (menu, toolbar and so on)
  //  makeMenu();
  scroll->setWidget(QMGL);
  Wnd->setCentralWidget(scroll);
  Wnd->show();
  return a.exec();
}

int animationSample(mglGraph *gr, void *)
{
  mglData dat(100);
  char str[32];
  gr->StartGIF("sample.gif");
  for (int i = 0; i < 100; i++) {
    gr->NewFrame(); // start frame
    gr->Box(); // some plotting
    sprintf(str, "sin(pi*x+%g*pi)", 0.02 * i);
    dat.Modify(str);
    gr->Plot(dat, "b");
    gr->EndFrame(); // end frame
  }
  gr->CloseGIF();
  return 0;
}

int runSample(int argc, char *argv[])
{
  
  mglGraphQT gr;
//  gr.Window(argc, argv, freqSample, "MathGL examples");
    gr.Window(argc,argv,log,"MathGL examples");
  return mglQtRun();
  
  Q_UNUSED(argc);
  Q_UNUSED(argv);
  /*  mglGraph *gr = new mglGraphZB;
   //  log(gr, NULL);
   freqSample(gr, NULL);
   //  animationSample(gr, NULL);
   gr->ShowImage();    delete gr;
   return 0;*/

}

bool xCoordinateLessThan_Main(const QPointF & x1, const QPointF &  x2)
{
  return x1.x() < x2.x();
}

bool yCoordinateLessThan_Main(const QPointF & y1, const QPointF & y2)
{
  return y1.y() < y2.y();
}


void testCopyContructorList()
{
  QList<QPointF> * list = new QList<QPointF>();
  list->append(QPointF(1.1, 5.0));
  list->append(QPointF(4.1, 7.0));
  list->append(QPointF(3.1, 2.0));
  list->append(QPointF(21.1, 44.0));
  list->append(QPointF(32.1, 64.0));
  list->append(QPointF(72.1, 43.0));
  list->append(QPointF(24.1, 94.0));
  list->append(QPointF(12.1, 14.0));
  
  cout << "\nlist: "<< endl;
  foreach(QPointF p, (*list)){
    cout << "(" << p.x() << ", " << p.y() << ") "; 
  }
  cout << "\ncopy: "<< endl;
  QList<QPointF> copyList = QList<QPointF>(*list);
  foreach(QPointF p, copyList){
    cout << "(" << p.x() << ", " << p.y() << ") "; 
  }
  cout << "\nchange element 0 in list: (2.0, 2.0)"<< endl;
  list->append(QPointF(2.0, 2.0));
  
  foreach(QPointF p, (*list)){
    cout << "(" << p.x() << ", " << p.y() << ") ";
  }
  cout << "\ncopy: "<< endl;
  foreach(QPointF p, copyList){
    cout << "(" << p.x() << ", " << p.y() << ") ";
  }
  
  qSort(copyList.begin(), copyList.end(), xCoordinateLessThan_Main);
  cout << "\ncopy ordered by x: "<< endl;
  foreach(QPointF p, copyList){
    cout << "(" << p.x() << ", " << p.y() << ") "; 
  }
  
  QList<QPointF> sublist = copyList.mid(3,5);
  
  
  qSort(sublist.begin(), sublist.end(), yCoordinateLessThan_Main);
  cout << "\nsublist ordered by y: " << endl;
  foreach(QPointF p, sublist){
    cout << "(" << p.x() << ", " << p.y() << ") "; 
  }
  
}

int otherTests(){
  testCopyContructorList();
  return 0;
}

using namespace bpp;
/*
int bppRaaTest(){
  try {
    RAA * raaObj = new RAA("genbank");
    Sequence * seq = 0;
//    seq = raaObj->getSeq("GU211234.1");
//    seq = raaObj->getSeq("GU323343.1");
    seq = raaObj->getSeq("L04470");
    if (seq) {
      cout << "Nombre secuencia: "<< seq->getName() <<endl;
      cout << "Nombre secuencia: "<< seq->toString() <<endl;
    }
    else{
      cout << "Ninguna secuencia concuerda con su bUsqueda"<< endl;
    }
    return 0;
  }
  catch (int e) {
    cout << "Excepci�n al crear conexion con el servidor." << endl
         << "Excepci�n: " << endl 
         << e 
         << endl;
    return 0;
  }
  
  
//  int result = raaObj->openDatabase("genbank", 0, 0);
  
//  if (result == 0)
//    cout << "Ok"<< endl;
//  else{
//    cout << "Ooops!: "<< result << endl;
//  }
 
}
*/
int roundTest()
{
  vector<double> numbers;
  
  numbers.push_back(1.1);
  numbers.push_back(2.1);
  numbers.push_back(2.09546);
  numbers.push_back(2.02122);
  numbers.push_back(170.078);
  numbers.push_back(2.5);
  
  
  for (unsigned int i = 0; i < numbers.size(); ++i) {
    cout << numbers.at(i) << "  "<< utils::round(numbers.at(i)) << endl;
  }
  return 0;
}

NormalPlot * qwtPlotNormalCurves(QWidget * parent)
{
  QList<vector<double> *> dataList;
  
  const int nPoints = 41;
  vector<double> * xValues  = new vector<double>(nPoints);
  vector<double> * y1Values = new vector<double>(nPoints);
  vector<double> * y2Values = new vector<double>(nPoints);
//  vector<double> ySinValues(nPoints);
//  vector<double> yCosValues(nPoints);
//  vector<double> ySinMValues(nPoints);
  
//  double pi = 3.1416;
  
//  for (int i = 0; i < nPoints; i += 1) {
//    xValues.at(i) = ((double)i * pi) / 180;
//    ySinValues.at(i) = sin(xValues.at(i));
//    yCosValues.at(i) = cos(xValues.at(i));
//    ySinMValues.at(i) = 2 * sin(xValues.at(i));
//  }
  
//  int q = -20;
  for (int i = 0, q = -20; i < nPoints; ++i, ++q) {
    xValues->at(i) = q;
  }
  
  y1Values->at(0)  = 2.21482376;
  y1Values->at(1)  = 2.21335273;
  y1Values->at(2)  = 2.21167236;
  y1Values->at(3)  = 2.20974298;
  y1Values->at(4)  = 2.20751535;
  y1Values->at(5)  = 2.20492786;
  y1Values->at(6)  = 2.20190272;
  y1Values->at(7)  = 2.19834070;
  y1Values->at(8)  = 2.19411402;
  y1Values->at(9)  = 2.18905639;
  y1Values->at(10) = 2.18294945;
  y1Values->at(11) = 2.17550425;
  y1Values->at(12) = 2.16633765;
  y1Values->at(13) = 2.15494700;
  y1Values->at(14) = 2.14070021;
  y1Values->at(15) = 2.12290090;
  y1Values->at(16) = 2.10108283;
  y1Values->at(17) = 2.07573302;
  y1Values->at(18) = 2.04903018;
  y1Values->at(19) = 2.02364757;
  y1Values->at(20) = 1.99885758;
  y1Values->at(21) = 1.96815334;
  y1Values->at(22) = 1.91955382;
  y1Values->at(23) = 1.84067197;
  y1Values->at(24) = 1.74977813;
  y1Values->at(25) = 1.67366250;
  y1Values->at(26) = 1.61604074;
  y1Values->at(27) = 1.57284440;
  y1Values->at(28) = 1.53994134;
  y1Values->at(29) = 1.51433757;
  y1Values->at(30) = 1.49399561;
  y1Values->at(31) = 1.47753027;
  y1Values->at(32) = 1.46398373;
  y1Values->at(33) = 1.45267914;
  y1Values->at(34) = 1.44312772;
  y1Values->at(35) = 1.43496921;
  y1Values->at(36) = 1.42793318;
  y1Values->at(37) = 1.42181316;
  y1Values->at(38) = 1.41644916;
  y1Values->at(39) = 1.41171554;
  y1Values->at(40) = 1.40751239;
  
  y2Values->at(0)  = 2.22041633;
  y2Values->at(1)  = 2.21890971;
  y2Values->at(2)  = 2.21719617;
  y2Values->at(3)  = 2.21523779;
  y2Values->at(4)  = 2.21298774;
  y2Values->at(5)  = 2.21038775;
  y2Values->at(6)  = 2.20736453;
  y2Values->at(7)  = 2.20382502;
  y2Values->at(8)  = 2.19964978;
  y2Values->at(9)  = 2.19468368;
  y2Values->at(10) = 2.18872281;
  y2Values->at(11) = 2.18149583;
  y2Values->at(12) = 2.17263769;
  y2Values->at(13) = 2.16165417;
  y2Values->at(14) = 2.14788264;
  y2Values->at(15) = 2.13048544;
  y2Values->at(16) = 2.10861254;
  y2Values->at(17) = 2.08204955;
  y2Values->at(18) = 2.05243473;
  y2Values->at(19) = 2.02324956;
  y2Values->at(20) = 1.99575571;
  y2Values->at(21) = 1.96493205;
  y2Values->at(22) = 1.92011556;
  y2Values->at(23) = 1.85006878;
  y2Values->at(24) = 1.76774652;
  y2Values->at(25) = 1.69676812;
  y2Values->at(26) = 1.64202132;
  y2Values->at(27) = 1.60048152;
  y2Values->at(28) = 1.56857252;
  y2Values->at(29) = 1.54358595;
  y2Values->at(30) = 1.52363684;
  y2Values->at(31) = 1.50742561;
  y2Values->at(32) = 1.49404474;
  y2Values->at(33) = 1.48284815;
  y2Values->at(34) = 1.47336645;
  y2Values->at(35) = 1.46525197;
  y2Values->at(36) = 1.45824253;
  y2Values->at(37) = 1.45213725;
  y2Values->at(38) = 1.44677992;
  y2Values->at(39) = 1.44204749;
  y2Values->at(40) = 1.43784184;
  
  
  dataList.append(xValues);
  dataList.append(y1Values);
  dataList.append(y2Values);
  
  QStringList curveIds;
  curveIds << "Seq_1" 
           << "Seq_2";
  
  NormalPlot * dqPlot = new NormalPlot(dataList, curveIds, parent);
  dqPlot->setTitle("Espectro Dq");
  dqPlot->setAxisTitle(QwtPlot::xBottom, "q");
  dqPlot->setAxisTitle(QwtPlot::yLeft, "Dq");
  dqPlot->resize(800,500);
  
  return dqPlot;
}

LinearPlot * qwtPlotLinearRegressionCurves(QWidget * parent)
{
  QList<vector<double> *> dataList;
  
  const int nPoints = 16;
  vector<double> * x1Values = new vector<double>(nPoints);
  vector<double> * y1Values = new vector<double>(nPoints);
  vector<double> * x2Values = new vector<double>(nPoints);
  vector<double> * y2Values = new vector<double>(nPoints);
  
  x1Values->at(0)  = -5.139710;
  x1Values->at(1)  = -2.682980;
  x1Values->at(2)  = -2.033630;
  x1Values->at(3)  = -1.643200;
  x1Values->at(4)  = -1.363130;
  x1Values->at(5)  = -1.144570;
  x1Values->at(6)  = -0.965325;
  x1Values->at(7)  = -0.813375;
  x1Values->at(8)  = -0.681497;
  x1Values->at(9)  = -0.565001;
  x1Values->at(10) = -0.460672;
  x1Values->at(11) = -0.366207;
  x1Values->at(12) = -0.279900;
  x1Values->at(13) = -0.200454;
  x1Values->at(14) = -0.126857;
  x1Values->at(15) = -0.058308;
                    
  y1Values->at(0)  = -13.479300;
  y1Values->at(1)  =  -6.952870;
  y1Values->at(2)  =  -5.729590;
  y1Values->at(3)  =  -5.073850;
  y1Values->at(4)  =  -4.419330;
  y1Values->at(5)  =  -3.958190;
  y1Values->at(6)  =  -3.573480;
  y1Values->at(7)  =  -3.241410;
  y1Values->at(8)  =  -2.896190;
  y1Values->at(9)  =  -2.688650;
  y1Values->at(10) =  -2.485950;
  y1Values->at(11) =  -2.287880;
  y1Values->at(12) =  -2.087170;
  y1Values->at(13) =  -1.925750;
  y1Values->at(14) =  -1.756650;
  y1Values->at(15) =  -1.579190;

  x2Values->at(0)  = -5.139710;
  x2Values->at(1)  = -2.682980;
  x2Values->at(2)  = -2.033630;
  x2Values->at(3)  = -1.643200;
  x2Values->at(4)  = -1.363130;
  x2Values->at(5)  = -1.144570;
  x2Values->at(6)  = -0.965325;
  x2Values->at(7)  = -0.813375;
  x2Values->at(8)  = -0.681497;
  x2Values->at(9)  = -0.565001;
  x2Values->at(10) = -0.460672;
  x2Values->at(11) = -0.366207;
  x2Values->at(12) = -0.279900;
  x2Values->at(13) = -0.200454;
  x2Values->at(14) = -0.126857;
  x2Values->at(15) = -0.058308;

  y2Values->at(0)  = -11.539400;
  y2Values->at(1)  = -5.657540;
  y2Values->at(2)  = -4.339440;
  y2Values->at(3)  = -3.573720;
  y2Values->at(4)  = -3.034720;
  y2Values->at(5)  = -2.628360;
  y2Values->at(6)  = -2.299440;
  y2Values->at(7)  = -2.025640;
  y2Values->at(8)  = -1.793270;
  y2Values->at(9)  = -1.596780;
  y2Values->at(10) = -1.422870;
  y2Values->at(11) = -1.267440;
  y2Values->at(12) = -1.127180;
  y2Values->at(13) = -1.001400;
  y2Values->at(14) = -0.886317;
  y2Values->at(15) = -0.781351;
  
  dataList.append(x1Values);
  dataList.append(y1Values);
  dataList.append(x2Values);
  dataList.append(y2Values);
  
  
  QList<vector<double> *> linearParams;
  
  vector<double> * linearFit1 = new vector<double>(2);
  linearFit1->at(0) =  2.279807722; // m
  linearFit1->at(1) = -1.368901965; // b
  
  vector<double> * linearFit2 = new vector<double>(2);
  linearFit2->at(0) =  2.079070978;
  linearFit2->at(1) = -0.403778793;
  
  linearParams.append(linearFit1);
  linearParams.append(linearFit2);
  
  QStringList curveIds;
  curveIds << "D(q=-20)" 
           << "D(q=1)";
  
  LinearPlot * linearPlot = new LinearPlot(dataList, curveIds, linearParams, parent);
  linearPlot->setTitle(QObject::trUtf8("Regresiones lineales para cálculo \nde valores Dq"));
  linearPlot->setAxisTitle(QwtPlot::xBottom, "ln(R/L)");
  linearPlot->setAxisTitle(QwtPlot::yLeft, "Dq");
  linearPlot->resize(800,500);
  
  return linearPlot;
}

int qwtPlotApp(int argc, char *argv[])
{
  QApplication a(argc, argv);
  
//  NormalPlot * examplePlot = qwtPlotNormalCurves();
//  LinearPlot * examplePlot = qwtPlotLinearRegressionCurves();
  
//  examplePlot->show();
    
//  return a.exec(); 
  
  
  
  QWidget vBox;
  vBox.setWindowTitle("Cpu Plot");
  
    
  NormalPlot * examplePlot = qwtPlotNormalCurves(&vBox);
//  LinearPlot * examplePlot = qwtPlotLinearRegressionCurves(&vBox);
  
  QString info(QObject::trUtf8("Presione en cada item de leyenda para activar o "
          "desactivar la curva correspondiente"));
  
  QLabel *label = new QLabel(info, &vBox);
  
  QVBoxLayout *layout = new QVBoxLayout(&vBox);
  layout->addWidget(examplePlot);
  layout->addWidget(label);
  
  vBox.resize(800,550);
  vBox.show();
  
  
//  QPixmap pixmap(examplePlot->size());
//  pixmap.fill(Qt::lightGray);
//  pixmap.fill(Qt::transparent);
  QImage pixmap(examplePlot->size(), QImage::Format_RGB32);
  pixmap.fill(qRgb(255, 255, 255));
  
  QwtPlotPrintFilter filter;
  int options = QwtPlotPrintFilter::PrintAll;
            options &= ~QwtPlotPrintFilter::PrintBackground;
            options |= QwtPlotPrintFilter::PrintFrameWithScales;
  filter.setOptions(options);
  
  if(!pixmap.isNull()){
    QString fileName = QFileDialog::getSaveFileName(examplePlot, QObject::trUtf8("Save the file as..."), QDir::currentPath(), QObject::trUtf8("JPEG (*.jpg);;Portable Network Graphics (*.png)"));
    if (!fileName.isEmpty()){
      if(fileName.endsWith(".png")){
        examplePlot->print(pixmap, filter);
        pixmap.save(fileName, "PNG", 100);
      }
      else if(fileName.endsWith(".jpg")){
        examplePlot->print(pixmap, filter);
        pixmap.save(fileName, "JPG", 100);
      }
      else{
        return 0;
      }
    }
  }
  
  return a.exec(); 
}

int main(int argc, char *argv[])
{
//  appNormal(argc, argv);
  qwtPlotApp(argc, argv);
//  treeTest();
//  appPlot(argc, argv);
//  return runSample(argc, argv); // MathGl samples
//  return otherTests();
//  bppRaaTest();
//  return roundTest();
  return 0;
}

