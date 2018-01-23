#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct entry {
	int tNumOfTransactions;
	int tNumOfProbes;

	entry(int tr = 0, int pr = 0) {
		tNumOfTransactions = tr;
		tNumOfProbes = pr;
	}

};


template <class HashedObj>
class HashTable { // Hash Table class
public:
	explicit HashTable(const HashedObj & notFound, int size = 101);

//	bool contains(const HashedObj & x) const;
	void makeEmpty();
	bool insert(const HashedObj & x);
//	bool insert(HashedObj && x);
	bool remove(const HashedObj & x);
	bool isFull();
	void print(ofstream & output);
	const HashedObj & find(const HashedObj & x);

	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry {
		HashedObj element;
		EntryType info;
		HashEntry(const HashedObj & e = HashedObj(), EntryType i = EMPTY) : element(e), info(i) {}
	};

	vector<HashEntry> array;
	vector<entry> sInsert;
	vector<entry> fInsert;
	vector<entry> sDelete;
	vector<entry> fDelete;
	vector<entry> sFind;
	vector<entry> fFind;

	int currentSize;
	const HashedObj ITEM_NOT_FOUND;

//	int nextPrime(int n);
//	bool isPrime(int n);
	bool isActive(int currentPos) const;
	bool isEmpty(int currentPos) const;
	bool isDel(int currentPos) const;
	void printArray(ofstream & output) const;
//	size_t myhash(const HashedObj & x) const;
};

int myhash(const int x, const int tableSize) {
	return (x % tableSize);
}

bool isPrime(int n) {
	if(n == 2 || n == 3)
		return true;

	if(n == 1 || n % 2 == 0)
		return false;

	for(int i = 3; i*i <= n; i += 2) {
		if(n % i == 0) {
			return false;
		}
	}

	return true;
}

int nextPrime(int n) {
	if(n % 2 == 0)
		n++;

	for(; !isPrime(n); n += 2)
		;

	return n;
}

#include "HashTable.cpp"
#endif
