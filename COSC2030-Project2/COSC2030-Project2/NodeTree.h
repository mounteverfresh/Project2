#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>


using std::string;
using std::vector;
using std::hash;

class Node {
public:
	string data;
	string id;
	string idParent;
	string rHash;
	string lHash;
	vector<string> rightHist;
	vector<string> leftHist;
	Node* parent;
	Node* right;
	Node* left;
	std::unordered_map<string, string>  map;
	std::hash<string> myHash;


	int hasChildren();
	int totalChildren();
	bool isFull();
	void addLeaf(Node * newNode, bool full);
	string idHash(hash<string> thisHash, string id, string event);
	Node* findNode(string in);
	string printEntry(string in);
	void printHistory();
	void updateParents();
	


	Node(string in, std::unordered_map<string,string> newMap);
	Node(Node * prnt, string in);
};

struct Tree {
	Tree(Node* rt);
	Tree();
	void addLeaf(Node * newNode);
	bool treeFull();
	int findHeight();
	Node * findNode(string in);
	void printNode(Node * node); // add stuff to this
	void changeNode(string idNode, string newData);


	void display(std::ostream& outfile);
	static void displayLeft(std::ostream & outfile, Node * subtree, std::string prefix);
	static void displayRight(std::ostream & outfile, Node * subtree, std::string prefix);


	Node * root;// move back to private when done testing
	int leaves; // ^^^^^^

private:
	int height;
	//Node* leftmost;
};

