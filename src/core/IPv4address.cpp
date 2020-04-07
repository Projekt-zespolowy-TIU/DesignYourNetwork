#include "IPv4address.h"

#include <string>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

#include "IPv4parser.h"

namespace core {
    IPv4address::IPv4address(std::string ipaddress):
        _IpAddress( IPv4parser::stringDecimal2octets(ipaddress) )
    {
    }

    std::string IPv4address::asStringDec() const
    {
        return IPv4parser::octetsToString(_IpAddress);
    }

    std::string IPv4address::asStringOct() const
    {
        return IPv4parser::octetsToString(_IpAddress);
    }

    boost::dynamic_bitset<> IPv4address::asBin() const
    {
        return _IpAddress;
    }

    std::ostream& operator<< (std::ostream& out, const IPv4address& c)
    {
        out << IPv4parser::octetsToString(c.asBin()) << std::endl;
        return out;
    }

    std::istream& operator>> (std::istream& in, IPv4address& c)
    {
        std::string a;
        in >> a;
        c = a;
        return in;
    }
}
