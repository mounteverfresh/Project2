#pragma once
#include <cstdlib>
#include <string>
using std::string;

string rand8String();

string rand8String()
{
	string out;
	while (out.length() < 8)
	{
		int random = std::rand() % 10;
		out = out + std::to_string(random);
	}
	return out;
}