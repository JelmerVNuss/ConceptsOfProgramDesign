/* This file is generated from TestCsv.csv */

#ifndef CSV_HPP
#define CSV_HPP

#include "CsvCollumn.hpp"

using namespace std;

struct TestCsv {
	static const CsvCollumn<int> kolom1() { return CsvCollumn<int>("kolom1", 0, ';');}
	static const CsvCollumn<string> kolom2() { return CsvCollumn<string>("kolom2", 1, ';');}
	static const CsvCollumn<int> kolom3() { return CsvCollumn<int>("kolom3", 2, ';');}
};

#endif /* CSV_HPP */