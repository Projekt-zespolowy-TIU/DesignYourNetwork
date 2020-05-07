#include "IPmaskBase.h"

#include <boost/dynamic_bitset.hpp>
#include <stdexcept>
#include <istream>
#include <memory>
#include <string>

#include "IPv4parser.h"
#include "IPv4mask.h"
#include "coreUtils.h"

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
        return static_cast<short>(_IpAddress.count());
    };

    std::istream& operator>>(std::istream& in, std::shared_ptr<IPmaskBase>& b)
    {
        std::string tempS;
        in >> tempS;

        if(dynamic_cast<IPv4mask*>(&*b))
        {
            b = IPv4parser{}.ipMaskFromString(tempS.c_str());
        }
        //else if(dynamic_cast<IPv6mask*>(&*b))
        else throw NotImplemented{}; //TODO: error handling

        return in;
    };
};
