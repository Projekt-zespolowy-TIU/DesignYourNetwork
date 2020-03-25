#include "ipv4parser.h"

namespace core {
    std::bitset<32> ipv4parser::stringDecimal2octets(std::string IP)
    {
        std::bitset<32> octetContainer;
            for(int i = 0; i < 4; i++)
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
        stringBinary.insert(stringBinary.begin()+ 8, '.');
        stringBinary.insert(stringBinary.begin()+ 17, '.');
        stringBinary.insert(stringBinary.begin()+ 26, '.');
        return stringBinary;
    }
}
