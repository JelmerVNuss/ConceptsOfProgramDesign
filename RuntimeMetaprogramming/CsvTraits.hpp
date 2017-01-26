/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvTraits.hpp
 * Author: Michiel
 *
 * Created on 22 januari 2017, 16:22
 */

#ifndef CSVTRAITS_HPP
#define CSVTRAITS_HPP

#include <string>

template <typename T>
class CsvTraits;

template <>
class CsvTraits<unsigned int> {
    public:
        typedef unsigned int Type;
        int Zero() { return 0; }
};
template <>
class CsvTraits<int> {
    public:
        typedef int Type;
        int Zero() { return 0; }
};
template <>
class CsvTraits<unsigned short> {
    public:
        typedef unsigned int Type;
        int Zero() { return 0; }
};
template <>
class CsvTraits<short> {
    public:
        typedef int Type;
        int Zero() { return 0; }
};
template <>
class CsvTraits<std::string> {
    public:
        typedef std::string Type;
        int Zero() { std::string(""); }
};
template <>
class CsvTraits<double> {
    public:
        typedef double Type;
        int Zero() { return 0.0; }
};



#endif /* CSVTRAITS_HPP */

