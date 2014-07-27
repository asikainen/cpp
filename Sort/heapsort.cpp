/***
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Util/util.hpp"
#include "../Vector/vector.hpp"
#include "heapsort.hpp"

// Main
int main(int argc, char **argv)
{
  // checking
  if (argc < 2)
    Error("usage: mkpq.exe file [i]");

  // pick parameters
  char * file = argv[1];
  
  // read the array for items
  int length;
  double *items = ReadVector(file, length);

  // sorting
  cout << "# heapsort with " << length << " items." << endl;
  HeapSort(items, 0, length-1);

  // plug the elements back to v
  for (int i=0; i<length; i++)
    cout << items[i] << endl;

  // done
  return 0;
}
