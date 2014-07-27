#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Defs/defs.hpp"
//#include "../Point/point.hpp"
#include "calc.hpp"

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
  if (cnt == 0)
    return;

  const double div = 1.0/(double)cnt;

  for (int i=0; i<l; i++)
    {
      m1[i] *= div;
      m2[i] *= div;
    }
}

// Set the values to the vector
void SetValues(int *vec, const int n, const int val)
{
  for (int i=0; i<n; i++)
    vec[i] = val;
}

// Set the values to the vector
void SetValues(float *vec, const int n, const float val)
{
  for (int i=0; i<n; i++)
    vec[i] = val;
}

// Set the values to the vector
void SetValues(double *vec, const int n, const double val)
{
  for (int i=0; i<n; i++)
    vec[i] = val;
}

// Sum of the vector's elements
double Sum(double *v, const int l)
{
  double s=0;
  for (int i=0; i<l; i++)
    s += v[i];
  return s;
}

// Sum of the vector's elements
float Sum(float *v, const int l)
{
  float s=0;
  for (int i=0; i<l; i++)
    s += v[i];
  return s;
}
// Sum of the vector's elements
int Sum(int *v, const int l)
{
  int s=0;
  for (int i=0; i<l; i++)
    s += v[i];
  return s;
}

// Printing
void PrintVector(int *v, const int n, char *txt)
{
  printf("\n# %s:\n",txt);
  for (int i=0; i<n; i++)
    printf("%d\n",v[i]);
  printf("\n");
}

// Printing
void PrintVector(float *v, const int n, char *txt)
{
  printf("\n# %s:\n",txt);
  for (int i=0; i<n; i++)
    printf("%g\n",v[i]);
  printf("\n");
}

// Printing
void PrintVector(double *v, const int n, char *txt)
{
  printf("\n# %s:\n",txt);
  for (int i=0; i<n; i++)
    printf("%g\n",v[i]);
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

/*
  C     **** Fortran version of IntToChar() ****
  subroutine int2char(integ,len,char)

  implicit none
  integer len,integ
  character*50 char         !NB! this is not the real length

  C     **** Local variables ****
  integer deca,i,j,lint
  character*10 charnum
  charnum='0123456789'

  lint=abs(integ)
  deca=10**(len-1)

  do i=1,len
     j=lint/deca+1
     char(i:i)=charnum(j:j)
     lint=lint-(j-1)*deca
     deca=deca/10
  end do

  return
  end
*/
