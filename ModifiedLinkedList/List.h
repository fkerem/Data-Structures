/*************************************************************************************
Author: Faik Kerem Örs
Date: 30/10/2016

#Programming Assignment - List.h - THE HEADER FILE OF THE TEMPLATED CLASSES.
*************************************************************************************/

#ifndef _LIST_H
#define _LIST_H
#include <iostream>
using namespace std;

template <class Object1, class Object2>
class List;

template <class Object1, class Object2>
class ListNode { 			// Node class to store strings and integers.
				 	// Each string node will point to an integer node and each int node will point to 
					// a string node thanks to the templated class.
	ListNode(const Object1 & data, ListNode *n = NULL) {
		this -> data = data;
		next = n;    // Next node of the same type will be pointed.
		head = NULL; // Each node will point to the head node of another type of list. Otherwise is also possible.
	}				 

	Object1 data; 	// Object1 will be the data.
	ListNode *next; // The next pointer will point to the same type of node.
	ListNode<Object2, Object1> *head; // Head node of another type of list will be pointed by this pointer.

	friend class List<Object1, Object2>; // List class should access to this class.
	friend class List<Object2, Object1>;
};

template <class Object1, class Object2>
class List {
public:
	List();
	~List();
	void clear(); 						// The function to clear the whole list.
	void clearSub(ListNode<Object1, Object2> *); 		// The function to clear the sublist of a node.
	void insert(const Object1 &, const Object2 &); 		// The function to insert strings and integers as sorted.
	void insertHead(const Object1 &); 			// The function to insert a node at the beginning of a list.
	void print(); 						// The function to print the intersection list.
	ListNode<Object2, Object1>* Find(const Object1 &) const;// The function to locate an object in the list.
	void intersect(Object1 &, ListNode<Object2, Object1> *);// The function to intersect associated documents of words.
private:
	ListNode<Object1, Object2> *head; 			// Head pointer will point to the first node of the list.
};

#include "List.cpp" 		// The implementations of the list class are included here because this is a template class and
#endif				// we should give the implementations. Therefore, List.cpp file should be excluded from build !
