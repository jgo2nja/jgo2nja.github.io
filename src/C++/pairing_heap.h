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
  void insert(city* newNode);
  
  // decreases the time (or increases priority) of a city (also calls augment)
  void decreaseKey(float newKey, city* target);
  
  // removes the minimum element (calls augmentPass after)
  void deleteMin();
  
  // tells whether the heap is empty
  bool empty();

 private:

  city* min;
};

#endif

