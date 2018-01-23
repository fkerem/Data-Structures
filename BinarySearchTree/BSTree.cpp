/*************************************************************************************
Author: Faik Kerem Örs
Date: 08/11/2016

#Programming Assignment - compression algorithm - BSTree.cpp
*************************************************************************************/

#include "BSTree.h"

BinarySearchTree::BinarySearchTree(const int & notFound) : ITEM_NOT_FOUND(notFound) { // The constructor
	root = NULL;
}

BinarySearchTree::~BinarySearchTree() { // The destructor
	makeEmpty();
	delete root;
}

//Private insert function to use recursively.
void BinarySearchTree::insert(const string & str, const int & intCode, BinaryNode *& t) const {
	if(t == NULL) {
		t = new BinaryNode(str, intCode, NULL, NULL);
	}
	else if(str < t -> key) {
		insert(str, intCode, t -> left);
	}
	else if(str > t -> key) {
		insert(str, intCode, t -> right);
	}
	else {
		;
	}
}

// Public insert function.
void BinarySearchTree::insert(const string & str, const int & intCode) {
	insert(str, intCode, root);
}

// This function returns the code if the key is found, otherwise it returns ITEM_NOT_FOUND.
const int & BinarySearchTree::elementAt(BinaryNode *t)const {
	if(t == NULL) {
		return ITEM_NOT_FOUND;
	}
	else {
		return t -> code;
	}
}

// Private find function to use recursively.
BinaryNode *BinarySearchTree::find(const string & str, BinaryNode *t) const {
	if(t == NULL) {
		return NULL;
	}
	else if(str < t -> key) {
		return find(str, t -> left);
	}
	else if(str > t -> key) {
		return find(str, t -> right);
	}
	else {
		return t;
	}
}

const int & BinarySearchTree::find(const string & str) const {
	return elementAt(find(str, root));
}

// Private makeEmpty function to use recursively.
void BinarySearchTree::makeEmpty(BinaryNode *& t) const {
	if(t != NULL) {
		makeEmpty(t -> left);
		makeEmpty(t -> right);
		delete t;
	}
	t = NULL;
}

void BinarySearchTree::makeEmpty() {
	makeEmpty(root);
}

// printTree function to test my Binary Search Tree. It's private to use recursively.
void BinarySearchTree::printTree(BinaryNode * t) const {
	if(t != NULL) {
		cout << t -> key << " " << t -> code << endl;
		printTree(t -> left);
		printTree(t -> right);
	}
}

void BinarySearchTree::printTree() const {
	printTree(root);
}
