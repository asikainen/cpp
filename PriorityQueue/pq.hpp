#ifndef pq_hpp
#define pq_hpp

// class PriorityQueue; priority queue implemented with a fixed-length heap
template <class Item>
class PriorityQueue
{
private:
  // members
  int _n;
  Item * _pq;

  // fix the heap condition upwards
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

  // exhange two items
  inline void Exchange(Item &item1, Item &item2)
  {
    Item tmp = item1;
    item1 = item2; 
    item2 = tmp;
  }

public:
  // constructor & destructor
  PriorityQueue(int maxN) :
    _n(0), _pq (new Item[maxN+1]){};

  // check if empty
  bool Empty() const { return (_n == 0); }

  // insert a new item
  void Insert(Item item)
  {
    // insert to the _pq vector to the last position
    _pq[++_n] = item; 

    // fix items upwards
    FixUp(_pq, _n);
  }
  
  // get the maximum item
  Item GetMax()
  {
    // exchange the data at 1 and _n-1
    Exchange(_pq[1], _pq[_n]);

    // fix downwards
    FixDown(_pq, 1, _n-1);

    // return the data at _n-1 and adjust the position
    return _pq[_n--];
  }

  // returns the current value of _n
  int GetN() { return _n;}
};

// prototypes

#endif
