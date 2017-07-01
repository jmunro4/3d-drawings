#ifndef __MATRIX_H
#define __MATRIX_H

#include <ostream>
#include "points.h"

using namespace std;

class Matrix
{
 private:
  int rows;
  int cols;
  float **matrix; // Double subscripted array of rows x cols

 public:
  Matrix();                          // Default constructor
  Matrix(int, int);                  // Construct matrix of size rows x columns
  Matrix(const Matrix&);             // Construct matrix from another matrix
  ~Matrix();                         // Destructor
  int getNumRows() const;
  int getNumCols() const;
  void setIdentity();                // Set matrix to identity matrix
  
  float* operator[](const int col);  // Allow individual items in matrix accessible via [][]

  Matrix& operator=(const Matrix& other);
};


Matrix operator+(const Matrix&,const Matrix&);   // Add two matrices
Matrix operator*(const Matrix&, const Matrix&);  // Multiply two matrices
Point operator*(const Matrix&, const Point&);    // Multiply matrix by a point (i.e., vector)
ostream& operator<<(ostream&, const Matrix&);    // Print matrix


#endif
