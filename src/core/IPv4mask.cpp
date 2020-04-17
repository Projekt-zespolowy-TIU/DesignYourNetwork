#include "IPv4mask.h"

#include <exception>
#include <boost/dynamic_bitset.hpp>

#include "IPmaskBase.h"

namespace core {
    IPv4mask::IPv4mask(const boost::dynamic_bitset<>& maskAddress): IPmaskBase{maskAddress}
    {
        boost::dynamic_bitset<> bits(32);
        bits.set(); //255.255.255.255
        if(maskAddress == bits) return;
        else
        {
            for(size_t i = 0; i != bits.size(); ++i)
            {
                bits.flip(i);
                if(maskAddress == bits) return;
            }
        }
        throw std::invalid_argument("IP is not a mask");
    }
}
