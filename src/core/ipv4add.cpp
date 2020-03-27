#include "ipv4add.h"
#include "ipv4parser.h"

#include <string>
#include <bitset>
#include <iostream>

namespace core {
    ipv4add::ipv4add(std::string ipaddress):
        _ipAddress( ipv4parser::stringDecimal2octets(ipaddress) )
    {
    }

    std::string ipv4add::asStringDec() const
    {
        return ipv4parser::octetsToString(_ipAddress);
    }

    std::string ipv4add::asStringOct() const
    {
        return ipv4parser::octetsToString(_ipAddress);
    }

    std::bitset<32> ipv4add::asBin() const
    {
        return _ipAddress;
    }

    std::ostream& operator << (std::ostream& out, const ipv4add& c)
    {
        out << ipv4parser::octetsToString(c.asBin()) << std::endl;
        return out;
    }

    std::istream& operator >> (std::istream& in, ipv4add& c)
    {
        std::string a;
        in >> a;
        c = a;
        return in;
    }
}
