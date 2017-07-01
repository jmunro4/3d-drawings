#include "matrix.h"
#include "points.h"
#include <iostream>

using namespace std;

Matrix::Matrix()
{
  rows = 0;
  cols = 0;
}

Matrix::Matrix(int rows, int cols)
{
  this->rows = rows;
  this->cols = cols;
  matrix = new float*[rows];
  for(int i = 0; i < rows; i++)
    {
      matrix[i] = new float[cols];
    }
}


Matrix::Matrix(const Matrix& orig)
{
  this->rows = orig.getNumRows();
  this->cols = orig.getNumCols();
  matrix = new float*[this->rows];
  for(int i = 0; i < this->rows; i++)
    {
      matrix[i] = new float[this->cols];
      for(int j = 0; j < this->cols; j++)
	{
	  matrix[i][j] = orig.matrix[i][j];
	}
    }
}

Matrix::~Matrix()
{
  for(int i = 0; i < rows; i++)
    {
      delete[] matrix[i];
    }
  delete[] matrix;
}

int Matrix::getNumRows() const
{
  return rows;
}

int Matrix::getNumCols() const
{
  return cols;
}

void Matrix::setIdentity()
{
  for(int i = 0; i < rows; i++)
    {
      for(int j = 0; j < cols; j++)
	{
	  if(i==j)
	    {
	      matrix[i][j] = 1;
	    }
	  else
	    {
	      matrix[i][j] = 0;
	    }
	}
    }
}

float* Matrix::operator[](const int col)
{
  return matrix[col];
}

Matrix& Matrix::operator=(const Matrix& other)
{
  Matrix temp = Matrix(other);
  this->rows = temp.rows;
  this->cols = temp.cols;
  this->matrix = new float*[this->rows];
  for(int i = 0; i < this->rows; i++)
    {
      matrix[i] = new float[this->cols];
      for(int j = 0; j < this->cols; j++)
	{
	  this->matrix[i][j] = temp.matrix[i][j];
	}
    }
  return *this;
}


Matrix operator+(const Matrix& a, const Matrix& b)
{
  Matrix acopy = Matrix(a);
  Matrix bcopy = Matrix(b);
  Matrix sum = Matrix(a.getNumRows(), a.getNumCols());
  for(int i = 0; i < a.getNumRows(); i++)
    {
      for(int j = 0; j < a.getNumCols(); j++)
	{
	  sum[i][j] = acopy[i][j] + bcopy[i][j];
	}
    }
  return sum;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
  Matrix acopy = Matrix(a);
  Matrix bcopy = Matrix(b);
  Matrix product = Matrix(a.getNumRows(), b.getNumCols());
  int n = a.getNumCols();
  for(int i = 0; i < a.getNumRows(); i++)
    {
      for(int j = 0; j < b.getNumCols(); j++)
	{
	  float sum = 0;
	  for(int k = 0; k < n; k++)
	    {
	      sum += acopy[i][k] * bcopy[k][j];
	    }
	  product[i][j] = sum;
	}
    }
  return product;
}

Point operator*(const Matrix& a, const Point& v)
{
  Matrix acopy = Matrix(a);
  Point vcopy = Point(v);
  Matrix vect = Matrix(3, 1);
  vect[0][0] = (float) vcopy.getX();
  vect[1][0] = (float) vcopy.getY();
  vect[2][0] = (float) vcopy.getZ();
  Matrix productM = acopy * vect;
  Point productV((int) productM[0][0], (int) productM[1][0], (int) productM[2][0]);
  return productV;
}

ostream& operator<<(ostream& out, const Matrix& a)
{
  Matrix acopy = Matrix(a);
  for(int i = 0; i < a.getNumRows(); i++)
    {
      out << '[';
      for(int j = 0; j < a.getNumCols(); j++)
	{
	  out << acopy[i][j] << ' ';
	}
      out << ']' << endl;
    }
  return out;
}
