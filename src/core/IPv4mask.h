#ifndef IIPMASK_H
#define IIPMASK_H

#include <boost/dynamic_bitset.hpp>

#include "IPv4address.h"

namespace core {
    class IPv4mask final: public IPv4address
    {
    public:
        IPv4mask() {};
        IPv4mask(const boost::dynamic_bitset<>& maskAddress);
        short getPrefix();
    };
}

#endif // IIPMASK_H
