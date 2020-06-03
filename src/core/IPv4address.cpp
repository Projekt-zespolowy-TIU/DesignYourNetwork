#include "IPv4address.h"

#include <string>
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

    IPv4address::IPv4address(const IPv4address &rhs)
    {
        this->_IpAddress = rhs._IpAddress;
    }

    IPv4address& IPv4address::operator=(const IPv4address &rhs)
    {
        this->_IpAddress = rhs._IpAddress;
        this->_Parser = rhs._Parser;
        return *this;
    }

    QString IPv4address::asStringDec() const
    {
        return boost::asio::ip::make_address_v4(_IpAddress.to_ulong()).to_string().c_str();
    }

    QString IPv4address::asStringBin() const
    {
        std::string stringBinary;
        boost::to_string(_IpAddress, stringBinary);

        for(short i = 8; i <= 26; i += 9)
            stringBinary.insert(stringBinary.begin()+ i, '.');

        return stringBinary.c_str();
    }

    IPv4address* IPv4address::_cloneImpl() const
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
