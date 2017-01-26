/* 
 * File:    main.hpp
 * Author:  Robin
 * Summary: The main class which shows an example of how to use the CSV-parser.
 */


#include "CsvIterator.hpp"
#include <iostream>
#include <fstream>

#include <boost/tuple/tuple.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

using namespace boost::tuples;
typedef tuple<int, std::string, std::string> record;

void doSomethingWithEachRow(int &total, const record& value){
    //Access each column by their corresponding index (0 in this case).
    total += boost::tuples::get<0>(value);
    std::cout << "First name: " << boost::tuples::get<1>(value) << std::endl;
}

int main(int argc, const char *argv[])
{
    //Arbitrary CSV file
    std::ifstream ifs("test.csv");
    csv::iterator<record> it(ifs);
    
    int total = 0;
    //Iterate through all rows.
    std::for_each(it, csv::iterator<record>(), [&total](const record& rec){
        //Call myFunc for every row in the CSV.
        doSomethingWithEachRow(total, rec);
    });
    
    std::cout << "Total numbers: " << total << std::endl;
    
    return 0;
}