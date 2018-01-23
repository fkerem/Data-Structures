/*************************************************************************************
Author: Faik Kerem Örs
Date: 16/08/2016

#Homework - LinkedList.cpp

Caution 1: This .cpp file should NOT be compiled because it includes the implementations
	   of the templated classes and they are included by the header file.
*************************************************************************************/

#include <iostream>
#include "LinkedList.h"
using namespace std;

template <class dataType>
LinkedList<dataType>::LinkedList() {
	firstNode = NULL;
	lastNode = NULL;
}

template <class dataType>
LinkedList<dataType>::LinkedList(const LinkedList<dataType> & list) {
	firstNode = NULL;
	lastNode = NULL;
	copyFromList(list);
}

template <class dataType>
LinkedList<dataType>::~LinkedList() {
	clear();
	delete firstNode;
	delete lastNode;
}

template <class dataType>
LinkedList<dataType>::node::node(dataType &data) {
	this -> data = &data;
	next = NULL;
}

template <class dataType>
void LinkedList<dataType>::insert(dataType &data) {
	node *nData = new node(data);
	if(lastNode != NULL) {
		lastNode -> next = nData;
	}
	else {
		firstNode = nData;
	}
	lastNode = nData;
}

template <class dataType>
ostream & operator<<(ostream & op1, const LinkedList<dataType> & list) {
	LinkedListIterator<dataType> *it = new LinkedListIterator<dataType>(list);
	while(it -> hasNext()) {
		op1 << *(it -> next());
	}
	delete it;
	return op1;
}

template <class dataType>
const LinkedList<dataType>& LinkedList<dataType>::operator=(const LinkedList<dataType> &list) {
	clear();
	copyFromList(list);
	return list;
}

template <class dataType>
LinkedList<dataType> LinkedList<dataType>::operator+(const LinkedList<dataType> &list) const {
	LinkedList<dataType> list3;
	list3.copyFromList(*this);
	list3.copyFromList(list);
	return list3;
}

template <class dataType>
void LinkedList<dataType>::remove(dataType &data) {
	node *p = firstNode;
	node *prev;
	dataType *pData = &data;
	while(p != NULL && p -> data != pData) {
		prev = p;
		p = p -> next;
	}

	if(p != NULL && firstNode -> data == pData) {
		firstNode = firstNode -> next;
	}
	else if(p != NULL) {
		prev -> next = p -> next;
		if(lastNode -> data == pData) {
			lastNode = prev;
		}
		delete p;
	}
}

template <class dataType>
void LinkedList<dataType>::clear() {
	node *p = firstNode;
	while(p != NULL) {
		firstNode = firstNode -> next;
		delete p;
		p = firstNode;
	}
	lastNode = firstNode;
}

template <class dataType>
void LinkedList<dataType>::copyFromList(const LinkedList<dataType> &list) {
	LinkedListIterator<dataType> *it = new LinkedListIterator<dataType>(list);
	while(it -> hasNext()) {
		insert(*(it -> next()));
	}
	delete it;
}

template <class dataType>
LinkedListIterator<dataType>::LinkedListIterator(const LinkedList<dataType> &list) : list(list) {
	nextNode = list.firstNode;
}

template <class dataType>
bool LinkedListIterator<dataType>::hasNext() const {
	return (nextNode != NULL);
}

template <class dataType>
dataType *LinkedListIterator<dataType>::next() {
	dataType *result = (nextNode != NULL ? nextNode -> data : NULL);
	nextNode = nextNode -> next;
	return result;
}
