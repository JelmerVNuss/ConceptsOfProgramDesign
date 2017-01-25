
#ifndef COL_OPERATIONS_H
#define COL_OPERATIONS_H

#include <string>
#include <cstdlib>
#include <stdexcept>  
#include <iostream>
#include "CSVExample.h"
#include <typeinfo>

template<typename T>
static void AddColumn(Item* items[LY][LX], int col1, int col2)
{
    for (int j = 0; j < LY; j++)
    {
        T c1 = getValue<T>(items[j][col1]);
        T c2 = getValue<T>(items[j][col2]);
        
        update<T>(items[j][col2], c1 + c2);
    }
}

#endif /* COL_OPERATIONS_H */

