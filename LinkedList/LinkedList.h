/*************************************************************************************
Author: Faik Kerem Örs
Date: 16/08/2016

#Homework - LinkedList.h - THE HEADER FILE OF THE INTERFACES and 
			   TEMPLATED CLASSES LinkedList and LinkedListIterator.

*************************************************************************************/

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
using namespace std;
// Templated Interface : List
template <class dataType>
class List {
public: // All functions are pure virtual.
	virtual ~List() = 0 {};
	virtual void insert(dataType &) = 0;
	virtual void remove(dataType &) = 0;
	virtual void clear() = 0;
};

// Templated Interface : Iterator
template <class dataType>
class Iterator {
public:
	virtual bool hasNext() const = 0;
	virtual dataType *next() = 0;
};

template <class dataType>
class LinkedList : public List<dataType> {
public:
	LinkedList();
	LinkedList(const LinkedList &);
	~LinkedList();
	void insert(dataType &);
	const LinkedList & operator=(const LinkedList & );
	LinkedList operator+(const LinkedList & ) const;
	void remove(dataType &);
	void clear();
	void copyFromList(const LinkedList &list);
private:
	class node {
	public:
		node(dataType &);
		dataType *data;
		node *next;
};
	node *firstNode;
	node *lastNode;
	template <class dataType>
	friend class LinkedListIterator;
};

template <class dataType>
class LinkedListIterator : public Iterator<dataType> {
public:
	LinkedListIterator(const LinkedList<dataType> &);
	bool hasNext() const;
	dataType *next();
private:
	const LinkedList<dataType> &list;
	typename LinkedList<dataType>::node *nextNode;
};

#include "LinkedList.cpp"
#endif
