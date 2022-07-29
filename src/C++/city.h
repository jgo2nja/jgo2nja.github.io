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

  string getPrevName();

  void setPrevName(string name);

  void makeKnown();

  bool getKnown();

  void makeUnknown();

  // Edge weight finder (between cities)

  float calculateTime(city* c);

  // Function to detach a city from its its siblings (and parent)

  void detach();

  // Function to augment one city with another through subtree adjustment

  city* augment(city* c);

  // Function to split all siblings apart and combine subtrees into one by augmenting

  city* augmentPass();

  void clear();

  city* deleteMin();

  
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

#endif
