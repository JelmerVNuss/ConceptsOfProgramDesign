/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: PC
 *
 * Created on 25 januari 2017, 13:30
 */

#include <cstdlib>
#include "items.h"
#include "CSVExample.h"
#include <string>
#include <typeinfo>
#include "col_operations.h"

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {

    Item* items[LY][LX];
    string types[LY][LX];
    
    cout << "Reading items..." << endl << endl;
    readItems(items, types, voorbeeldCSV);
    
    cout << "Printing items:" << endl << endl;
    printItems(items, types);
    
    update<int>(items[0][1], 314);
    cout << endl << "Changed the value of [0][1] to: " << to_string(getValue<int>(items[0][1])) << endl;
    
    update<string>(items[1][0], "Johan");
    cout << "Changed the value of [1][0] to: " << getValue<string>(items[1][0]) << endl;
    
    changeType<int>(items, types, 1, 2, 5);
    cout << "Changed the type and value of [1][2] to " << to_string(getValue<int>(items[1][2])) << endl;
      
    cout << endl << "Printing items:" << endl << endl;
    printItems(items, types);
    
    AddColumn<int>(items, 1, 2);
    cout << "Added 2nd column to 3rd column " << endl;
       
    cout << endl << "Printing items:" << endl << endl;
    printItems(items, types);
    
    return 0;
}

