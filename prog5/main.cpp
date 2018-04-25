// main test driver for Heap Homework 5 Assignment
// Created by Frank M. Carrano and Tim Henry.
// modified by Minh An Cao

//
//  CIS 22C - Winter 2017
//  Homework 5
//
//  Uses a heap like a priority queue to sort the priority and serial numbers of customers and prints out the heap based on priority or serial number.
//
// Student Score: 85
//
// Instructor Score:
//

/*
Name: Minh An Cao
Date: 3/16/17
IDE: CodeBlocks and MSVS
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Customer.h"
#include "ArrayMaxHeap.h"
#include <iomanip>

using namespace std;

void readFile(ArrayMaxHeap<Customer>* &serialHeap, ArrayMaxHeap<Customer>* &priorityHeap);
void displayAsIndented(Customer & cust, int & indent);
void displayAsPrioritySequence(ArrayMaxHeap<Customer>* &heap);


void readFile(ArrayMaxHeap<Customer>* &serialHeap, ArrayMaxHeap<Customer>* &priorityHeap)
{
    ifstream infile;
    infile.open("overbooked.txt");

    if(!infile.good())
    {
        cout <<"Error opening file!\n";
        exit(101);
    }

    string years;
    string mileage;
    string name;

    double priority;
    double serialNumber;
    int sequenceNum = 1;

    int yrs;
    int miles;

    while(!infile.eof())
    {
        getline(infile, years, ' ');
        getline(infile, mileage, ' ');
        getline(infile, name);

        yrs = atoi(years.c_str());
        miles = atoi(mileage.c_str());

        priority = miles /(1000 + yrs - sequenceNum);
        serialNumber = priority * (100 + (100 - sequenceNum));

        Customer cust;
        cust.setYears(yrs);
        cust.setMileage(miles);
        cust.setName(name);
        cust.setPriority(priority);
        cust.setSerialNum(serialNumber);

        serialHeap->addAsSerial(cust);
        priorityHeap->addAsPriority(cust);
        sequenceNum++;
    }

}

// display function
void displayAsIndented(Customer & cust, int & indent)
{
	cout << setw(indent) << cust.getSerialNum() << " - " << cust.getName() << endl;
}


// display function
void displayAsPrioritySequence(ArrayMaxHeap<Customer>* &heap)
{
    Customer cust;

    int size = heap->getNumberOfNodes(); //gets number of nodes before deleting them

	for (int i = 0;i<size;i++)
    {
        heap->removeAsPriority(cust);
        cout << "\nName: " << cust.getName() << "\nPriority: " << cust.getPriority() << "\nSerial Number: " << cust.getSerialNum() << endl;
    }
}

int main()
{
    ArrayMaxHeap<Customer>* serialHeap = new ArrayMaxHeap<Customer>();
    ArrayMaxHeap<Customer>* priorityHeap = new ArrayMaxHeap<Customer>();
    readFile(serialHeap, priorityHeap);

    cout << "------------------------------------------------------";
    cout << "\nIndented Tree for Serial Heap: " << endl;
    cout << "------------------------------------------------------\n";
    serialHeap->printList(displayAsIndented); //displays indented tree of heap sorted based on serial number

    cout << "\n------------------------------------------------------";
    cout << "\nPriority Sequence List for Priority Heap: " << endl;
    cout << "------------------------------------------------------";
    displayAsPrioritySequence(priorityHeap);

    system("pause");

    return 0;
}

/*Output results:
------------------------------------------------------
Indented Tree for Serial Heap:
------------------------------------------------------
18321 - Jonathan Nguyen
   18216 - Paul Ng
           13032 - Peter Edwards
                   10348 - Robert Hill
                           10192 - Tom Martin
                            9699 - Steven Chen
                   12480 - Vincent Gonzales
                            6494 - Paula Hung
                           12012 - Vladimir Johnson
            7938 - Steve Che
                    3315 - Mary Lou Gilley
                    3990 - Lou Masson
   17424 - Amanda Trapp
           17266 - Bob Che
                   16732 - Linda Lee
                   11781 - Dave Lightfoot
           13896 - Warren Rexroad
                    9858 - Sue Andrews
                    6105 - Joanne Brown

------------------------------------------------------
Priority Sequence List for Priority Heap:
------------------------------------------------------
Name: Paul Ng
Priority: 99
Serial Number: 18216

Name: Jonathan Nguyen
Priority: 93
Serial Number: 18321

Name: Bob Che
Priority: 89
Serial Number: 17266

Name: Linda Lee
Priority: 89
Serial Number: 16732

Name: Amanda Trapp
Priority: 88
Serial Number: 17424

Name: Peter Edwards
Priority: 72
Serial Number: 13032

Name: Warren Rexroad
Priority: 72
Serial Number: 13896

Name: Vladimir Johnson
Priority: 66
Serial Number: 12012

Name: Vincent Gonzales
Priority: 65
Serial Number: 12480

Name: Dave Lightfoot
Priority: 63
Serial Number: 11781

Name: Steven Chen
Priority: 53
Serial Number: 9699

Name: Sue Andrews
Priority: 53
Serial Number: 9858

Name: Tom Martin
Priority: 52
Serial Number: 10192

Name: Robert Hill
Priority: 52
Serial Number: 10348

Name: Steve Che
Priority: 42
Serial Number: 7938

Name: Paula Hung
Priority: 34
Serial Number: 6494

Name: Joanne Brown
Priority: 33
Serial Number: 6105

Name: Lou Masson
Priority: 21
Serial Number: 3990

Name: Mary Lou Gilley
Priority: 17
Serial Number: 3315

Process returned 0 (0x0)   execution time : 0.044 s
Press any key to continue.
*/
