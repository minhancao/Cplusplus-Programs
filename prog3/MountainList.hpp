//
//  MountainList.hpp
//
//  Header file for the circularly doubly linked list of Mountain objects.
//
//
//

#ifndef MountainList_hpp
#define MountainList_hpp

using namespace std;

#include <string>
#include "Mountain.hpp"


class MountainList
{
private:
    int counter;//keeps track of how many items are in the list

    // Declare a structure for the list
    struct ListNode
    {
        Mountain mount;     // The value in this node
        ListNode *forw;     // To point to the next node
        ListNode *prev;     // To point to the previous node
    };

    ListNode *head;        // List head pointer
    ListNode *tail;        // List tail pointer
	ListNode *sent;        // List sentinel node


public:
     MountainList();  // Constructor
    ~MountainList();   // Destructor

    // Linked list operations
    void insertNode(Mountain x);
    bool deleteNode(string);

	//search functions for search manager in main
	void searchByName(string) const;

	//compare function used to compare two strings regardless of case sensitivity and spaces
	bool strEquals(string str1, string str2) const;

	//counter function that returns number of items still in list
    int getCounter();

    void printforward();
    void printbackward();

};

#endif
