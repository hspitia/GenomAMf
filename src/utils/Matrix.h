#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

//namespace utils 
//{
  
  template <class T>
  class Matrix
  {
    private:
      int rows;
      int cols;
      T ** matrix;
      
      T ** createMatrix(const int & rows, const int & cols, const T & initValue=0){
        T ** matrix_tmp = new T*[rows];
        
        for(int i=0; i<rows; i++){
          matrix_tmp[i] = new T[cols];
          for(int j = 0; j < cols; ++j){
            matrix_tmp[i][j] = initValue;
          }
        }
        
        return matrix_tmp;
      }
      
      void imprimir(std::ostream & outStream) const{
        if(matrix != NULL){
          for(int i = 0; i < rows; i++ ){
            for(int j = 0; j < cols; j++ ){
              outStream<<setw(5)<<matrix[i][j]<<" ";
            }
            outStream<<endl;
          }
        }
        else
          outStream<<"NULL"<<endl;
      }
      
    public:
      Matrix() : rows(0), cols(0), matrix(NULL){};
      
      Matrix(const Matrix<T> & matrixOriginal) {
        rows = matrixOriginal.rows;
        cols = matrixOriginal.cols;
        
        matrix = createMatrix(rows, cols);
        
        for(int i = 0; i < rows; i++ ){
          for(int j = 0; j < cols; j++ ){
            matrix[i][j] = matrixOriginal.matrix[i][j];
          }
        }
      }
      
      Matrix(const int & rows, const int & cols, const T & initValue = 0){
        this->rows = rows;
        this->cols = cols;
        // cout<<"Constructor "<<initValue<<endl;
        matrix = createMatrix(rows, cols, initValue);
      }
      
      ~Matrix(){
        if(matrix != NULL){
          for(int i=0; i<rows; i++)
          {
            delete []matrix[i];
          }
          delete []matrix;
        }
      }
      
      
      int getRows(){
        return rows;
      }
      
      int getCols(){
        return cols;
      }
      
      
      T getAt(const int & row, const int & col){
        //      if(row < 0 || row >= rows) {
        //        cerr<<" ERROR - Matrix::getAt(): row index out of bounds ["<< row<<"]["<< col<<"] in ["<< rows-1 <<"]["<< cols-1 <<"]"<<endl;
        //        assert(false);
        //      }
        //      if(col < 0 || col >= cols) {
        //        cerr<<" ERROR - Matrix::getAt(): col index out of bounds ["<< row<<"]["<< col<<"] in ["<< rows-1 <<"]["<< cols-1 <<"]"<<endl;
        //        assert(false);
        //      }
        // require(row >= 0 && row < rows, "ERROR - Matrix::getAt(): row index out of bounds");
        // require(col >= 0 && col < cols, "ERROR - Matrix::getAt(): col index out of bounds");
        return matrix[row][col];
      }
      
      void setAt(const int & row, const int & col, const T & valor){
        //      if(row < 0 || row >= rows) {
        //        cerr<<" ERROR - Matrix::setAt(): row index out of bounds ["<< row<<"]["<< col<<"] in ["<< rows-1 <<"]["<< cols-1 <<"]"<<endl;
        //        assert(false);
        //      }
        //      if(col < 0 || col >= cols) {
        //        cerr<<" ERROR - Matrix::setAt(): col index out of bounds ["<< row<<"]["<< col<<"] in ["<< rows-1 <<"]["<< cols-1 <<"]"<<endl;
        //        assert(false);
        //      }
        // require(row >= 0 && row < rows, "ERROR - Matrix::setAt(): row index out of bounds");
        // require(col >= 0 && col < cols, "ERROR - Matrix::setAt(): col index out of bounds");
        matrix[row][col] = valor;
      }
      
      bool isEmpty(){
        if(matrix == NULL) return true;
        return false;
      }
      
      Matrix<T> & operator= (const Matrix<T> & matrixObject){
        for(int i = 0; i < rows; ++i){
          for(int j = 0; j < cols; ++j){
            matrix[i][j] = matrixObject.matrix[i][j];
          }
        }
        return *this;
      }
      
      friend std::ostream &operator << (std::ostream & outStream, const Matrix<T> & objMatrix){
        objMatrix.imprimir(outStream);
        return outStream;
      }
      
      friend std::ostream &operator << (std::ostream & outStream, const Matrix<T> * objMatrix){
        (*objMatrix).imprimir(outStream);
        return outStream;
      }
      
      void save(const char * fileName){
        ofstream outputFile(fileName);
        if(matrix != NULL){
          for(int i = 0; i < rows; i++ ){
            for(int j = 0; j < cols; j++ ){
              outputFile<<setw(5)<<matrix[i][j]<<" ";
            }
            outputFile<<endl;
          }
        }
        else
          outputFile<<"NULL"<<endl;
      }
      
      T ** getMatrix(){
        return matrix;
      }
  };
//}

#endif // MATRIX_H
