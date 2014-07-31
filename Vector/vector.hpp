/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef vector_hpp
#define vector_hpp

// Switches
//#define CHECK_INDEX_RANGES
//#define USE_VECTOR_STATIC_COUNTERS
//#define PRINT_CONSTR_DESTR_INFO

template <class T>
class Vector
{
  //private:
protected:
#ifdef USE_VECTOR_STATIC_COUNTERS
  static int whichVector;
#endif
  int size, offset;

  T *data;

  // Private copy function
  void Copy(const Vector<T> &rhs);

public:
  // Constr. & destr.
  Vector(const int = 1);
  Vector(const int, const int);
  ~Vector();

  // Accessor
  int GetSize() const { return size; }
  int GetOffset() const { return offset; }

  // Operators
  Vector<T> & operator = (const Vector<T>&);
  Vector<T> & operator += (const Vector<T>&);
  Vector<T> & operator -= (const Vector<T>&);
  Vector<T> & operator = (const T);
  Vector<T> & operator += (const T);
  Vector<T> & operator -= (const T);
  Vector<T> & operator *= (const T);
  Vector<T> & operator /= (const T);
  inline T & operator () (const int); // throw(OutOfRange);
  inline const T & operator () (const int) const; // throw(OutOfRange) const;

  // Methods
  const double Dot(const Vector<T> &) const;
  const double Norm() const;
  void Allocate();
  void Zero();
  void Free();
  void Resize(const int);
  void Resize(const int, const int);
  void Print(char * = NULL);
  void Normalize();
  T Max() const;
  T Min() const;
  T Sum() const;
  int Find(const T) const;

  // IO
  bool Write(char *);
  bool Read(char *, const int = 0);

  // Friend function
  friend ostream& operator << <T>(ostream &, const Vector<T> &);
  friend istream& operator >> <T>(istream &, Vector<T> &);

  // Exception
  class OutOfRange
  {
  public:
    OutOfRange(char *txt = NULL){
#ifdef USE_VECTOR_STATIC_COUNTERS
      cout << endl << "# Vector<T> :: whichVector = " << whichVector << endl;
#endif
      printf("# Vector<T> :: %s; OutOfRange!\n",txt);
    }
  };
  
  // Exceptions
  class InvalidArgument{
  public:
    InvalidArgument(char *txt) {
      printf("# Vector<T> :: %s; InvalidArgument!\n",txt);
    }
  };

};

// Constructor for a vector with index in the range [0,...,s-1]
template <class T>
Vector<T> :: Vector(const int s) :
  size (s),
  offset (0)
{
#ifdef USE_VECTOR_STATIC_COUNTERS
  // Count the instances
  whichVector++;
#ifdef PRINT_CONSTR_DESTR_INFO
  cout << " vector constructor = " << whichVector << endl;
#endif
#endif

  // Allocate
  Allocate();

  // Set elements zero
  Zero();
}

// Constructor for a vector with an index range [imin,imin+1,...,imax]
template <class T>
Vector<T> :: Vector(const int imin, const int imax) :
  size (imax - imin + 1),
  offset (imin)
{
#ifdef USE_VECTOR_STATIC_COUNTERS
  // Count the instances
  whichVector++;
#endif

  Allocate();
  Zero();
  //cout << "# Vector(); size = " << size << " offset = " << offset << endl;
}

template <class T>
void Vector<T> :: Allocate()
{
  // Allocate and set to zero
  data = new T [size];
}

template <class T>
void Vector<T> :: Copy(const Vector<T> &rhs)
{
  // Size and offset
  size = rhs.GetSize();
  offset = rhs.GetOffSet();

  // Allocate space
  Allocate();

  // Copy entries
  for (int i=0; i<size; i++)
    data[i] = rhs.data[i];
}

// Make entries zero
template <class T>
void Vector<T> :: Zero()
{
  for (int i=0; i<size; i++)
    data[i] = 0;
}

// Destructor
template <class T>
Vector<T> :: ~Vector()
{
#ifdef PRINT_CONSTR_DESTR_INFO
  cout << " vector DESTRUCTOR " << whichVector << endl;
#endif
  Free();
}

// Free memory
template <class T>
void Vector<T> :: Free()
{
  if (data != NULL)
    delete [] data;
}

// Resize a vector
template <class T>
void Vector<T> :: Resize(const int newSize)
{
  if (size == newSize)
    return;
  size = newSize;
  offset = 0;
  Free();
  Allocate();
  Zero();
}

// Resize a vector to an index range [imin,imin+1,...,imax]
template <class T>
void Vector<T> :: Resize(const int imin, const int imax)
{
  size = (imax - imin + 1);
  offset = (imin);
  Free();
  Allocate();
  Zero();
}

// Parenthesis operator
template <class T>
inline T & Vector<T> :: operator () (const int i)
{
  const int index = i - offset;
#ifdef CHECK_INDEX_RANGES
  if (index >= 0 && index < size)
    return data[index];
  throw OutOfRange("operator () index overflow");
#else
  return data[index];
#endif
}

// Parenthesis operator
template <class T>
inline const T & Vector<T> :: operator () (const int i) const
{
  const int index = i - offset;
#ifdef CHECK_INDEX_RANGES
  if (index >= 0 && index < size)
    return data[index];
  throw OutOfRange("operator () index overflow");
#else
  return data[index];
#endif
}

// Equality operator
template <class T>
Vector<T> & Vector<T> :: operator = (const Vector<T> &rhs)
{
  // Checking
  if (this == &rhs)
    return *this;

  // Resize if necessary
  if (rhs.GetSize() != size)
    {
      delete [] data;
      size = rhs.GetSize();
      offset = rhs.GetOffset();
      data = new T [size];
    }

  // Copy elements
  for (int i=0; i<size; i++)
    data[i] = rhs.data[i];

  // Done
  return *this;
}

// Increment operator
template <class T>
Vector<T> & Vector<T> :: operator += (const Vector<T> &rhs)
{
  if (size != rhs.GetSize())
    throw InvalidArgument("operator += (); incompatible vectors");
  for (int i=0; i<size; i++)
    data[i] += rhs.data[i];
  return *this;
}

// Decrement operator
template <class T>
Vector<T> & Vector<T> :: operator -= (const Vector<T> &rhs)
{
  if (size != rhs.GetSize())
    throw InvalidArgument("operator -= (); incompatible vectors");
  for (int i=0; i<size; i++)
    data[i] -= rhs.data[i];
  return *this;
}

// Equality operator (makes each entry equal to given value)
template <class T>
Vector<T> & Vector<T> :: operator = (const T value)
{
  for (int i=0; i<size; i++)
    data[i] = value;
  return *this;
}

// += operator for adding a scalar
template <class T>
Vector<T> & Vector<T> :: operator += (const T value)
{
  for (int i=0; i<size; i++)
    data[i] += value;
  return *this;
}

// -= operator for subtracting a scalar
template <class T>
Vector<T> & Vector<T> :: operator -= (const T value)
{
  for (int i=0; i<size; i++)
    data[i] -= value;
  return *this;
}

// *= operator for multiplying by a scalar
template <class T>
Vector<T> & Vector<T> :: operator *= (const T value)
{
  for (int i=0; i<size; i++)
    data[i] *= value;
  return *this;
}

// /= operator for multiplying by a scalar
template <class T>
Vector<T> & Vector<T> :: operator /= (const T value)
{
  if (value == 0)
    throw InvalidArgument("operator /= (); division by zero");
  for (int i=0; i<size; i++)
    data[i] /= value;
  return *this;
}

// Dot product
template <class T>
const double Vector<T> :: Dot(const Vector<T> &v) const
{
  if (v.GetSize() != size)
    throw InvalidArgument("Dot(); incompatible vectors");
  double dotProduct = 0;
  for (int i=0; i<size; i++)
    dotProduct += data[i] * v.data[i];
  return dotProduct;
}

// Vector norm
template <class T>
const double Vector<T> :: Norm() const
{
  double norm = (double)sqrt((double)Dot(*this));
  return norm;
}

// Printing
template <class T>
void Vector<T> :: Print(char *txt)
{
  cout << txt << endl;
  for (int i=0; i<size; i++)
    cout << i << "\t" << data[i] << endl;
}

// Normalization to unity
template <class T>
void Vector<T> :: Normalize()
{
  T sum = Sum();
  if (sum == 0)
    sum = 1;
  const T norm = 1.0/sum;
  for (int i=0; i<size; i++)
    data[i] *= norm;
}

// Largest element
template <class T>
T Vector<T> :: Max() const
{
  T mmax = data[0];
  for (int i=0; i<size; i++)
    if (data[i] > mmax)
      mmax = data[i];
  return mmax;
}

// Find a given element; if found, return the (order) index of the element;
// if not found, return -1
template <class T>
int Vector<T> :: Find(const T value) const
{
  int ind = -1;
  for (int i=0; i<n; i++)
    {
      if (data(i) == value)
	{
	  ind = i;
	  break;
	}
    }
  return ind;
}

// Smallest element
template <class T>
T Vector<T> :: Min() const
{
  T mmin = data[0];
  for (int i=0; i<size; i++)
    if (data[i] < mmin)
      mmin = data[i];
  return mmin;
}

// Sum of elements
template <class T>
T Vector<T> :: Sum() const
{
  T sum = 0;
  for (int i=0; i<size; i++)
    sum += data[i];
  return sum;
}

// read a vector
template <class T>
bool Vector<T> :: Read(char *fileName, const int offSet)
{
  // file to read indexes from
  ifstream fin(fileName);
  if (!fin)
    return false;
  const int k = GetNumberOfLines(fileName);

  // resize
  if (offSet == 0)
    this->Resize(k);
  else
    this->Resize(offSet,k);

  // read the elements of the vector
  cout << "# Reading file " << fileName << "..." << flush;
  for (int i=0; i<size; i++)
    fin >> data[i];
  fin.close();
  cout << " ok." << flush << endl;

  // done
  return true;
}

// write a vector
template <class T>
bool Vector<T> :: Write(char *fileName)
{
  // file to read indexes from
  ofstream fout(fileName);
  if (!fout)
    return false;

  // write the elements of the vector
  cout << "# Writing file " << fileName << "..." << flush;
  for (int i=0; i<size; i++)
    fout << data[i] << endl;
  fout.close();
  cout << " ok." << flush << endl;

  // done
  return true;
}

// Output
template <class T>
ostream& operator << (ostream &output, const Vector<T>& theVector)
{
  for (int i=0; i<theVector.GetSize(); i++)
    output << theVector.data[i] << endl;//tab; // << endl;
  return output;
}

// Input
template <class T>
istream& operator >> (istream &input, Vector<T>& theVector)
{
  T tmp;
  for (int i=0; i<theVector.GetSize(); i++)
    if (input >> tmp)
      theVector.data[i] = tmp;
    else
      cout << "# friend istream& operator >> reading FAILURE at i = "
	   << i << endl;
  return input;
}

#endif
