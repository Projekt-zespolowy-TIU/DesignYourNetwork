#include "IPv4mask.h"

#include "coreUtils.h"

namespace core {
    IPv4mask::IPv4mask(const boost::dynamic_bitset<>& maskAddress): IPv4address{maskAddress}
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
    }

    IPv4mask::IPv4mask(const QString& ipAddress): IPv4address(ipAddress)
    {
        *this = _Parser->ipFromString(ipAddress);
    }

    IPv4mask *IPv4mask::_cloneImpl() const
    {
        return new IPv4mask(*this);
    }

    std::istream& operator>>(std::istream& in, IPv4mask& rhs)
    {
        QString tempS;
        in >> tempS;

        rhs = tempS;

        return in;
    };
};
