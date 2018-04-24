// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// modified by Minh An Cao

//
//  CIS 22C - Winter 2017
//  Homework 4
//
//  Menu-driven program that implements a simple BST-based database. Creates the BST from an input text file.
//
// Student Score: 85
//
// Instructor Score:
//

/*
Name: Minh An Cao
Date: 2/26/17
IDE: CodeBlocks and MSVS
*/

#include "BinarySearchTree.h"  // BST ADT
#include "Student.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

void display(Student & stud);
void displayList(Student & stud, int & level, int & indent);
void displayStudentInfo(Student temp);
void searchByPrimaryKey(BinarySearchTree<Student>* tree, int target);
void findSmallest(BinarySearchTree<Student>* tree);
void findLargest(BinarySearchTree<Student>* tree);
void readFile(BinarySearchTree<Student>* &tree);
void displayMenu();
void menu(BinarySearchTree<Student>* &tree1Ptr);

// display function to pass to BST traverse functions
void display(Student & stud)
{
   cout << stud.getId() << endl;
}

// display function to pass to BST traverse functions
void displayList(Student & stud, int & level, int & indent)
{
   cout << setw(indent) << level << ". " << stud.getId() << endl;
}

// display function to pass to BST traverse functions
void displayStudentInfo(Student temp)
{
    cout << "ID: " << temp.getId() << endl;
    cout << "Name: " << temp.getName() << endl;
    cout << "GPA: " << fixed << setprecision(2) << temp.getGpa() << endl;
}

void searchByPrimaryKey(BinarySearchTree<Student>* tree, int target)
{
    Student temp1;
    Student temp;
    temp1.setId(target);

    bool found = tree->getEntry(temp1, temp);


    if (!found)
    {
        cout << "\nStudent is not in the tree!\n";
    }

    else
    {
        cout << "\nStudent found!\n";
        displayStudentInfo(temp);
    }
}

void findSmallest(BinarySearchTree<Student>* tree)
{
    Student temp;

    bool found = tree->findSmallest(temp);


    if (!found)
    {
        cout << "\nNothing is in the tree!\n";
    }

    else
    {
        cout << "\nSmallest: \n";
        displayStudentInfo(temp);
    }
}

void findLargest(BinarySearchTree<Student>* tree)
{
    Student temp;

    bool found = tree->findLargest(temp);


    if (!found)
    {
        cout << "\nNothing is in the tree!\n";
    }

    else
    {
        cout << "\nLargest: \n";
        displayStudentInfo(temp);
    }
}

void readFile(BinarySearchTree<Student>* &tree)
{
    Student temp;
    ifstream inputfile;
    inputfile.open("gpa.txt");
    if(!inputfile.good())
    {
        cout <<"Error opening file!\n";
        exit(101);
    }

    int id;
    string idS;
    string name;
    string gpaS;
    double gpa;

    while(!inputfile.eof())
    {
        getline(inputfile, idS, ' ');
        getline(inputfile, name, ';');
        getline(inputfile, gpaS);
        id = atof(idS.c_str()); //to make the string of the elevation into a double
        gpa = atof(gpaS.c_str()); //to make the string of the elevation into a double
        temp.setName(name);
        temp.setId(id);
        temp.setGpa(gpa);
        tree->insert(temp);
    }
    inputfile.close();
}

void displayMenu()
{
    cout << "\n================================================================================";
    cout << setw(42) << "MENU\n";
    cout << "================================================================================\n";
    cout << "D - Depth-First Traversals: inorder, preorder, postorder\n"; // recursive
    cout << "I - Iterative Depth-First Traversals: inorder, preorder, postorder\n";
    cout << "B - Tree Breadth-First Traversals: Print by level\n"; //iterative
    cout << "S - Search by the primary key (student ID - unique key)\n"; // iterative
    cout << "M - Find the smallest\n"; // recursive
    cout << "X - Find the largest\n"; // recursive
    cout << "T - Print the BST as an indented list (show level numbers)\n";// see below // recursive
    cout << "H - Help - to show the menu\n";
    cout << "E - Exit\n";
}

void menu(BinarySearchTree<Student>* &tree1Ptr)
{
    displayMenu();

    char input;

    do {
        cin >> input;
        switch(input) {
            case 'D': case 'd':
                cout << "Inorder: \n";
                tree1Ptr->inOrder(display);
                cout << "\n\nPreorder: \n";
                tree1Ptr->preOrder(display);
                cout << "\n\nPostorder: \n";
                tree1Ptr->postOrder(display);
                break;

            case 'I': case 'i':
                cout << "Inorder: \n";
                tree1Ptr->iterInOrder(display);
                cout << "\n\nPreorder: \n";
                tree1Ptr->iterPreOrder(display);
                cout << "\n\nPostorder: \n";
                tree1Ptr->iterPostOrder(display);
                break;

            case 'B': case 'b':
                cout << "Breadthorder: \n";
                tree1Ptr->breadthOrder(display);
                break;

            case 'S': case 's':
                int searchid;
                cout << "Enter student ID to search: \n";
                cin >> searchid;
                searchByPrimaryKey(tree1Ptr, searchid);
                break;

            case 'M': case 'm':
                findSmallest(tree1Ptr);
                break;

            case 'X': case 'x':
                findLargest(tree1Ptr);
                break;

            case 'T': case 't':
                tree1Ptr->printList(displayList);
                break;

            case 'A': case 'a':
                cout << "Developer: Minh An Cao\n";
                break;

            case 'H': case 'h':
                displayMenu();
                break;

            case 'E': case 'e':
                cout << "Program exiting...\n";
                break;

            default:
                cout << "Invalid input. Please pick an option from the menu.\n";
                input = 'H'; //used to avoid asking user what user wants to do next
                break;
        }

        if(input != 'H' && input != 'h' && input != 'e' && input != 'E')
        cout << "\nWhat would you like to do next?\n";
    }while(input != 'E' && input != 'e');
}

int main()
{
   BinarySearchTree<Student>* tree1Ptr = new BinarySearchTree<Student>();

   readFile(tree1Ptr);
   menu(tree1Ptr);
   tree1Ptr->clear(); //destroys tree

   return 0;
}
