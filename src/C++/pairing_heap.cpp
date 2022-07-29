// James O'Connell jgo2nja
// Last Updated: 23 July 2022

// pre-processing
#include "city.h"
#include "pairing_heap.h"
#include <string>

// declare the namespace
using namespace std;

// default construct
pairing_heap::pairing_heap(){
  min = NULL;
}

// overload construct with min value
pairing_heap::pairing_heap(city* c){
  min = c;
}

// destructor to free memory
pairing_heap::~pairing_heap(){
}

// getter and setter
city* pairing_heap::getMin(){
  min->makeKnown();
  return min;
}

void pairing_heap::setMin(city* newCity){
  min = newCity;
}

// insert new element
void pairing_heap::insert(city* c){
  min=min->augment(c);
}

// increase priority of a node (by decreasing time)
void pairing_heap::decreaseKey(float newKey, city* target){
  
  // remove target from existing heap
  if(target!=min){
    target->detach();
    // decrease the key
    target->setTime(newKey);
  
    // combine heaps (re insert)
    min=min->augment(target);
  }
  // if the target is the minimum already, just decrease the key
  else{
    target->setTime(newKey);
  }
  

}

bool pairing_heap::empty(){
  // condition for emptiness
  if(min==NULL){
    return true;
  }
  return false;
}

void pairing_heap::deleteMin(){
  min=min->deleteMin();
}
