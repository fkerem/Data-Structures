/*************************************************************************************
Author: Faik Kerem Örs
Date: 26/12/2016

#Programming Assignment - MPQ.cpp
*************************************************************************************/

#include "MPQ.h" // The header file.

// This MPQ is index 1 based !
MPQ::MPQ(int size) : Heap(size), Location(size) { // Constructor
	currentSize = 0;
}

MPQ::~MPQ() { // Destructor
	currentSize = 0;

	for(unsigned int i = 0; i < Heap.size(); i++) {
		Heap[i] = 0;
		Location[i] = 0;
	}
}

bool MPQ::isEmpty() const { // To check whether the MPQ is empty.
	return currentSize == 0;
}

bool MPQ::isFull() const { // Heap is 1 based so it will be full when the current size is less than the actual heap size.
	return currentSize == Heap.size() - 1;
}


void MPQ::insert(int value, int label) { // Insert function.
	if(!isFull()) {
		int hole = ++currentSize;

		for( ; hole > 1 && value > Heap[hole / 2].value; hole /= 2) { // Percolate Up.
			Heap[hole] = Heap[hole / 2];
			Location[Heap[hole / 2].label] = hole; // Location parallel vector is updated.
		}
		Heap[hole] = Object(value, label);
		Location[label] = hole; // Location vector is updated.
	}
	else { // Warning if the MPQ is full.
		cout << "The priority queue is full, the object couldn't be inserted." << endl;
	}
}

int MPQ::Remove(int label) { // To remove a value with its label.
	if(!isEmpty()) { // The program will warn the user if the MPQ is empty.
		int value = Heap[Location[label]].value;
		Heap[Location[label]] = Heap[currentSize--]
		percolateDown(Location[label]); // Percolationg down the new value in the removed index.
		return value;
	}
	else {
		cout << "The priority queue is already empty, the object couldn't be removed." << endl;
		return 0;
	}
}

int MPQ::GetMax() {
	return Heap[1].value;
}

void MPQ::percolateDown(int hole) {
	int child;
	Object temp = Heap[hole]; // Temp is the item which will be percolated down.

	for( ; hole * 2 <= currentSize; hole = child) { // The boundary for the children will be current size.
		child = hole * 2;

		if(child != currentSize && Heap[child + 1].value > Heap[child].value)
			child++; // Child is the maximum of the children.

		if(Heap[child].value > temp.value) {
			Heap[hole] = Heap[child]; 	    // Swap the hole with the maximum child.
			Location[Heap[child].label] = hole; // Location parallel vector is updated.
		}
		else
			break;
	}
	Heap[hole] = temp;
	Location[temp.label] = hole;
}

void MPQ::BuildHeap(vector<Object> a) { // BuildHeap function.
	for(unsigned int j = 0; j < a.size(); j++) {
		Heap[j + 1] = a[j];
	}

	currentSize = Heap.size() - 1;

	for (int i = currentSize / 2; i > 0; i--)
		percolateDown(i);
}

void MPQ::heapsort(vector<Object> & a) { // Heapsort algorithm to sort the input array.
	BuildHeap(a);

	for(int i = currentSize; i > 0; i--) { // Sort inside the MPQ.
		Object temp = Heap[1]; // Swap maximum value with the last position.
		Heap[1] = Heap[i];
		Heap[i] = temp;
		currentSize--; 	      // Heap is shrinked to sort successfully.
		percolateDown(1);     // Form the sorted MPQ.
	}

	for(unsigned int j = 0; j < a.size(); j++) // The sorted private array is copied to input array.
		a[j] = Heap[j + 1]; 		   // Private vector is index 1 based while input vector is 0 based.

}
