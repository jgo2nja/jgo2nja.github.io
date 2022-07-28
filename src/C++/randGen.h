// James O'Connell jgo2nja
// Last Updated: 27 July 2022


// pre-processing
#ifndef RANDGEN_H
#define RANDGEN_H

#include <vector>

// declare the namespace
using namespace std;

class randGen{
 public:

  // constructor
  randGen(int linMultiplier, int constant, int modulo);

  ~randGen();

  // number generator
  vector<float> getRandomFloats(int size);

 private:
  // linear multiplier
  int a;
  // constant
  int c;
  // modulo
  int K;
};


#endif
