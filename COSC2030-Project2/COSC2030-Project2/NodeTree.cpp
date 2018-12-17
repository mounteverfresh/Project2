#include "stdafx.h"
#include "NodeTree.h"
#include <cmath>



Node::Node(string in = "abcdefgh")
{
	data = in;
}

int Node::hasChildren()
{
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
			left = newNode;
		}
	}
	else if (left != NULL && left->isFull())
	{
		if (right == NULL)
		{
			right = newNode;
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
			left = newNode;
		}
		else if (!left->isFull())
		{
			left->addLeaf(newNode, false);
		}
		else if (hasChildren() == 1)
		{
			right = newNode;
		}
		else
		{
			right->addLeaf(newNode, false);
		}

	}
}



Tree::Tree(Node* rt = new Node)
{
	root = rt;
	height = findHeight();
	leaves = 1 + root->totalChildren();
}

void Tree::addLeaf(Node * newNode)
{
	root->addLeaf(newNode, root->isFull());
	leaves++;
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
		outfile << "---" << root->data << std::endl;
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
		outfile << prefix + "/---" << subtree->data << std::endl;
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
		outfile << prefix + "\\---" << subtree->data << std::endl;
		displayRight(outfile, subtree->right, prefix + "     ");
	}
}



