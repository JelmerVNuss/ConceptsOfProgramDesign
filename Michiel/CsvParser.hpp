/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvParser.hpp
 * Author: Michiel
 *
 * Created on January 19, 2017, 12:18 PM
 */

#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include <string>
#include <vector>

/*
 * From here untill class definition: unused old template code.
 * Actual code begins on line 96.
 * 
 * The template codes following, untill the class, are largely from
 * https://monoinfinito.wordpress.com/series/introduction-to-c-template-metaprogramming/
 */

/* Define List */
struct NIL {
	typedef NIL Head;
	typedef NIL Tail;
};

template <typename H, typename T=NIL> struct Lst {
	typedef H Head;
	typedef T Tail;
};
/***************/

/* Define Char */
template <char N> struct Char{ static const char result = N; };
/***************/

typedef Lst<Char<'a'>, Lst<Char<'b'> > > List;

/* Print words 
template <typename LST> 
struct NthChar {
    static const Char result = typename LST::Head::result;
};
/***************/

/* Basic List operations */
template <typename LST> struct Length {
    static const unsigned int result = 1 + Length< typename LST::Tail >::result;
};

template <> struct Length<NIL> {
    static const unsigned int result = 0;
};
/*************************/

/* Equality operator */
template <class X, class Y> struct Eq { static const bool result = false; };
template <class X> struct Eq<X, X> { static const bool result = true; };
/*********************/
/*
template <char a, char b> struct CEQ {
    static const bool result = a == b;
};

template <typename LST, const char* arr> struct Equals {
    static const bool result = CEQ<LST::Head::result, *arr >::result && Equals<Lst::Tail, (const char*)arr+1 >::result;
};

template <> struct Equals<NIL, const char*> {
    static const bool result = true;
};
/*************************/
/*
template<char a> struct IsNullTerminator {
    static const bool result = a == '\0';
};

template<const char* a> struct C_String_Length {
    static const unsigned int result = 1 + IsNullTerminator<*a>::result ? 0 : C_String_Length<a + 1>::result;
};

/* Get Nth in list */
template <typename LST, int N> struct Nth {
    typedef typename LST::Tail Tail;
    typedef typename Nth<Tail, N-1>::result result;
};
 
template <typename LST> struct Nth<LST, 0> {
    typedef typename LST::Head result;
};
/*******************/

/* Actual code begins here */

/*
 * Simple class that reads a CSV files header and second line (for types)
 * and generates C++ code.
 */
class CsvParser {
public:
    CsvParser();
    CsvParser(const CsvParser& orig);
    virtual ~CsvParser();
    
    void ParseToTemplate(const char* csv_path, char seperator);
private:
    std::vector<std::string> split_line(std::string const& line, char seperator);
    
    /*
     * The following functions were used to generate template-ready lists of characters.
     */
    std::string parse_to_template(const std::vector<std::string>& fields);
    std::string rec_parse_field(std::string field);
    std::string rec_parse_list(const std::vector<std::string>& list);
};

#endif /* CSVPARSER_HPP */

