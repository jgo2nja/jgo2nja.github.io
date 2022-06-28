/**
 * @file "solver.cpp"
 * World Puzzle Solver
 * @author James O'Connell jgo2nja
 * @date 28 April 2022
 *
 **/

#include<string>
#include<vector>
#include<iostream>
#include<queue>
#include<algorithm>
#include<unordered_set>
#include"vertex.h"

using namespace std;

/**
 * @brief This function finds all puzzle configurations adjacent to the one inserted
 *
 * This function identifies the position of the hole in the puzzle and creates new puzzle configurations from it with strings
 *
 * @param initialState a vertex representing the state from which adjacent states will be calculated
 *
 * @return A vector containing all adjacent states
 **/
vector<vertex*> findAdjacent(vertex* initialState){
  vector<vertex*> adjacentVector;
  int zeroCurrent = initialState->getZero();
  int distCurrent = initialState->getDist();
  string gameCurrent = initialState->getState();
  if(zeroCurrent == 0){
    string switch1 = gameCurrent;
    string switch2 = gameCurrent;
    swap(switch1[0],switch1[1]);
    swap(switch2[0],switch2[3]);
    vertex* newState1 = new vertex(switch1,distCurrent+1,zeroCurrent+1);
    vertex* newState2 = new vertex(switch2,distCurrent+1,zeroCurrent+3);
    adjacentVector.push_back(newState1);
    adjacentVector.push_back(newState2);
  }
  else if(zeroCurrent == 1){
    string switch1 = gameCurrent;
    string switch2 = gameCurrent;
    string switch3 = gameCurrent;
    swap(switch1[1],switch1[0]);
    swap(switch2[1],switch2[2]);
    swap(switch3[1],switch3[4]);
    vertex* newState1 = new vertex(switch1,distCurrent+1,zeroCurrent-1);
    vertex* newState2 = new vertex(switch2,distCurrent+1,zeroCurrent+1);
    vertex* newState3 = new vertex(switch3,distCurrent+1,zeroCurrent+3);
    adjacentVector.push_back(newState1);
    adjacentVector.push_back(newState2);
    adjacentVector.push_back(newState3);
  }
  else if(zeroCurrent == 2){
    string switch1 = gameCurrent;
    string switch2 = gameCurrent;
    swap(switch1[2],switch1[1]);
    swap(switch2[2],switch2[5]);
    vertex* newState1 = new vertex(switch1,distCurrent+1,zeroCurrent-1);
    vertex* newState2 = new vertex(switch2,distCurrent+1,zeroCurrent+3);
    adjacentVector.push_back(newState1);
    adjacentVector.push_back(newState2);
  }
  else if(zeroCurrent == 3){
    string switch1 = gameCurrent;
    string switch2 = gameCurrent;
    string switch3 = gameCurrent;
    swap(switch1[3],switch1[0]);
    swap(switch2[3],switch2[4]);
    swap(switch3[3],switch3[6]);
    vertex* newState1 = new vertex(switch1,distCurrent+1,zeroCurrent-3);
    vertex* newState2 = new vertex(switch2,distCurrent+1,zeroCurrent+1);
    vertex* newState3 = new vertex(switch3,distCurrent+1,zeroCurrent+3);
    adjacentVector.push_back(newState1);
    adjacentVector.push_back(newState2);
    adjacentVector.push_back(newState3);
  }
  else if(zeroCurrent == 4){
    string switch1 = gameCurrent;
    string switch2 = gameCurrent;
    string switch3 = gameCurrent;
    string switch4 = gameCurrent;
    swap(switch1[4],switch1[1]);
    swap(switch2[4],switch2[3]);
    swap(switch3[4],switch3[5]);
    swap(switch4[4],switch4[7]);
    vertex* newState1 = new vertex(switch1,distCurrent+1,zeroCurrent-3);
    vertex* newState2 = new vertex(switch2,distCurrent+1,zeroCurrent-1);
    vertex* newState3 = new vertex(switch3,distCurrent+1,zeroCurrent+1);
    vertex* newState4 = new vertex(switch4,distCurrent+1,zeroCurrent+3);
    adjacentVector.push_back(newState1);
    adjacentVector.push_back(newState2);
    adjacentVector.push_back(newState3);
    adjacentVector.push_back(newState4);
  }
  else if(zeroCurrent == 5){
    string switch1 = gameCurrent;
    string switch2 = gameCurrent;
    string switch3 = gameCurrent;
    swap(switch1[5],switch1[2]);
    swap(switch2[5],switch2[4]);
    swap(switch3[5],switch3[8]);
    vertex* newState1 = new vertex(switch1,distCurrent+1,zeroCurrent-3);
    vertex* newState2 = new vertex(switch2,distCurrent+1,zeroCurrent-1);
    vertex* newState3 = new vertex(switch3,distCurrent+1,zeroCurrent+3);
    adjacentVector.push_back(newState1);
    adjacentVector.push_back(newState2);
    adjacentVector.push_back(newState3);
  }
  else if(zeroCurrent == 6){
    string switch1 = gameCurrent;
    string switch2 = gameCurrent;
    swap(switch1[6],switch1[7]);
    swap(switch2[6],switch2[3]);
    vertex* newState1 = new vertex(switch1,distCurrent+1,zeroCurrent+1);
    vertex* newState2 = new vertex(switch2,distCurrent+1,zeroCurrent-3);
    adjacentVector.push_back(newState1);
    adjacentVector.push_back(newState2);
  }
  else if(zeroCurrent == 7){
    string switch1 = gameCurrent;
    string switch2 = gameCurrent;
    string switch3 = gameCurrent;
    swap(switch1[7],switch1[8]);
    swap(switch2[7],switch2[6]);
    swap(switch3[7],switch3[4]);
    vertex* newState1 = new vertex(switch1,distCurrent+1,zeroCurrent+1);
    vertex* newState2 = new vertex(switch2,distCurrent+1,zeroCurrent-1);
    vertex* newState3 = new vertex(switch3,distCurrent+1,zeroCurrent-3);
    adjacentVector.push_back(newState1);
    adjacentVector.push_back(newState2);
    adjacentVector.push_back(newState3);
  }
  else{
    string switch1 = gameCurrent;
    string switch2 = gameCurrent;
    swap(switch1[8],switch1[7]);
    swap(switch2[8],switch2[5]);
    vertex* newState1 = new vertex(switch1,distCurrent+1,zeroCurrent-1);
    vertex* newState2 = new vertex(switch2,distCurrent+1,zeroCurrent-3);
    adjacentVector.push_back(newState1);
    adjacentVector.push_back(newState2);
  }
  return adjacentVector;
}
/**
 *
 * @brief This function uses the breadth-first search algorithm to calculate the steps necessary to solve a puzzle
 *
 * This function uses a queue to handle one vertex at a time, and uses an unordered set to ensure no vertices are checked twice, calculates adjacent vertices, and checks all against the end puzzle state
 *
 *
 * @param stateZero the input state of the puzzle
 *
 *
 * @return an int indicating how many steps it takes to reach the end state
 **/
int shortestPath(vertex* stateZero){
  string goalState = "123456780";
  if(stateZero->getState() == goalState){
    return 0;
  }
  queue<vertex*> algoQueue;
  unordered_set<string> all;
  algoQueue.push(stateZero);
  while(!algoQueue.empty()){
    vertex* getStates = algoQueue.front();
    algoQueue.pop();
    vector<vertex*> neighbors = findAdjacent(getStates);
    for(int i = 0; i < neighbors.size(); i++){
      if(neighbors[i]->getState() == goalState || neighbors[i]->getDist() > 31){
	return neighbors[i]->getDist();
      }
      if(all.find(neighbors[i]->getState()) == all.end()){
	  algoQueue.push(neighbors[i]);
      }
      all.insert(neighbors[i]->getState());
    }
  }
  return 32;
}

/**
 *
 * @brief Main handles ihe input of the puzzle into a string, performs calculations on it, and ouputs the number of steps
 *
 * @return An int representing the end state of the program
 *
 **/

int main(){
  string initialState;
  char c;
  int index = 0;
  int zeropos;
  cout << "Enter Puzzle" << endl;
  while(cin.good()){
    cin >> c;
    if(c == '0'&& index <9){
      zeropos = index;
    }
    initialState += string(1,c);
    index++;
  }
  string initial = initialState.substr(0,9);
  vertex* stateZero = new vertex(initial, 0, zeropos);
  cout << "Solving puzzle" << endl;
  int result = shortestPath(stateZero);

  string output;

  if(result <=31){
    output = to_string(result);
  }else{
    output = "IMPOSSIBLE";
  }
  cout << output << endl;
  return 0;
}
