/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef matrix_hpp
#define matrix_hpp

// Switches
#define CHECK_INDEX_RANGES

// Defaults
const int defaultMatrixNrow = 1;
const int defaultMatrixNcol = 1;

// class Matrix definition
template <class T>
class Matrix
{
private:
  // Number of rows and columns
  int nRow, nCol;

  // The two dimensional data array
  T ** data;

  // Private copy function
  void Copy(const Matrix<T> &);

public:
  // Constr. & destr.
  Matrix();
  Matrix(const int = defaultMatrixNrow, const int = defaultMatrixNcol);
  Matrix(const Matrix<T> &);
  ~Matrix();

  // Methods
  void Allocate();
  void Zeroes();
  void Free();
    
  Matrix<T> & Identity();
  Matrix<T> & Transpose();
  Matrix<T> & Subtract(const Matrix<T> &);
  Matrix<T> & Add(const Matrix<T> &);


  // Inline methods
  inline const int NRow() const { return nRow; }
  inline const int NCol() const { return nCol; }
  
  // Output
  friend ostream& operator << <T>(ostream &, const Matrix<T> &);
  void Print(char * = NULL);

  // Operators
  inline T & operator () (const int, const int);
  inline T const & operator () (const int, const int) const;
  Matrix<T> & operator = (const Matrix<T> &);
  Matrix<T> & operator = (const T);
  Matrix<T> operator * (const Matrix<T> &) const;
  Matrix<T> operator * (const T) const;

  // Exceptions
  class OutOfRange{
  public:
    OutOfRange(char *txt) {
      printf("# Matrix<T> :: %s; OutOfRange!\n",txt);
    }
  };

  // Exceptions
  class InvalidArgument{
  public:
    InvalidArgument(char *txt) {
      printf("# Matrix<T> :: %s; InvalidArgument!\n",txt);
    }
  };
};

// Constructor
template <class T>
Matrix<T> :: Matrix(const int nrow, const int ncol) :
  nRow (nrow),
  nCol(ncol)
{
  // Allocate memory
  Allocate();

  // Zero entries
  Zeroes();
}

// Constructor
template <class T>
Matrix<T> :: Matrix(const Matrix<T> &rhs) :
  nRow (rhs.NRow()),
  nCol(rhs.NCol())
{
  // Allocate memory
  Allocate();

  // Copy entries
  this->Copy(rhs);
}

// Destructor
template <class T>
Matrix<T> :: ~Matrix()
{
  // Free memory
  Free();
}

// Allocation
template <class T>
void Matrix<T> :: Allocate()
{
  data = new T*[nRow];
  for (int i=0; i<nRow; i++)
    data[i] = new T[nCol];
}

// Initialization
template <class T>
void Matrix<T> :: Zeroes()
{
  for (int i=0; i<nRow; i++)
    for (int j=0; j<nCol; j++)
      data[i][j] = 0;
}

// Free the memory
template <class T>
void Matrix<T> :: Free()
{
  if (data != NULL)
    {
      for (int i=nRow-1; i>=0; i--)
	delete [] data[i];
      delete [] data;
      data = NULL;
    }
}

// Bracket operator
template <class T>
inline T & Matrix<T> :: operator () (const int i, const int j)
{
#ifdef CHECK_INDEX_RANGES
  if (i > nRow)
    throw OutOfRange("operator(); row index incorrect");
  if (j > nCol)
    throw OutOfRange("operator(); column index incorrect");
#endif
  return data[i][j];
}

// Bracket operator
template <class T>
inline const T & Matrix<T> :: operator () (const int i, const int j) const
{
#ifdef CHECK_INDEX_RANGES
  if (i > nRow)
    throw OutOfRange("operator(); row index incorrect");
  if (j > nCol)
    throw OutOfRange("operator(); column index incorrect");
#endif
  return data[i][j];
}

// Equality operator
template <class T>
Matrix<T> & Matrix<T> :: operator = (const Matrix<T> &rhs)
{
  if (this == &rhs)
    return *this;
  Free();
  this->Copy(rhs);
  return *this;
}

// Equality operator (all elements equal to 'val')
template <class T>
Matrix<T> & Matrix<T> :: operator = (const T val)
{
  for (int i=0; i<nRow; i++)
    for (int j=0; j<nCol; j++)
      data[i][j] = val;
  return *this;
}

// Matrix multiplication
template <class T>
Matrix<T> Matrix<T> :: operator * (const Matrix<T> &arg) const
{
  if (nCol != arg.NRow())
    throw InvalidArgument("operator *; incompatible matrices");
  Matrix<T> result(nRow,arg.NCol());
  for (int i=0; i<nRow; i++)
    for (int j=0; j<arg.NCol(); j++)
      {
	T sum = 0;
	for (int k=0; k<nCol; k++)
	  sum += (*this)(i,k) * arg(k,j);
	result(i,j) = sum;
      }

  return result;
}

// Matrix multiplication (with a scalar)
template <class T>
Matrix<T> Matrix<T> :: operator * (const T val) const
{
  Matrix<T> result(nRow,nCol);
  for (int i=0; i<nRow; i++)
    for (int j=0; j<nCol; j++)
      result(i,j) = (*this)(i,j) * val;

  return result;
}

// Transpose
template <class T>
Matrix<T>& Matrix<T> :: Transpose()
{
  // Checking
  if (nRow != nCol)
    Error("# Matrix<T> :: Transpose(); nCol != nRow");

  // A temporary matrix
  Matrix<T> tmp(*this);

  // Take the transpose
  for (int i=0; i<nRow; i++)
    for (int j=0; j<nCol; j++)
      data[i][j] = tmp(j,i);

  // Done
  return *this;
}

// Transpose
template <class T>
Matrix<T>& Matrix<T> :: Identity()
{
  // Checking
  if (nRow != nCol)
    Error("# Matrix<T> :: Identity(); nCol != nRow");

  // Set all elements to zero
  Zeroes();

  // Set elements
  for (int i=0; i<nRow; i++)
    data[i][i] = 1;

  // Done
  return *this;
}

// Subtract 'Matrix<T> m' from 'this' 
template <class T>
Matrix<T>& Matrix<T> :: Subtract(const Matrix<T> &m)
{
  // Checking
  if (nRow != m.NRow())
    Error("# Matrix<T> :: Subtract(); nRow disagreement");
  if (nCol != m.NCol())
    Error("# Matrix<T> :: Subtract(); nCol disagreement");

  // Subtract the entries
  for (int i=0; i<nRow; i++)
    for (int j=0; j<nCol; j++)
      data[i][j] -= m(i,j);

  // Done
  return *this;
}

// Add 'Matrix<T> m' to 'this' 
template <class T>
Matrix<T>& Matrix<T> :: Add(const Matrix<T> &m)
{
  // Checking
  if (nRow != m.NRow())
    Error("# Matrix<T> :: Subtract(); nRow disagreement");
  if (nCol != m.NCol())
    Error("# Matrix<T> :: Subtract(); nCol disagreement");

  // Subtract the entries
  for (int i=0; i<nRow; i++)
    for (int j=0; j<nCol; j++)
      data[i][j] += m(i,j);

  // Done
  return *this;
}

// Private copy function
template <class T>
void Matrix<T> :: Copy(const Matrix<T> &rhs)
{
  // Number of rows and columns
  nRow = rhs.NRow();
  nCol = rhs.NCol();

  // Allocate space
  Allocate();

  // Copy entries
  for (int i=0; i<nRow; i++)
    for (int j=0; j<nCol; j++)
      data[i][j] = rhs(i,j);
}

// Printing
template <class T>
void Matrix<T> :: Print(char *txt)
{
  cout << "\n# " << txt << ":" << endl;
  for (int j=0; j<nCol; j++)
    {
      for (int i=0; i<nRow; i++)
	cout << data[i][j] << " ";
      cout << endl;
    }
  cout << endl;
}

// Output using ostream operator << overload
template <class T>
ostream& operator << (ostream &output, const Matrix<T>& theMatrix)
{
  output << endl;
  for (int j=0; j<theMatrix.NCol(); j++)
    {
      for (int i=0; i<theMatrix.NRow(); i++)
	output << theMatrix(i,j) << " ";
      output << endl;
    }
  output << endl;
  return output;
}

#endif
