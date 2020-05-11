#include "IPmaskBase.h"

#include <boost/dynamic_bitset.hpp>
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

        throw IPFormatExcept("Passed value cannot be converted into valid IP version 4 mask");
    };

    short IPmaskBase::getPrefix() const
    {
        return static_cast<short>(_IpAddress.count());
    }

    short IPmaskBase::getLength() const
    {
        return static_cast<short>(_IpAddress.size());
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
