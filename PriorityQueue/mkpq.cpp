/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#include <string>
#include <iostream.h>
#include <fstream.h>
#include <vector.h>
#include <algo.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../Util/util.hpp"
#include "../Ranmar/ranmar.hpp"
#include "../Random/random.hpp"
#include "../Vector/vector.hpp"
#include "item.hpp"
#include "pq.hpp"
#include "mkpq.hpp"


// Main
int main(int argc, char **argv)
{
  // checking
  if (argc < 2)
    Error("usage: mkpq.exe file [i]");

  // pick parameters
  char * file = argv[1];
  int inverse = 0;
  if ( argc >= 3 )
    inverse = atoi(argv[2]);

  // read values
  Vector<double> v;
  v.Read(file);

  // check if use regular/inverse priority queue
  if ( inverse == 0 )
    {
      // priority queue
      PriorityQueue<double> pq(v.GetSize());
      
      // insert values
      for (int i=0; i<v.GetSize(); i++)
	pq.Insert(v(i));
      
      // get values according to the priority
      for (int i=0; i<v.GetSize(); i++)
	cout << (pq.GetMax()) << endl;
    }
  
  // done
  return 0;
}
