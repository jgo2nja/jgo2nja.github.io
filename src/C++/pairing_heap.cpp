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
pairing_heap::pairing_heap(city* minCity){
  min = minCity;
}

// destructor to free memory
pairing_heap::~pairing_heap(){
}

// getter and setter
city* pairing_heap::getMin(){
  return min;
}

void pairing_heap::setMin(city* newCity){
  min = newCity;
}

// insert new element
pairing_heap* pairing_heap::insert(city* insertCity){
  
  // initialize new pointer in memory
  pairing_heap* newHeap = new pairing_heap(insertCity);
  
  // augment with existing heap
  return augment(this, newHeap);
}

// increase priority of a node (by decreasing time)
pairing_heap* pairing_heap::decreaseKey(float newKey, city* target){
  
  // remove target from existing heap
  city* breakCity = detach(target);
  
  // decrease the key
  breakCity->setTime(newKey);
  // create new heap in memory
  pairing_heap* breakHeap = new pairing_heap(breakCity);
  // combine heaps (re insert)
  return augment(this, breakHeap);
}

bool pairing_heap::empty(){
  // condition for emptiness
  if(min==NULL){
    return true;
  }
  return false;
}

pairing_heap* pairing_heap::deleteMin(){
  // get start of child list
  city* newCity = min->getChild();
  // break ties
  min->setChild(NULL);
  // check if there are no children
  if(newCity==NULL){
    min = NULL;
    // return an empty heap
    return this;
  }
  else{
    // combine siblings into new heap
    return augmentPass(newCity);
  }
}


pairing_heap* augmentPass(city* startingCity){
  // a queue is needed for continual passing and combining heaps
  queue<pairing_heap*> passQueue;
  
  // left most child passed in
  city* currentCity = startingCity;
  
  // loop through siblings
  while(currentCity != NULL){

    // create a new heap
    pairing_heap* newHeap = new pairing_heap(currentCity);
    // move iterator forward
    
    currentCity = currentCity->getNext();
    
    // break ties
    if(currentCity != NULL){
      currentCity->getPrev()->setNext(NULL);
      currentCity->setPrev(NULL);
    }
    passQueue.push(newHeap);
  }
  // wait until there is just one heap left
  while(passQueue.size() > 1){
    // take 2 off the queue
    pairing_heap* heap1 = passQueue.front();
    passQueue.pop();
    pairing_heap* heap2 = passQueue.front();
    passQueue.pop();
    // combine them
    pairing_heap* resultant = augment(heap1, heap2);
    passQueue.push(resultant);
  }
  // take the final one
  pairing_heap* returnHeap = passQueue.front();
  // clean up
  return returnHeap;
}

pairing_heap* augment(pairing_heap* first, pairing_heap* second){
  // find out which to knock out
  if(first->getMin()->getTime() < second->getMin()->getTime()){
    // weird pointer stuff
    if(first->getMin()->getChild() == NULL){
      first->getMin()->setChild(second->getMin());
      second->setMin(NULL);
      // clean up
      delete second;
      return first;
    }
    else{
      city* temp = first->getMin()->getChild();
      first->getMin()->setChild(second->getMin());
      first->getMin()->getChild()->setNext(temp);
      temp->setPrev(first->getMin()->getChild());
      second->setMin(NULL);
      delete second;
      return first;
    }
  }
  else{
    if (second->getMin()->getChild() == NULL){
      second->getMin()->setChild(first->getMin());
      first->setMin(NULL);
      delete first;
      return second;
    }
    else{
      city* temp = second->getMin()->getChild();
      second->getMin()->setChild(first->getMin());
      second->getMin()->getChild()->setNext(temp);
      temp->setPrev(second->getMin()->getChild());
      first->setMin(NULL);
      delete first;
      return second;
    }
  }
}
