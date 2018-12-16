#include "stdafx.h"
#include "Node.h"
#include <string>
#include <functional>

using std::string;

Node::Node()
{

}

Node::Node(const char* in)
{
	id = 001;
	data = in;

}

Node::Node(Node* parent, string in)
{
	parentId = parent->id;
	data = in;
	id = parentId + 1;
}

bool Node::checkFull()
{
	if (rChild != NULL && lChild != NULL)
	{
		return true;
	}
	return false;
}
void Node::addRhist()
{
	rHist.push_back(rHash);
}

void Node::addLhist()
{
	lHist.push_back(lHash);
}

Node Node::newChild(string in)
{
	Node newNode;
	if (lChild == NULL)
	{
		lChild =  new Node(this, in);
		newNode = *lChild;
	}
	else if (rChild == NULL)
	{
		rChild = new Node(this, in);
		newNode = *rChild;
	}
	else
	{
		lChild->newChild(in);
	}
	return newNode;
}