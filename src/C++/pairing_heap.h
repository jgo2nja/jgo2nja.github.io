// James O'Connell jgo2nja
// Last Updated: 23 July 2022

// pre-processing
#ifndef PAIRING_HEAP_H
#define PAIRING_HEAP_H

#include "city.h"
#include <string>
#include <queue>

// declare the namespace
using namespace std;

class pairing_heap{
 public:

  // constructor
  pairing_heap();
  
  // overloaded constructor
  pairing_heap(city* minCity);
  
  // destructor
  ~pairing_heap();
  
  // getters and setters
  city* getMin();
  
  void setMin(city*);
  
  // inserts a new city into the heap (calls augment to do so)
  pairing_heap* insert(city* newNode);
  
  // decreases the time (or increases priority) of a city (also calls augment)
  pairing_heap* decreaseKey(float newKey, city* target);
  
  // removes the minimum element (calls augmentPass after)
  pairing_heap* deleteMin();
  
  // tells whether the heap is empty
  bool empty();

 private:

  city* min;
};

// function to combine pairing heaps by a largest-knockout method
pairing_heap* augment(pairing_heap* first, pairing_heap* second);

// function to combine siblings into a new heap after the minimum is deleted
pairing_heap* augmentPass(city* startChild);

#endif

