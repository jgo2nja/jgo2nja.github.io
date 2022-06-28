/**
 *
 * @file "vertex.h"
 * Header for game storage state
 * @author James O'Connell jgo2nja
 * @date 28 April 2022
 *
 **/

#ifndef VERTEX_H
#define VERTEX_H

#include<string>

using namespace std;

class vertex{
 public:
  vertex();

  vertex(string inputState, int newDist, int zero);

  ~vertex();

  string getState();

  int getZero();  

  int getDist();

 private:
  string gameState;
  int dist;
  int zeroPos;
};


#endif
