// CPD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

//template klasse om constante ints in op te slaan
template <int N> struct Int {
	static const int value = N;
};

//-------------------van internet----------------------
//constante string klasse:
class str_const { // constexpr string
public:
	const char* const p_;
	const std::size_t sz_;
	template<std::size_t N>
	constexpr str_const(const char(&a)[N]) : // ctor
		p_(a), sz_(N - 1) {}
	constexpr char operator[](std::size_t n) { // []
		return n < sz_ ? p_[n] :
			throw std::out_of_range("");
	}
	constexpr std::size_t size() { return sz_; } // size()
};
//-----------------------------------------------------


//primary template to calculate powers of 10 in compile time
template<int N>  class Pow10
{
public:
	enum { result = 10 * Pow10<N - 1>::result };
};
//specialization template
template<> class Pow10<0>
{
public:
	enum { result = 1 };
};

//primary template to read int from character array
template< int DIM, typename T> class CharToInt
{
public:
	static int result(T* ptr) {
		return Pow10<DIM - 1>::result * (*ptr - 48) + CharToInt<DIM - 1, T>::result(ptr + 1);
	}
};
//specialization template
template<typename T> class CharToInt<1, T >
{
public:
	static int result(T* ptr) {
		return *ptr - 48;
	}
};
//(helper) template to define convenience function "ParseInt"
template <int DIM, typename T>
inline int ParseInt(T* a)
{
	return CharToInt<DIM, T>::result(a);
}

/*
//base class to define gerneral items
class Item
{

};
//template class to define items of type T
template<typeame T>
class DeducedItem : public Item {
public:
	DeducedItem(T v) 
	{ 
		var = v; 
	};
	~DeducedItem() {};

	T var;
};

//get the value of an item
template<typename T>
T getValue(Item* ptr)
{
	return *(T*)ptr;
}
//update the value of an item
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
				//here is where templates are instantiated
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
*/



static constexpr str_const voorbeeldCSV[5][3] = { { "Robin", "1", "2" },
											{ "Jelmer", "3", "Random string" },
											{ "Michiel", "410", "1230" },
											{ "Hugo", "6", "1" },
											{ "Thomas", "400", "200" } };


int main() {

	//int n = Pow10<4>::result;
	//cout << to_string(n) << endl; 	//prints 10^4

	//char chars[2];
	//chars[0] = '1';
	//chars[1] = '2';
	//int m = ParseInt<2>(chars);
	//cout << to_string(m) << endl;  //prints integer 'm' parsed from  'chars'
	
	//problem: lenght of character array needs to be hard-coded
	

	Int <voorbeeldCSV[4][1].size()> length;		//lengte van de string "400" (=3)
	str_const chars = voorbeeldCSV[4][1];		//constante string "400"
	int n = ParseInt<length.value>(chars.p_);	// n = 400

	cout << n << endl;

	//probleem: dit werkt dus niet...   :
	/*
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			Int <j> J;
			Int <i> i;
			str_const chars = ...
			int n = ...

		}
	}  */



	//how to get the 'lenght' of an element in a CSV file during compile time?


	//Item* items[5][3];
	//string types[5][3];

	//readItems(items, types, voorbeeldCSV);
	//printItems(items, types);
	//cout << endl;
	//update<int>(items[0][1], 3);
	//cout << "changed the value of [0][1] to: " << to_string(getValue<int>(items[0][1])) << endl;
	//cout << endl;
	//printItems(items, types);
	
	string inp;
	cin >> inp;

	return 0;
}


