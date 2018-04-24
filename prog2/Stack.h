/**~*~*
   Stack template

   This stack template is used to be a template for any type of Stack.
   It has the usual functions of push, pop, isEmpty, getCount, and getTop.
   One function named display is implemented here to display all the items in the stack.
*~**/
#ifndef DYNAMICSTACK_H
#define DYNAMICSTACK_H
#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
   // Structure for the stack nodes
   struct StackNode
   {
      T value;          // Value in the node
      StackNode *next;  // Pointer to next node
   };

   StackNode *top;     // Pointer to the stack top
   int count;

public:
   //Constructor
   Stack(){top = NULL; count = 0;}

   // Destructor
   ~Stack();

   // Stack operations
   bool push(T);
   bool pop(T &);
   bool isEmpty();
   int getCount();
   int getTop();
   void display();
};

/**~*~*
   Destructor
*~**/
template <class T>
Stack<T>::~Stack()
{
   StackNode *currNode, *nextNode;

   // Position nodePtr at the top of the stack.
   currNode = top;

   // Traverse the list deleting each node.
   while (currNode) //while (currNode != NULL)
   {
      nextNode = currNode->next;
      delete currNode;
      currNode = nextNode;
   }
}

/**~*~*
  Member function push pushes the argument onto
  the stack.
*~**/
template <class T>
bool Stack<T>::push(T item)
{
   StackNode *newNode; // Pointer to a new node

   // Allocate a new node and store num there.
   newNode = new StackNode;
   if (!newNode)
       return false;
   newNode->value = item;

   // Update links and counter
   newNode->next = top;
   top = newNode;
   count++;

   return true;
}

/**~*~*
  Member function pop pops the value at the top
  of the stack off, and copies it into the variable
  passed as an argument.
*~**/
template <class T>
bool Stack<T>::pop(T &item)
{
   StackNode *temp; // Temporary pointer

   // empty stack
   if (count == 0)
       return false;

   // pop value off top of stack
   item = top->value;
   temp = top->next;
   delete top;
   top = temp;
   count--;

   return true;
}

/**~*~*
  Member function isEmpty returns true if the stack
  is empty, or false otherwise.
*~**/
template <class T>
bool Stack<T>::isEmpty()
{
   return count == 0;
}

/**~*~*
  Member function getCount returns count of the number of items in the stack
*~**/
template <class T>
int Stack<T>::getCount()
{
    return count;
}

/**~*~*
  Member function getTop returns the top item(value) in the stack
*~**/
template <class T>
int Stack<T>::getTop()
{
    return top->value;
}

/**~*~*
  Member function display displays all the items in the stack.
*~**/
template <class T>
void Stack<T>::display()
{
    StackNode *pCur;

    // Position pCur: skip the head of the list.
    pCur = top;
    // While pCur points to a node, traverse the list.

    cout << "\nStack after reading file(from top to bottom): \n";

    if(count > 0) //if stack is not empty
    {
        while (pCur)
        {
            // Display the value in this node.
            cout << pCur->value << " ";
            // Move to the next node.
            pCur = pCur->next;
        }
        cout << "\n";
    }

    else //if stack is empty
    {
        cout << "Error: Cannot display stack because it is empty.\n";
    }
}
#endif
