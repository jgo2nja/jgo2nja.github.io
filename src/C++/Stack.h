// Creator: James O'Connell jgo2nja (aside from given methods)
// Last Updated: 06 February 2022

#ifndef STACK_H
#define STACK_H

#include "StackNode.h"

using namespace std;


class Stack {
public:
  
    Stack();

    Stack(const Stack& source);

    ~Stack();

    Stack& operator=(const Stack& source);

    bool empty() const;

    void makeEmpty();

    void push(int x);

    void pop();

    int top() const;

private:
    StackNode* head;
  
    StackNode* tail;

    friend class StackItr;
};

#endif
