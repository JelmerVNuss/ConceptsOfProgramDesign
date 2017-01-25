/* This file is generated from TestCsv.csv */

#ifndef CSV_HPP
#define CSV_HPP

#include "CsvCollumn.hpp"

using namespace std;

struct TestCsv {
	static CsvCollumn<int> kolom1() { return CsvCollumn<int>("kolom1", 0, ';');}
	static CsvCollumn<string> kolom2() { return CsvCollumn<string>("kolom2", 1, ';');}
	static CsvCollumn<int> kolom3() { return CsvCollumn<int>("kolom3", 2, ';');}
};

#endif /* CSV_HPP */