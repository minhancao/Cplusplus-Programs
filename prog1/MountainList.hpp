//
//  Mountains.hpp
//
//
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
    int counter = 0;//keeps track of how many items are in the list

    // Declare a structure for the list
    struct ListNode
    {
        Mountain mount;     // The value in this node
        ListNode *next;     // To point to the next node
    };

    ListNode *head;        // List head pointer


public:
     MountainList();  // Constructor
    ~MountainList();   // Destructor

    // Linked list operations
    void insertNode(Mountain x);
    bool deleteNode(string);
    void displayList() const;

	//search functions for search manager in main
	void searchByName(string) const;
	void searchByRange(string) const;
	void searchByState(string) const;

	//compare function used to compare two strings regardless of case sensitivity and spaces
	bool strEquals(string str1, string str2) const;

	//counter function that returns number of items still in list
    int getCounter();

};

#endif
