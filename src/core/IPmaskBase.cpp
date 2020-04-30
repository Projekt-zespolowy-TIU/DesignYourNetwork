#include "IPmaskBase.h"

namespace core{
    IPmaskBase::IPmaskBase(const boost::dynamic_bitset<> &maskAddress): IPaddressBase{maskAddress}
    {
        boost::dynamic_bitset<> bits(maskAddress.size());
        bits.set();
        if(maskAddress == bits) return;
        else
        {
            for(size_t i = 0; i != bits.size(); ++i)
            {
                bits.flip(i);
                if(maskAddress == bits) return;
            };
        };
        throw std::invalid_argument("IP is not a mask");
    };

    short IPmaskBase::getPrefix() const
    {
        return _IpAddress.count();
    };
};
