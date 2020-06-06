#include "IPv6mask.h"

#include "coreUtils.h"

namespace core {
    IPv6mask::IPv6mask(const boost::dynamic_bitset<>& maskAddress):
        IPv6address{maskAddress}
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

        throw IPFormatExcept("Passed value cannot be converted into valid IP version 6 mask");
    }

    IPv6mask::IPv6mask(const QString& ipAddress)
    {
        *this = _Parser->ipFromString(ipAddress);
    }

    IPv6mask *IPv6mask::_cloneImpl() const
    {
        return new IPv6mask(*this);
    }

    std::istream& operator>>(std::istream& in, IPv6mask& rhs)
    {
        QString tempS;
        in >> tempS;

        rhs = tempS;

        return in;
    };
};
