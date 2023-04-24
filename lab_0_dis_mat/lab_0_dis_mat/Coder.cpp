#include "Coder.h"

#include <iostream> //cout cin
#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <bitset>
#include <unordered_map>
#include <regex>
#include <map>
using namespace std;


void Coder::opener(bool f )
{
		cout << "	" << " _   _          __   __                          " << endl;
		cout << "	" << "| | | |        / _| / _|                         " << endl;
		cout << "	" << "| |_| | _   _ | |_ | |_  _ __ ___    __ _  _ __  " << endl;
		cout << "	" << "|  _  || | | ||  _||  _|| '_ ` _ \\  / _` || '_ \\ " << endl;
		cout << "	" << "| | | || |_| || |  | |  | | | | | || (_| || | | |" << endl;
		cout << "	" << "\\_| |_/ \\__,_||_|  |_|  |_| |_| |_| \\__,_||_| |_|" << endl;
		cout << "	";
		if (f == 1) { cout << "d e "; }
		cout << "c o d i n g " << endl << endl;
}

void Coder::opener_RLE(bool f)
{
		cout << "	" << " ____  _      ______" << endl;
		cout << "	" << "| __ \\| |    |  ____|" << endl;
		cout << "	" << "| |_) | |    | |__" << endl;
		cout << "	" << "| _  /| |    |  __|" << endl;
		cout << "	" << "| |\\ \\| |____| |____" << endl;
		cout << "	" << "|_| \\_\\______|______|" << endl;

	
	cout << "	";
	if (f == 1) { cout << "d e "; }
	cout << "c o d i n g " << endl << endl;

}


struct comp
{// Объект сравнения, который будет использоваться для упорядочивания кучи

    bool operator()(const Node* l, const Node* r) const
    {
        // элемент с наивысшим приоритетом имеет наименьшую частоту
        return l->freq > r->freq;
    }
};

bool isLeaf(Node* root) {
    return root->left == nullptr && root->right == nullptr;
}


void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)
{// Проходим по дереву Хаффмана и сохраняем коды Хаффмана на карте.
    if (root == nullptr) {
        return;
    }

    // найден листовой узел
    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != "") ? str : "1";
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int& index, string str, string &res)
{// Проходим по дереву Хаффмана и декодируем закодированную строку
    
    if (root == nullptr) {
        return;
    }

    // найден листовой узел
    if (isLeaf(root))
    {
        res.push_back(root->ch);
        return ;
    }

    index++;

    if (str[index] == '0') {
        decode(root->left, index, str, res);
    }
    else {
        decode(root->right, index, str, res);
    }
   
}


Node* buildHuffmanTree(string text)
{
    // базовый случай: пустая строка
    if (text == "") { return NULL; }


    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }


    priority_queue<Node*, vector<Node*>, comp> pq;


    for (auto pair : freq) { pq.push(getNode(pair.first, pair.second, nullptr, nullptr)); }


    while (pq.size() != 1)//пока не 1 узел
    {

        Node* left = pq.top(); pq.pop();
        Node* right = pq.top();    pq.pop();


        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }


    Node* root = pq.top();
    return root;
}



vector<char> encode_RLE(string &txt) {

    
    std::vector<char> res;

    int index = 0;
    
    while (index < txt.length()) {

        char symbol = txt[index];
        char len_series = 0;

        while (symbol == txt[index + len_series]) {
            //длинна серии одинаковых символ
            len_series++;
            if (len_series == 127) { break; }
            //переброс
        }

        if (len_series == 1) {
            //если одиноковый символ 1
            vector<char> tmp = { symbol };
            while ( (txt.length() > (index + len_series + 1)  && txt[index + len_series] != txt[index + len_series + 1]  )) {

                tmp.push_back(txt[index + len_series]);
                len_series++;
               
            }



            res.push_back(len_series + 128);
            for (auto c : tmp) { res.push_back(c);  }
            index = index + len_series;
            continue;
        }

        res.push_back(len_series);
        res.push_back(symbol);
        //пополнение кратность + символ
        index = index + len_series;
        //if (index < 998) { cout << index <<endl; }

    }

    //for (int i = 0; i < res.size(); i++) {         std::bitset<8> x(res[i]);        cout << x << " ";    }
    //вывод

    return res;
}

string decode_RLE(string& txt, string &separator) {
    string res;
    
    /*regex regex("\\_");

    vector<string> out(
        sregex_token_iterator(txt.begin(), txt.end(), regex, -1),
        sregex_token_iterator()
    );*/


    vector<char> out(txt.begin(), txt.end());

    int n;
    bool flag = true;
    for (int i = 0; i < out.size(); i++) {
        n = bitset<8>(out[i]).to_ulong();

        if (n < 128) {
            i++;

            for (int j = 0; j < n; j++) {
                res += char(bitset<8>(out[i]).to_ulong());
            }
        }
        else {
            n = n - 128;
            i++;
            for (int j = i; j < i + n; j++) {
                res += char(bitset<8>(out[j]).to_ulong());
            }
            i = i + n - 1;

        }


    }
    return res;
}




pair<string, Node*> Coder::Huffman(bool action, string text )
{
    
	string res;
	if (action == 0) {
        
        float cod_price = 0;
		opener(action);
	    root = buildHuffmanTree(text);
       
        unordered_map<char, string> huffmanCode;
        encode(root, "", huffmanCode);

        cout <<"\t" << "Коды букв: ";
        for (auto pair : huffmanCode) {
            cout << pair.first << "-" << pair.second << " ";
            //подсчет цены кодирования
            float count_char = count(text.begin(), text.end(), pair.first);
            float p_char = count_char / text.length();
            cod_price += p_char * pair.second.length();
        }
        cout << endl;



        // Печатаем закодированную строку
        string str;
        for (char ch : text) {   str += huffmanCode[ch];   }

        cout << "\t" << "Вес строки: " << text.size() << " байт" << endl;
        cout << "\t" << "Вес закодированной строки: " << str.size()/8 << " байт" << endl;
        cout << "\t" << "Kоэффициент сжатия : " << float(text.size()) / (str.size() / 8 ) << endl;


        cout << "\t" << "Цена кодирования : " << cod_price << endl;
        return make_pair(str, root);
        
	}
	else if (action == 1) {
        if (root == NULL) {
            cout << "текст не закодирован ";
            return make_pair(" ", nullptr);
        }
		opener(action);

        if (isLeaf(root)) { while (root->freq--) {  cout << root->ch;  }        }
        else {
            int index = -1;
            while (index < (int)text.size() - 1) {
                 decode(root, index, text, res);
                
            }
        }
        cout << endl;
	}
	return make_pair( res, root);
}

std::string Coder::RLE(bool action, std::string text)
{

    string separator = "_";
	string res;
    opener_RLE(action);//банер


	if (action == 0) {
        
        vector<char> code_rle = encode_RLE(text); //кодируем
        

        int count_char = 0;
        //cout << "\t" << "закодированная строка : ";
        for (auto i : code_rle) {
            if (i == '\0') { break; }
            //cout << i;
            bitset<8> x(i);
            res += x.to_string() + separator;
            count_char++;
        }// форматируем для вывода
        cout << endl;


        // отношение объёма исходных несжатых данных к объёму сжатых данных
        cout << "\t" << "Kоэффициент сжатия: " << float(text.length()) / count_char << endl; 
        string str(code_rle.begin(), code_rle.end());
        return str;
	}
	else if (action == 1) {

		
        res = decode_RLE(text, separator);

	}
	return res;
}

Node* getNode(char ch, int freq, Node* left, Node* right)
{// Функция для выделения нового узла дерева
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}


