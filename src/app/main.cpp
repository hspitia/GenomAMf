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
#include <mfa/SandBoxMethod.h>
#include <mfa/Plotter.h>

#include <utils/Utils.h>

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



int main(int argc, char *argv[])
{
  appNormal(argc, argv);
//  treeTest();
//  appPlot(argc, argv);
//  return runSample(argc, argv); // MathGl samples
//  return otherTests();
//  bppRaaTest();
//  return roundTest();
  return 0;
}

