/**
 * @file MatrixOperations.h
 * @date 26/11/2009
 * @author He-.ctor Fabio Espitia Navarro <br>
 * Universidad del Valle - Escuela de Ingenier&iacute;a de Sistemas y 
 * Computaci&oacute;n.<br>
 * Santiago de Cali - Colombia
 * @brief 
 */

/* 
 *         File:  MatrixOperations.h
 *   Created on:  26/11/2009
 *       Author:  He-.ctor Fabio Espitia Navarro
 *  Institution:  UNIVERSIDAD DEL VALLE - ESCUELA DE INGENIERIA DE SISTEMAS Y 
 *                COMPUTACION 
 *      Project:  GenomAMf
 *      License:  GNU GPL. See more details in LICENSE file
 *  Description:  
 */

#ifndef MATRIXOPERATIONS_H_
#define MATRIXOPERATIONS_H_

//#define TEST_MODE

#ifdef TEST_MODE
#include <QtCore>
#endif

// STD 
#include <cmath>
#include <iostream>

using namespace std;

#include <NumCalc/Matrix.h>
#include <NumCalc/VectorExceptions.h>

//#include <Utils/Exceptions.h>

using namespace bpp;

/**
 * 
 */

#ifdef TEST_MODE
class MatrixOperations : public QObject
#else 
class MatrixOperations
#endif
{
#ifdef TEST_MODE
  Q_OBJECT
#endif
  
  public:
    MatrixOperations() {}
    virtual ~MatrixOperations() {}
    
    
    template<class Scalar>
    static void add(const Matrix<Scalar>& A, const Matrix<Scalar>& B, 
                    Matrix<Scalar>& O) throw (DimensionException)
    {
      
      unsigned int ncA = A.getNumberOfColumns();
      unsigned int nrA = A.getNumberOfRows();
      unsigned int nrB = B.getNumberOfRows();
      unsigned int ncB = B.getNumberOfColumns();
      unsigned int nrO = O.getNumberOfRows();
      unsigned int ncO = O.getNumberOfColumns();
      
      if (ncA != ncB)
        throw DimensionException("MatrixOperations::add(). A and B must "
          "have the same number of columns.", ncB, ncA);
      if (nrA != nrB)
        throw DimensionException("MatrixOperations::add(). A and B must "
          "have the same number of rows.", nrB, nrA);
      if (ncA != ncO)
        throw DimensionException("MatrixOperations::add(). A and O must "
          "have the same number of columns.", ncO, ncA);
      if (nrA != nrO)
        throw DimensionException("MatrixOperations::add(). A and O must "
          "have the same number of rows.", nrO, nrA);
      if (ncB != ncO)
        throw DimensionException("MatrixOperations::add(). B and O must "
          "have the same number of columns.", ncO, ncA);
      if (nrB != nrO)
        throw DimensionException("MatrixOperations::add(). B and O must "
          "have the same number of rows.", nrO, nrA);
      
      for (unsigned int i = 0; i < A.getNumberOfRows(); i++) {
        for (unsigned int j = 0; j < A.getNumberOfColumns(); j++) {
          O(i, j) = A(i, j) + B(i, j);
        }
      }
    }
    
    template<class Scalar>
    static void sub(const Matrix<Scalar>& A, const Matrix<Scalar>& B, 
                    Matrix<Scalar>& O) throw (DimensionException) 
    {
      unsigned int ncA = A.getNumberOfColumns();
      unsigned int nrA = A.getNumberOfRows();
      unsigned int nrB = B.getNumberOfRows();
      unsigned int ncB = B.getNumberOfColumns();
      unsigned int nrO = O.getNumberOfRows();
      unsigned int ncO = O.getNumberOfColumns();
      
      if (ncA != ncB)
        throw DimensionException(" MatrixOperations::sub(). A and B must "
          "have the same number of columns.", ncB, ncA);
      if (nrA != nrB)
        throw DimensionException(" MatrixOperations::sub(). A and B must "
          "have the same number of rows.", nrB, nrA);
      if (ncA != ncO)
        throw DimensionException(" MatrixOperations::sub(). A and O must "
          "have the same number of columns.", ncO, ncA);
      if (nrA != nrO)
        throw DimensionException(" MatrixOperations::sub(). A and O must "
          "have the same number of rows.", nrO, nrA);
       if (ncB != ncO)
        throw DimensionException(" MatrixOperations::sub(). B and O must "
          "have the same number of columns.", ncO, ncA);
      if (nrB != nrO)
        throw DimensionException(" MatrixOperations::sub(). B and O must "
          "have the same number of rows.", nrO, nrA);
      
      for (unsigned int i = 0; i < A.getNumberOfRows(); i++) {
        for (unsigned int j = 0; j < A.getNumberOfColumns(); j++) {
          O(i, j) = A(i, j) - B(i, j);
//          cout << A(i,j) <<" - " <<B(i, j) << " = "<< O(i, j) << endl; 
        }
      }
    }

    template<class Scalar>
    static double sum(const Matrix<Scalar>& A)
    {
      unsigned int nRows = A.getNumberOfRows();
      unsigned int nCols = A.getNumberOfColumns();
      Scalar sum = 0.0;
      
      for (unsigned int i = 0; i < nRows; i++) {
        for (unsigned int j = 0; j < nCols; j++) {
//          cout << "sum: " << sum;
          sum += A(i, j);
//          cout << " += " << A(i,j) << " = " << sum << endl;
        }
      }
      return sum;
    }
    
    template<class Scalar>
    static double average(const Matrix<Scalar>& A)
    {
      unsigned int nRows = A.getNumberOfRows();
      unsigned int nCols = A.getNumberOfColumns();
      double sumation = static_cast<double> (sum<Scalar> (A));
      double nElements = static_cast<double>(nRows * nCols);
      double average = sumation / nElements;
      
      return average;
    }
    
    template<class Scalar>
    static double variance(const Matrix<Scalar>& A, const double & average)
    {
      unsigned int nRows = A.getNumberOfRows();
      unsigned int nCols = A.getNumberOfColumns();
      double sum = 0.0;
      double difference = 0.0;
      
      for (unsigned int i = 0; i < nRows; i++) {
        for (unsigned int j = 0; j < nCols; j++) {
          difference = static_cast<double>(A(i,j)) - average; 
          sum += pow(difference, 2);
        }
      }
      
      double nElements = static_cast<double>(nRows * nCols);
      double variance = sqrt(sum / nElements);
      
      return variance;
    }
    
    template<class Scalar>
    static double covariance(const Matrix<Scalar>& A, const Matrix<Scalar>& B,
                             const double & averageA, const double & averageB)
    {
      unsigned int ncA = A.getNumberOfColumns();
      unsigned int nrA = A.getNumberOfRows();
      unsigned int ncB = B.getNumberOfColumns();
      unsigned int nrB = B.getNumberOfRows();
      
      if (ncA != ncB)
        throw DimensionException("MatrixOperations::covariance(). A and B must "
          "have the same number of columns.", ncB, ncA);
      if (nrA != nrB)
        throw DimensionException("MatrixOperations::covariance(). A and B must "
          "have the same number of rows.", nrB, nrA);
      
      double sum = 0.0;
      double differenceA = 0.0;
      double differenceB = 0.0;
      
      for (unsigned int i = 0; i < nrA; i++) {
        for (unsigned int j = 0; j < ncA; j++) {
          differenceA = static_cast<double>(A(i,j)) - averageA; 
          differenceB = static_cast<double>(B(i,j)) - averageB; 
          sum += differenceA * differenceB;
        }
      }
      
      double nElements = static_cast<double>(nrA * ncA);
      double covariance = sqrt(sum / nElements);
      
      return covariance;
    }
    
    template<class Scalar>
    static void normalize(Matrix<Scalar>& A) throw (DimensionException) 
    {
      for (unsigned int i = 0; i < A.getNumberOfRows(); i++) {
        for (unsigned int j = 0; j < A.getNumberOfColumns(); j++) {
          if (A(i, j) > 0)
            A(i, j) = 1;
        }
      }
    }
    
    template<class Scalar>
    static void normalize(const Matrix<Scalar>& A, 
                          Matrix<Scalar>& O) throw (DimensionException) 
    {
      unsigned int ncA = A.getNumberOfColumns();
      unsigned int nrA = A.getNumberOfRows();
      unsigned int nrO = O.getNumberOfRows();
      unsigned int ncO = O.getNumberOfColumns();
      
      if (ncA != ncO)
        throw DimensionException(" MatrixOperations::normalize(). A and O must "
          "have the same number of columns.", ncO, ncA);
      if (nrA != nrO)
        throw DimensionException(" MatrixOperations::normalize(). A and O must "
          "have the same number of rows.", nrO, nrA);
      
      for (unsigned int i = 0; i < A.getNumberOfRows(); i++) {
        for (unsigned int j = 0; j < A.getNumberOfColumns(); j++) {
          if (A(i, j) > 0)
            O(i, j) = 1;
          else
            O(i, j) = 0;
        }
      }
    }
};

#endif /* MATRIXOPERATIONS_H_ */
