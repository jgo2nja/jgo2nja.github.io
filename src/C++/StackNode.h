// Creator: James O'Connell jgo2nja (aside from given methods)
// Last Updated: 06 February 2022

#ifndef STACKNODE_H
#define STACKNODE_H

#include <iostream>

using namespace std;

class StackNode {
public:
    StackNode();

private:
    int value;         
    StackNode* next;     
    StackNode* previous;

    friend class Stack;

    friend class StackItr;

};

#endif
