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

/* Find position in list */
template <class Elm, class LST> struct Position {
    private:
    typedef typename LST::head H;
    typedef typename LST::tail T;
    static const bool found = Eq<H, Elm>::result;
    public:
    static const int result = found? 1 : 1 + Position<Elm, T>::result;
};
 
template <class Elm> struct Position<Elm, NIL> {
    static const int result = 0;
};
/*************************/

/* Get Nth in list */
template <typename LST, int N> struct Nth {
    typedef typename LST::Tail Tail;
    typedef typename Nth<Tail, N-1>::result result;
};
 
template <typename LST> struct Nth<LST, 0> {
    typedef typename LST::head result;
};
/*******************/

class CsvParser {
public:
    
    CsvParser();
    CsvParser(const CsvParser& orig);
    virtual ~CsvParser();
    
    void ParseToTemplate(const char* csv_path, const char* template_file, char seperator = ';');
private:
    std::vector<std::string> split_line(std::string const& line, char seperator);
    std::string parse_to_template(const std::vector<std::string>& fields);
    std::string rec_parse_field(std::string field);
    std::string rec_parse_list(const std::vector<std::string>& list);
};

#endif /* CSVPARSER_HPP */

