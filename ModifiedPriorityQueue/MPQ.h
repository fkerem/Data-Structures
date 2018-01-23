/*************************************************************************************
Author: Faik Kerem Örs
Date: 26/12/2016

#Programming Assignment - MPQ.h - THE HEADER FILE OF THE MPQ CLASS.
*************************************************************************************/

#ifndef _MPQ_H
#define _MPQ_H
#include <iostream>
#include <vector>

using namespace std;

struct Object {     // Struct to store the coordinates which will be used in the separate array
	int value;  // and to store heights with their label to be used in the modified priority queue.
	int label;
	string side;

	Object(int value = 0, int label = 0, string side = "") { // Struct constructor
		this -> value = value;
		this -> label = label;
		this -> side = side;
	}
};

class MPQ { 	   // Modified Priority Queue Class
public:
	MPQ(int size);
	~MPQ();

	bool isEmpty() const; // The function to check whether MPQ is empty.
	bool isFull() const;  // The function to check whether MPQ is full.
	void insert(int value, int label); // To insert an item to the MPQ.
	int Remove(int label);  // To remove the value with its label and return it.
	int GetMax(); 		// To get the maximum value.
	void heapsort(vector<Object> & a); // Heapsort Algorithm

private:
	int currentSize;
	vector<Object> Heap;  // Heap array
	vector<int> Location; // Parallel private array to maintain a link between a value and its label.

	void BuildHeap(vector<Object> a); // BuildHeap function to use in heapsort algorithm.
	void percolateDown(int hole); 	  // Percolate Down
};

#endif
