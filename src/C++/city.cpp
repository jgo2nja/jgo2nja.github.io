// James O'Connell jgo2nja
// Last Updated: 14 July 2022

// City class implementation

//-----------------------------------------------------

// Each city has an identifying string property, formatted as (City, Province), a time property for storing the shortest path, positions for distance calculation, a previous city field to back track shortest paths, and left right child pointers

// Pre-processing directives (other files and libraries)
#include "city.h"
#include <string>
#include <cmath>
#include <queue>

// Declare the namespace (standard)
using namespace std;

// Default constructor
city::city(){
  //default values for fields
  name="";
  prevName="";
  // distance set at approx infinity initially
  time=65536;
  xpos=0;
  ypos=0;
  traffic='0';
  child = NULL;
  next = NULL;
  previous = NULL;
  known=false;
}

// Overloaded constructor (pass by reference for faster performance)
city::city(const string& s, float x, float y, char t){
  // fill values
  name=s;
  prevName="";
  time=65536;
  xpos=x;
  ypos=y;
  traffic=t;
  child = NULL;
  next = NULL;
  previous = NULL;
  known = false;
}

// Getters and Setters (no setter for name, it doesn't change)

string city::getName(){
  return name;
}

float city::getTime(){
  return time;
}

float city::getX(){
  return xpos;
}

float city::getY(){
  return ypos;
}

char city::getTraffic(){
  return traffic;
}

void city::setTime(float newTime){
  time=newTime;
  
}

void city::setPrevName(string name){
  prevName = name;
}

string city::getPrevName(){
  return prevName;
}

void city::makeKnown(){
  known=true;
}

bool city::getKnown(){
  return known;
}

void city::makeUnknown(){
  known=false;
}

// Destructor to free allocated memory
city::~city(){
}

// distance calculation function

float city::calculateTime(city* d){
  // use distance formula to get straight line value
  float dist = std::sqrt((d->xpos-xpos)*(d->xpos-xpos)+(d->ypos-ypos)*(d->ypos-ypos));

  // 6 possible scenarios
  
  // Edges can not be more than 15 miles base
  // Edges can not be to the same vertex (0.01 for float corrections)
  if((dist > 10) || (dist < 0.01)){
    return -1;
  }
  // Traffic effects on distance are standardized here
  else if(traffic=='S' && d->traffic == 'S'){
    return 1.5*dist;
  }
  else if((traffic=='M' && d->traffic == 'S')||(traffic=='S' && d->traffic == 'M')){
    return 1.25*dist;
  }
  else if((traffic=='F' && d->traffic == 'M')||(traffic=='M' && d->traffic == 'F')){
    return 0.75*dist;
  }
  else if(traffic=='F' && d->traffic == 'F'){
    return 0.5*dist;
  }
  else{
    return dist;
  }
  
  
}

// function to rearrange pointers to remove a node from the pairing heap

// used with decrease key


void city::detach(){
  // Case 1: Has parent but no sibling
  if(previous->child == this && next == NULL){
    previous->child = NULL;
    previous=NULL;
  }
  // Case 2: Has parent and sibling
  else if(previous->child == this && next != NULL){
    previous->child = next;
    next->previous = previous;
    previous=NULL;
    next=NULL;
  }
  // Case 3: No parent and sibling
  else if(next != NULL){
    previous->next = next;
    next->previous = previous;
    next=NULL;
    previous=NULL;
  }
  // Case 4: No parent, no sibling
  else{
    previous->next = next;
    previous=NULL;
  }
}

city* city::augment(city* c){
  // find out which to knock out
  if(time < c->time){
    // weird pointer stuff
    if(child == NULL){
      child = c;
      child->previous = this;
      return this;
    }
    else{
      city* temp = child;
      child = c;
      child->previous = this;
      child->next=temp;
      temp->previous = child;
      return this;
    }
  }
  else{
    if (c->child == NULL){
      c->child=this;
      previous=c;
      return c;
    }
    else{
      city* temp = c->child;
      c->child=this;
      c->child->previous=c;
      c->child->next=temp;
      temp->previous = c->child;
      return c;
    }
  }
}

city* city::augmentPass(){
  // a queue is needed for continual passing and combining heaps
  queue<city*> passQueue;

  city* temp=this;
  
  // left most child passed in  
  // loop through siblings
  while(temp != NULL){
    passQueue.push(temp);

    temp = temp->next;
    
    // break ties
    if(temp!= NULL){
      temp->previous->next=NULL;
      temp->previous=NULL;
    }
  }
  // wait until there is just one heap left
  while(passQueue.size() > 1){
    // take 2 off the queue
    city* c1 = passQueue.front();
    passQueue.pop();
    city* c2 = passQueue.front();
    passQueue.pop();
    // combine them
    passQueue.push(c1->augment(c2));
  }
  // take the final one
  city* resultant = passQueue.front();
  // clean up
  passQueue.pop();

  return resultant;
}

city* city::deleteMin(){
  // get start of child list
  city* c = child;

  // check if there are no children
  if(c==NULL){
    // make the heap empty
    return NULL;
  }
  else{
    // break ties
    child=NULL;
    c->previous=NULL;
    // combine siblings into new heap
    c=c->augmentPass();
    // return the child
    return c;
  }
}

void city::clear(){
  previous=NULL;
  next=NULL;
  child=NULL;
}
