#ifndef IIPMASK_H
#define IIPMASK_H

#include <boost/dynamic_bitset.hpp>

#include "IPmaskBase.h"

namespace core {
    class IPv4mask final: public IPmaskBase
    {
    public:
        IPv4mask() : IPmaskBase(boost::dynamic_bitset<>(32)) {};
        IPv4mask(const boost::dynamic_bitset<>& maskAddress);
    };
}

#endif // IIPMASK_H
