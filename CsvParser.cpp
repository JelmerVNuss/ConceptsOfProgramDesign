/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CsvParser.cpp
 * Author: Michiel
 * 
 * Created on January 19, 2017, 12:18 PM
 */

#include "CsvParser.hpp"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <sstream>


CsvParser::CsvParser() {
}

CsvParser::CsvParser(const CsvParser& orig) {
}

CsvParser::~CsvParser() {
}

void CsvParser::ParseToTemplate(const char* csv_path, const char* template_file, char seperator)
{
    std::string line;
    std::ifstream myfile (csv_path);
    std::ofstream output;
    std::string template_list = "";
    if (myfile.is_open())
    {
        getline(myfile, line);
        std::vector<std::string> fields = split_line(line, seperator);
        template_list = parse_to_template(fields);
        //std::cout << template_list;
//        while ( getline (myfile,line) )
//        {
//            std::cout << line << '\n';
//        }
        myfile.close();
    }
    
    std::stringstream file;
    file << "/* This file is generated from " << csv_path << " */\n\n";
    file << "#ifndef CSV_HPP\n#define CSV_HPP\n\n";
    //file << "struct NIL {\n\ttypedef NIL Head;\n\ttypedef NIL Tail;\n};\n\n";
    //file << "template <typename H, typename T=NIL> struct Lst {\n\ttypedef H Head;\n\ttypedef T Tail;\n};\n\n";
    //file << "template <char N> struct Char{ static const char result = N; };\n\n";
    file << "typedef " << template_list << " Fields; \n\n";
    file << "#endif /* CSV_HPP */";
    
    output.open(template_file, std::ios::out | std::ios::trunc);
    output << file.str();
    output.close();
    
    std::cout << file.str();
}

std::vector<std::string> CsvParser::split_line(const std::string& line, char seperator)
{
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = line.find(seperator, start)) != std::string::npos) 
    {
        tokens.push_back(line.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(line.substr(start));
    return tokens;
}

std::string CsvParser::parse_to_template(const std::vector<std::string>& fields)
{
    std::stringstream to_return;
    
    return rec_parse_list(fields);
}

std::string CsvParser::rec_parse_list(const std::vector<std::string>& list)
{
    if(list.empty())
        return "";
    
    std::stringstream to_return;
    
    to_return << "Lst<" << rec_parse_field(list[0]);
    
    if(list.size() > 1)
        to_return << ", " << rec_parse_list(std::vector<std::string>(list.begin() + 1, list.end()));
    
    to_return << " >";
    
    return to_return.str();
}

std::string CsvParser::rec_parse_field(std::string field)
{
    if(field.empty())
        return "";
    
    std::stringstream to_return; 
    
    to_return << "Lst<Char<'" << field[0] << "'>";
    if(field.size() > 1)
        to_return << ", " << rec_parse_field(field.substr(1,field.size() - 1));
    
    to_return << " >";
    
    return to_return.str();
}

std::vector<std::string> split(const std::string &text, char sep) {

}