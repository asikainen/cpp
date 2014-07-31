/***
 * Date: ~2001
 * Author: Joonas Asikainen <tjasikai@mac.com>
 */

#ifndef heapsort_hpp
#define heapsort_hpp

// exhange two items
template <class Item>
inline void Exchange(Item &item1, Item &item2)
{
  Item tmp = item1;
  item1 = item2; 
  item2 = tmp;
}

// fix the heap condition upwards
template <class Item>
void FixUp(Item items[], int k)
{
  // division k/2 implemented as a bit shift for speedup
  while ( k > 1 && items[(k>>1)] < items[k] )
    {
      // exhange elements
      Exchange(items[k], items[(k>>1)]);
	
      // parent index
      k = (k>>1);
    }
}

// fix the heap condition downwards
template <class Item>
void FixDown(Item items[], int k, int n)
{
  // multiplication k*2 implemented as a bit shift for speedup
  while ( (k<<1) <= n )
    {
      // index of the left child
      int j = (k<<1);
	
      // check if right child is larger and adjust index if needed
      if ( j < n && items[j] < items[j+1] ) j++;

      // stop condition; child no more larger than the current
      if ( !(items[k] < items[j]) ) break;

      // exhange items
      Exchange(items[k], items[j]);

      // update index
      k = j;
    }    
}

// heap sort
template <class Item>
void HeapSort(Item a[], int l, int r)
{
  // the number of elements
  int n = r - l + 1;

  // pointer to the array
  Item *pq = a + l - 1;

  for ( int k=n/2; k >= 1; k--)
    FixDown(pq, k , n);

  while ( n > 1 )
    {
      Exchange(pq[1], pq[n]);
      FixDown(pq, 1, (--n));
    }
}
#endif
