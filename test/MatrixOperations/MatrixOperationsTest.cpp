#include <QtTest/QtTest>
#include <NumCalc/Matrix.h>
#include <NumCalc/MatrixTools.h>
#include "utils/MatrixOperations.h"

class MatrixOperationsTest : public QObject
{
  Q_OBJECT
  
  private:
    RowMatrix<int> A;
    RowMatrix<int> B;
    RowMatrix<int> O;
    int n;
    
  private slots:
    void initTestCase();
    void add();
    void sub();
    void average();
    void covariance();
    void variance();
    
};

void MatrixOperationsTest::initTestCase()
{
  n = 4;
  A = RowMatrix<int>(n, n);
  B = RowMatrix<int>(n, n);
  O = RowMatrix<int>(n, n);
  
  int counter = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      A(i, j) = counter + 2;
      B(i, j) = counter;
      ++counter;
    }
  }
  MatrixTools::print(A);
  MatrixTools::print(B);
}

void MatrixOperationsTest::add()
{
  MatrixOperations::add<int>(A, B, O);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      QCOMPARE(O(i, j), (A(i, j) + B(i, j)));
    }
  }
}

void MatrixOperationsTest::sub()
{
  MatrixOperations::sub<int>(A, B, O);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      QCOMPARE(O(i, j), (A(i, j) - B(i, j)));
    }
  }
}

void MatrixOperationsTest::average()
{
  double result = MatrixOperations::average<int>(A);
  int sum = 0;
  
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      sum += A(i, j);
    }
  }
  double expected = ((double)sum / (double)(n * n));
  cout << "\t average() - "
          "result: " << result << " expected: " <<  expected << endl;
  
  QCOMPARE(result, expected);
}

void MatrixOperationsTest::covariance()
{
  double averageA = MatrixOperations::average<int>(A);
  double averageB = MatrixOperations::average<int>(B);
  
  double sum = 0.0;
  double differenceA = 0.0;
  double differenceB = 0.0;
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      differenceA = static_cast<double>(A(i,j)) - averageA; 
      differenceB = static_cast<double>(B(i,j)) - averageB; 
      sum += differenceA * differenceB;
    }
  }
  
  double nElements = n * n;
  double expected = sqrt(sum / nElements);

  double result = MatrixOperations::covariance(A, B, averageA, averageB);
  
  cout << "\t covariance() - "
          "result: " << result << " expected: " <<  expected << endl;
  
  QCOMPARE(result, expected);
}

void MatrixOperationsTest::variance()
{
//  A(2, 1) = 23;
//  A(2, 2) = 156;
  
  double average = MatrixOperations::average<int>(A);
  
  double sum = 0.0;
  double difference = 0.0;
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      difference = static_cast<double>(A(i,j)) - average; 
      sum += pow(difference, 2);
    }
  }
  
  double nElements = n * n;
  double expected = sqrt(sum / nElements);

  double result = MatrixOperations::variance<int>(A, average);
  
  cout << "\t variance() - "
          "result: " << result << " expected: " <<  expected << endl;
  
  QCOMPARE(result, expected);
}

QTEST_MAIN(MatrixOperationsTest)
#include "MatrixOperationsTest.moc"
