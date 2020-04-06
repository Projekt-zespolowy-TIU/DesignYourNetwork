#ifndef IPV4ADD_H
#define IPV4ADD_H

#include <string>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

namespace core{
    class ipv4add
    {
    public:
        ipv4add(): _ipAddress(32) {};
        ipv4add(const boost::dynamic_bitset<>& ipaddress): _ipAddress(ipaddress) {}
        ipv4add(std::string ipaddress);

        std::string asStringDec() const;
        std::string asStringOct() const;
        boost::dynamic_bitset<> asBin() const;

        friend std::ostream& operator << (std::ostream& out, const ipv4add& c);
        friend std::istream& operator >> (std::istream& in,  ipv4add& c);

    private:
        boost::dynamic_bitset<> _ipAddress;
    };
}

#endif // IPV4ADD_H
