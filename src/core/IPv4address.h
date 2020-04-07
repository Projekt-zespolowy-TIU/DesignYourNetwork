#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include <string>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

namespace core{
    class IPv4address
    {
    public:
        IPv4address(): _IpAddress(32) {};
        IPv4address(const boost::dynamic_bitset<>& ipaddress): _IpAddress(ipaddress) {}
        IPv4address(std::string ipaddress);

        std::string asStringDec() const;
        std::string asStringOct() const;
        boost::dynamic_bitset<> asBin() const;

        friend std::ostream& operator<< (std::ostream& out, const IPv4address& c);
        friend std::istream& operator>> (std::istream& in,  IPv4address& c);

    private:
        boost::dynamic_bitset<> _IpAddress;
    };
}

#endif // IPV4ADDRESS_H
