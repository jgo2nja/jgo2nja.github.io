// James O'Connell jgo2nja
// Last Updated: 20 July 2022

// City(Node) header outline


// Pre-processing
#ifndef CITY_H
#define CITY_H

#include<string>

// namespace
using namespace std;

// class definition
class city{
 public:
  // constructors
  city();

  city(const string& name, float startx, float starty, char newTraffic);

  // destructor

  ~city();

  // getters and setters
  
  string getName();

  float getTime();

  void setTime(float newTime);

  float getX();

  float getY();

  char getTraffic();

  city* getChild();

  city* getPrev();

  city* getNext();

  void setChild(city* newChild);

  void setNext(city* newNext);

  void setPrev(city* newPrev);

  string getPrevName();

  void setPrevName(string name);

  void makeKnown();

  bool getKnown();

  void makeUnknown();

  // Edge weight finder (between cities)

  float calculateTime(city* destination);


 private:
  // data fields
  // time from starting city
  float time;
  // x coordinate of the city
  float xpos;
  // y coordinate of the city
  float ypos;
  // name of the city
  string name;
  // name of the last city visited before this one
  string prevName;
  // traffic speed in the city
  char traffic;
  // child pointer
  city* child;
  // left sibling pointer
  city* previous;
  // right sibling pointer
  city* next;
  // known identifier
  bool known;
};

// function to detach a city from its siblings
city* detach(city* detachCity);
#endif

