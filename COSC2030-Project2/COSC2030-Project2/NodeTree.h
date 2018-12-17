#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <functional>


using std::string;
using std::vector;
using std::hash;

class Node {
public:
	string data;
	Node* parent;
	Node* right;
	Node* left;
	int hasChildren();
	int totalChildren();
	bool isFull();
	void addLeaf(Node * newNode, bool full);
	Node(string in);
};

struct Tree {
	Tree(Node* rt);
	void addLeaf(Node * newNode);
	bool treeFull();
	int findHeight();
	void display(std::ostream& outfile);
	static void displayLeft(std::ostream & outfile, Node * subtree, std::string prefix);
	static void displayRight(std::ostream & outfile, Node * subtree, std::string prefix);

	Node * root;// move back to private when done testing
	int leaves; // ^^^^^^


private:
	int height;
	//Node* leftmost;
};

