/***
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef calc_hpp
#define calc_hpp

//template <class T>
//class Point;

// Definitions
#ifndef MAX_POWER
#define MAX_POWER 15
#endif

#ifndef EPS
#define EPS 1.0E-9
#endif

// Prototypes
char *IntToChar(const int, const int);

int PowerOfTwo(const int);
int PowerOfThree(const int);
int Min(int *, const int);
int Max(int *, const int);
int Sum(int *, const int);

float Min(float *, const int);
float Max(float *, const int);
float Sum(float *, const int);

double Min(double *, const int);
double Max(double *, const int);
double Sum(double *, const int);

void NormalizeMoments(double *, double *, const int, const int);
void SetValues(int *, const int, const int = 0);
void SetValues(double *, const int, const double = 0.0);
void PrintVector(int *, const int, char *);
void PrintVector(float *, const int, char *);
void PrintVector(double *, const int, char *);
void Error(char []);

// Inline functions

// Absolute value
inline int Abs(int i)
{
  return ( i > 0 ? i : (-i) );
}

// Absolute value
inline float Abs(float f)
{
  return ( f > 0 ? f : (-f) );
}

// Absolute value
inline double Abs(double d)
{
  return ( d > 0 ? d : (-d) );
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

// Statistical error; div = 1/N, where
// N is the number of samples.
inline double StatError(const double m1, const double m2, const double div)
{
  double error=m2-m1*m1;

  if (error > EPS)
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

#endif
