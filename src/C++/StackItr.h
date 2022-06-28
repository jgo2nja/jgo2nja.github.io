// Creator: James O'Connell jgo2nja
// Last Updated: 07 February 2022
#ifndef STACKITR_H
#define STACKITR_H

#include "StackNode.h"
#include "Stack.h"

class StackItr {
public:
    StackItr();
  
    StackItr(StackNode* theNode);

    bool isPastEnd() const;

    bool isPastBeginning() const;

    void moveForward();

    void moveBackward();

    int retrieve() const;

private:
    StackNode* current;

    friend class Stack;

    friend class StackNode;
};

#endif
