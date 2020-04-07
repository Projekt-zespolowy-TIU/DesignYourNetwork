#ifndef IPV4PARSER_H
#define IPV4PARSER_H

#include <string>
#include <boost/dynamic_bitset.hpp>

namespace core{
    class IPv4parser
    {
    public:
        static boost::dynamic_bitset<> stringDecimal2octets(std::string decimalDottedAddress);
        static std::string octetsToString(const boost::dynamic_bitset<>& octetsIP);
    };
}

#endif // IPV4PARSER_H
