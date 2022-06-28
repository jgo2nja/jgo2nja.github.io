// Creator: James O'Connell jgo2nja
// Last Updated: 07 February 2022

#include "StackNode.h"
#include "Stack.h"
#include "StackItr.h"

#include <iostream>

using namespace std;

StackItr::StackItr(){
  current = NULL;
}

StackItr::StackItr(StackNode* theNode){
  current = theNode;
}

bool StackItr::isPastEnd() const{
  if ((*current).next == NULL){
    return true;
  }else{
    return false;
  }
}

bool StackItr::isPastBeginning() const{
  if ((*current).previous == NULL){
    return true;
  }else{
    return false;
  }
}

void StackItr::moveForward(){
  if (isPastEnd()){
  }else{
    current = (*current).next;
  }
}

void StackItr::moveBackward(){
  if (isPastBeginning()){
  }else{
    current = (*current).previous;
  }
}

int StackItr::retrieve() const{
  return (*current).value;
}

