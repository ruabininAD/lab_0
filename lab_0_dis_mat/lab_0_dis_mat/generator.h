#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;


class generator
{	
	string alf; // �������
	map <char, int> mp; // ��� ����� ����
	string value; // ������

public:
	generator(string alf, int len);
	void head();
	string get_string();
	
};

