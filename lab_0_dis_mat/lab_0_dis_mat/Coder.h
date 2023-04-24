#pragma once
#include <string>

using namespace std;

struct Node
{
    char ch;
    int freq;
    Node* left, * right;
};


Node* getNode(char ch, int freq, Node* left, Node* right);



class Coder
{
	void opener(bool f = 0);
	void opener_RLE(bool f = 0);
    Node* root = NULL;

public:
	
	std::pair<string, Node*> Huffman(bool action, string text);
	std::string RLE(bool action, std::string text);
};

