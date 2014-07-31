/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../Defs/defs.hpp"
#include "../Ranmar/ranmar.hpp"
#include "random.hpp"


// Gaussian random numbers with zero mean and unit variance
void Random :: Gaussian(const int nrnd, float rndv[])
{
  const int n=nrnd/2;
  //const float twoPi = 6.28318530718;
  const float twoPi = 4.0*asin(1.0);

  // Generate Gaussian random numbers with zero mean
  // and SQRT(var) variance using the Box-Muller method
  for (int i=0; i<n; i++)
    {
      float rnd1=Get();
      float rnd2=Get();
      rndv[2*i]   = (sqrt(-2.0*log(rnd1)))*(cos(twoPi*rnd2));
      rndv[2*i+1] = (sqrt(-2.0*log(rnd1)))*(sin(twoPi*rnd2));
    }
}

// Gaussian random numbers with zero mean and the given variance
void Random :: Gaussian(const int nrnd, float var, float rndv[])
{
  const int n=nrnd/2;
  const float variance=sqrt(var);
  //const float twoPi = 6.28318530718;
  const float twoPi = 4.0*asin(1.0);

  // Generate Gaussian random numbers with zero mean
  // and SQRT(var) variance using the Box-Muller method
  for (int i=0; i<n; i++)
    {
      float rnd1=Get();
      float rnd2=Get();
      rndv[2*i]   = (sqrt(-2.0*log(rnd1)))*(cos(twoPi*rnd2))*variance;
      rndv[2*i+1] = (sqrt(-2.0*log(rnd1)))*(sin(twoPi*rnd2))*variance;
    }
}

// Generate random numbers with x^(-alpha) distribution
void Random :: Power(const int nrnd, const float alpha, float rndv[])
{
  const float ia=1.0/(alpha+1.0);
  float rnd;

  for (int i=0; i<nrnd; i++)
    {
      rnd = 1.0-Get();
      if (rnd == 0) rnd = EPS;
      rndv[i] = pow(rnd,ia);
    }
}
