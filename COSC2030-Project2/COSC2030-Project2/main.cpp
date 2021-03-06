// Kyle Leadbetter. Alejandro Bermudez
//

#include "stdafx.h"
#include <iostream>
#include "NodeTree.h"

using std::cout;
using std::cin;
using std::endl;

void tfPrint(bool in);

int main()
{
	string command;
	bool done = false;
	std::unordered_map<string, string> newMap = std::unordered_map<string, string>();
	Tree mainTree = Tree();
	while (done == false)
	{
		cout << "--------------\n";
		cout << "enter a command(? for help):  ";
		cin >> command;
		if (command == "add")
		{
			cout << "enter data for new entry: ";
			cin >> command;
			mainTree.addLeaf(new Node(command, newMap));
		}
		else if (command == "display")
		{
			mainTree.display(cout);
		}
		else if (command == "lookup")
		{
			cout << "enter data to find node: ";
			cin >> command;
			mainTree.findNode(command);
		}
		else if (command == "modify")
		{
			cout << "enter the id of the node you would like to modify,\n followed by the new data entry: ";
			string idIn;
			string dataIn;
			cin >> idIn >> dataIn;
			

		}
		else if (command == "end")
		{
			done = true;
		}
		else
		{
			cout << "valid commands:" << endl <<
				"add - add a name to the tree" << endl <<
				"display - visualize tree" << endl <<
				"end - end program" << endl <<
				"lookup - display contents of given node" << endl <<
				"modify - modify contents of given node" << endl;
		}
	}

	//system("pause");
	return 0;
}


void tfPrint(bool in) //pure test method that is easy to look at to save me typing
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