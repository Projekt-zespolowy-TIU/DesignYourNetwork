#include "IPaddressBase.h"

#include <boost/asio/ip/address.hpp>
#include <iostream>
#include <QString>

#include "coreUtils.h"
#include "IPv4address.h"
#include "IPv4parser.h"
#include "IPv4mask.h"

namespace core {
    IPaddressBase IPaddressBase::operator& (const IPaddressBase& var) const
    {
        return (this->_IpAddress & var._IpAddress);
    };

    std::istream& operator>>(std::istream& in, IPaddressBase& b)
    {
        std::string tempS;
        in >> tempS;
        IPv4parser parser4;

        if(dynamic_cast<IPv4mask*>(&b))
        {
            auto regularV4address = parser4.ipFromString(tempS.c_str());
            IPv4mask mask_constraints{regularV4address._IpAddress};
            b = mask_constraints;
        }
        else if(dynamic_cast<IPv4address*>(&b))
        {
            b = parser4.ipFromString(tempS.c_str());
        }
        //else if(dynamic_cast<IPv6address*>(&b))
        else throw NotImplemented{}; //TODO: error handling

        return  in;
    };

    QString IPaddressBase::asStringDec() const
    {
        boost::asio::ip::address tempAddress;

        if(_IpAddress.size() == 32) tempAddress = boost::asio::ip::make_address_v4(_IpAddress.to_ulong());
        else if(_IpAddress.size() == 128) throw NotImplemented{};
        else throw NotImplemented{}; //TODO: error handling

        return tempAddress.to_string().c_str();
    };

    QString IPaddressBase::asStringBin() const
    {
        std::string stringBinary;
        if(_IpAddress.size() == 32)
        {
            boost::to_string(_IpAddress, stringBinary);
            for(short i = 8; i <= 26; i += 9)
                stringBinary.insert(stringBinary.begin()+ i, '.');
            return stringBinary.c_str();
        }
        else if(_IpAddress.size() == 128) throw NotImplemented{"Printing ipv6 is not implemented"};
        else throw NotImplemented{}; //TODO: error handling
    };

    bool IPaddressBase::operator==(const IPaddressBase& x) const
    {
        return this->_IpAddress == x._IpAddress;
    };

    IPaddressBase IPaddressBase::operator| (const IPaddressBase& var) const
    {
        return (this->_IpAddress | var._IpAddress);
    };

    bool IPaddressBase::operator!=(const IPaddressBase& x) const
    {
        return this->_IpAddress != x._IpAddress;
    };
};
