#include "IPv6address.h"

#include <string>
#include <sstream>
#include <boost/asio/ip/address.hpp>

#include "coreUtils.h"

namespace core {
    IPv6address::IPv6address(const boost::dynamic_bitset<>& ip)
    {
        if(ip.size() != 128)
            throw IPFormatExcept{"Passed value cannot be converted into valid IP version 6"};

        _IpAddress = ip;
    }

    IPv6address::IPv6address(const QString& ip)
    {
        *this = _Parser->ipFromString(ip);
    }

    IPv6address::IPv6address(const IPv6address& rhs)
    {
        this->_IpAddress = rhs._IpAddress;
    }

    IPv6address& IPv6address::operator=(const IPv6address& rhs)
    {
        this->_IpAddress = rhs._IpAddress;
        this->_Parser = rhs._Parser;
        return *this;
    }

    QString IPv6address::asStringDec() const noexcept
    {
        auto bitsetArray =
                this->_convertBitsetIPv6ToArrayUCharIPv6(this->_IpAddress);
        auto addv6 = boost::asio::ip::make_address_v6(bitsetArray);
        return addv6.to_string().c_str();
    }

    QString IPv6address::asStringBin() const noexcept
    {
        std::string stringBinary;
        boost::to_string(_IpAddress, stringBinary);

        std::stringstream ss;
        ss << stringBinary.at(0);

        for(size_t i = 1; i < stringBinary.size(); i++)
        {
            if((i % 16) == 0)
            {
                ss << ':';
            }
            ss << stringBinary.at(i);
        }
        return ss.str().c_str();
    }

    std::array<unsigned char, 16> IPv6address::_convertBitsetIPv6ToArrayUCharIPv6(
            const boost::dynamic_bitset<>& bitset) const noexcept
    {
        std::string tempString;
        boost::to_string(bitset, tempString);
        std::reverse(tempString.begin(), tempString.end());

        std::array<boost::dynamic_bitset<>, 16> tableBitset;

        int bitCounter = 0;
        int arrayElementCounter = 0;
        for(const auto& bit : tempString)
        {
            if(bit == '1')
                tableBitset.at(arrayElementCounter).push_back(true);
            else
                tableBitset.at(arrayElementCounter).push_back(false);

            bitCounter++;
            if(!(bitCounter % 8))
            {
                arrayElementCounter++;
            }
        }

        std::reverse(tableBitset.begin(), tableBitset.end());

        std::array<unsigned char, 16> tableBitsetReturnType;

        for(size_t i = 0; i < tableBitsetReturnType.size(); i++)
        {
            tableBitsetReturnType.at(i) = tableBitset.at(i).to_ulong();
        }

        return tableBitsetReturnType;
    }

    IPv6address* IPv6address::_cloneImpl() const noexcept
    {
        return new IPv6address(*this);
    }

    std::istream& operator>>(std::istream& in, IPv6address& rhs)
    {
        throw NotImplemented{};
        QString tempS;
        in >> tempS;

        rhs = tempS;

        return  in;
    }
}
