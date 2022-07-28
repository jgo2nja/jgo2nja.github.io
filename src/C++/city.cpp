// James O'Connell jgo2nja
// Last Updated: 14 July 2022

// City class implementation

//-----------------------------------------------------

// Each city has an identifying string property, formatted as (City, Province), a time property for storing the shortest path, positions for distance calculation, a previous city field to back track shortest paths, and left right child pointers

// Pre-processing directives (other files and libraries)
#include "city.h"
#include <string>
#include <cmath>

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
city::city(const string& cityName, float startx, float starty, char newtraffic){
  // fill values
  name=cityName;
  prevName="";
  time=65536;
  xpos=startx;
  ypos=starty;
  traffic=newtraffic;
  child = NULL;
  next = NULL;
  previous = NULL;
  known = false;
}

// Getters and Setters (no setter for name, it doesn't change)

void city::setChild(city* newChild){
  child = newChild;
}

void city::setNext(city* newNext){
  next= newNext;
}

void city::setPrev(city* newPrev){
  previous = newPrev;
}

city* city::getChild(){
  return child;
}

city* city::getNext(){
  return next;
}

city* city::getPrev(){
  return previous;
}

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

float city::calculateTime(city* destination){
  // use distance formula to get straight line value
  float distance = std::sqrt((destination->getX()-xpos)*(destination->getX()-xpos)+(destination->getY()-ypos)*(destination->getY()-ypos));

  // 6 possible scenarios
  
  // Edges can not be more than 15 miles base
  // Edges can not be to the same vertex (0.01 for float corrections)
  if((distance > 10) || (distance < 0.01)){
    return -1;
  }
  // Traffic effects on distance are standardized here
  else if(traffic=='S' && destination->getTraffic() == 'S'){
    return 1.5*distance;
  }
  else if((traffic=='M' && destination->getTraffic() == 'S')||(traffic=='S' && destination->getTraffic() == 'M')){
    return 1.25*distance;
  }
  else if((traffic=='F' && destination->getTraffic() == 'M')||(traffic=='M' && destination->getTraffic() == 'F')){
    return 0.75*distance;
  }
  else if(traffic=='F' && destination->getTraffic() == 'F'){
    return 0.5*distance;
  }
  else{
    return distance;
  }
  
  
}

// function to rearrange pointers to remove a node from the pairing heap

// used with decrease key

city* detach(city* detachCity){
  // Case 1: Left and Right Siblings do not exist
  if(detachCity->getPrev()==NULL && detachCity->getNext() == NULL){
    return detachCity;
  }
  // Case 2: Only right sibling exists
  else if(detachCity->getPrev() == NULL && detachCity->getNext() != NULL){
    detachCity->getNext()->setPrev(NULL);
    detachCity->setNext(NULL);
    return detachCity;
  }
  // Case 3: Only left sibling exists
  else if(detachCity->getPrev() !=NULL && detachCity->getNext() == NULL){
    detachCity->getPrev()->setNext(NULL);
    detachCity->setPrev(NULL);
    return detachCity;
  }
  // Case 4: Both siblings exist
  else{
    detachCity->getPrev()->setNext(detachCity->getNext());
    detachCity->getNext()->setPrev(detachCity->getPrev());
    detachCity->setNext(NULL);
    detachCity->setPrev(NULL);
    return detachCity;
  }
}
