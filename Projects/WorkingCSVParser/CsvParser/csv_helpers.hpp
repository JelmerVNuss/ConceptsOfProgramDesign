#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/tokenizer.hpp>
namespace csv {
    // Tokenized string iterator
    typedef boost::tokenizer<boost::escaped_list_separator<char> >::iterator tokenizedString;

    /*
     * This method will be called wihin the helper and filler function to check
     * whether the amount of tokens matches the amount of elements in the tuple.
     */
    void checkIteratorRange(const tokenizedString& curr, const tokenizedString& end) throw(std::out_of_range)
    {
        if(curr == end){
            throw(std::out_of_range("Not enough parameters building the tuple."));
        }
    }
    
    /*
     * Inductive case: Fill the N'th element of the tuple by parsing the N'th
     * element from the list of tokens to the type located at the N'th posiion
     * in the tuple.
     */
    template<class Tuple, int N >
    struct helper {
        static void fill(Tuple& tuple, tokenizedString& i, tokenizedString& end)
        {
            using namespace boost::tuples;             
            typedef typename element<length<Tuple>::value - N - 1, Tuple>::type value_type;
            checkIteratorRange(i, end);
            get<length<Tuple>::value - N - 1>(tuple) = boost::lexical_cast<value_type>(i -> c_str());
            ++i;
            helper<Tuple,N-1>::fill(tuple, i, end);
        }
    };    

    /*
     * Inductive case: Fill the N'th element of the tuple by parsing the N'th
     * element from the list of tokens to the type located at the N'th posiion
     * in the tuple.
     */
    template<class Tuple>
    struct helper<Tuple, 0> 
    {
        static void fill(Tuple& tuple, tokenizedString& i, tokenizedString& end)
        {
            using namespace boost::tuples;
            typedef typename boost::tuples::element<length<Tuple>::value - 1, Tuple>::type value_type;
            checkIteratorRange(i, end);
            get<length<Tuple>::value - 1>(tuple) = boost::lexical_cast<value_type>(i -> c_str());
            ++i;
        };
    };

    /*
     * Filler struct which get called by the CSV Iterator.
     * Uses the helper to construct the tuple.
     */
    template<class Tuple>
    struct filler 
    {
        static void fill(Tuple& tuple, tokenizedString&& begin,tokenizedString&& end)
        {
            checkIteratorRange(begin, end);
            helper<Tuple, boost::tuples::length<Tuple>::value - 1>::fill(tuple, begin, end);
        }
    };
};