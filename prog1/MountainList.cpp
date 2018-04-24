//
//  Mountains.cpp
//
//
//
//
//

#include "MountainList.hpp"

#include <iostream>
#include <iomanip>


//**************************************************
// Constructor - make senteniel node at beginning
// of linked list
//**************************************************
MountainList::MountainList()
{
    head = new ListNode; // head points to the sentinel node
    head->mount.setElevation(0);
    head->mount.setName("");
    head->mount.setRange("");
    head->mount.setState("");
    head->next = NULL;
}

//**************************************************
// The displayList function shows the value
// stored in each node of the linked list
// pointed to by head.
//**************************************************
void MountainList::displayList() const
{
    ListNode *pCur;

    // Display a header
    cout << right << "====="  << setw(23) << "=========" << setw(7) << "=====" <<  setw(24) << "===== " <<endl;
    cout << right << "Name "  << setw(23) << "Elevation" << setw(7) << "Range" <<  setw(24) << "State " <<endl;
    cout << right << "====="  << setw(23) << "=========" << setw(7) << "=====" <<  setw(24) << "===== " <<endl;

    // Position pCur: skip the head of the list.
    pCur = head->next;
    // While pCur points to a node, traverse the list.

    while (pCur)
    {
        // Display the value in this node.
        pCur->mount.displayMountain(); //improvement??
        // Move to the next node.
        pCur = pCur->next;
    }
    // End of the report
    cout << "=================================================================" <<endl;
}

//**************************************************
// The insertNode function inserts a new node in
// a sorted list (it keeps the list sorted)
//**************************************************
void MountainList::insertNode(Mountain dataIn)
{
    ListNode *newNode;  // A new node
    ListNode *pCur;     // To traverse the list
    ListNode *pPre;     // The previous node

    // Allocate a new node and store num there.
    newNode = new ListNode;
    newNode->mount = dataIn;


    // Initialize pointers
    pPre = head;
    pCur = head->next;
    while (pCur != NULL && pCur->mount.getName() < dataIn.getName())
    {
        pPre = pCur;
        pCur = pCur->next;
    }

    // Insert the new node between pPre and pCur
    pPre->next = newNode;
    newNode->next = pCur;

    MountainList::counter++;//adds one to the counter(items in the linked list)
}

//**************************************************
// The deleteNode function searches for a node
// with num as its value. The node, if found, is
// deleted from the list and from memory.
//**************************************************
bool MountainList::deleteNode(string target)
{
    ListNode *pCur;       // To traverse the list
    ListNode *pPre;        // To point to the previous node
    bool deleted = false;
    // Initialize pointers
    pPre = head;
    pCur = head->next;

    while (pCur != NULL && !strEquals(target, pCur->mount.getName()))
    {
        pPre = pCur;
        pCur = pCur->next;
    }

    // If found, delete the node
	if (pCur != NULL && strEquals(target, pCur->mount.getName()))
    {
        pPre->next = pCur->next;
        delete pCur;
        deleted = true;
        MountainList::counter--;//subtracts 1 from the counter(items in the linked list)
    }
    return deleted;

}

//**************************************************
// The searchByName function searches for a node
// with target as its mountain name. If found,
// it prints out the mountain object at the current
// node.
//**************************************************
void MountainList::searchByName(string target) const
{
    ListNode *pCur;        // To transverse the list

    pCur = head->next;
	string x;
    while (pCur != NULL && !strEquals(target,pCur->mount.getName()))
    {
		pCur = pCur->next;

    }

    if(pCur!= NULL)
    {
        cout << "FOUND: "
             << pCur->mount.getName() << " "
             << pCur->mount.getElevation() << " "
             << pCur->mount.getRange() << " "
             << pCur->mount.getState() << " \n\n";
    }
    else
        cout << target << " NOT FOUND\n\n";
}

//**************************************************
// The searchByRange function searches for a node
// with target as its mountain range. If found,
// it prints out the mountain object at the current
// node.
//**************************************************
void MountainList::searchByRange(string target) const
{
	ListNode *pCur;        // To transverse the list

	pCur = head->next;
	string x;
	bool found = false;
	while (pCur != NULL)
	{
		if (pCur != NULL && strEquals(target, pCur->mount.getRange()))
		{
			found = true;
			cout << "FOUND: "
				<< pCur->mount.getName() << " "
				<< pCur->mount.getElevation() << " "
				<< pCur->mount.getRange() << " "
				<< pCur->mount.getState() << " \n";
		}

		pCur = pCur->next;
	}

	if (!found)
	{
		cout << target << " NOT FOUND\n\n";
	}
}

//**************************************************
// The searchByState function searches for a node
// with target as its mountain state. If found,
// it prints out the mountain object at the current
// node.
//**************************************************
void MountainList::searchByState(string target) const
{
	ListNode *pCur;        // To transverse the list

	pCur = head->next;
	string x;
	bool found = false;
	while (pCur != NULL)
	{
		if (pCur != NULL && strEquals(target, pCur->mount.getState()))
		{
			found = true;
			cout << "FOUND: "
				<< pCur->mount.getName() << " "
				<< pCur->mount.getElevation() << " "
				<< pCur->mount.getRange() << " "
				<< pCur->mount.getState() << " \n";
		}

		pCur = pCur->next;
	}

	if (!found)
	{
		cout << target << " NOT FOUND\n\n";
	}
}

//**************************************************
// The strEquals function takes in 2 strings,
// compares them regardless of case sensitivity and
// spaces, and returns true if the 2 strings are
// equal, false otherwise.
//**************************************************
bool MountainList::strEquals(string str1,string str2)const
{
	string tempTarget; //used to store target string to compare

	for (int i = 0; i < str1.size(); i++) //for loop used to change str1 to lowercase and removes spaces then assign to temptarget
	{

		if (str1[i] != ' ')
		{
			tempTarget += tolower(str1[i]);
		}
	}

	string temp; //used to store the current name string to compare
	for (int j = 0; j < str2.size(); j++) //for loop used to change str2 to lowercase and removes spaces, then assigns to temp
	{

		if (str2[j] != ' ')
		{
			temp += tolower(str2[j]);
		}
	}
	return (temp == tempTarget);
}

int MountainList::getCounter()//keeps track of how many items are in the list
{
	return MountainList::counter;
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************
MountainList::~MountainList()
{
    ListNode *pCur;   // To traverse the list
    ListNode *pNext;  // To point to the next node


    pCur = head->next;
    while (pCur != NULL)
    {

        pNext = pCur->next;

        // Delete the current node.
        cout << "DEBUG - Destructor: Now deleting " << pCur->mount.getName() << endl;
        delete pCur;


        pCur = pNext;
    }

    delete head; // delete the sentinel node
}
