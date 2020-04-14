#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include <boost/dynamic_bitset.hpp>

#include "IPaddressBase.h"

namespace core{
    class IPv4address: public IPaddressBase
    {
    public:
        IPv4address(): IPaddressBase(boost::dynamic_bitset<>(32)) {};
        IPv4address(const boost::dynamic_bitset<>& ipaddress): IPaddressBase(ipaddress) {};
    };
}

#endif // IPV4ADDRESS_H
