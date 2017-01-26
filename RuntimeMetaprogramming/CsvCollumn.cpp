/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvCollumn.cpp
 * Author: Michiel
 * 
 * Created on 22 januari 2017, 16:10
 */


#include "CsvCollumn.hpp"

template<>
int CsvCollumn<int>::_get(const std::string& value)
{
    try {
        return std::stoi(value);
    } catch(std::invalid_argument ex) {
        std::cout << "Invalid arg error: " << value << " " << ex.what() << std::endl;
    }
    return 0;
}

template<>
double CsvCollumn<double>::_get(const std::string& value)
{
    return std::stod(value);
}

template<>
std::string CsvCollumn<std::string>::_get(const std::string& value)
{
    return value;
}