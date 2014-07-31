/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef fractal_hpp
#define fractal_hpp

// Constants
static const double pi = acos(-1.0);  // Pi
static const double theta = pi / 3.0; // Rotation angle
static const double ct = cos(theta), st = sin(theta); // sin / cos

// Output file
static const char fileName[10] = "star.dat";

// Data arrays
Vector<double> x, y;

// Prototypes
int NumberOfPoints(const int);
int GetPoints(const int, int &, int &, int &,const int);

void NextLevel(const double, const double,
	       const double, const double);
void MakeStar(const int, const int);
void MakeStar(const int, const int,
	      const int, const int,
	      const double, const double,
	      const double, const double);
void MakeStar(const int, const int,
	      const double, const double,
	      const double, const double);
void Mark(const double,
	  const double,
	  const double,
	  const double,
	  const double,
	  const double,
	  const double,
	  const double,
	  const double,
	  const double);
void Mark(const int i1,
	  const int i2,
	  const int i3,
	  const double x1,
	  const double x2,
	  const double x3,
	  const double y1,
	  const double y2,
	  const double y3);
void Print(const int i0, const int i1,
	   const int i2, const int i3, const int i4);
void Store(const char *fname);
void InitFile(const char *fname, const int, const int);

#endif
