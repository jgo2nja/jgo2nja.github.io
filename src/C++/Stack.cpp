// Creator: James O'Connell jgo2nja
// Last Updated: 06 February 2022

#include "Stack.h"
#include "StackItr.h"
#include "StackNode.h"
#include <cstdlib>
#include <string>

using namespace std;

Stack::Stack(){
  head = new StackNode();
  tail = new StackNode();
  (*head).next = tail;
  (*head).previous = NULL;
  (*tail).previous = head;
  (*tail).next = NULL;
}

Stack::Stack(const Stack& source){
  head = new StackNode();
  tail = new StackNode();
  (*head).next = tail;
  (*head).previous = NULL;
  (*tail).previous = head;
  (*tail).next = NULL;

  StackItr iter(source.head->next);
  while(!iter.isPastEnd()){
    push(iter.retrieve());
    iter.moveForward();
  }
}

Stack::~Stack(){
  (*this).makeEmpty();
  delete head;
  delete tail;
}

Stack& Stack::operator=(const Stack& source){
  if (this == &source){
    return *this;
  }else {
    (*this).makeEmpty();
    
    StackItr iter(source.head->next);
    while(!iter.isPastEnd()){
     push(iter.retrieve());
     iter.moveForward();
    }
    
  }
  return *this;
}

bool Stack::empty() const{
  if ((*head).next == tail){
    return true;
  }else{
    return false;
  }
}

void Stack::makeEmpty(){
  while(!(*this).empty()){
    (*this).pop();
  }
}

void Stack::push(int x){
  StackNode * newNode = new StackNode();
  (*((*tail).previous)).next = newNode;
  (*newNode).previous = &(*((*tail).previous));
  (*tail).previous = newNode;
  (*newNode).next = tail;
  (*newNode).value = x;  
}

void Stack::pop(){
  if((*this).empty()){
    cout << "Error: Program terminated after attempting to access empty stack (too many operators in input)" << endl;
    exit(-1);
  }else{
    StackNode * deleteNode = (*tail).previous;
    (*((*deleteNode).next)).previous = &(*((*deleteNode).previous));
    (*((*deleteNode).previous)).next = &(*((*deleteNode).next));
    delete deleteNode;
  }  
}

int Stack::top() const{
  if ((*this).empty()){
    cout << "Error: Program terminated after attempting to access empty stack (too many operators in input)" << endl;
    exit(-1);
  }else{
    return (*((*tail).previous)).value;
  }
}
