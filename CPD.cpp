// CPD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Item
{

};

template<typename T>
class DeducedItem : public Item {
public:
	DeducedItem(T v) 
	{ 
		var = v; 
	};
	~DeducedItem() {};

	T var;
};


template<typename T>
T getValue(Item* ptr)
{
	return *(T*)ptr;
}

template<typename T>
void update(Item* ptr, T value)
{
	*(T*)ptr = value;
}

bool IsInt(string s)
{
	int i;
	try
	{
		i = stoi(s);
	}
	catch(invalid_argument e)
	{
		return false;
	}
	return true;
}

bool IsFloat(string s)
{
	float f;
	try {
		f = stof(s);
	}
	catch (invalid_argument e)
	{
		return false;
	}
	return true;
}

void printItems(Item* items[5][3], string types[5][3])
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 3; i++)
		{

			Item* x = items[j][i];
			string s;
			string t = types[j][i];
			if (t == "integer") s = to_string(getValue<int>(x));
			else s = getValue<string>(x);

			cout << s << "  (" << t << ")";
			if (i < 2) cout << ", ";
		}
		cout << endl;
	}
}

void readItems(Item* items[5][3], string types[5][3], string CSV[5][3])
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			string current = CSV[j][i];
			if (IsInt(current))
			{
				items[j][i] = new DeducedItem<int>(stol(current));
				types[j][i] = "integer";
			}
			else
			{
				items[j][i] = new DeducedItem<string>(current);
				types[j][i] = "string";
			}
		}
	}
}

int main() {

	string voorbeeldCSV[5][3] = { {"Robin", "1", "2"},
								{"Jelmer", "3", "Random string"},
								{"Michiel", "410", "1230"},
								{"Hugo", "6", "1"},
								{"Thomas", "400", "200"}
	};

	Item* items[5][3];
	string types[5][3];

	readItems(items, types, voorbeeldCSV);
	printItems(items, types);
	cout << endl;
	update<int>(items[0][1], 3);
	cout << "changed the value of [0][1] to: " << to_string(getValue<int>(items[0][1])) << endl;
	cout << endl;
	printItems(items, types);
	
	string inp;
	cin >> inp;

	return 0;
}


