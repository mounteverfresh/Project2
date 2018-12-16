#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <functional>

using std::string;
using std::vector;
using std::hash;

class Node {
private:
	int id;
	int parentId;
	string data;
	int rHash;
	int lHash;
	vector<int> rHist;
	vector<int> lHist;
	Node* parent;
	Node* rChild;
	Node* lChild;
	bool full;

public:
	Node();
	Node(const char* in); //should only be used to make a root node
	Node(Node* parent, string in);
	bool checkFull();
	void addRhist();
	void addLhist();
	Node newChild(string in);
};