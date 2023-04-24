#include "generator.h"
#include <stdlib.h> // srand
#include <time.h> // time
#include <map>
#include <iostream>
#include <random>

generator::generator(string _alf, int len)
{
	alf = _alf;
	srand(time(NULL));

	string alfp = "";
	int count = 1;
	for (char letter : alf)
	{
		for (int count_letter = 0; count_letter < count; count_letter++) {
			alfp.push_back(letter);
		}
		count++;
	}

	cout <<"\t" << "Сенерирована строка на основе алфавита: \"" << _alf << "\"" << endl;
	cout << "\t" << "Подстрока: \"" << alfp << "\"" << endl;
	
	for (char i : alf) { mp[i] = 0; }
	int elem;
	for (int i = 0; i < len; i++){
		elem = alfp[rand() % alfp.length()];
		value.push_back(elem);
		mp[elem]++;
	}
	
}

void generator::head()
{	
	cout  << "Начало строки: " ;
	if (value.length() < 60) {
		std::cout << value;
	}
	else {
		std::cout << value.substr(0, 60);
	}
	std::cout <<"..." << endl;
	cout  << "Подсчет количества символов в строке: \n";
	for (auto i : mp)
		cout << "\t"  << i.first << ": " << i.second<< endl;

}

string generator::get_string()
{
	return value;
}


