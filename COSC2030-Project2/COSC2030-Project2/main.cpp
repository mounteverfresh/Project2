// Kyle Leadbetter. Alejandro Bermudez
//

#include "stdafx.h"
#include <iostream>
#include "Node.h"

using std::cout;
using std::cin;

int main()
{
	string in;
	cout << "Enter data for root node:  ";
	const char* input= new char[8];
	cin >> in;
	input = in.c_str();
	Node newNode = Node(input);
	system("pause");
}

