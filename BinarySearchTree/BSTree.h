/**********************************************************************************
Author: Faik Kerem Örs
Date: 08/11/2016

#Programming Assignment - compression algorithm - BSTree.h - 
THE HEADER FILE OF BinaryNode and BinarySearchTree CLASSES.
**********************************************************************************/

#ifndef _BSTREE_H
#define _BSTREE_H
#include <iostream>
#include <string>
using namespace std;

//  class BinarySearchTree;

class BinaryNode { // Node class to store keys and codes.
	string key;
	int code;
	BinaryNode *left;  // left child pointer
	BinaryNode *right; // right child pointer

	BinaryNode(const string & key, const int & code, BinaryNode *left, BinaryNode *right) { // constructor
		this -> key = key;
		this -> code = code;
		this -> left = left;
		this -> right = right;
	}

	friend class BinarySearchTree; // BinarySearchTree class should access to this class.
};

class BinarySearchTree { // BinarySearchTree class to store nodes.
public: 		 // Constructor, Destructor and Public functions of this class.
	BinarySearchTree(const int &);
	~BinarySearchTree();
	const int & find(const string &) const;
	bool isEmpty() const;
	void printTree() const;
	void makeEmpty();
	void insert(const string &, const int &);

private:
	BinaryNode *root; 		// The pointer to point to the root node.
	const int ITEM_NOT_FOUND; 	// sentinel value to return if the key is not found.
	void insert(const string &, const int &, BinaryNode *&) const;  // Private insert function to use recursively.
	BinaryNode *find(const string &, BinaryNode *) const; 		// Private find function to use recursively.
	void makeEmpty(BinaryNode *&) const; // Private makeEmpty function to use recursively.
	void printTree(BinaryNode *) const;  // This function is not needed but I put to test my BS Tree.
	const int & elementAt(BinaryNode *) const; // Returns the code if the key is found, otherwise returns ITEM_NOT_FOUND.

};

#endif
