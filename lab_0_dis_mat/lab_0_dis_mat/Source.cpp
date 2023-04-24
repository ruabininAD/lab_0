#include <iostream>
#include "generator.h"
#include "Coder.h"
using namespace std;

namespace Operation
{
	bool coding = false;
	bool decoding = true;
};


generator text("abcde", 300);
Coder a;





void exampleRLE() {
	auto RLEcode = a.RLE(Operation::coding, text.get_string());
	cout << "\tRLEcode: " << RLEcode.substr(0, 100) << "..." << endl;
	cout << "\tпроверка сохранности текста после кодирования и декодирования RLE: " << bool(text.get_string() == a.RLE(Operation::decoding, RLEcode)) << endl;

}

void exampleHuffman() {
	pair<string, Node*> myH = a.Huffman(Operation::coding, text.get_string());
	cout << "\tHuffmanCode " << myH.first.substr(0, 100) << endl;
	cout << "\tпроверка сохранности текста после кодирования и декодирования Хаффмана: " << bool(text.get_string() == a.Huffman(Operation::decoding, myH.first).first) << endl;

} 

void exampleRLE_Huffman() {

	pair<string, Node*> H_R = a.Huffman(Operation::coding, a.RLE(Operation::coding, text.get_string()));

	auto CodingRes =  a.RLE(Operation::decoding, a.Huffman(Operation::decoding, H_R.first).first);
	cout << "\tпроверка сохранности текста после кодирования и декодирования RLE + Хаффмана: " << bool(text.get_string() == CodingRes) << endl;

}


void exampleHuffman_RLE() {
	pair<string, Node*> H_R = a.Huffman(Operation::coding,  text.get_string());
	auto H_Rcode = a.RLE(Operation::coding, H_R.first);

	auto H_code = a.RLE(Operation::decoding, H_Rcode);
	auto CodingRes = a.Huffman(Operation::decoding, H_code).first;

	cout << "\tпроверка сохранности текста после кодирования и декодирования Хаффмана + RLE: " << bool(text.get_string() == CodingRes) << endl;

}

void menu() {
	text.head();

	cout << "\n"
		"1) закодировать RLE\n"
		"2) закодировать в Huffman\n"
		"3) RLE + Huffman\n"
		"4) Huffman + RLE\n";
	int choise;
	cin >> choise;
	switch (choise)
	{

	case 1:
		exampleRLE();
		break;
	case 2:
		exampleHuffman();
		break;
	case 3:
		exampleRLE_Huffman();
		break;
	case 4:
		exampleHuffman_RLE();
		break;
	default:
		cout << "не та кнопочка \n ";
		break;
	}

}


int main() {
	setlocale(LC_ALL, "Russian");

	

	while (1) {
		menu();
		cout << "\n---------------------\n";
	}

	
	
	

	

	//string doubleH = a.Huffman(Operation::coding, a.RLE(Operation::coding, text.get_string()));
	//string myRLE = a.RLE(Operation::coding, text.get_string());
	//cout << "закодированный RLE текст: " << myRLE.substr(0, 60) << endl;
	//pair<string, Node*> H_R = a.Huffman(Operation::coding, a.RLE(Operation::coding, text.get_string()));
	//auto res  = a.RLE(Operation::coding, a.Huffman(Operation::coding, text.get_string()).first);
	//cout << "-- "<<text.get_string() << endl;
	//auto x =  a.RLE(Operation::coding, text.get_string());
	//cout << x << endl;
	//cout <<"chfd" << text.get_string() == a.RLE(Operation::decoding, x);
	/*
	 	vector<string> test_RLE = { "a",
								//"ab",
								//"aaaa",
								//"bcaaaa",
								//"aaaasd",
								//"aaaavvvv",
								"aaaasdvvvv" };
	for (string s : test_RLE) {
		cout<< "\t" << a.RLE(Operation::coding, s) << " : " << s << endl;
	}
	string code_RLE = a.RLE(Operation::coding, "aaaasdvvvv");
	cout << "\t" << a.RLE(Operation::decoding, code_RLE) << " : " << code_RLE << endl;
	
	*/


	return 0;
}