#ifndef IPV4ADD_H
#define IPV4ADD_H

#include <string>
#include <bitset>
#include <iostream>

namespace core{
    class ipv4add
    {
    public:
        ipv4add() {};
        ipv4add(const std::bitset<32>& ipaddress) { _ipAddress = ipaddress; }
        ipv4add(std::string ipaddress);

        const std::string asString() const;
        const std::bitset<32> asBin() const;

        friend std::ostream & operator << (std::ostream &out, const ipv4add &c);
        friend std::istream & operator >> (std::istream &in,  ipv4add &c);

    private:
        std::bitset<32> _ipAddress;
    };
}

#endif // IPV4ADD_H
