//
//  CIS 22C - Winter 2017
//  Homework 2
//
//  STACK ADT
//
// Project: One of the stack applications is to backtrack. As an example take a list of numbers.
// Each time we read 0, display the number of elements in the stack, each time we read 1, display
// the element at the top of the stack, each time we read a positive number we push it onto the stack,
// and each time we read a negative number, we pop and print as many values from the stack as
// the absolute value of the negative number. If there are fewer numbers in the stack, print a message and
// nothing else. When the end of the file is detected, print a message and the items left in the stack.
//
// GRADING
//
// 10 - Create a project consisting of 2 files: Stack.h and 22C_Hw2.cpp
// 10 - Create and process the array of strings
// 45 - Read numbers from file and process stack
// 10 - Implement the getTop function
// 10 - Implement the getCount function
// 10 - The main() function
//  5 - Self assessment
// Did you write comments for the new functions?
// Did you completely test the program?
// Did you save the updated output at the end of this source file as a comment?
//
// Student Score: 90
//
// Instructor Score:
//

/*
Name: Minh An Cao
Date: 1/25/17
Compiler: CodeBlocks
*/

#include <iostream>
#include <fstream>
#include <cmath>

#include "Stack.h"

using namespace std;

// Constants for the menu choices
const int numbers1 = 1,
          numbers2  = 2,
          numbers3 = 3,
          QUIT = 4;

//Function prototypes:
int menu();
int getValidNum(int, int);
void processFile(int, Stack<int> *);
void pushItem(Stack<int> *, int);
void popItem(Stack<int> *);

int main()
{
    //Creates stack object
    Stack<int> *stack = new Stack<int>;

    string fileList[] = {"numbers1.txt", "numbers2.txt", "numbers3.txt", "QUIT"};
	int choice; //for the menu
	int holder;
	ifstream readFile;

    while ((choice = menu())!= QUIT)
    {
        switch (choice)
        {
           case numbers1:
                readFile.open(fileList[0].c_str()); //opens numbers1.txt

                while(readFile >> holder)
                {
                    processFile(holder, stack); //process function for the numbers in the text file
                    if(readFile.eof())
                    {
                        stack->display();
                    }
                }

                stack->~Stack(); //clears stack
                readFile.close();
                readFile.clear();
                break;

           case numbers2:
                stack = new Stack<int>(); //constructs new stack
                readFile.open(fileList[1].c_str()); //opens numbers2.txt

                while(readFile >> holder)
                {
                    processFile(holder, stack);
                    if(readFile.eof())
                    {
                        stack->display();
                    }
                }

                stack->~Stack(); //clears stack
                readFile.close();
                readFile.clear();
                break;

           case numbers3:
               {
                stack = new Stack<int>();
                readFile.open(fileList[2].c_str()); //opens numbers3.txt

                while(readFile >> holder)
                {
                    processFile(holder, stack);
                    if(readFile.eof())
                    {
                        stack->display();
                    }
                }

                stack->~Stack(); //clears stack
                readFile.close();
                readFile.clear();
                break;
               }
        }
    }

    delete stack;
    cout << "\n\t*** THE END ***\n";

    return 0;
}

/**~*~*
   The menu function displays the menu and gets
   the user's choice, which is assigned to the
   reference parameter.
*~**/
int menu()
{
    int choice;
     // Display the menu and get the user's choice.
     cout << "\n======================================================="
          << "\nWhich file would you like to read into the stack?\n\t"
          << numbers1
          << " - numbers1.txt\n\t"
          << numbers2
          << " - numbers2.txt\n\t"
          << numbers3
          << " - numbers3.txt\n\t"
          << QUIT
          << " - Quit the program\n"
          << "Enter your choice: ";

     choice = getValidNum(numbers1, QUIT);
     return choice;
}

/**~*~*
   This function prompts the user to enter an integer number within a given range
   If the input is not valid (not a number or if it is outside of the range) it
   prompts the user to enter a new number, until the input is valid.
*~**/
int getValidNum(int low, int high)
{
    int num;
    bool success;

    do
    {
        cout << "Please enter a number (" << low << " to " << high << "): ";
        success = cin >> num;
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(!success || num < low || num > high);

    return num;
}

/**~*~*
   This function processes the text file and adds it to the stack if it's a positive number,
   prints number of elements in the stack if it's 0, prints out the top value in the stack if it's 1,
   and removes the top value or item if it's a negative number.
*~**/
void processFile(int holder, Stack<int> *stack)
{
    if(holder == 0)//if number processed was 0, print out number of elements in stack
    {
        cout << "\nNumber of items in stack: " << stack->getCount() << endl;
    }

    if(holder == 1 && !stack->isEmpty()) //if number processed is 1 and stack is not empty, print out top item in stack
    {
        cout << "\nValue of top item in stack: " << stack->getTop() << endl;
    }

    if(holder == 1 && stack->isEmpty()) //if number processed is 1 and stack is empty, lets the user know the stack is empty
    {
        cout << "Error: Cannot display value of top item in stack: \n";
        cout << "Stack is empty!" << endl;
    }

    if(holder > 1)//if number processed is positive and greater than 1, pushes the number processed into the stack
    {
        pushItem(stack, holder);
    }

    if(holder < 0)//if number processed is negative, pops out the top item in the stack
    {
        if (stack->isEmpty()) //if stack is empty, there's nothing to pop out
        {
            cout << "\nError: Stack is empty, cannot pop anything out!\n";
        }

        if (stack->getCount() < abs(holder)) //if the absolute value of the negative number processed is bigger
            //than the stack count, then the stack cannot pop out more items than it actually has
        {
            cout << "\nError: Cannot pop out " << abs(holder) << " items from the stack with a count of " << stack->getCount() << "." << endl;
        }

        if(stack->getCount() >= abs(holder) && !stack->isEmpty())//stack must not be empty and stack count must be higher than the
            //absolute value of the negative number processed in order for the stack to pop out its top item
        {
            for (int i = 0;i<abs(holder);i++)
            {
                    popItem(stack);
            }
        }
    }
}

/**~*~*
   This function pushes the number(positive and greater than 1) processed from the text file into the stack.
*~**/
void pushItem(Stack<int> *stack, int item)
{
     cout << "\n\t" << item << " will be pushed onto the stack\n";
     stack->push(item);
}

/**~*~*
   This function removes the top item in the stack.
*~**/
void popItem(Stack<int> *stack)
{
    bool status;
     int item = 0;

     // Pop the item.
     status = stack->pop(item);

     // Display the item.
     if (status)
     {
        cout << "\n\t" << item << " was popped.\n\n";
     }

     else
     {
        cout << "\n\t*** Empty stack! ***\n\n";
     }
}


/* =============== OUTPUT ===============

=======================================================
Which file would you like to read into the stack?
        1 - numbers1.txt
        2 - numbers2.txt
        3 - numbers3.txt
        4 - Quit the program
Enter your choice: Please enter a number (1 to 4): 1

        10 will be pushed onto the stack

        20 will be pushed onto the stack

        30 will be pushed onto the stack

Value of top item in stack: 30

        40 will be pushed onto the stack

Number of items in stack: 4

        50 will be pushed onto the stack

        50 was popped.


        40 was popped.


        15 will be pushed onto the stack

        25 will be pushed onto the stack

        25 was popped.


        15 was popped.


        30 was popped.


        60 will be pushed onto the stack

        80 will be pushed onto the stack

Stack after reading file(from top to bottom):
80 60 20 10

=======================================================
Which file would you like to read into the stack?
        1 - numbers1.txt
        2 - numbers2.txt
        3 - numbers3.txt
        4 - Quit the program
Enter your choice: Please enter a number (1 to 4): 2

        10 will be pushed onto the stack

        20 will be pushed onto the stack

        30 will be pushed onto the stack

Error: Cannot pop out 6 items from the stack with a count of 3.

        40 will be pushed onto the stack

        50 will be pushed onto the stack

        50 was popped.


        40 was popped.


        30 was popped.


        20 was popped.


        10 was popped.


Stack after reading file(from top to bottom):
Error: Cannot display stack because it is empty.

=======================================================
Which file would you like to read into the stack?
        1 - numbers1.txt
        2 - numbers2.txt
        3 - numbers3.txt
        4 - Quit the program
Enter your choice: Please enter a number (1 to 4): 3

        15 will be pushed onto the stack

        25 will be pushed onto the stack

        35 will be pushed onto the stack

        45 will be pushed onto the stack

Number of items in stack: 4

Value of top item in stack: 45

Number of items in stack: 4

        55 will be pushed onto the stack

        65 will be pushed onto the stack

        75 will be pushed onto the stack

Number of items in stack: 7

Value of top item in stack: 75

Number of items in stack: 7

Error: Cannot pop out 50 items from the stack with a count of 7.

Number of items in stack: 7

Value of top item in stack: 75

Number of items in stack: 7

        75 was popped.


        65 was popped.


        55 was popped.


        45 was popped.


        35 was popped.


        10 will be pushed onto the stack

        40 will be pushed onto the stack

        50 will be pushed onto the stack

        60 will be pushed onto the stack

        70 will be pushed onto the stack

        80 will be pushed onto the stack

        90 will be pushed onto the stack

Number of items in stack: 9

Value of top item in stack: 90

Number of items in stack: 9

        90 was popped.


        80 was popped.


        70 was popped.


        13 will be pushed onto the stack

        23 will be pushed onto the stack

        33 will be pushed onto the stack

        43 will be pushed onto the stack

        54 will be pushed onto the stack

        54 was popped.


        43 was popped.


        33 was popped.


        23 was popped.


        13 was popped.


Number of items in stack: 6

Value of top item in stack: 60

Number of items in stack: 6

        17 will be pushed onto the stack

        27 will be pushed onto the stack

        7 will be pushed onto the stack

        47 will be pushed onto the stack

        57 will be pushed onto the stack

        67 will be pushed onto the stack

        77 will be pushed onto the stack

        87 will be pushed onto the stack

        97 will be pushed onto the stack

        19 will be pushed onto the stack

        29 will be pushed onto the stack

        39 will be pushed onto the stack

        49 will be pushed onto the stack

        59 will be pushed onto the stack

        69 will be pushed onto the stack

        79 will be pushed onto the stack

        89 will be pushed onto the stack

        99 will be pushed onto the stack

Number of items in stack: 24

Value of top item in stack: 99

        99 was popped.


        89 was popped.


        79 was popped.


        69 was popped.


        59 was popped.


        49 was popped.


Number of items in stack: 18

Value of top item in stack: 39

        14 will be pushed onto the stack

        24 will be pushed onto the stack

        34 will be pushed onto the stack

        44 will be pushed onto the stack

Number of items in stack: 22

Error: Cannot pop out 150 items from the stack with a count of 22.

        54 will be pushed onto the stack

        64 will be pushed onto the stack

Number of items in stack: 24

Stack after reading file(from top to bottom):
64 54 44 34 24 14 39 29 19 97 87 77 67 57 47 7 27 17 60 50 40 10 25 15

=======================================================
Which file would you like to read into the stack?
        1 - numbers1.txt
        2 - numbers2.txt
        3 - numbers3.txt
        4 - Quit the program
Enter your choice: Please enter a number (1 to 4): 4

        *** THE END ***

Process returned 0 (0x0)   execution time : 5.269 s
Press any key to continue.


*/

