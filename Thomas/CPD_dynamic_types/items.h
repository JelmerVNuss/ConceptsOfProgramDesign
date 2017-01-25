#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <cstdlib>
#include <stdexcept>  
#include <iostream>
#include "CSVExample.h"
#include <typeinfo>

using namespace std;  

//base class to define gerneral items
class Item
{

};
//template class to define items of type T
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

template<typename T>
void changeType(Item* items[LY][LX], string types[LY][LX], int idY, int idX, T value)
{
    types[idY][idX] = typeid(T).name();
    items[idY][idX] = new DeducedItem<T>(value);
    update<T>(items[idY][idX], value);    
}


static bool IsInt(string s)
{
    int i;
    try
    {
	i = std::stoi(s);
    }
    catch(invalid_argument e)
    {
	return false;
    }
    return true;
}

static void printItems(Item* items[LY][LX], string types[LY][LX])
{
    for (int j = 0; j < LY; j++)
    {
        for (int i = 0; i < LX; i++)
	{
            Item* x = items[j][i];
            string s;
            string t = types[j][i];
            if (t == "i") { s = to_string(getValue<int>(x)); t = "int"; }
            else { s = getValue<string>(x); t = "str"; }
            cout << s << "  (" << t << ")";
            if (i < LX - 1) cout << ", ";
	}
	cout << endl;
    }
}

static void readItems(Item* items[LY][LX], string types[LY][LX], const string CSV[LY][LX])
{
    for (int j = 0; j < 5; j++)
    {
	for (int i = 0; i < 3; i++)
	{
            string current = CSV[j][i];
            if (IsInt(current))
            {   //here is where templates are instantiated
                items[j][i] = new DeducedItem<int>(stoi(current));
                types[j][i] = "i";
            }
            else
            {
                items[j][i] = new DeducedItem<string>(current);
		types[j][i] = "Ss";
            }
	}
    }
}

#endif /* ITEMS_H */

