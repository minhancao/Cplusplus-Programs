// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Minh An Cao

//
//  BinarySearchTree.h
//
//  This is the header file for the BinarySearchTree class.
//
//  Minh An Cao
//

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include "BinaryNode.h"

using namespace std;

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* nodePtr, ItemType & target, bool & success) const;

	//find smallest node
	BinaryNode<ItemType>* findSmallestNode(BinaryNode<ItemType>* nodePtr, bool & success) const;

	//find largest node
	BinaryNode<ItemType>* findLargestNode(BinaryNode<ItemType>* nodePtr, bool & success) const;

	//prints tree as indented list
	void printIndentedList(void visit(ItemType &, int &, int &), BinaryNode<ItemType>* nodePtr, int level, int indent);

public:
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(ItemType & target, ItemType & returnedItem) const;
	//find smallest node
	bool findSmallest(ItemType & returnedItem) const;
	//find largest node
	bool findLargest(ItemType & returnedItem) const;
    //prints tree as indented list
	void printList(void visit(ItemType &, int &, int &));

};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	BinaryTree<ItemType>::count++;
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	BinaryTree<ItemType>::count--;
	return isSuccessful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(ItemType& target, ItemType & returnedItem) const
{
    bool isSuccessful = false;
    BinaryNode<ItemType>* temp;
	temp = findNode(this->rootPtr, target, isSuccessful);

	if(isSuccessful)
    {
        returnedItem = temp->getItem();
    }
	return isSuccessful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::findSmallest(ItemType & returnedItem) const
{
    bool successful = false;
    BinaryNode<ItemType>* temp;
	temp = findSmallestNode(this->rootPtr, successful);

	if(successful)
    {
        returnedItem = temp->getItem();
    }
	return successful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::findLargest(ItemType & returnedItem) const
{
    bool successful = false;
    BinaryNode<ItemType>* temp;
	temp = findLargestNode(this->rootPtr, successful);

	if(successful)
    {
        returnedItem = temp->getItem();
    }
	return successful;
}

template<class ItemType>
void BinarySearchTree<ItemType>::printList(void visit(ItemType &, int &, int &))
{
    printIndentedList(visit, this->rootPtr, 1, 0);
}



//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    if (nodePtr == NULL)
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }

    if (newNodePtr->getItem().getId() <= nodePtr->getItem().getId())//uses the student id to compare
    {
        nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
        return nodePtr;
    }

   else{
        nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
        return nodePtr;
   }

}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          ItemType target,
                                                          bool & success)

{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem().getId() > target.getId())//uses the student id to compare
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem().getId() < target.getId())
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = NULL;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = NULL;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == NULL)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = NULL;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == NULL)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                            ItemType & target, bool & success) const
{
   while(nodePtr != NULL)
   {
       if(nodePtr->getItem().getId() == target.getId())
       {
           success = true;
           return nodePtr;
           break;
       }

       if(target.getId() > nodePtr->getItem().getId())
       {
           nodePtr = nodePtr->getRightPtr();
       }

       else
        if(target.getId() < nodePtr->getItem().getId())
       {
           nodePtr = nodePtr->getLeftPtr();
       }
   }

   return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findSmallestNode(BinaryNode<ItemType>* nodePtr, bool & success) const
{
    if(nodePtr == NULL)
    {
        return nodePtr;
    }

    if(nodePtr->getLeftPtr() == NULL)
    {
        success = true;
        return nodePtr;
    }

    else{
        return findSmallestNode(nodePtr->getLeftPtr(), success);
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findLargestNode(BinaryNode<ItemType>* nodePtr, bool & success) const
{
    if(nodePtr == NULL)
    {
        return nodePtr;
    }

    if(nodePtr->getRightPtr() == NULL)
    {
        success = true;
        return nodePtr;
    }

    else{
        return findLargestNode(nodePtr->getRightPtr(), success);
    }
}

template<class ItemType>
void BinarySearchTree<ItemType>::printIndentedList(void visit(ItemType &, int &, int &), BinaryNode<ItemType>* nodePtr, int level, int indent)
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item, level, indent);
		printIndentedList(visit, nodePtr->getRightPtr(), level+1, indent+8);
		printIndentedList(visit, nodePtr->getLeftPtr(), level+1, indent+8);
	}
}



#endif
