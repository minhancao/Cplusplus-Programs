//
//  CIS 22C - Winter 2017
//  Homework 3
//
//  Build and process a sorted circularly doubly-linked list of Mountain objects with the use of a sentinel node.
//
// Student Score: 88
//
// Instructor Score:
//

/*
Name: Minh An Cao
Date: 2/9/17
IDE: CodeBlocks and MSVS
*/

#include "MountainList.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

void printInfo();
void readFromFile(MountainList &list);
void deleteManager(MountainList &list);
void searchManager(const MountainList &list);

int main()
{
    MountainList list;

    printInfo();
    readFromFile(list);
    list.printforward();
	list.printbackward();
    cout << "There are " << list.getCounter() << " items in the list\n\n";
    searchManager(list);
    deleteManager(list);
    cout << "\nThere are " << list.getCounter() << " items in the list\n\n";
    list.printforward();
	list.printbackward();

    return 0;
}
//**************************************************
// Print info about the project
//**************************************************
void printInfo()
{
    cout << "\t\t\t Build and process a sorted linked list\n"
         << "\t\t\t     data: Mountains in US\n\n";
}

//**************************************************
// Read items from file and inserts them into a
// sorted linked list
//**************************************************
void readFromFile(MountainList &list)
{
    Mountain temp;
    string space;

    ifstream inputfile;
    inputfile.open("mountains.txt");
    if(!inputfile.good())
    {
        cout <<"Error opening file!\n";
        exit(101);
    }

    string n;
    string stringE; //to read the elevation as a string
    double e; //to make the string of the elevation into a double
    string r;
    string s;

    while(!inputfile.eof())
    {
        getline(inputfile, n, ';');
        getline(inputfile, stringE, ';'); //to read the elevation as a string
        getline(inputfile, r, ';');
        getline(inputfile, s, ';');
        getline(inputfile, space);
        e = atof(stringE.c_str()); //to make the string of the elevation into a double
        temp.setName(n);
        temp.setElevation(e);
        temp.setRange(r);
        temp.setState(s);
        list.insertNode(temp);
    }
    inputfile.close();

}

//**************************************************
// Delete manager: prompt the user to enter
// items, and if found, delets them from the list
//**************************************************
void deleteManager(MountainList &list)
{
    string deleteName;

    cout << "\n ====== DELETE ======\n\n";
    do
    {

        cout<<"Enter name of mountain to delete or QUIT to stop deleting: \n";
        getline(cin,deleteName);
        if(deleteName!= "quit" && deleteName != "QUIT")
        {
            if(list.deleteNode(deleteName))
                cout << deleteName << " deleted\n";
            else
                cout << deleteName << " not found\n";

        }

    }while(deleteName!= "quit" && deleteName != "QUIT");

}
//**************************************************
// Search manager: prompt the user to enter
// items, and if found, displays related information
//**************************************************
void searchManager(const MountainList &list)
{
	string choice;

    cout << "\n ====== SEARCH ======\n\n";
    do
    {
		cout << "\nEnter name of mountain to search or QUIT to stop searching: " << endl;
		getline(cin, choice);
        if (choice != "QUIT" && choice != "quit")
        {
            list.searchByName(choice);
        }

    }while(choice != "QUIT" && choice != "quit");

}
/* =============== OUTPUT ===============
                         Build and process a sorted linked list
                             data: Mountains in US

=====              =========  =====                  =====
Name               Elevation  Range                  State
=====              =========  =====                  =====
Adams                  12281  Cascade Range          Washington
Antero                 14276  Sawatch Range          Colorado
Bachelor                9068  Cascade Range          Oregon
Castle Peak             9109  Sierra Nevada          California
Churchill              15638  Saint Elias Mountains  Alaska
Doublet Peak           13600  Wind River Range       Wyoming
Granite Peak           12807  Beartooth Mountains    Montana
Half Dome               8836  Yosemite National Park California
Jeff Davis Peak        12771  Snake Range            Nevada
Mauna Kea              13803  Mauna Kea              Hawaii
Pyramid Peak            9985  Crystal Range          California
Rainier                14411  Cascade Range          Washington
Shasta                 14179  Cascade Range          California
Torbert                11413  Tordillo Mountains     Alaska

=====              =========  =====                  =====
Name               Elevation  Range                  State
=====              =========  =====                  =====
Torbert                11413  Tordillo Mountains     Alaska
Shasta                 14179  Cascade Range          California
Rainier                14411  Cascade Range          Washington
Pyramid Peak            9985  Crystal Range          California
Mauna Kea              13803  Mauna Kea              Hawaii
Jeff Davis Peak        12771  Snake Range            Nevada
Half Dome               8836  Yosemite National Park California
Granite Peak           12807  Beartooth Mountains    Montana
Doublet Peak           13600  Wind River Range       Wyoming
Churchill              15638  Saint Elias Mountains  Alaska
Castle Peak             9109  Sierra Nevada          California
Bachelor                9068  Cascade Range          Oregon
Antero                 14276  Sawatch Range          Colorado
Adams                  12281  Cascade Range          Washington

There are 14 items in the list


 ====== SEARCH ======


Enter name of mountain to search or QUIT to stop searching:
Half Dome

FOUND:
Half Dome               8836  Yosemite National Park California


Enter name of mountain to search or QUIT to stop searching:
castel peak
castel peak NOT FOUND


Enter name of mountain to search or QUIT to stop searching:
QUIT

 ====== DELETE ======

Enter name of mountain to delete or QUIT to stop deleting:
Half Dome
Half Dome deleted
Enter name of mountain to delete or QUIT to stop deleting:
Castle pek
Castle pek not found
Enter name of mountain to delete or QUIT to stop deleting:
Castle Peak
Castle Peak deleted
Enter name of mountain to delete or QUIT to stop deleting:
QUIT

There are 12 items in the list

=====              =========  =====                  =====
Name               Elevation  Range                  State
=====              =========  =====                  =====
Adams                  12281  Cascade Range          Washington
Antero                 14276  Sawatch Range          Colorado
Bachelor                9068  Cascade Range          Oregon
Churchill              15638  Saint Elias Mountains  Alaska
Doublet Peak           13600  Wind River Range       Wyoming
Granite Peak           12807  Beartooth Mountains    Montana
Jeff Davis Peak        12771  Snake Range            Nevada
Mauna Kea              13803  Mauna Kea              Hawaii
Pyramid Peak            9985  Crystal Range          California
Rainier                14411  Cascade Range          Washington
Shasta                 14179  Cascade Range          California
Torbert                11413  Tordillo Mountains     Alaska

=====              =========  =====                  =====
Name               Elevation  Range                  State
=====              =========  =====                  =====
Torbert                11413  Tordillo Mountains     Alaska
Shasta                 14179  Cascade Range          California
Rainier                14411  Cascade Range          Washington
Pyramid Peak            9985  Crystal Range          California
Mauna Kea              13803  Mauna Kea              Hawaii
Jeff Davis Peak        12771  Snake Range            Nevada
Granite Peak           12807  Beartooth Mountains    Montana
Doublet Peak           13600  Wind River Range       Wyoming
Churchill              15638  Saint Elias Mountains  Alaska
Bachelor                9068  Cascade Range          Oregon
Antero                 14276  Sawatch Range          Colorado
Adams                  12281  Cascade Range          Washington

DEBUG - Destructor: Now deleting Adams
DEBUG - Destructor: Now deleting Antero
DEBUG - Destructor: Now deleting Bachelor
DEBUG - Destructor: Now deleting Churchill
DEBUG - Destructor: Now deleting Doublet Peak
DEBUG - Destructor: Now deleting Granite Peak
DEBUG - Destructor: Now deleting Jeff Davis Peak
DEBUG - Destructor: Now deleting Mauna Kea
DEBUG - Destructor: Now deleting Pyramid Peak
DEBUG - Destructor: Now deleting Rainier
DEBUG - Destructor: Now deleting Shasta
DEBUG - Destructor: Now deleting Torbert

Process returned 0 (0x0)   execution time : 53.110 s
Press any key to continue.
*/
