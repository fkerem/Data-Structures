/*
WARNING : THIS FILE SHOULD BE EXCLUDED FROM BUILD !
*/

#include "HashTable.h"
//Member Functions
template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj & notFound, int size = 101) 
	: ITEM_NOT_FOUND(notFound), array(nextPrime(size)), sInsert(nextPrime(size) + 1), fInsert(nextPrime(size) + 1), 
		sDelete(nextPrime(size) + 1), fDelete(nextPrime(size) + 1), sFind(nextPrime(size) + 1), fFind(nextPrime(size) + 1) {
	makeEmpty();
}

template <class HashedObj>
void HashTable<HashedObj>::makeEmpty() { //makeEmpty
	currentSize = 0;
	for(auto & entry : array) {
		entry.info = EMPTY;
	}
}

/*
template <class HashedObj>
bool HashTable<HashedObj>::contains(const HashedObj & x) const {
	return isActive(findPos(x));
}
*/

template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const {
	return array[currentPos].info == ACTIVE;
}

template <class HashedObj>
bool HashTable<HashedObj>::isEmpty(int currentPos) const {
	return array[currentPos].info == EMPTY;
}

template <class HashedObj>
bool HashTable<HashedObj>::isDel(int currentPos) const {
	return array[currentPos].info == DELETED;
}

template <class HashedObj>
bool HashTable<HashedObj>::insert(const HashedObj & x) { //Insert
	int collisionNum = 0;
	int currentPos = myhash(x, array.size());
	int temp = currentPos;
	bool full = false;
	bool isDeleted = false;
	int DeletedEntry;

	while(array[currentPos].info != EMPTY && array[currentPos].element != x && !full) {
		currentPos++;
		collisionNum++;
		if(currentPos >= int(array.size()))
			currentPos -= array.size();
		if(isDel(currentPos) && (!isDeleted)) {
			DeletedEntry = currentPos;
			isDeleted = true;
		}
		if(currentPos == temp)
			full = true;
	}

	if(array[currentPos].element == x && isDel(currentPos) && !isDeleted) {
		DeletedEntry = currentPos;
	}

	if(isActive(currentPos) && !full) {
		//failed
		fInsert[currentSize].tNumOfTransactions = fInsert[currentSize].tNumOfTransactions + 1; 
		fInsert[currentSize].tNumOfProbes = fInsert[currentSize].tNumOfProbes + collisionNum;
		return false;
	}
	else if(isEmpty(currentPos) && !isDeleted) {
		//succeded.
		sInsert[currentSize].tNumOfTransactions = sInsert[currentSize].tNumOfTransactions + 1;
		sInsert[currentSize].tNumOfProbes = sInsert[currentSize].tNumOfProbes + collisionNum;
		array[currentPos] = HashEntry(x, ACTIVE);
		currentSize++;
		return true;
	}
	else if((full && isDeleted) || (array[currentPos].element == x && isDel(currentPos)) || (isEmpty(currentPos) && isDeleted)) {
		//insert to the deleted cell.
		sInsert[currentSize].tNumOfTransactions = sInsert[currentSize].tNumOfTransactions + 1;
		sInsert[currentSize].tNumOfProbes = sInsert[currentSize].tNumOfProbes + collisionNum;
		array[DeletedEntry] = HashEntry(x, ACTIVE);
		return true;
	}
	else {
		// failed.
		fInsert[currentSize].tNumOfTransactions = fInsert[currentSize].tNumOfTransactions + 1;
		fInsert[currentSize].tNumOfProbes = fInsert[currentSize].tNumOfProbes + collisionNum;
		return false;
	}
}

template <class HashedObj>
bool HashTable<HashedObj>::remove(const HashedObj & x) { // delete
	int collisionNum = 0;
	int currentPos = myhash(x, array.size());
	int temp = currentPos;
	bool full = false;

	while(array[currentPos].info != EMPTY && array[currentPos].element != x && !full) {
		currentPos++;
		collisionNum++;
		if(currentPos >= int(array.size()))
			currentPos -= array.size( );
		if(currentPos == temp)
			full = true;
	}

	if(isActive(currentPos) && !full) {
		sDelete[currentSize].tNumOfTransactions = sDelete[currentSize].tNumOfTransactions + 1;
		sDelete[currentSize].tNumOfProbes = sDelete[currentSize].tNumOfProbes + collisionNum;
		array[currentPos].info = DELETED;
		return true;
	}
	fDelete[currentSize].tNumOfTransactions = fDelete[currentSize].tNumOfTransactions + 1;
	fDelete[currentSize].tNumOfProbes = fDelete[currentSize].tNumOfProbes + collisionNum;
	return false;
}
/*
template <class HashedObj>
int HashTable<HashedObj>::nextPrime(int n) {
	if(n % 2 == 0)
		n++;

	for(; !isPrime(n); n += 2)
		;

	return n;
}

template <class HashedObj>
bool HashTable<HashedObj>::isPrime(int n) {
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
*/
template <class HashedObj>
bool HashTable<HashedObj>::isFull() {
	return currentSize == array.size();
}

template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find(const HashedObj & x) { // find
	int collisionNum = 0;
	int currentPos = myhash(x, array.size());
	int temp = currentPos;
	bool full = false;

	while(array[currentPos].info != EMPTY && array[currentPos].element != x && !full) {
		currentPos++;
		collisionNum++;
		if(currentPos >= int(array.size()))
			currentPos -= array.size( );
		if(currentPos == temp)
			full = true;
	}

	if(isActive(currentPos) && !full) {
		sFind[currentSize].tNumOfTransactions = sFind[currentSize].tNumOfTransactions + 1;
		sFind[currentSize].tNumOfProbes = sFind[currentSize].tNumOfProbes + collisionNum;
		return array[currentPos].element;
	}
	fFind[currentSize].tNumOfTransactions = fFind[currentSize].tNumOfTransactions + 1;
	fFind[currentSize].tNumOfProbes = fFind[currentSize].tNumOfProbes + collisionNum;
	return ITEM_NOT_FOUND;
}

template<class HashedObj>
void HashTable<HashedObj>::printArray(ofstream & output) const{ // private printArray
	output << "EXPERIMENT" << endl;
	output << endl;
	output << "Successful Insert" << endl;
	for(unsigned int i = 0; i < sInsert.size(); i++) {
		if(sInsert[i].tNumOfTransactions > 0)
			output << double(i) / array.size() << " \t" << double(sInsert[i].tNumOfProbes) / sInsert[i].tNumOfTransactions << endl;
	}

	output << endl;
	output << "Failed Insert" << endl;

	for(unsigned int i = 0; i < fInsert.size(); i++) {
		if(fInsert[i].tNumOfTransactions > 0)
			output << double(i) / array.size() << " \t" << double(fInsert[i].tNumOfProbes) / fInsert[i].tNumOfTransactions << endl;
	}

	output << endl;
	output << "Successful Delete" << endl;

	for(unsigned int i = 0; i < sDelete.size(); i++) {
		if(sDelete[i].tNumOfTransactions > 0)
			output << double(i) / array.size() << " \t" << double(sDelete[i].tNumOfProbes) / sDelete[i].tNumOfTransactions << endl;
	}

	output << endl;
	output << "Failed Delete" << endl;

	for(unsigned int i = 0; i < fDelete.size(); i++) {
		if(fDelete[i].tNumOfTransactions > 0)
			output << double(i) / array.size() << " \t" << double(fDelete[i].tNumOfProbes) / fDelete[i].tNumOfTransactions << endl;
	}

	output << endl;
	output << "Successful Find" << endl;

	for(unsigned int i = 0; i < sFind.size(); i++) {
		if(sFind[i].tNumOfTransactions > 0)
			output << double(i) / array.size() << " \t" << double(sFind[i].tNumOfProbes) / sFind[i].tNumOfTransactions << endl;
	}

	output << endl;
	output << "Failed Find" << endl;

	for(unsigned int i = 0; i < fFind.size(); i++) {
		if(fFind[i].tNumOfTransactions > 0)
			output << double(i) / array.size() << " \t" << double(fFind[i].tNumOfProbes) / fFind[i].tNumOfTransactions << endl;
	}

	output << endl << endl;
}

template <class HashedObj>
void HashTable<HashedObj>::print(ofstream & output) { // public print
	printArray(output);
}
