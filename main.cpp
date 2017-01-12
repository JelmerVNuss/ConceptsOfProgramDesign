

#include <bits/c++config.h>
#include <iostream>
#include <vector>
#include <type_traits>
#include <string>
#include <tuple>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

template <std::size_t I = 0, typename Iterator, typename ...Ts>
inline typename std::enable_if< I == sizeof...(Ts), void>::type
parse(std::tuple<Ts...> &tuple, Iterator it)
{
};

template <std::size_t I = 0, typename Iterator, typename ...Ts>
inline typename std::enable_if< I < sizeof...(Ts), void>::type 
parse(std::tuple<Ts...> &tuple, Iterator it)
{
	std::get<I>(tuple) = boost::lexical_cast<typename std::tuple_element<I, std::tuple<Ts...> >::type >(*it);
	parse<I + 1, Iterator, Ts...>(tuple, ++it);
};

template<bool C, typename Ta, typename Tb>
class IfThenElse;

template<typename Ta, typename Tb>
class IfThenElse<true, Ta, Tb> {
    public:
        typedef Ta Result;
};

int main(int argc, char *argv[])
{
	std::string sample = "first,second,3,4,5.01,sei";
	std::tuple<std::string, std::string, int, int, double, std::string> values;
	std::vector<std::string> fields;

	boost::split(fields, sample, boost::is_any_of(","));

        for(int i = 0; i < fields.size(); i++)
            std::cout << fields[i] << std::endl;

	parse(values, fields.begin());

        using VesselDatatype = std::tuple<std::string, std::string, int, int, double, std::string>;
        
//        int i = 0;
//        auto VesselLoaderFunc  = [&i] (VesselDatatype data) {
//            std::cout << i << " Vessel: " << data._M_head() << std::endl;
//            ++i;
//        };
	std::cout << (std::get<2>(values) * 5) << std::endl;
}