/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Vector/vector.hpp"
#include "util.hpp"
// a tab spacing manipulator
ostream & tab(ostream &astream)
{
  return (astream << '\t');
}

// a spacing manipulator
ostream & space(ostream &astream)
{
  return (astream << ' ');
}

// Returns the exponent if l is a power of 2
// in the range [2,...,MAX_POWER], else returns -1
int PowerOfTwo(const int l)
{
  int cnt = 0, power = 1;

  while (cnt < MAX_POWER)
    {
      cnt++;
      power *= 2;
      if (power == l)
	break;
    }

  //printf("l=%d pow=%d cnt=%d\n",l,power,cnt);

  if ( (cnt > 0) && (cnt < MAX_POWER) )
    return cnt;
  else
    return -1;
}

// Get the size (either size_, or the next power of two)
int NextPowerOfTwo(const int size_)
{
  int size = 1;

  while (size < size_)
    size <<= 0x01;

  return size;
}


// Returns the exponent if l is a power of 3
// in the range [3,...,MAX_POWER], else returns -1
int PowerOfThree(const int l)
{
  int cnt = 0, power = 1;

  while (cnt < MAX_POWER)
    {
      cnt++;
      power *= 3;
      if (power == l)
	break;
    }

  //printf("l=%d pow=%d cnt=%d\n",l,power,cnt);

  if ( (cnt > 0) && (cnt < MAX_POWER) )
    return cnt;
  else
    return -1;
}

// Error handling
void Error(char errorText[])
{
  printf("# Error: %s\n",errorText);
  exit(1);
}

// Minimum of a vector
double Min(double *v, const int n)
{
  double vmin = v[0];
  for (int i=1; i<n; i++)
    if (v[i] < vmin)
      vmin = v[i];
  return vmin;
}

// Maximum of a vector
double Max(double *v, const int n)
{
  double vmax = v[0];
  for (int i=1; i<n; i++)
    if (v[i] > vmax)
      vmax = v[i];
  return vmax;
}

// Minimum of a vector
float Min(float *v, const int n)
{
  float vmin = v[0];
  for (int i=1; i<n; i++)
    if (v[i] < vmin)
      vmin = v[i];
  return vmin;
}

// Maximum of a vector
float Max(float *v, const int n)
{
  float vmax = v[0];
  for (int i=1; i<n; i++)
    if (v[i] > vmax)
      vmax = v[i];
  return vmax;

}

// Minimum of a vector
int Min(int *v, const int n)
{
  int vmin = v[0];
  for (int i=1; i<n; i++)
    if (v[i] < vmin)
      vmin = v[i];
  return vmin;
}

// Maximum of a vector
int Max(int *v, const int n)
{
  int vmax = v[0];
  for (int i=1; i<n; i++)
    if (v[i] > vmax)
      vmax = v[i];
  return vmax;

}

// Normalize the 1st and 2nd moments of the sampled data
void NormalizeMoments(double *m1, double *m2, const int l, const int cnt)
{
  if (cnt != 0)
    {
      const double div = 1.0/(double)cnt;
      for (int i=0; i<l; i++)
	{
	  m1[i] *= div;
	  m2[i] *= div;
	}
    }
  else
    printf("# Error in normalization; counter zero!\n");
}

// Copy values from v2 to v1
void CopyVector(double *v1, double *v2, const int l)
{
  for (int i=0; i<l; i++)
    v1[i] = v2[i];
}

// Copy values from v2 to v1
void CopyVector(int *v1, int *v2, const int l)
{
  for (int i=0; i<l; i++)
    v1[i] = v2[i];
}

// Pause for debugging
void Pause()
{
  char s[32];
  printf("# Press <enter> to continue, <q> to quit. ");
  scanf("%c",s);
  if (s[0] == 'q') exit(1);
}

// Quit?
bool Quit()
{
  int quit;
  printf("# Quit (0/1)? ");
  scanf("%d",&quit);
  if (quit == 0)
    return false;
  else
    return true;
}

// Returns the sum of the elements of the given vector
int Sum(int *v, const int n)
{
  int sum = 0;
  for (int i=0; i<n; i++)
    sum += v[i];
  return sum;
}

// Returns the sum of the elements of the given vector
float Sum(float *v, const int n)
{
  float sum = 0;
  for (int i=0; i<n; i++)
    sum += v[i];
  return sum;
}

// Returns the sum of the elements of the given vector
double Sum(double *v, const int n)
{
  double sum = 0;
  for (int i=0; i<n; i++)
    sum += v[i];
  return sum;
}

// Pick the index from the pdf
int IndexFromPdf(const double *pdf, const double prnd, const int pdfcnt)
{
  int n = 0;
  double p = 0.0;

  while ( (p < prnd) && (n < pdfcnt) )
    {
      p += pdf[n++];
    }
  return n-1;
}

// Normalize vector with the given counter
void NormalizeVector(double *v, const int l, const int cnt)
{
  if (cnt != 0)
    {
      const double div = 1.0/(double)cnt;
      for (int i=0; i<l; i++)
	v[i] *= div;
    }
  else
    printf("# Error in normalization; counter zero!\n");
}

// a 2d array of doubles
double ** Dmatrix(const int nrows, const int ncols)
{
  double **m = new double *[nrows];
  for (int i=0; i<nrows; i++)
    m[i] = new double [ncols];
  return m;
}

// a 2d array of floats
float ** Fmatrix(const int nrows, const int ncols)
{
  float **m = new float *[nrows];
  for (int i=0; i<nrows; i++)
    m[i] = new float [ncols];
  return m;
}

// a 2d array of ints
int ** Imatrix(const int nrows, const int ncols)
{
  int **m = new int *[nrows];
  for (int i=0; i<nrows; i++)
    m[i] = new int [ncols];
  return m;
}

// free allocated memory
void FreeMatrix(double **m, const int nrows, const int ncols)
{
  if (m != NULL)
    {
      for (int i=nrows-1; i>=0; i--)
	delete [] m[i];
      delete m;
      m = NULL;
    }
}


// free allocated memory
void FreeMatrix(float **m, const int nrows, const int ncols)
{
  if (m != NULL)
    {
      for (int i=nrows-1; i>=0; i--)
	delete [] m[i];
      delete m;
      m = NULL;
    }
}


// free allocated memory
void FreeMatrix(int **m, const int nrows, const int ncols)
{
  if (m != NULL)
    {
      for (int i=nrows-1; i>=0; i--)
	delete [] m[i];
      delete m;
      m = NULL;
    }
}

// Normalize to unity
void Normalize(double *v, const int n)
{
  double factor = Sum(v,n);

  if (factor < CALC_EPS)
    Error("Division by zero in Normalize()");

  factor = 1.0/factor;
  for (int i=0; i<n; i++)
    v[i] *= factor;
}

// Set the values to the vector
void SetValues(int *a, const int n, const int val)
{
  for (int i=0; i<n; i++)
    a[i] = val;
}

// Set the values
void SetValues(int **a, const int I, const int J, const int val)
{
  for (int i=0; i<I; i++)
    for (int j=0; j<J; j++)
      a[i][j] = val;
}

// Set the elements to given value
void SetValues(int ***a, const int I, const int J, const int K,
	       const int v)
{
  for (int i=0; i<I; i++)
    for (int j=0; j<J; j++)
      for (int k=0; k<K; k++)
	a[i][j][k] = v;
}

// Set the values to the vector
void SetValues(double *a, const int n, const double val)
{
  for (int i=0; i<n; i++)
    a[i] = val;
}

// Set the (constant) value to the matrix elements
void SetValues(double **a, const int I, const int J, const double v)
{
  for (int i=0; i<I; i++)
    for (int j=0; j<J; j++)
      a[i][j] = v;
}

// Set the (constant) value
void SetValues(double ***a, const int I, const int J, const int K,
	       const double v)
{
  for (int i=0; i<I; i++)
    for (int j=0; j<J; j++)
      for (int k=0; k<K; k++)
	a[i][j][k] = v;
}

// Set the values to the vector
void SetValues(float *a, const int n, const float val)
{
  for (int i=0; i<n; i++)
    a[i] = val;
}

// Set the (constant) value to the matrix elements
void SetValues(float **a, const int I, const int J, const float v)
{
  for (int i=0; i<I; i++)
    for (int j=0; j<J; j++)
      a[i][j] = v;
}

// Set the (constant) value
void SetValues(float ***a, const int I, const int J, const int K,
	       const float v)
{
  for (int i=0; i<I; i++)
    for (int j=0; j<J; j++)
      for (int k=0; k<K; k++)
	a[i][j][k] = v;
}

// Allocate a 3d integer array
int *** Iarray3D(const int lx, const int ly, const int lz)
{
  int ***a = new int **[lx];
  for (int i=0; i<lx; i++)
    {
      a[i] = new int *[ly];
      for (int j=0; j<ly; j++)
	a[i][j] = new int [lz];
    }
  return a;
}

// Free memory allocated for a 3d integer array
void FreeArray3D(int ***a, const int lx, const int ly, const int lz)
{
  for (int i=lx-1; i>=0; i--)
    {
      for (int j=ly-1; j>=0; j--)
	delete [] a[i][j];
      delete [] a[i];
    }
  delete [] a;
}

// Allocate a 3d float array
float *** Farray3D(const int lx, const int ly, const int lz)
{
  float ***a = new float **[lx];
  for (int i=0; i<lx; i++)
    {
      a[i] = new float *[ly];
      for (int j=0; j<ly; j++)
	a[i][j] = new float [lz];
    }
  return a;
}

// Free memory allocated for a 3d float array
void FreeArray3D(float ***a, const int lx, const int ly, const int lz)
{
  for (int i=lx-1; i>=0; i--)
    {
      for (int j=ly-1; j>=0; j--)
	delete [] a[i][j];
      delete [] a[i];
    }
  delete [] a;
}

// Allocate a 3d double array
double *** Darray3D(const int lx, const int ly, const int lz)
{
  double ***a = new double **[lx];
  for (int i=0; i<lx; i++)
    {
      a[i] = new double *[ly];
      for (int j=0; j<ly; j++)
	a[i][j] = new double [lz];
    }
  return a;
}

// Free memory allocated for a 3d double array
void FreeArray3D(double ***a, const int lx, const int ly, const int lz)
{
  for (int i=lx-1; i>=0; i--)
    {
      for (int j=ly-1; j>=0; j--)
	delete [] a[i][j];
      delete [] a[i];
    }
  delete [] a;
}

// Printing
void Print3D(int ***a, const int lx, const int ly, const int lz, char *txt)
{
  printf("\n# %s:\n",txt);
  for (int k=lz-1; k>=0; k--)
    {
      printf("\n# k = %d\n",k);
      for (int j=ly-1; j>=0; j--)
	{
	  for (int i=0; i<lx; i++)
	    printf("%3d ",a[i][j][k]);
	  printf("\n");
	}
      printf("\n");
    }
}

// Printing
void Print(const int x, const int y, const bool newLine)
{
  cout << "(x,y) = (" << x << "," << y << ") ";
  if (newLine)
    cout << endl;
}

// Printing
void Print(const int x, const int y, const int z, const bool newLine)
{
  cout << "(x,y,z) = (" << x << "," << y << "," << z << ") ";
  if (newLine)
    cout << endl;
}

// Get a number from cmd line
int GetInt(char *txt)
{
  int i;
  cout << "# Give an integer variable " << txt << " ";
  cin >> i;
  return i;
}

// Get a number from cmd line
float GetFloat(char *txt)
{
  float f;
  cout << "# Give a float variable " << txt << " ";
  cin >> f;
  return f;
}

// Get a number from cmd line
double GetDouble(char *txt)
{
  double d;
  cout << "# Give a double variable " << txt << " ";
  cin >> d;
  return d;
}

// Returns true for yes and false for no
bool YesOrNo(char *txt)
{
  int yn;
  cout << "# " << txt << " (1/0)? ";
  cin >> yn;
  if (yn == 0)
    return false;
  else
    return true;
}


// Printing
void Print(double *v, const int n, char *txt)
{
  printf("\n# %s:\n",txt);
  for (int i=0; i<n; i++)
    printf("%d\t%g\n",i,v[i]);
  printf("\n");
}

// Printing
void Print(double *v1, double *v2, const int n, char *txt)
{
  printf("\n# %s:\n",txt);
  for (int i=0; i<n; i++)
    printf("%g\t%g\n",v1[i],v2[i]);
  printf("\n");
}

// Printing
void Print(int *v, const int n, char *txt)
{
  printf("\n# %s:\n",txt);
  for (int i=0; i<n; i++)
    printf("%d\t%d\n",i,v[i]);
  printf("\n");
}

// Printing
void Print(int **a, const int lx, const int ly, char *txt)
{
  printf("\n# %s:\n",txt);
  for (int i=0; i<lx; i++)
    {
      for (int j=0; j<lx; j++)
	printf("%2d ",a[i][j]);
      printf("\n");
    }
  printf("\n");
}

// Printing
void Print(double *v1, int *v2, const int n, char *txt)
{
  printf("\n# %s:\n",txt);
  for (int i=0; i<n; i++)
    printf("%g\t%d\n",v1[i],v2[i]);
  printf("\n");
}

// returns a character array of length 'fl' that contains
// the 'number' with possible initial zeroes 
char *IntToChar(const int number, const int fl)
{
  char *cn = new char[fl+1];
  char charnum[11] = "0123456789";
  int absn = Abs(number);
  int dec = (int)pow( 10.0,((double)(fl-1)) );

  // Check that the number doesn't exceed the field length
  if ( absn >= (dec*10) ) Error("IntToChar(); Increase field length!");

  // Loop over the field length and pick the characters
  // corresponding to each dec. in the number
  for (int i=0; i<fl; i++)
    {
      // Pick i'th character from the number
      const int j = absn/dec;
      // Copy to cn[]
      cn[i] = charnum[j];
      // Subtract the part corresponding to i'th character from the number
      absn -= (j*dec);
      // Decrease dec by a factor of 10
      dec /= 10;
    }

  // Done
  return cn;
}

// Check the number of rows and columns in the given data file.
// Assuming that each column is separated by a whitespace, comma or tab.
void GetDataFileSize(char *fname, int &nrow_, int &ncol_)
{
  ifstream fin(fname);

  // Read data 
  if (fin)
    {
      char ch, oldch = '\n';
      int nrow = 0, ncol = 0, colcnt = 1;
      while (fin.get(ch))
	{
	  // Remove spaces from the start of the line
	  if (oldch == '\n')
	    while ( (ch = fin.get()) != ' ' && ch != ',' && ch != '\t' );
	  
	  // Check for a new column (oldch is used later to check
	  // for possible extra spaces at the end of line)
	  if ( IsSeparation(ch) )
	    {
	      oldch = ' ';
	      colcnt++;
	      // Wind until the next non-separating character
	      do fin.get(ch); while ( IsSeparation(ch) );
	    }
	  else
	    oldch = ch;

	  // Set column counter zero if a new line
	  if (ch == '\n')
	    {
	      // Increase row counter
	      nrow++;

	      // Decrease colcnt if the last character before
	      // the newline was a separation char
	      if ( IsSeparation(oldch) )
		colcnt--;

	      // Check for mismatched column counts
	      if ( (nrow > 1) && (colcnt != ncol) )
		Error("GetDataFileSize(): number of columns do not match.");

	      // Store to ncol and reset colcnt
	      ncol = colcnt;
	      colcnt = 1;
	    }
	  // Store ch to oldch for checking
	  oldch = ch;
	}

      // Return the values
      nrow_ = nrow;
      ncol_ = ncol;
    }
  else
    {
      // Mark the size negative
      nrow_ = -1;
      ncol_ = -1;
      cout << "# File " << fname <<" doesn't exist" << endl;
    }
}

// Check if the given character is separates numbers
bool IsSeparation(char ch)
{
  if ( (ch == ' ') || (ch == ',') || (ch == '\t') )
    return true;
  else
    return false;
}


// Check the number of rows and columns in the given data file.
// Assuming that each column is separated by a whitespace, comma or tab.
// Further, it is assumed that the matrix is written to file in order:
// 
//  -> i
// |
// v j
//
void GetDataFileSize(int &nrow_, int &ncol_,
		     const char *fname, const char comment)
{
  // Declarations
  ifstream fin(fname);

  // Read data 
  if (fin)
    {
      // The buffer
      const int bufferSize = 1024;
      char *buffer = new char[bufferSize];

      // Counters
      int ncol = 0, nrow = 0, nrprev = 0;
      while (fin.getline(buffer,bufferSize))
	{
	  // Exclude comment lines
	  if (buffer[0] != comment)
	    {
	      // Mark the line end to the buffer
	      int lineSize = strlen(buffer);
	      buffer[lineSize] = '\n';

	      // Increase the row counter
	      ncol++;
      
	      // Count the number of columns
	      nrprev = nrow;
	      nrow = GetNumberOfItems(buffer,lineSize,IsSeparation);

	      // Check for discrepancy in column counts
	      if ( (ncol > 1) && (nrow != nrprev) )
		Error("CheckFileSize(): number of columns do not match.");
	    }
	}

      // Return values
      ncol_ = ncol;
      nrow_ = nrow;
    }
  else
    {
      // Mark the size negative
      ncol_ = -1;
      nrow_ = -1;
      cout << "# File " << fname << " doesn't exist" << endl;
    }
}

// Skip separation characters in the char *
void SkipSeparation(char *chr, int &cnt, bool (*IsSeparation)(char))
{
  while ( IsSeparation(chr[cnt]) )
    cnt++;
}


// Skip separation characters in the char *
void SkipSeparation(char *chr, int &cnt)
{
  while ( IsSeparation(chr[cnt]) )
    cnt++;
}

// Count the number of items in the buffer separated by separation marks
int GetNumberOfItems(char *chr, const int size,
		     bool (*IsSeparation)(char))
{
  // Counter for the scanning of the vector
  int items = 1, cnt = 0;
      
  // Wind until the first non-separating character
  SkipSeparation(chr,cnt,IsSeparation);

  // Count the number of columns
  while ( cnt < size)
    {
      // Check for separation
      if (IsSeparation(chr[cnt]))
	{
	  items++;
	  SkipSeparation(chr,cnt,IsSeparation);
	}

      // Increase counter
      cnt++;
    }

  // Decrease colcnt if the last character before
  // the newline was a separation char
  if ( IsSeparation(chr[size-1]) )
    items--;

  // Done
  return items;
}

// Counts the number of lines in file
int GetNumberOfLines(const char *fileName)
{
  // Declarations
  ifstream fin(fileName);
  int nlines = 0;

  // Read data 
  if (fin)
    {
      // The buffer
      const int bufferSize = 1024;
      char *buffer = new char[bufferSize];

      // Counters
      while (fin.getline(buffer,bufferSize))
	nlines++;
      delete [] buffer;
      fin.close();
	
    }
  else
    cout << "# Unable to open file " << fileName << endl;
  return nlines;
}

// Extracts numbers from a string
int ExtractNumbers(char * mystr , double  *numbers, int & ntot)
{
  ntot=0;
  char *test; 
  test=strtok (mystr," ");
  while (test != NULL)
    {
      // you can also have more than a single space between the numbers
      if (*test != ' ')
	numbers[ntot++] = atof(test);
      test=strtok(NULL," ");
    }
  return ntot;
}

// Extracts the n'th number (integer type) from the string
int ExtractInt(char * mystr, const int n)
{
  int ntot=0;
  char *test; 
  test=strtok (mystr," ");
  while (test != NULL)
    {
      // you can also have more than a single space between the numbers
      if (*test != ' ')
	{
	  if (ntot == n)
	    return (atoi(test));
	  ntot++;
	}
      test=strtok(NULL," ");
    }
  return 0;
}

// Fill a string with given numbers
int NumbersToString(char * mystr , double  *numbers, const int n)
{
  char *number = new char[64];
  for (int i=0; i<n; i++)
    {
      sprintf(number,"%g ",numbers[i]);
      strcat(mystr,number);
    }
  strcat(mystr,"\n");
  delete [] number;
  return 0;
}

// QuickSort from NR. Assumes that arr[] is in the range 1,...,n!
void Sort(const int n, double arr[])
{
  const int M = 7;
  const int NSTACK = 50;
  int i, ir = n, j, k, l = 1;
  int jstack = 0;
  int *istack;
  float a;

  // Stack
  istack = new int [NSTACK];
  istack--;

  // Looping
  for (;;)
    {
      if (ir-l < M)
	{
	  for (j=l+1;j<=ir;j++)
	    {
	      a = arr[j];
	      for (i=j-1;i>=1;i--)
		{
		  if (arr[i] <=  a) break;
		  arr[i+1] = arr[i];
		}
	      arr[i+1] = a;
	    }
	  if (jstack  ==  0) break;
	  ir = istack[jstack--];
	  l = istack[jstack--];
	}
      else
	{
	  k = (l+ir) >> 1;
	  Swap(arr[k],arr[l+1]);
	  if (arr[l+1] > arr[ir])
	    {
	      Swap(arr[l+1],arr[ir]);
	    }
	  if (arr[l] > arr[ir])
	    {
	      Swap(arr[l],arr[ir]);
	    }
	  if (arr[l+1] > arr[l])
	    {
	      Swap(arr[l+1],arr[l]);
	    }
	  i = l+1;
	  j = ir;
	  a = arr[l];
	  for (;;)
	    {
	      do i++; while (arr[i] < a);
	      do j--; while (arr[j] > a);
	      if (j < i) break;
	      Swap(arr[i],arr[j]);
	    }
	  arr[l] = arr[j];
	  arr[j] = a;
	  jstack += 2;
	  if (jstack > NSTACK)
	    Error("NSTACK too small in sort.");
	  if (ir-i+1 >= j-l)
	    {
	      istack[jstack] = ir;
	      istack[jstack-1] = i;
	      ir = j-1;
	    }
	  else
	    {
	      istack[jstack] = j-1;
	      istack[jstack-1] = l;
	      l = i;
	    }
	}
    }

  // Free stack
  delete [] ++istack;
}

// Print number's bits
void PrintBits(const int number, const int n)
{
  cout << " number = " << number << " bits = ";
  for (int i=n-1; i>=0; i--)
    {
      if ((number & (0x01<<i)))
	cout << 1;
      else
	cout << 0;
    }
  cout << endl;
}

// read a vector
double *ReadVector(char *file, int &length)
{

  // get the number of items in the data file
  length = GetNumberOfLines(file);

  // regular array for elements  
  double *items = new double[length];

  // read data
  int i=0;
  ifstream fin(file);
  while ( i < length )
    {
      double item;
      fin >> item;
      items[(i++)] = item;
    }
  fin.close();

  // done
  return items;
}
