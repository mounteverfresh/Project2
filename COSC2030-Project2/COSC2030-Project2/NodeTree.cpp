#include "stdafx.h"
#include "NodeTree.h"
#include "Utility.h"
#include <cmath>
#include <iostream>
#include <functional>

using std::cout;
using std::endl;



Node::Node(string in = "abcdefgh", std::unordered_map<string, string> newMap = std::unordered_map<string, string>())
{
	data = in;
	rightHist = vector<string>();
	leftHist = vector<string>();
	idParent = rand8String();
	parent = NULL;
	right = NULL;
	left = NULL;
	map = newMap;
	myHash = map.hash_function();
	id = idHash(myHash, in, idParent);
	rHash = lHash = "";

}

Node::Node(Node * prnt, string in)
{
	parent = prnt;
	data = in;
	idParent = parent->id;
	rightHist = vector<string>();
	leftHist = vector<string>();
	map = prnt->map;
	myHash = prnt->myHash;
	id = idHash(myHash, in, idParent);
	rHash = lHash = "";
	right = left = NULL;
}

int Node::hasChildren()
{
	if (this == NULL)
	{
		return 0;
	}
	if (right == NULL && left == NULL)
	{
		return 0;
	}
	else if (right == NULL || left == NULL)
	{
		return 1;
	}
	else { return 2; }
}

int Node::totalChildren()
{
	if (this == NULL)
	{
		return 0;
	}
	else
	{
		if (right == NULL && left == NULL)
		{
			return 0;
		}
		else if (right == NULL || left == NULL)
		{
			if (right == NULL)
			{
				return 1 + left->totalChildren();
			}
			else
			{
				return 1 + right->totalChildren();
			}
		}
		else { return 2 + left->totalChildren() + right->totalChildren(); }
	}
}

bool Node::isFull()
{
	if (hasChildren() == 0)
	{
		return true;
	}
	else if (hasChildren() == 2) 
	{
		if ((left->isFull() && right->isFull()) &&
			(left->totalChildren() == right->totalChildren()))
		{
			return true;
		}
		return false;
	}
	return false;
}

void Node::addLeaf(Node * newNode, bool full)
{
	if (full) //adds new level if tree is full
	{
		if (left != NULL)
		{
			left->addLeaf(newNode, true);
		}
		else
		{
			left = new Node(this, newNode->data);
			left->updateParents();
		}
	}
	else if (left != NULL && left->isFull())
	{
		
		
			if (right == NULL)
			{
				right = new Node(this, newNode->data);
				right->updateParents();
			}
			else if (right->totalChildren()==left->totalChildren())
			{
				left->addLeaf(newNode, true);
			}
			else
			{
				right->addLeaf(newNode, false);
			}
		
	}
	else
	{
		if (hasChildren() == 0)
		{
			left = new Node(this, newNode->data);
			left->updateParents();
		}
		else if (!left->isFull())
		{
			left->addLeaf(newNode, false);
		}
		else if (hasChildren() == 1)
		{
			right = new Node(this, newNode->data);
			right->updateParents();
		}
		else
		{
			right->addLeaf(newNode, false);
		}

	}
}

Node* Node::findNode(string in)
{
	if (data == in)
	{
		return this;
	}
	else if (left == NULL && right == NULL)
	{
		return NULL;
	}
	Node * result = new Node();
	if (left != NULL)
	{
		result = left->findNode(in);
	}
	if (result == NULL)
	{
		if (right != NULL)
		{
			result = right->findNode(in);
		}
	}

	return result;
}

string Node::idHash(hash<string> thisHash, string id, string event)
{
	size_t h1 = thisHash(id);
	size_t h2 = thisHash(event);
	size_t h3;
	if (h1 > h2)
	{
		h3 = h1 - h2;
	}
	else
	{
		h3 = h2 - h1;
	}
	h1 = thisHash(std::to_string(h3));
	string final = std::to_string(h1);
	final = final.substr(0, 8);
	return final;
}

string Node::printEntry(string in)
{
	if (in.c_str() == NULL)
	{
		return "Entry not found.";
	}
	else
	{
		return in;
	}
}

void Node::printHistory()
{
	cout << "Left History:" << endl;
	if (leftHist.empty())
	{
		cout << "\tempty" << endl;
	}
	else
	{
		for (size_t i = 0; i < leftHist.size(); i++)
		{
			cout  << i << ")\t" << leftHist[i] << endl;
		}
	}
	cout << "Right History:" << endl;
	if (rightHist.empty())
	{
		cout << "\tempty" << endl;
	}
	else
	{
		for (size_t i = 0; i < rightHist.size(); i++)
		{
			cout  << i << ")\t" << rightHist[i] << endl;
		}
	}
}

void Node::updateParents()
{
	if (parent != NULL)
	{
		if (this == parent->left)
		{
			parent->lHash = idHash(myHash, id, data);
			parent->leftHist.push_back(parent->lHash);
		}
		else
		{
			parent->rHash = idHash(myHash, id, data);
			parent->rightHist.push_back(parent->rHash);

		}
	}
}


//------------------Tree Code-------------------//


Tree::Tree(Node* rt = new Node)
{
	root = rt;
	height = findHeight();
	leaves = 1 + root->totalChildren();
}

Tree::Tree()
{
	leaves = 0;
	height = 0;
}
void Tree::addLeaf(Node * newNode)
{
	if (leaves == 0)
	{
		root = newNode;
		leaves = 1;
		height = 1;
	}
	else
	{
		root->addLeaf(newNode, root->isFull());
		leaves++;
	}
}

int Tree::findHeight()
{
	int count = 1;
	Node * iter = root;
	while (iter->left != NULL)
	{
		count++;
		iter = iter->left;
	}
	return count;
}

bool Tree::treeFull()
{
	height = findHeight();
	if (leaves == (pow(2, height) - 1))
	{
		return true;
	}
	return false;
}

Node * Tree::findNode(string in)
{
	Node * foundNode = root->findNode(in);
	printNode(foundNode);
	return foundNode;
}

void Tree::printNode(Node* node)
{
	if (node == NULL)
	{
		cout << "--------------------\nNode not found.\n--------------------" << endl;
	}
	else {
		cout << "--------------------" << endl <<
			"ID:\t" << node->printEntry(node->id) << endl <<
			"PID:\t" << node->printEntry(node->idParent) << endl <<
			"Data:\t" << node->printEntry(node->data) << endl <<
			"LHASH:\t" << node->printEntry(node->lHash) << endl <<
			"RHASH:\t" << node->printEntry(node->rHash) << endl;

		node->printHistory();
		cout << "--------------------" << endl;
	}
}

void Tree::changeNode(string idNode, string newData)
{
	Node * modify = root->findNode(idNode);
	modify->data = newData;
	modify->updateParents();
}

//---------Display----------
/*
the instructions said visualize so I adapted the display tree functions from 
lab 8 to visualize this, an original function would have acted very similar to this one.
*/

void Tree::display(std::ostream& outfile)
{
	std::string prefix;
	if (root == NULL)
	{
		outfile << "-" << std::endl;
	}
	else
	{
		displayLeft(outfile, root->left, "    ");
		outfile << "---" << root->id << std::endl;
		displayRight(outfile, root->right, "    ");
	}
}

void
Tree::displayLeft(std::ostream & outfile,
	Node * subtree, std::string prefix)
{
	if (subtree == NULL)
	{
		outfile << prefix + "/" << std::endl;
	}
	else
	{
		displayLeft(outfile, subtree->left, prefix + "     ");
		outfile << prefix + "/---" << subtree->id << std::endl;
		displayRight(outfile, subtree->right, prefix + "|    ");
	}
}

void
Tree::displayRight(std::ostream & outfile,
	Node * subtree, std::string prefix)
{
	if (subtree == NULL)
	{
		outfile << prefix + "\\" << std::endl;
	}
	else
	{
		displayLeft(outfile, subtree->left, prefix + "|    ");
		outfile << prefix + "\\---" << subtree->id << std::endl;
		displayRight(outfile, subtree->right, prefix + "     ");
	}
}
//----------------end of borrowed code----------



