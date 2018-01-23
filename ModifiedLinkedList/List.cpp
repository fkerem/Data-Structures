/*************************************************************************************
Author: Faik Kerem Örs
Date: 30/10/2016

#Programming Assignment - List.cpp

Caution: This .cpp file should NOT be built because it includes the implementations
	 of the templated classes and they are included by the header file.
	 Therefore, PLEASE EXCLUDE THIS .CPP FILE FROM BUILD.
*************************************************************************************/

#include "List.h"     // Header file.
#include "strutils.h" // Strutils will be used to compare strings.
#include <string>

// The constructor of the List class.
template <class Object1, class Object2>
List<Object1, Object2>::List() {
	head = NULL; 
}

// The destructor of the List class.
template <class Object1, class Object2>
List<Object1, Object2>::~List() {
	clear();
	delete head;
}

// The member function to clear the whole list.
template <class Object1, class Object2>
void List<Object1, Object2>::clear() {
	ListNode<Object1, Object2> *p = head;
	while(p != NULL) {
		clearSub(p); 		// First, the sublist of the node will be cleared.
		head = head -> next;
		delete p;
		p = head;
	}
}

// The member function to insert a node at the beginning of the list.
template <class Object1, class Object2>
void List<Object1, Object2>::insertHead(const Object1 & data) {
	ListNode<Object1, Object2> *nNode = new ListNode<Object1, Object2>(data);

	nNode -> next = head;
	head = nNode;
}

// The function to insert words and document numbers as sorted. (Not a regular sort!)
template <class Object1, class Object2>
void List<Object1, Object2>::insert(const Object1 & data, const Object2 & intData) {
	ListNode<Object1, Object2> *nNode = new ListNode<Object1, Object2>(data); // New node(contains string in our case) of the main list is created.
	ListNode<Object1, Object2> *p = head; // Pointers to traverse the main list.
	ListNode<Object1, Object2> *prev;
	ListNode<Object2, Object1> *intNode = new ListNode<Object2, Object1>(intData); // New node(contains integer in our case) of the sublist is created.
	ListNode<Object2, Object1> *pint;     // Pointers to traverse the sublist.
	ListNode<Object2, Object1> *prevint;

	if(head != NULL) { // If the list is not empty, the nodes should be placed in the correct area to make the list sorted.
		if(LowerString(data).compare(LowerString(p->data)) < 0) { // If the string value of new data is less than the head of the list,
			nNode -> next = head;				  // New node should be inserted to the beginning of the list.
			head = nNode;
			nNode -> head = intNode;
		}
		else { // Otherwise, the list should be traversed to locate where to insert to make sorted list.
			while(p != NULL && LowerString(data).compare(LowerString(p -> data)) != 0 && LowerString(data).compare(LowerString(p -> data)) > 0) {
				prev = p;
				p = p -> next;
			}
			// If there is a node containing same data, its sublist should be updated.
			if(p != NULL && LowerString(data).compare(LowerString(p -> data)) == 0) {
				pint = p -> head;
				
				if(intData < pint -> data) {	 	// If the data for sublist is less than the head of the sublist,
					intNode -> next = p -> head; 	// New head of the sublist should be intNode.
					p -> head = intNode;
				}
				else { // Otherwise, sublist should be traversed in the increasing order to locate where to add new intNode.
					while(pint != NULL && intData != pint -> data && intData > pint -> data) {
						prevint = pint;
						pint = pint -> next;
					}
							    // If pint equals NULL, intNode should be added to the end of the list
					if(pint == NULL) {  // because it's the node that containst biggest integer.
						intNode -> next = pint;
						prevint -> next = intNode;
					} // Otherwise, new intNode should be insterted between two nodes.
					else if(intData != pint -> data) {
						intNode -> next = pint;
						prevint -> next = intNode;
					}
				}
			}
			else { // Otherwise, new Node will be located at the end of the list or between two nodes of the list.
				prev -> next = nNode;
				nNode -> next = p;
				nNode -> head = intNode;
			}
		}
	}
	else {			// If the list is already empty,
		head = nNode;   // The head of the list should be new node.
		nNode -> head = intNode; // The head of the sublist of new node should also be intNode.
	}
}

// The member function to find a node that contains given data(parameter) and to return its sublist if it exists.
template <class Object1, class Object2> // This function will help to intersect sublists.
ListNode<Object2, Object1>* List<Object1, Object2>::Find(const Object1 & word) const {
	ListNode<Object1, Object2> *p = head;
	while(p != NULL && p -> data != word) {
		p = p -> next;
	}
	if(p != NULL) {
		return p -> head;
	}
	else {
		return NULL;
	}
}

/* * This is a print function that I write to print a list in a classical way but not necessarily used in this homework.
   * I used it to check if the lists are preprocessed correctly.

template <class Object1, class Object2>
void List<Object1, Object2>::print() {
	ListNode<Object1, Object2> *p = head;
	while(p != NULL) {
		cout << p -> data << " ";
		ListNode<Object2, Object1> *pInt = p -> head;
		while(pInt != NULL) {
			cout << pInt -> data << " ";
			pInt = pInt -> next;
		}
		cout << endl;
		p = p -> next;
	}
}

*/

template <class Object1, class Object2>
void List<Object1, Object2>::print() { // Print function to print the intersection list in the correct format of output.
	if(head != NULL) { // If there is an intersection,
		ListNode<Object2, Object1> *p = head -> head; // Intersected documents will be contained in the sublist.
		ListNode<Object2, Object1> *pNum = head -> head;
		int num = 0;
		while(pNum != NULL) { // The number of documents intersected will be counted.
			num++;
			pNum = pNum -> next;
		}
		cout << num << " "; // It will also be printed first.
		while(p != NULL) {  // Then, the matching document numbers will be printed in increasing order.
			cout << p -> data << " ";
			p = p -> next;
		}
		cout << endl;
	}
	else { // If the sublist is empty, there is no matched document and the number of documents intersected will be printed as 0.
		cout << "0" << endl;
	}

}

// The function to clear the sublist of a node. The node's location is taken as parameter.
template <class Object1, class Object2>
void List<Object1, Object2>::clearSub(ListNode<Object1, Object2> *head) {
	ListNode<Object2, Object1> *p = head -> head;
	while(p != NULL) { // By starting from the head node of the sublist, the list will be cleared.
		head -> head = head -> head -> next;
		delete p;
		p = head -> head;
	}
}

/*
   The function to intersect associated documents of the words.
   The intersecting documents' numbers will be stored in the sublist of dummy node as sorted.
   The dummy node will be used to understand if there was a situation that
   the document numbers didn't match and the sublist was cleared before.

   Note: If the sublist(intersection list) is empty when there is the dummy node in the main list,
   this means that the document numbers of the initial words didn't already intersect in this query
   so that we shouldn't check for the further intersections of the document numbers anymore in this query.
*/
template <class Object1, class Object2>
void List<Object1, Object2>::intersect(Object1 & dummy, ListNode<Object2, Object1> * docList) {
	if(docList != NULL) { // If there is a document list that can intersect with initial intersection, it will be checked.
		ListNode<Object2, Object1> *p = docList;
		if(head != NULL && head -> head != NULL) {  // If the main list and sublist is not empty, there can be an intersection.
			bool isChanged = true;		    // However, if the sublist is empty when there is the dummy node in the main list,
							    // we don't check.
			ListNode<Object2, Object1> *pInt = head -> head;
			ListNode<Object2, Object1> *prevInt = NULL;
			ListNode<Object2, Object1> *previousInt;
			while(pInt != NULL && p != NULL) {     // Initial intersection and document list will be traversed for new intersection.
				if(pInt -> data < p -> data) { // If the number in the intersection list is smaller than the number
							       // in the document list,
					previousInt = pInt;
					pInt = pInt -> next;
					if(prevInt != NULL) {  	       // If there was an intersection in this tour before, that node should be 
						prevInt -> next = pInt;// connected to the next node of the node that is to be deleted anymore.
					}
					delete previousInt;
					previousInt = NULL;
				}
				else if(p -> data < pInt -> data) { // If the number in the current node of the document list is smaller,
					p = p -> next;
				}
				else { // Otherwise, there is an intersection in current nodes.
					if(isChanged) {
						head -> head = pInt;
						isChanged = false;
					}
					prevInt = pInt;
					pInt = pInt -> next;
					p = p -> next;
				}
			}
			if(pInt != NULL) { // If pInt is not NULL, there are some next nodes that are not intersecting and they should be deleted.
				ListNode<Object2, Object1> *previous;
				prevInt -> next = NULL;
				while(pInt != NULL) {   // Here, the rest of the nodes which are not intersecting are cleared.
					previous = pInt;
					pInt = pInt -> next;
					delete previous;
					previous = NULL;
				}
			}
			if(isChanged) {		     // If there is no any intersection and all nodes are deleted,
				head -> head = NULL; // head of the sublist should be updated as NULL.
			}
		}
		else if(head == NULL){      // If the main list is empty, this means that this is the first condition for intersection.
			while(p != NULL) {  // Therefore, all elements in the sublist of the word should be inserted to intersection list.
				insert(dummy, p -> data);
				p = p -> next;
			}
		}
	}
	else { // Otherwise, the sublist should be cleared because there can't be any intersection if the word is not present.
		if(head != NULL)
			clearSub(head);
		else
			insertHead(dummy);
	}
}
