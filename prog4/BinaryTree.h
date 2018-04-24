// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Minh An Cao

//
//  BinaryTree.h
//
//  This is the header file for the BinaryTree class.
//
//  Minh An Cao
//

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Stack.h"
#include "Queue.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { }
	BinaryTree & operator = (const BinaryTree & sourceTree);

	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
	void iterPreOrder(void visit(ItemType &)) const {_iterpreorder(visit, rootPtr);}
	void iterInOrder(void visit(ItemType &)) const  {_iterinorder(visit, rootPtr);}
	void iterPostOrder(void visit(ItemType &)) const{_iterpostorder(visit, rootPtr);}
	void breadthOrder(void visit(ItemType &)) const{_breadthorder(visit, rootPtr);}

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0;
	virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(ItemType & anEntry, ItemType & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _iterpreorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _iterinorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _iterpostorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _breadthorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;

};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;


    return newNodePtr;
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if(nodePtr != NULL)
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        delete(nodePtr);
        if(nodePtr->getLeftPtr()!=NULL)
            nodePtr->setLeftPtr(NULL);
        if(nodePtr->getRightPtr()!=NULL)
            nodePtr->setRightPtr(NULL);
        nodePtr=NULL;
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}


template<class ItemType>
void BinaryTree<ItemType>::_iterpreorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
		Stack<BinaryNode<ItemType>*> s;

		if (nodePtr != 0)
        {
            s.push(nodePtr);
        }

		while(!s.isEmpty())
        {
            BinaryNode<ItemType>* temp;
            s.pop(temp);
            ItemType item = temp->getItem();
            visit(item);

            if (temp->getRightPtr() != NULL)
                s.push(temp->getRightPtr());

            if (temp->getLeftPtr() != NULL)
                s.push(temp->getLeftPtr());
        }
}


template<class ItemType>
void BinaryTree<ItemType>::_iterinorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Stack<BinaryNode<ItemType>*> s;

    do
    {
        if (nodePtr != NULL)
        {
        s.push(nodePtr);
        nodePtr = nodePtr->getLeftPtr();
        }

        else
        {
            s.pop(nodePtr);
            ItemType item = nodePtr->getItem();
            visit(item);
            nodePtr = nodePtr->getRightPtr();
        }
    }while (!s.isEmpty() || nodePtr != NULL);

}

template<class ItemType>
void BinaryTree<ItemType>::_iterpostorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Stack<BinaryNode<ItemType>*> s;

	if (nodePtr == NULL)
		return;

	do
	{
		while (nodePtr!=0)
		{
			if (nodePtr->getRightPtr() != 0)
				s.push(nodePtr->getRightPtr());
				s.push(nodePtr);


			nodePtr = nodePtr->getLeftPtr();
		}

		s.pop(nodePtr);

		if (nodePtr->getRightPtr() != 0 && s.getTop() == nodePtr->getRightPtr())
		{
			BinaryNode<ItemType>* temp;
			s.pop(temp);
			s.push(nodePtr);
			nodePtr = nodePtr->getRightPtr();
		}
		else
		{
			ItemType item = nodePtr->getItem();
            visit(item);
			nodePtr = NULL;
		}
	} while (!s.isEmpty());
}

template<class ItemType>
void BinaryTree<ItemType>::_breadthorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	Queue<BinaryNode<ItemType>*> q;

	if (nodePtr != 0)
	{
		q.enqueue(nodePtr);
	}

	while (!q.isEmpty())
	{
		BinaryNode<ItemType>* temp;
		q.queueFront(temp);
		ItemType item = temp->getItem();
        visit(item);

		if (temp->getLeftPtr() != NULL)
			q.enqueue(temp->getLeftPtr());

		if (temp->getRightPtr() != NULL)
			q.enqueue(temp->getRightPtr());

		q.dequeue(temp);
	}

}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{

}

#endif

