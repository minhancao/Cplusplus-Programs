//
//  CIS 22C - Winter 2017
//  Homework 1
//
//  Build and process a sorted singly-linked list of Mountain objects
//
// GRADING
//
// 10 - Create a project consisting of at least 5 source and header files
// 10 - Display the number of items in the list
// 20 - Replace the Mountain structure by a Mountain class
// 10 - Improved displayList()
// 10 - Improved searchList()
// 10 - Improved other functions
// 25 - New feature
//  5 - Self assessment
// Did you write comments for the new functions?
// Did you completely test the program?
// Did you save the updated output at the end of this source file as a comment?
//
// Student Score: 95
//
// Instructor Score:
//

/*
Name: Minh An Cao
Date: 1/18/17
IDE: CodeBlocks and MSVS
*/

#include "MountainList.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

void printInfo();
void readFromFile(MountainList &list);
void deleteManager(MountainList &list);
void searchManager(const MountainList &list);

int main()
{
    MountainList list;

    printInfo();
    readFromFile(list);
    list.displayList();
    cout << "There are " << list.getCounter() << " items in the list\n\n";
    searchManager(list);
    deleteManager(list);
    cout << "There are " << list.getCounter() << " items in the list\n\n";
    list.displayList();

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
        cout <<"Error opening file!\n";


    string n;
    double e;
    string r;
    string s;

    while(!inputfile.eof())
    {
        getline(inputfile, n);
        inputfile >> e;
        inputfile.ignore();
        inputfile.clear();
        getline(inputfile, r);
        getline(inputfile, s);
        getline(inputfile, space);
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

        cout<<"What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT \n";
        getline(cin,deleteName);
        if(deleteName!= "quit" && deleteName != "QUIT")
        {
            if(list.deleteNode(deleteName))
                cout<<  deleteName << " deleted\n";
            else
                cout<< deleteName << " not found\n";

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
	string input;

    cout << "\n ====== SEARCH ======\n\n";
    do
    {
		input = "";
		cout << "\nHow would you like to search for mountains: name, range, state? \n(Please have input be in lowercase to choose option)" << endl;
		cout << "If you don't want to search, enter QUIT \n";
		getline(cin,choice);
		if (choice == "name"){
			do{
				cout << "\nWhat mountain name do you want to search for? If you dont want to search for a mountain name enter QUIT \n";
				getline(cin, input);
				if (input != "quit" && input != "QUIT")
				{
					list.searchByName(input);
				}
			}while(input != "quit" && input != "QUIT");
		}

		else if (choice == "range"){
			do{
				cout << "\nWhat mountain range do you want to search for? If you dont want to search for a mountain range enter QUIT \n";
				getline(cin, input);
				if (input != "quit" && input != "QUIT")
				{
					list.searchByRange(input);
				}
			} while (input != "quit" && input != "QUIT");
		}

		else if (choice == "state"){
			do{
				cout << "\nWhat mountain state do you want to search for? If you dont want to search for a mountain state enter QUIT \n";
				getline(cin, input);
				if (input != "quit" && input != "QUIT")
				{
					list.searchByState(input);
				}
			} while (input != "quit" && input != "QUIT");
		}

		else if (choice == "QUIT" || choice == "quit"){
			choice = "quit";
		}

		else
		{
			cout << "Please enter correct input.\n\n";
		}

    }while(choice != "quit" && choice != "QUIT");

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
=================================================================
There are 14 items in the list


 ====== SEARCH ======


How would you like to search for mountains: name, range, state?
(Please have input be in lowercase to choose option)
If you don't want to search, enter QUIT
DOublet Peak
Please enter correct input.


How would you like to search for mountains: name, range, state?
(Please have input be in lowercase to choose option)
If you don't want to search, enter QUIT
name

What mountain name do you want to search for? If you dont want to search for a m
ountain name enter QUIT
Doublet Peak
FOUND: Doublet Peak 13600 Wind River Range Wyoming


What mountain name do you want to search for? If you dont want to search for a m
ountain name enter QUIT
doubletpeAk
FOUND: Doublet Peak 13600 Wind River Range Wyoming


What mountain name do you want to search for? If you dont want to search for a m
ountain name enter QUIT
QUIT

How would you like to search for mountains: name, range, state?
(Please have input be in lowercase to choose option)
If you don't want to search, enter QUIT
range

What mountain range do you want to search for? If you dont want to search for a
mountain range enter QUIT
cascade range
FOUND: Adams 12281 Cascade Range Washington
FOUND: Bachelor 9068 Cascade Range Oregon
FOUND: Rainier 14411 Cascade Range Washington
FOUND: Shasta 14179 Cascade Range California

What mountain range do you want to search for? If you dont want to search for a
mountain range enter QUIT
TordilloMountains
FOUND: Torbert 11413 Tordillo Mountains Alaska

What mountain range do you want to search for? If you dont want to search for a
mountain range enter QUIT
potato
potato NOT FOUND


What mountain range do you want to search for? If you dont want to search for a
mountain range enter QUIT
quit

How would you like to search for mountains: name, range, state?
(Please have input be in lowercase to choose option)
If you don't want to search, enter QUIT
state

What mountain state do you want to search for? If you dont want to search for a
mountain state enter QUIT
California
FOUND: Castle Peak 9109 Sierra Nevada California
FOUND: Half Dome 8836 Yosemite National Park California
FOUND: Pyramid Peak 9985 Crystal Range California
FOUND: Shasta 14179 Cascade Range California

What mountain state do you want to search for? If you dont want to search for a
mountain state enter QUIT
texas
texas NOT FOUND


What mountain state do you want to search for? If you dont want to search for a
mountain state enter QUIT
aLaskA
FOUND: Churchill 15638 Saint Elias Mountains Alaska
FOUND: Torbert 11413 Tordillo Mountains Alaska

What mountain state do you want to search for? If you dont want to search for a
mountain state enter QUIT
quit

How would you like to search for mountains: name, range, state?
(Please have input be in lowercase to choose option)
If you don't want to search, enter QUIT
potato
Please enter correct input.


How would you like to search for mountains: name, range, state?
(Please have input be in lowercase to choose option)
If you don't want to search, enter QUIT
NAME
Please enter correct input.


How would you like to search for mountains: name, range, state?
(Please have input be in lowercase to choose option)
If you don't want to search, enter QUIT
QUIT

 ====== DELETE ======

What Mountain do you want to delete? If you dont want to delete a Mountain, ente
r QUIT
shasta
shasta deleted
What Mountain do you want to delete? If you dont want to delete a Mountain, ente
r QUIT
baChelor
baChelor deleted
What Mountain do you want to delete? If you dont want to delete a Mountain, ente
r QUIT
quit
There are 12 items in the list

=====              =========  =====                  =====
Name               Elevation  Range                  State
=====              =========  =====                  =====
Adams                  12281  Cascade Range          Washington
Antero                 14276  Sawatch Range          Colorado
Castle Peak             9109  Sierra Nevada          California
Churchill              15638  Saint Elias Mountains  Alaska
Doublet Peak           13600  Wind River Range       Wyoming
Granite Peak           12807  Beartooth Mountains    Montana
Half Dome               8836  Yosemite National Park California
Jeff Davis Peak        12771  Snake Range            Nevada
Mauna Kea              13803  Mauna Kea              Hawaii
Pyramid Peak            9985  Crystal Range          California
Rainier                14411  Cascade Range          Washington
Torbert                11413  Tordillo Mountains     Alaska
=================================================================
DEBUG - Destructor: Now deleting Adams
DEBUG - Destructor: Now deleting Antero
DEBUG - Destructor: Now deleting Castle Peak
DEBUG - Destructor: Now deleting Churchill
DEBUG - Destructor: Now deleting Doublet Peak
DEBUG - Destructor: Now deleting Granite Peak
DEBUG - Destructor: Now deleting Half Dome
DEBUG - Destructor: Now deleting Jeff Davis Peak
DEBUG - Destructor: Now deleting Mauna Kea
DEBUG - Destructor: Now deleting Pyramid Peak
DEBUG - Destructor: Now deleting Rainier
DEBUG - Destructor: Now deleting Torbert

Process returned 0 (0x0)   execution time : 167.247 s
Press any key to continue.
*/
