//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Array-based implementation of the ADT heap.
ArrayMaxHeap.h */

//Modified by Minh An Cao

#ifndef _ARRAY_MAX_HEAP
#define _ARRAY_MAX_HEAP

#include <cmath>

template<class ItemType>
class ArrayMaxHeap
{
private:
   static const int ROOT_INDEX = 0;        // Helps with readability
   static const int DEFAULT_CAPACITY = 21; // Small capacity to test for a full heap
   ItemType* items;                        // Array of heap items
   int itemCount;                          // Current count of heap items
   int maxItems;                           // Maximum capacity of the heap


   // Returns the array index of the left child
   int getLeftChildIndex(int nodeIndex) const;

   // Returns the array index of the right child
   int getRightChildIndex(int nodeIndex) const;

   // Returns the array index of the parent node
   int getParentIndex(int nodeIndex) const;

   // Tests whether this node is a leaf
   bool isLeaf(int nodeIndex) const;

   //Rebuilds semiheap to a heap based on serial number
   void heapRebuild(int subTreeRootIndex);

   // Rebuilds semiheap to a heap based on priority number
   void heapRebuildInPriorityNumber(int subTreeRootIndex);

   // Makes a heap from an array
   void heapCreate();

   void printIndentedList(void visit(ItemType &, int &), int subTreeRootIndex, int indent);

public:
   ArrayMaxHeap();
   ArrayMaxHeap(const ItemType someArray[], const int arraySize);
   virtual ~ArrayMaxHeap();

   // HeapInterface Public Methods:
   bool isEmpty() const;
   int getNumberOfNodes() const;
   int getHeight() const;
   ItemType peekTop() const;
   bool addAsSerial(const ItemType& newData);
   bool addAsPriority(const ItemType& newData);
   bool removeAsSerial(ItemType& removedItem);  //removes top item and puts that top item into the reference parameter
   bool removeAsPriority(ItemType& removedItem);  //removes top item and puts that top item into the reference parameter
   void clear();
   void rebuildHeapInSerialNumber();
   void rebuildHeapInPriorityNumber();

   void printList(void visit(ItemType &, int &));
}; // end ArrayMaxHeap

//--------------------------------------------------------------------------------------------------------------
//PUBLIC FUNCTIONS
//--------------------------------------------------------------------------------------------------------------
template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
	// Dynamically allocate memory for the array
	items = new ItemType[maxItems];
}  // end default constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::
ArrayMaxHeap(const ItemType someArray[], const int arraySize):
             itemCount(arraySize), maxItems(2 * arraySize)
{
   // Allocate the array
   items = new ItemType[2 * arraySize];

   // Copy given values into the array
   for (int i = 0; i < itemCount; i++)
   {
      items[i] = someArray[i];
   }

   // Reorganize the array into a heap
   heapCreate();
} // end constructor

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
	// Delete the dynamic memory allocated for the array.
	delete[] items;
}  // end destructor

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const
{
	// If itemCount is zero, returns true. Else, returns false.
	if (itemCount == 0)
		return true;
	else
		return false;
}  // end isEmpty

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const
{
	return itemCount;
}  // end getNumberOfNodes

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const
{
	// Use mathematical formula to calculate the height of the heap.
	return ceil(log2(itemCount + 1));  //ceil rounds up the number
}  // end getHeight

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const
{
   // If heap is empty, throw an exception.
   if (isEmpty()){

    try{
        throw exception();
    }

    catch(...){
        cout<<"Heap is empty"<<endl;
    }
   }
   // Otherwise, return the first item of the array.
   return items[0];
} // end peekTop

template<class ItemType>
bool ArrayMaxHeap<ItemType>::addAsSerial(const ItemType& newData)
{
	// Returns false if the itemCount is equal to the maximum amount of item.
	if (itemCount == maxItems)
		return false;

	// Insert newData into the bottom of the tree
	items[itemCount] = newData;

	// Trickle new item up to the appropriate spot in the tree
	int newDataIndex = itemCount;
	bool inPlace = false;

	// Repeat the process as long as newDataIndex is greater than zero
	// and inPlace is false
	while (newDataIndex > 0 && !inPlace)
	{
		// Get the parent node's index
		int parentIndex = (newDataIndex - 1) / 2;

		// Item is in place if the priority value of the newData is
		// lesser or equal than the parent node's value
		if (items[newDataIndex].getSerialNum() <= items[parentIndex].getSerialNum())
			inPlace = true;
		else
		{
			// Otherwise, swap newDataIndex's value with the parentIndex
			swap(items[newDataIndex], items[parentIndex]);
			// set newDataIndex to the parentIndex to repeat the process
			newDataIndex = parentIndex;
		}
	}

	// Increase the itemCount
	itemCount++;

	// The process is done, returns true.
	return true;
}  // end add

template<class ItemType>
bool ArrayMaxHeap<ItemType>::addAsPriority(const ItemType& newData)
{
	// Returns false if the itemCount is equal to the maximum amount of item.
	if (itemCount == maxItems)
		return false;

	// Insert newData into the bottom of the tree
	items[itemCount] = newData;

	// Trickle new item up to the appropriate spot in the tree
	int newDataIndex = itemCount;
	bool inPlace = false;

	// Repeat the process as long as newDataIndex is greater than zero
	// and inPlace is false
	while (newDataIndex > 0 && !inPlace)
	{
		// Get the parent node's index
		int parentIndex = (newDataIndex - 1) / 2;

		// Item is in place if the priority value of the newData is
		// lesser or equal than the parent node's value
		if (items[newDataIndex].getPriority() <= items[parentIndex].getPriority())
			inPlace = true;
		else
		{
			// Otherwise, swap newDataIndex's value with the parentIndex
			swap(items[newDataIndex], items[parentIndex]);
			// set newDataIndex to the parentIndex to repeat the process
			newDataIndex = parentIndex;
		}
	}

	// Increase the itemCount
	itemCount++;

	// The process is done, returns true.
	return true;
}  // end add

template<class ItemType>
bool ArrayMaxHeap<ItemType>::removeAsSerial(ItemType& removedItem)
{
	// If the heap is empty, return false.
	if (isEmpty())
		return false;

	removedItem = items[0]; //sets the item that is about to be removed to the parameter

	// Copy the item from the last node into the root
	items[0] = items[itemCount - 1];

	// Remove the last node
	itemCount--;

	 // Transform the semiheap back into the heap
	heapRebuild(0);

	// The process is done, returns true.
	return true;
}  // end remove

template<class ItemType>
bool ArrayMaxHeap<ItemType>::removeAsPriority(ItemType& removedItem)
{
	// If the heap is empty, return false.
	if (isEmpty())
		return false;

	removedItem = items[0]; //sets the item that is about to be removed to the parameter

	// Copy the item from the last node into the root
	items[0] = items[itemCount - 1];

	// Remove the last node
	itemCount--;

	 // Transform the semiheap back into the heap
	heapRebuildInPriorityNumber(0);

	// The process is done, returns true.
	return true;
}  // end remove

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
	// Sets the itemCount to 0
	itemCount = 0;
}  // end clear

template<class ItemType>
void ArrayMaxHeap<ItemType>::rebuildHeapInSerialNumber()
{
	heapRebuild(0);
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::rebuildHeapInPriorityNumber()
{
	heapRebuildInPriorityNumber(0);
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::printList(void visit(ItemType &, int &))
{
    printIndentedList(visit, 0, 0);
}


//--------------------------------------------------------------------------------------------------------------
//PRIVATE FUNCTIONS
//--------------------------------------------------------------------------------------------------------------
template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
}  // end getLeftChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(int nodeIndex) const
{
	return (2 * nodeIndex) + 2;
}  // end getRightChildIndex

template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(int nodeIndex) const
{
	return (nodeIndex - 1) / 2;
}  // end getParentIndex

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(int nodeIndex) const
{
	// If the left child index and right child index is not within the
	// itemCount, return true. Else, return false.
	if (!(getLeftChildIndex(nodeIndex) < itemCount) && !(getRightChildIndex(nodeIndex) < itemCount))
		return true;
	else
		return false;
}  // end isLeaf

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(int subTreeRootIndex)
{
	// Recursively trickle the item at index subTreeRootIndex down
	// to its proper position by swapping it with its larger child,
	// if the child is larger than the item. If the item is at a
	// leaf, nothing needs to be done.
	if (!isLeaf(subTreeRootIndex))
	{
		// The root must have a left child; assume it is the larger child.
		int largerChildIndex = 2 * subTreeRootIndex + 1; // Left child index

		if (getRightChildIndex(subTreeRootIndex) != 0)
		{
			int rightChildIndex = largerChildIndex + 1; // Right child index
			if (items[rightChildIndex].getSerialNum() > items[largerChildIndex].getSerialNum())
				largerChildIndex = rightChildIndex; // Larger child index
		}

		// If the item in the root is smaller than the item in the larger child,
		// swap items
		if (items[subTreeRootIndex].getSerialNum() <= items[largerChildIndex].getSerialNum())
		{
			swap(items[subTreeRootIndex], items[largerChildIndex]);
			//Transform the semiheap rooted at largerChildIndex into a heap
			heapRebuild(largerChildIndex);
		}
	} // Else root is a leaf, so you are done
}  // end heapRebuild

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuildInPriorityNumber(int subTreeRootIndex)
{
	// Recursively trickle the item at index subTreeRootIndex down
	// to its proper position by swapping it with its larger child,
	// if the child is larger than the item. If the item is at a
	// leaf, nothing needs to be done.
	if (!isLeaf(subTreeRootIndex))
	{
		// The root must have a left child; assume it is the larger child.
		int largerChildIndex = 2 * subTreeRootIndex + 1; // Left child index

		if (getRightChildIndex(subTreeRootIndex) != 0)
		{
			int rightChildIndex = largerChildIndex + 1; // Right child index
			if (items[rightChildIndex].getPriority() > items[largerChildIndex].getPriority())
				largerChildIndex = rightChildIndex; // Larger child index
		}

		// If the item in the root is smaller than the item in the larger child,
		// swap items
		if (items[subTreeRootIndex].getPriority() <= items[largerChildIndex].getPriority())
		{
			swap(items[subTreeRootIndex], items[largerChildIndex]);
			//Transform the semiheap rooted at largerChildIndex into a heap
			heapRebuildInPriorityNumber(largerChildIndex);
		}
	} // Else root is a leaf, so you are done
}  // end heapRebuild

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
   for (int index = itemCount / 2; index >= 0; index--)
   {
      heapRebuild(index);
   }  // end for
}  // end heapCreate

template<class ItemType>
void ArrayMaxHeap<ItemType>::printIndentedList(void visit(ItemType &, int &), int subTreeRootIndex, int indent)
{
	if (subTreeRootIndex < itemCount)
	{
		ItemType item = items[subTreeRootIndex];
		visit(item, indent);
		printIndentedList(visit, getLeftChildIndex(subTreeRootIndex), indent+8);
		printIndentedList(visit, getRightChildIndex(subTreeRootIndex), indent+8);
	}


}

#endif
