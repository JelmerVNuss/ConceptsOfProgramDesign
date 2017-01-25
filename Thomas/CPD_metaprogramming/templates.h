#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <string>
#include <iostream>

using namespace std;

//------------------------------------------------------

//Class used to store constant strings
//Author: Scott Schur - C++ 11: New Tools for Class and Library Authors, 2012
//Source: https://github.com/boostcon/cppnow_presentations_2012

class str_const { // constexpr string
public:
    const char* const p_;
    const std::size_t sz_;
    template<std::size_t N>
    constexpr str_const(const char(&a)[N]) : // constructor
	p_(a), sz_(N - 1) {}
    constexpr char operator[](std::size_t n) { // [] - operator
	return n < sz_ ? p_[n] :
	throw std::out_of_range("");
    }
    constexpr std::size_t size() { return sz_; } // size()
};
//--------------------------------------------------------


//primary template to calculate powers of 10 in compile time
template<int N>  class Pow10
{
public:
    enum { result = 10 * Pow10<N - 1>::result };
};
//specialization template
template<> class Pow10<0>
{
public:
    enum { result = 1 };
};

//primary template to read int from character array
template< int DIM, typename T> class CharToInt
{
public:
    static int result(T* ptr) {
	return Pow10<DIM - 1>::result * (*ptr - 48) + CharToInt<DIM - 1, T>::result(ptr + 1);
    }
};
//specialization template
template<typename T> class CharToInt<1, T >
{
public:
    static int result(T* ptr) {
        return *ptr - 48;
    }
};
//(helper) template to define convenience function "ParseInt"
template <int DIM, typename T>
inline int ParseInt(T* a)
{
	return CharToInt<DIM, T>::result(a);
}

#endif /* TEMPLATES_H */

