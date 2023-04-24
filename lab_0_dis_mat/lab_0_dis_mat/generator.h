#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;


class generator
{	
	string alf; // алфавит
	map <char, int> mp; // мап число букв
	string value; // строка

public:
	generator(string alf, int len);
	void head();
	string get_string();
	
};

