#include "ipv4parser.h"

#include <bitset>
#include <string>

namespace core {
    std::bitset<32> ipv4parser::stringDecimal2octets(std::string IP)
    {
        std::bitset<32> octetContainer;
            for(short i = 0; i < 4; i++)
            {
                octetContainer <<= 8;
                auto position = IP.find_first_of('.');
                auto x = IP.substr(0, position);
                IP = IP.substr(++position);
                octetContainer |= std::bitset<32>(std::stoll(x));
            }
            return octetContainer;
    }

    std::string ipv4parser::octetsToString(const std::bitset<32>& octetsIP)
    {
        auto stringBinary = octetsIP.to_string();
        for(short i = 8; i <= 26; i+=9)
            stringBinary.insert(stringBinary.begin()+ i, '.');
        return stringBinary;
    }
}
