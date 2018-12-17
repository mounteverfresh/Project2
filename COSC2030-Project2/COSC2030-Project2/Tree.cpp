

#include "stdafx.h"
#include "NodeTree.h"


Tree::Tree(Node* rt = new Node)
{
	root = rt;
	height = 1;
	leaves = 1 + root->totalChildren();
}

bool Tree::addLeaf(string in)
{
	Node * newParent = root;
	Node * newNode = new Node(in);
	if (treeFull())
	{
		height++;
		while (newParent->left != NULL)
		{
			newParent = newParent->left;
		}
		newParent->left = newNode;
	}
	else
	{
		if (newParent->left)
		{

		}
	}
	leaves++;
	return false;
}

bool Tree::treeFull()
{
	if (leaves == (pow(2, height) - 1))
	{
		return true;
	}
	return false;
}
