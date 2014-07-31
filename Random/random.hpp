/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef random_hpp
#define random_hpp

// class Random: random numbers from different distributions
class Random : public Ranmar
{
protected:
  // Length of the grnd vector
  int maxrnd;
  // Counter
  int cnt;
  // The array for Gaussia rnd's
  float *grnd;

public:
  // Constructors
  inline Random();
  inline Random(int seed, int maxLen = DEFAULT_LENGTH);

  // Destructor
  inline ~Random();

  // Uniform random numbers
  inline int Uniform(const int);
  inline int Uniform(const int, const int);
  inline float Uniform();
  inline float Uniform(const float);
  inline float Uniform(const float, const float);
  inline double UniformD();
  inline double Uniform(const double);
  inline double Uniform(const double, const double);
  inline float Gaussian();

  // Gaussian random numbers
  void Gaussian(const int, float *);
  void Gaussian(const int, const float, float *);
  void Power(const int, const float, float *);

};

// Default constructor
inline Random :: Random() :
  Ranmar(),
  maxrnd (DEFAULT_LENGTH),
  cnt (maxrnd),
  grnd (new float[maxrnd])
{
}

// Constructor
inline Random :: Random(int seed, int maxLength) :
  Ranmar(seed,maxLength),
  maxrnd (DEFAULT_LENGTH),
  cnt (maxrnd),
  grnd (new float[maxrnd])
{
}

// Destructor
inline Random :: ~Random()
{
  delete [] grnd;
}

// Uniform rnd in interval [0,rndMax[
inline int Random :: Uniform(const int rndMax)
{
  return (int)((rndMax+1)*Get());
}

// Uniform rnd in interval ]rndMin,rndMax[
inline int Random :: Uniform(const int rndMin, const int rndMax)
{
  return (int)(rndMin + (rndMax + 1 - rndMin)*Get());
}

// Uniform rnd in interval ]0,1[
inline float Random :: Uniform()
{
  return Get();
}

// Uniform rnd in interval ]0,rndMax[
inline float Random :: Uniform(const float rndMax)
{
  return rndMax*Get();
}

// Uniform rnd in interval ]rndMin,rndMax[
inline float Random :: Uniform(const float rndMin, const float rndMax)
{
  return (rndMin + (rndMax - rndMin)*Get());
}

// Uniform rnd in interval ]0,1[
inline double Random :: UniformD()
{
  return Get();
}

// Uniform rnd in interval ]0,rndMax[
inline double Random :: Uniform(const double rndMax)
{
  return rndMax*Get();
}

// Uniform rnd in interval ]rndMin,rndMax[
inline double Random :: Uniform(const double rndMin, const double rndMax)
{
  return (rndMin + (rndMax - rndMin)*Get());
}

// Return a random number from Gaussian distribution
inline float Random :: Gaussian()
{
  // Check the rnd counter and load new Gaussians to array if needed
  if (++cnt >= maxrnd)
    {
      Gaussian(maxrnd,grnd);
      cnt = 0;
    }
  // Return a Gaussian rnd
  return grnd[cnt];
}

#endif
