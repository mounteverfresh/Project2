// Kyle Leadbetter. Alejandro Bermudez
//

#include "stdafx.h"
#include <iostream>
#include "NodeTree.h"

using std::cout;
using std::cin;

void tfPrint(bool in);

int main()
{
	int in;
	cout << "--------------\n";
	Node * root = new Node("1");
	Tree newTree = Tree(root);
	cout << "number of leaves:  ";
	cin >> in;
	for (int i = 2; i < (in + 1); i++)
	{
		newTree.addLeaf(new Node(std::to_string(i)));
	}
	tfPrint(newTree.treeFull());
	newTree.display(cout);

	//system("pause");
	return 0;
}


void tfPrint(bool in) //pure test method to save me typing
{
	static int count = 1;
	cout << "Test " << count << ":  ";
	if (in)
	{
		cout << "true\n--------------\n";
	}
	else {
		cout << "false\n--------------\n";
	}
	count++;
}