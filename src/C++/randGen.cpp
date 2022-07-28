// James O'Connell jgo2nja
// Last Updated: 22 July 2022

// pre-processing
#include "randGen.h"
#include <vector>

// declare the namespace
using namespace std;

// constructor
randGen::randGen(int linMultiplier, int constant, int modulo){
  a = linMultiplier;
  c = constant;
  K = modulo;
}

// destructor
randGen::~randGen(){
}

// number generator
vector<float> randGen::getRandomFloats(int size){
  // first, the numbers will be ints
  vector<unsigned int> randomInts;
  // the seed (starting element) is 1000
  randomInts.push_back(1000);
  // create vitrual randomness
  for(int i = 1; i<size+1; i++){
    unsigned int previous = randomInts[i-1];
    unsigned int next = (a*previous+c)%K;
    randomInts.push_back(next);
  }
  // turn the ints into floats between 0 and 1
  vector<float> randomFloats;
  for(int j = 1; j<randomInts.size();j++){
    float random = float(randomInts[j])/K;
    randomFloats.push_back(random);
  }
  return randomFloats;
}
