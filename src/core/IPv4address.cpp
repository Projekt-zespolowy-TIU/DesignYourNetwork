#include "IPv4address.h"

#include <string>
#include <sstream>
#include <boost/asio/ip/address.hpp>

#include "coreUtils.h"

namespace core {
    IPv4address::IPv4address(const boost::dynamic_bitset<>& ip)
    {
        if(ip.size() != 32)
            throw IPFormatExcept{"Passed value cannot be converted into valid IP version 4"};

        _IpAddress = ip;
    }

    IPv4address::IPv4address(const QString& ip)
    {
        *this = _Parser->ipFromString(ip);
    }

    IPv4address::IPv4address(const IPv4address& rhs)
    {
        this->_IpAddress = rhs._IpAddress;
    }

    IPv4address& IPv4address::operator=(const IPv4address& rhs)
    {
        this->_IpAddress = rhs._IpAddress;
        this->_Parser = rhs._Parser;
        return *this;
    }

    QString IPv4address::asStringDec() const noexcept
    {
        return boost::asio::ip::make_address_v4(_IpAddress.to_ulong()).to_string().c_str();
    }

    QString IPv4address::asStringBin() const noexcept
    {
        std::string stringBinary;
        boost::to_string(_IpAddress, stringBinary);

        std::stringstream ss;
        ss << stringBinary.at(0);

        for(size_t i = 1; i < stringBinary.size(); i++)
        {
            if((i % 8) == 0)
            {
                ss << '.';
            }
            ss << stringBinary.at(i);
        }
        return ss.str().c_str();
    }

    IPv4address* IPv4address::_cloneImpl() const noexcept
    {
        return new IPv4address(*this);
    }

    std::istream& operator>>(std::istream& in, IPv4address& rhs)
    {
        QString tempS;
        in >> tempS;

        rhs = tempS;

        return  in;
    }
};
