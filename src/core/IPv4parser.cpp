#include "IPv4parser.h"

#include <string>
#include <boost/dynamic_bitset.hpp>

namespace core {
    boost::dynamic_bitset<> IPv4parser::stringDecimal2octets(std::string IP)
    {
        boost::dynamic_bitset<> octetContainer(32);
            for(short i = 0; i < 4; i++)
            {
                octetContainer <<= 8;
                auto position = IP.find_first_of('.');
                auto x = IP.substr(0, position);
                IP = IP.substr(++position);
                octetContainer |= boost::dynamic_bitset<>(32, std::stoll(x));
            }
            return octetContainer;
    }

    std::string IPv4parser::octetsToString(const boost::dynamic_bitset<>& octetsIP)
    {
        std::string stringBinary;
        boost::to_string(octetsIP, stringBinary);
        for(short i = 8; i <= 26; i+=9)
            stringBinary.insert(stringBinary.begin()+ i, '.');
        return stringBinary;
    }
}
