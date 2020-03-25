#ifndef IPV4PARSER_H
#define IPV4PARSER_H

#include <string>
#include <bitset>

namespace core{
    class ipv4parser
    {
    public:
        static std::bitset<32> stringDecimal2octets(std::string decimalDottedAddress);
        static std::string octetsToString(const std::bitset<32> &octetsIP);
    };
}

#endif // IPV4PARSER_H
