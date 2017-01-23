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

#ifndef CSVCOLLUMN_HPP
#define CSVCOLLUMN_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "CsvTraits.hpp"



template <typename T>
class CsvCollumn {
public:
    CsvCollumn(const char* name, const int& number, char delimiter);
    CsvCollumn(const CsvCollumn& orig);
    virtual ~CsvCollumn();
    
    inline typename CsvTraits<T>::Type Get(const unsigned int& row_number, std::ifstream& stream);
private:
    inline typename CsvTraits<T>::Type _get(const std::string& value);
    
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
inline typename CsvTraits<T>::Type CsvCollumn<T>::Get(const unsigned int& row_number, std::ifstream& stream)
{
    //TODO: Logic to read from file
    std::string value = "";  
    std::getline(stream, value);
    std::getline(stream, value);
    for(unsigned int i = 0; i < row_number; ++i) {
        std::getline(stream, value);
    }
    
    value = split(value)[number];
    return _get(value);
}


template<>
inline typename CsvTraits<int>::Type CsvCollumn<int>::_get(const std::string& value)
{
    try {
        return std::stoi(value);
    } catch(std::invalid_argument ex) {
        std::cout << "Invalid arg error: " << value << " " << ex.what() << std::endl;
    }
    return 0;
}

template<>
inline typename CsvTraits<double>::Type CsvCollumn<double>::_get(const std::string& value)
{
    return std::stod(value);
}

template<>
inline typename CsvTraits<std::string>::Type CsvCollumn<std::string>::_get(const std::string& value)
{
    return value;
}
template<typename T>
std::vector<std::string> CsvCollumn<T>::split(const std::string& value)
{
    std::stringstream ss(value);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delimiter)) {
        elems.push_back(item);
        // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}


#endif /* CSVCOLLUMN_HPP */

