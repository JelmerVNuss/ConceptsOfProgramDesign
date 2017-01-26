/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvCollumn.hpp
 * Author: Michiel
 *
 * Created on 22 januari 2017, 16:10
 */


#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstring>
#include "CsvTraits.hpp"


#ifndef CSVCOLLUMN_HPP
#define CSVCOLLUMN_HPP

/*
 * CsvCollumn is the generic class that can be used for each column in a CSV file.
 * It takes a template type parameter to define what type the Get function should return
 * And thus, what type it should parse the string from the CSV file from.
 * Since it is template code, as in, the code should be generated for each type we wish it to work for,
 * The definition AND the declaration of the functions is done in this header file.
 */
template <typename T>
class CsvCollumn {
public:
    CsvCollumn(const char* name, const int& number, char delimiter);
    CsvCollumn(const CsvCollumn& orig);
    virtual ~CsvCollumn();
    
    /// The generic Get function which can be called for every kind of column.
    /// \param row_number Which row number you want the value from
    /// \param stream The filestream to read from
    /// \return the parsed value of type T from row row_number, from the filestream.
    T Get(const unsigned int& row_number, const char* file_name);
private:
    /// The function that actually parses. Uses template parameter specialization
    /// to choose the right type to parse the value to and to return
    /// \param value as string that needs to be parsed to type T
    /// \return the parsed value of type T
    T _get(const std::string& value);
    std::vector<std::string> split(const std::string& value);
    std::string name;
    int number;
    char delimiter;
};

template<typename T>
CsvCollumn<T>::CsvCollumn(const char* _name, const int& _number, char _delimiter) 
    : name(_name), number(_number), delimiter(_delimiter) {
}

template<typename T>
CsvCollumn<T>::CsvCollumn(const CsvCollumn& orig) {
}

template<typename T>
CsvCollumn<T>::~CsvCollumn() {
}

template<typename T>
T CsvCollumn<T>::Get(const unsigned int& row_number, const char* file_name)
{
    std::ifstream stream (file_name);
    
    std::string value = "";  
    std::getline(stream, value);
    std::getline(stream, value);
    for(unsigned int i = 0; i < row_number; ++i) {
        std::getline(stream, value);
    }
    
    value = split(value)[number];
    return _get(value);
}



template<typename T>
std::vector<std::string> CsvCollumn<T>::split(const std::string& value)
{
    std::stringstream ss(value);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delimiter)) {
        elems.push_back(item);
    }
    return elems;
}


#endif /* CSVCOLLUMN_HPP */

