#include <bits/c++config.h>
#include <iostream>
#include <vector>
#include <type_traits>
#include <string>
#include <tuple>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

template <typename T> inline
T const& max (T const& a, T const& b)
{
    return a<b ? b : a;
}

template <typename T, ... list> inline
T const& max (T const& a, T const& b, T const& x)
{
    return max (a, max(b, x));
}


template <typename T> inline
T const& min (T const& a, T const& b)
{
    return a>b ? b : a;
}

template <typename T, ... list> inline
T const& min (T const& a, T const& b, T const& x)
{
    return min (a, min(b, x));
}