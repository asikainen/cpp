/***
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef util_hpp
#define util_hpp

//template <class T>
//class Point;

// Definitions
#ifndef MAX_POWER
#define MAX_POWER 15
#endif

#ifndef CALC_EPS
#define CALC_EPS 1.0E-12
#endif

// Prototypes
ostream & tab(ostream &);
ostream & space(ostream &);

char *IntToChar(const int, const int);

bool Quit();
bool YesOrNo(char *);
bool IsSeparation(char);

int NextPowerOfTwo(const int);
int PowerOfTwo(const int);
int PowerOfThree(const int);
int Min(int *, const int);
int Max(int *, const int);
int Sum(int *, const int);
int IndexFromPdf(const double *, const double, const int);
int GetInt(char * = "variable");
int GetNumberOfItems(char *, const int, bool (*)(char));
int GetNumberOfLines(const char *fileName);

float Min(float *, const int);
float Max(float *, const int);
float Sum(float *, const int);
float GetFloat(char * = "variable");

double Min(double *, const int);
double Max(double *, const int);
double Sum(double *, const int);
double GetDouble(char * = "variable");

void Normalize(double *, const int);
void NormalizeMoments(double *, double *, const int, const int);
void NormalizeVector(double *, const int, const int);
void SetValues(int *, const int, const int = 0);
void SetValues(int **, const int, const int, const int = 0);
void SetValues(int ***, const int, const int, const int, const int = 0);
void SetValues(double *, const int, const double = 0.0);
void SetValues(double **, const int, const int, const double = 0.0);
void SetValues(double ***, const int, const int, const int,
	       const double = 0.0);
void SetValues(float *, const int, const float = 0.0);
void SetValues(float **, const int, const int, const float = 0.0);
void SetValues(float ***, const int, const int, const int,
	       const float = 0.0);
void CopyVector(double *, double *, const int);
void CopyVector(int *, int *, const int);
void Error(char * = "(default)");
void Print(double *, const int, char *);
void Print(double *, double *, const int, char *);
void Print(int *, const int, char *);
void Print(int **, const int, const int, char * = NULL);
void Print3D(int ***, const int, const int, const int,
	     char * = "a 3D array");
void Print(double *, int *, const int, char *);
void Pause();
void Print(const int, const int, const bool = false);
void Print(const int, const int, const int, const bool = false);
void GetDataFileSize(char *, int &, int &);
void GetDataFileSize(int &, int &, const char *, const char = '#');
void SkipSeparation(char *, int &);
void SkipSeparation(char *, int &, bool (*)(char));
void Sort(const int, double []);
void PrintBits(const int, const int);

int ExtractNumbers(char *, double *, int &);
int ExtractInt(char *, const int);
int NumbersToString(char *, double *, const int);

double *ReadVector(char *, int &);

int **Imatrix(const int, const int);
float **Fmatrix(const int, const int);
double **Dmatrix(const int, const int);

void FreeMatrix(double **, const int, const int);
void FreeMatrix(float **, const int, const int);
void FreeMatrix(int **, const int, const int);

int ***Iarray3D(const int, const int, const int);
float ***Farray3D(const int, const int, const int);
double ***Darray3D(const int, const int, const int);

void FreeArray3D(int ***, const int, const int, const int);
void FreeArray3D(float ***, const int, const int, const int);
void FreeArray3D(double ***, const int, const int, const int);

// Inline functions

// Absolute value
inline int Abs(int i)
{
  return ( i >= 0 ? i : (-i) );
}

// Absolute value
inline float Abs(float f)
{
  return ( f >= 0 ? f : (-f) );
}

// Absolute value
inline double Abs(double d)
{
  return ( d >= 0 ? d : (-d) );
}

// Maximum of two
inline int Max(int a, int b)
{
  return (a > b ? a : b);
}

// Maximum of two
inline float Max(float a, float b)
{
  return (a > b ? a : b);
}

// Maximum of two
inline double Max(double a, double b)
{
  return (a > b ? a : b);
}

// Minimum of two
inline int Min(int a, int b)
{
  return (a < b ? a : b);
}

// Minimum of two
inline float Min(float a, float b)
{
  return (a < b ? a : b);
}

// Minimum of two
inline double Min(double a, double b)
{
  return (a < b ? a : b);
}

// Average of two
inline int Ave(int a, int b)
{
  return ((a + b) / 2);
}

// Average of two
inline float Ave(float a, float b)
{
  return (0.5 * (a + b));
}

// Average of two
inline double Ave(double a, double b)
{
  return (0.5 * (a + b));
}


// Check the sign for 'a' according to that of 'b'
inline int Sign(int a, int b)
{
  return ((b) >= 0.0 ? Abs(a) : -Abs(a));
}

// Check the sign for 'a' according to that of 'b'
inline float Sign(float a, float b)
{
  return ((b) >= 0.0 ? Abs(a) : -Abs(a));
}

// Check the sign for 'a' according to that of 'b'
inline double Sign(double a, double b)
{
  return ((b) >= 0.0 ? Abs(a) : -Abs(a));
}

// Statistical error; div = 1/N, where
// N is the number of samples.
inline double StatError(const double m1, const double m2, const double div)
{
  double error = m2 - m1 * m1;

  if (error > CALC_EPS)
    error=sqrt(error*div);
  else
    error=0.0;

  return error;
}

// Uniformly distributed random number in interval [rndMin,rndMax]
inline int UniformRnd(const float rnd, const int rndMin, const int rndMax)
{
  return (int)(rndMin + (rndMax + 1 - rndMin)*rnd);
}

// Uniformly distributed random number in interval [0,rndMax[
inline int UniformRnd(const float rnd, const int rndMax)
{
  return (int)((rndMax+1)*rnd);
}

// Uniformly distributed random number in interval ]rndMin,rndMax[
inline float UniformRnd(const float rnd, const float rndMin,
			const float rndMax)
{
  return (float)(rndMin + (rndMax - rndMin)*rnd);
}

// Uniformly distributed random number in interval ]0,rndMax[
inline float UniformRnd(const float rnd, const float rndMax)
{
  return (float)(rndMax*rnd);
}

// Uniformly distributed random number in interval ]rndMin,rndMax[
inline double UniformRnd(const float rnd, const double rndMin,
			 const double rndMax)
{
  return (double)(rndMin + (rndMax - rndMin)*rnd);
}

// Uniformly distributed random number in interval ]0,rndMax[
inline double UniformRnd(const float rnd, const double rndMax)
{
  return (double)(rndMax*rnd);
}

// Forward discrete derivative (vector to be differentiated: v,
// inverse dx: idx). NOTE: no bounds checking!
inline double Dxf(const int i, const double *v, const double idx)
{
  return (v[i+1] - v[i])*idx;
}

// Backward discrete derivative (vector to be differentiated: v,
// inverse dx: idx). NOTE: no bounds checking!
inline double Dxb(const int i, const double *v, const double idx)
{
  return (v[i] - v[i-1])*idx;
}

// Central discrete derivative (vector to be differentiated: v,
// inverse dx*2: idx2). NOTE: no bounds checking!
inline double Dxc(const double *v, const int i,  const double idx2)
{
  return (v[i+1] - v[i-1])*idx2;
}

// Discrete 2nd order derivative (vector to be differentiated: v,
// inverse dx^2: idxsq). NOTE: no bounds checking!
inline double Dx2(const int i, const double *v, const double idxsq)
{
  return (v[i+1] - 2.0*v[i] + v[i-1])*idxsq;
}

// Power 2
inline double Square(const double x)
{
  return x*x;
}

// Power 3
inline double Cube(const double x)
{
  return x*x*x;
}

// Periodic integers
inline int PBC(const int x, const int l)
{
  if (x >= l)
    return x-l;
  else if (x < 0)
    return x+l;
  else
    return x;
}

// An integer folded to [0,l[. Function assumes that
// the argument x is in range [-l+1,l-1].
inline int Fold(const int x, const int l)
{
  // x -= lx*floor(x*ilx + 0.5);
  const int hl = l>>1;
  if (x <= -hl)
    return l+x;
  else if (x >= hl)
    return -l+x;
  else
    return x;
}

// An float folded to [0,l[
inline float Fold(const float x, const float l)
{
  return  x - l*floor(x/l + 0.5);
}

// An double folded to [0,l[
inline double Fold(const double x, const double l)
{
  return  x - l*floor(x/l + 0.5);
}

// The gradient (forward; assuming that x,x-1,x+1 etc are in the proper range
inline void GradientF(double **m, const int x, const int y,
		      const double dxinv, const double dyinv,
		      double &gradx, double &grady)
{
  // df(x)/dx_i = [f(x+h_i*e_i)-f(x)]/h_i
  gradx = ( m[x+1][y] - m[x][y] ) * dxinv;
  grady = ( m[x][y+1] - m[x][y] ) * dyinv;
}

// The gradient (central); assuming that x,x-1,x+1 etc are in the proper range
inline void GradientC(double **m, const int x, const int y,
		      const double dxinv2, const double dyinv2,
		      double &gradx, double &grady)
{
  // df(x)/dx_i = [f(x+h_i*e_i)-f(x)]/h_i
  gradx = ( m[x+1][y] - m[x-1][y] ) * dxinv2;
  grady = ( m[x][y+1] - m[x][y-1] ) * dyinv2;
}

// The gradient (backward); assuming that x,x-1,x+1 etc are in the proper range
inline void Gradient(double **m, const int x, const int y,
		     const double dxinv, const double dyinv,
		     double &gradx, double &grady)
{
  // df(x)/dx_i = [f(x+h_i*e_i)-f(x)]/h_i
  gradx = ( m[x][y] - m[x-1][y] ) * dxinv;
  grady = ( m[x][y] - m[x][y-1] ) * dyinv;
}

// Swap a and b
inline void Swap(double &a, double &b)
{
  double temp = a;
  a = b;
  b = temp;
}

#endif
