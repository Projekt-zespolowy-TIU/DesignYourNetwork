#include "IPaddress.h"

#include "coreUtils.h"

namespace core {
    IPaddress::IPaddress(const boost::dynamic_bitset<>& ip):
        _IpAddress{ip}
    {
    }

    std::unique_ptr<IPaddress> IPaddress::clone() const noexcept
    {
        return std::unique_ptr<IPaddress>(_cloneImpl());
    }

    short IPaddress::getPrefix() const
    {
        if(!isMask())
            throw IPFormatExcept{"This IP address is not proper IP mask-like address."};
        return static_cast<short>(_IpAddress.count());
    }

    short IPaddress::getAddressLength() const noexcept
    {
        return static_cast<short>(_IpAddress.size());
    }

    boost::dynamic_bitset<> IPaddress::raw() const noexcept
    {
        return _IpAddress;
    }

    QString IPaddress::asStringBin() const noexcept
    {
        std::string temp;
        boost::to_string(_IpAddress, temp);
        return temp.c_str();
    }

    QString IPaddress::asStringDec() const noexcept
    {
        return asStringBin();
    }

    bool IPaddress::isMask() const noexcept
    {
        boost::dynamic_bitset<> bits(_IpAddress.size());
        bits.set();
        if(_IpAddress == bits) return true;
        else
        {
            for(size_t i = 0; i != bits.size(); ++i)
            {
                bits.flip(i);
                if(_IpAddress == bits) return true;
            };
        };

        return false;
    }

    IPaddress* IPaddress::_cloneImpl() const noexcept
    {
        return new IPaddress(*this);
    }

    bool operator==(const IPaddress& lhs, const IPaddress& rhs) noexcept
    {
        return lhs.raw() == rhs.raw();
    }

    bool operator!=(const IPaddress& lhs, const IPaddress& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    boost::dynamic_bitset<> operator&(const IPaddress& lhs, const IPaddress& rhs) noexcept
    {
        return lhs.raw() & rhs.raw();
    };

    boost::dynamic_bitset<> operator|(const IPaddress& lhs, const IPaddress& rhs) noexcept
    {
        return lhs.raw() | rhs.raw();
    }
}
