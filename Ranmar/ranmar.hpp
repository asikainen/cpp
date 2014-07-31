/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef ranmar_hpp
#define ranmar_hpp

// Definitions
#define DEFAULT_LENGTH 1024

// Ranmar class definition
class Ranmar
{
protected:
  // Ranmar variables
  float u[98], c, cd, cm;
  int i97, j97;

  // RND array size.
  int rndMax;

  // Index of the present random number
  int index;

  // The seed
  int seed;

  // The RND array
  float *rnd;
  
  // Original cranmar method. Fills vec-array with len new random numbers
  void Generate(float *vec,int len);

public:
  // Constructor
  inline Ranmar();
  inline Ranmar(int seed, int maxLen = DEFAULT_LENGTH);

  // Destructor
  inline ~Ranmar();

  // Check the seed
  inline int CheckSeed(int seed = 0);
  inline int Seed();

  // Returns a random float in the range (0,1)
  inline float Get();

  // Original crmarin-method
  void Initialize(int ijkl);

};

// Default constructor: creates a new Ranmar class representative
// with a seed from the clock and default length
inline Ranmar :: Ranmar() :
  rndMax(DEFAULT_LENGTH), 
  index(DEFAULT_LENGTH),
  seed((int)time(NULL))
{ 
  // Printing
  printf("# Ranmar is using seed: %d (generated from the clock)\n",seed);

  // Initialize the generator
  Initialize(seed); 

  // Allocate the rnd[] vector
  rnd = new float[rndMax];
}

// Constructor: creates a new Ranmar class representative
inline Ranmar :: Ranmar(int Seed, int maxLen) :
  rndMax(maxLen), 
  index(maxLen),
  seed()
{ 
  // Check that seed is not zero
  seed = CheckSeed(Seed);
  if (Seed == 0)
    printf("# Ranmar is using seed: %d (generated from the clock)\n",seed);

  // Initialize the generator
  Initialize(seed); 

  // Allocate the rnd[] vector
  rnd = new float[rndMax];
}

// Returns a new random number (float)
inline float Ranmar :: Get()
{ 
  if(++index >= rndMax)
    {
      Generate(rnd,rndMax);
      index=0;
    }
  return rnd[index]; 
}

// Destructor; deletes the dynamically allocated RND vector.
inline Ranmar :: ~Ranmar()
{
  delete [] rnd;
}

// Check the seed; if zero, get one from the clock
inline int Ranmar :: CheckSeed(int Seed)
{
  // If seed is zero, set it from the clock
  if (Seed == 0)
    return (int)time(NULL);
  else
    return Seed;
}

// Returns the seed
inline int Ranmar :: Seed()
{ return seed; }

#endif
