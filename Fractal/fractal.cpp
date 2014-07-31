/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../Util/util.hpp"
#include "../Ranmar/ranmar.hpp"
#include "../Random/random.hpp"
#include "../Vector/vector.hpp"
#include "../Matrix/matrix.hpp"
#include "../Algorithms/alg.hpp"
#include "fractal.hpp"

// Main; computes the Koch fractal star
int main(int argc, char **argv)
{
  // Check arguments
  if (argc < 2)
    Error("usage: fractal.exe arg(s)");

  // Extract parameters
  const int l = atoi(argv[1]);

  // Checking
  if (l > 7)
    return 1;
  const int n = NumberOfPoints(l); 

  // Printing
  cout << "# number of levels = " << l
       << " number of points = " << n << endl;

  // Resize
  x.Resize(n);
  y.Resize(n);

  // Initialization
  InitFile(fileName,n,l);

  // Generate stars
  MakeStar(n,l);

  // Done
  return 0;
}

// Generate stars
void MakeStar(const int n, const int l)
{
  // line end points
  double x0, y0, x1, y1;

  // Set the initial points
  x0 = 0; y0 = 0; x1 = 1; y1 = 0;
  x(0) = x0; x(n-1) = x1; y(0) = y0; y(n-1) = y1;  

  // Generate the star
  MakeStar(0,l,0,n,x0,y0,x1,y1);

  // Store
  Store(fileName);

  // Set the initial points
  x0 = 1; y0 = 0; x1 = 0.5; y1 = -2./3.;
  x(0) = x0; x(n-1) = x1; y(0) = y0; y(n-1) = y1;  

  // Generate the star
  MakeStar(0,l,0,n,x0,y0,x1,y1);

  // Store
  Store(fileName);

  // Set the initial points
  x0 = 0.5; y0 = -2./3.; x1 = 0; y1 = 0;
  x(0) = x0; x(n-1) = x1; y(0) = y0; y(n-1) = y1;  

  // Generate the star
  MakeStar(0,l,0,n,x0,y0,x1,y1);

  // Store
  Store(fileName);


}

// Count number of points recursively
int NumberOfPoints(const int l)
{
  if (l == 0)
    return 2;
  int n = 2;
  for (int i=0; i<l; i++)
    n = 4 * n - 3;
  return n;
}

// Computes the next level
void NextLevel(const double xl, const double yl,
	       const double xr, const double yr)
{
  // Constants
  const double dx = (xr - xl)/3, dy = (yr - yl)/3,
    ct = cos(theta), st = sin(theta);

  // First point
  const double x0 = xl + dx;
  const double y0 = yl + dy;

  // Second point, rotated by 60 degrees
  const double x1 = x0 + (dx * ct - dy * st);
  const double y1 = y0 + (dx * st + dy * ct);

  // Third point
  const double x2 = xl + 2 * dx;
  const double y2 = yl + 2 * dy;

  // Mark points
  Mark(xl,x0,x1,x2,xr,yl,y0,y1,y2,yr);
}

// Get the vertex points
int GetPoints(const int i0,
	       int &i1,
	       int &i2,
	       int &i3,
	       const int i4)
{
  if (i0 == i4)
    return 1;
  const int di = (i4 - i0) / 4;
  i1 = i0 + di;
  i2 = i0 +  2 * di;
  i3 = i0 + 3 * di;
  return 0;
}

// Generates the star recursively
void MakeStar(const int l, const int lmax,
	      const double x0, const double y0,
	      const double x4, const double y4)
{
  // Check if maximum level reached
  if (l == lmax)
    return;

  // Constants
  const double dx = (x4 - x0)/3, dy = (y4 - y0)/3;

  // First point
  const double x1 = x0 + dx;
  const double y1 = y0 + dy;

  // Second point, rotated by 60 degrees
  const double x2 = x1 + (dx * ct - dy * st);
  const double y2 = y1 + (dx * st + dy * ct);

  // Third point
  const double x3 = x0 + 2 * dx;
  const double y3 = y0 + 2 * dy;

  // Mark the new points
  Mark(x0,x1,x2,x3,x4,y0,y1,y2,y3,y4);

  // The next level
  MakeStar(l+1,lmax,x0,y0,x1,y1);
  MakeStar(l+1,lmax,x1,y1,x2,y2);
  MakeStar(l+1,lmax,x2,y2,x3,y3);
  MakeStar(l+1,lmax,x3,y3,x4,y4);
}

// Mark the points
void Mark(const double x0,
	  const double x1,
	  const double x2,
	  const double x3,
	  const double x4,
	  const double y0,
	  const double y1,
	  const double y2,
	  const double y3,
	  const double y4)
{
  ofstream fout("star.dat",ios::app);
  if (!fout)
    return;
  fout << x0 << "\t" << y0 << endl
       << x1 << "\t" << y1 << endl
       << x2 << "\t" << y2 << endl
       << x3 << "\t" << y3 << endl
       << x4 << "\t" << y4 << endl << endl;
  fout.close();
}

// Generates the star recursively
void MakeStar(const int l, const int lmax,
	      const int i0, const int i4,
	      const double x0, const double y0,
	      const double x4, const double y4)
{
  // Check if maximum level reached
  if (l == lmax)
    return;

  // Indices
  int i1 = 0, i2 = 0, i3 = 0;
  if (GetPoints(i0,i1,i2,i3,i4) != 0)
    Error("GetPoints()");
  //cout << "# new indices: " << i1 << "\t" << i2 << "\t" << i3 << endl;

  // Constants
  const double dx = (x4 - x0)/3, dy = (y4 - y0)/3;

  // First point
  const double x1 = x0 + dx;
  const double y1 = y0 + dy;

  // Second point, rotated by 60 degrees
  const double x2 = x1 + (dx * ct - dy * st);
  const double y2 = y1 + (dx * st + dy * ct);

  // Third point
  const double x3 = x0 + 2 * dx;
  const double y3 = y0 + 2 * dy;

  // Mark the points
  Mark(i1,i2,i3,x1,x2,x3,y1,y2,y3);

  // The next level
  MakeStar(l+1,lmax,i0,i1,x0,y0,x1,y1);
  MakeStar(l+1,lmax,i1,i2,x1,y1,x2,y2);
  MakeStar(l+1,lmax,i2,i3,x2,y2,x3,y3);
  MakeStar(l+1,lmax,i3,i4,x3,y3,x4,y4);
}

// Printing
void Print(const int i0, const int i1,
	   const int i2, const int i3, const int i4)
{
  cout << i0 << "\t" 
       << i1 << "\t" 
       << i2 << "\t" 
       << i3 << "\t" 
       << i4 << "\n" ;
}

// Mark the points
void Mark(const int i1,
	  const int i2,
	  const int i3,
	  const double x1,
	  const double x2,
	  const double x3,
	  const double y1,
	  const double y2,
	  const double y3)
{
  x(i1) = x1;
  x(i2) = x2;
  x(i3) = x3;
  y(i1) = y1;
  y(i2) = y2;
  y(i3) = y3;
}

// Store
void Store(const char *fname)
{
  ofstream fout(fname,ios::app);
  if (!fout)
    return;
  for (int i=0; i<x.GetSize(); i++)
    fout << x(i) << "\t" << y(i) << endl;
  fout.close();
}

// Store
void InitFile(const char *fname, const int n, const int l)
{
  ofstream fout(fname);
  if (!fout)
    return;
  fout << "# levels = " << l << " number of points = " << n << endl;
  fout.close();
}
