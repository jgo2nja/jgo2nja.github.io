/**
 * @file "vertex.cpp"
 * Game State Implementation
 * @author James O'Connell jgo2nja
 * @date 28 April 2022
 *
 *
 **/

#include "vertex.h"
#include<string>
#include<vector>

using namespace std;

vertex::vertex(){
  gameState = "";
  dist = 0;
  zeroPos = 0;
}

  /**
   *
   * @brief Default Constructor
   *
   * @param currentState a string representing the puzzle state of the vertex
   *
   * @param newDist the distance of this vertex from the zero state puzzle (in moves)
   *
   * @param zero the location of the hole in the puzzle (by index in the array)
   *
   * @return A vertex object
   *
   **/
vertex::vertex(string currentState, int newDist, int zero){
  gameState = currentState;
  dist = newDist;
  zeroPos = zero;
}

vertex::~vertex(){
}

  /**
   *
   * @brief A getter method for the string state of the vertex
   *
   * @return The value of the state in the vertex
   **/

string vertex::getState(){
  return gameState;
}

    /**
   *
   * @brief A getter method for the zero location of the vertex
   *
   * @return The value of the zero location in the vertex
   **/

int vertex::getZero(){
  return zeroPos;
}

/**
   *
   * @brief A getter method for the distance state of the vertex from the zero state
   *
   * @return The value of the distance state in the vertex
   **/

int vertex::getDist(){
  return dist;
}
