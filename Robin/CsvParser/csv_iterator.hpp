#include <string>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include "csv_helpers.hpp"

namespace csv {
    template<class Tuple>
        class iterator {
            private:
                bool isBadFormat;
                std::istream* inputStream;
                std::string currentLine;
                bool isCurrValid; // Marks that currentResult is no longer valid
                Tuple currentResult; // Useful for passing pointers around
            public:
                
                /**
                 * Constructor denoting end of range
                 */
                iterator() : isBadFormat(true),isCurrValid(true) 
                {
                }

                iterator(std::istream& in) : isBadFormat(false), inputStream(&in),isCurrValid(true) 
                {
                    //Read the headers (names of the columns).
                    std::string headers;
                    std::getline(*inputStream, headers);
                    this->operator++();
                }

                Tuple operator*() throw (boost::bad_lexical_cast, std::out_of_range) 
                {
                    if(isCurrValid)
                    {
                        try 
                        {
                            using namespace boost;
                            typedef tokenizer<escaped_list_separator<char> > Tokens;
                            Tokens tokens(currentLine);
                            filler<Tuple>::fill(currentResult,tokens.begin(),tokens.end());
                        } catch (boost::bad_lexical_cast& ex)
                        {
                            // Catch cast exception.
                            isBadFormat = true;
                            throw(ex);
                        } catch (std::out_of_range& ex)
                        {
                            // Exception when not enough columns in the record
                            isBadFormat = true;
                            throw(ex);
                        }
                        //We are done with the current row.
                        isCurrValid = false;
                    }
                    return currentResult;
                }

                bool operator==(const iterator& other) {
                    return (isBadFormat) && other.isBadFormat;
                }

                bool operator!=(const iterator& other) {
                    return !(*this == other);
                }

                iterator& operator++() {
                    bool couldRead = std::getline(*inputStream, currentLine);
                    isBadFormat = !couldRead;
                    isCurrValid = true;
                    return *this;
                }
        };
};
