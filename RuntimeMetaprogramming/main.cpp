

#include <bits/c++config.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <type_traits>
#include <string>
#include <tuple>

#include "TestCsv.hpp"

int main(int argc, char *argv[])
{
    /*
     * So, if _PARSE is defined. Either in the main function, or by passing the 
     * compile flag -D_PARSE, the CsvParser will do it's job, making that stage 1 
     * of the "type-provider".
     */
#define _PARSEA
#ifdef _PARSE
    CsvParser parser;
    parser.ParseToTemplate("TestCsv.csv", ';');
    exit(0);
#else
    /*
     * And if we do not pass that argument, we can make use of the generated code.
     */
    const char* file_name = "TestCsv.csv";
    // Print the ID (first column) of row 2
    std::cout << TestCsv::id().Get(1, file_name) << std::endl;
    
    // Print the name (column 2) of row 3
    std::cout << TestCsv::name().Get(2, file_name) << std::endl;
#endif /* PARSE */
}