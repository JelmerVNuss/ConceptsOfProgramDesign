
#include <cstdlib>
#include <string>
#include <iostream>
#include "templates.h"
#include "CSVExample.h"

using namespace std;

/*
 * 
 */

void printItems()
{
    for (int j = 0; j < LY ;j ++)
    {
        for (int i = 0; i < LX; i++)
        {
            for (int z = 0; z < exampleCSV[j][i].size(); z++)
            {
                cout << exampleCSV[j][i][z];
            }
            if (i < LX - 1) cout << ", ";
        }
        cout << endl;
    }
}

//example how to parse an int from string during compilation:
constexpr str_const elem_41 = exampleCSV[4][1];
const int E_41 = ParseInt<elem_41.size()>(elem_41.p_);

//here is another one:
constexpr str_const elem_22 = exampleCSV[2][2];
const int E_22 = ParseInt<elem_22.size()>(elem_22.p_);

printVoid(int row, int col, const int n)
{
    cout << endl << "Int parsed from string at index [" + to_string(row) + "][" + to_string(col) + "] during compile time: " << 
            to_string(n) << endl;
}

int main(int argc, char** argv) {
 
    printItems();
    
    printVoid(4,1,E_41);
    printVoid(2,2,E_22);
    
    return 0;
}

