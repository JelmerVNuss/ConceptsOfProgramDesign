/* This file is generated from TestCsv.csv */

#ifndef CSV_HPP
#define CSV_HPP

#include "CsvCollumn.hpp"

using namespace std;

struct TestCsv {
	static CsvCollumn<int> id() { return CsvCollumn<int>("id", 0, ';');}
	static CsvCollumn<string> name() { return CsvCollumn<string>("name", 1, ';');}
	static CsvCollumn<int> additional() { return CsvCollumn<int>("additional", 2, ';');}
};

#endif /* CSV_HPP */