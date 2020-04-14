#include "IPaddressBase.h"

#include <boost/asio/ip/address.hpp>
#include <iostream>
#include <string>

#include "coreUtils.h"
#include "IPv4address.h"
#include "IPv4parser.h"

namespace core {
    IPaddressBase IPaddressBase::operator& (const IPaddressBase& var) const
    {
        return (this->_IpAddress & var._IpAddress);
    }

    std::istream& operator>>(std::istream& in, IPaddressBase& b)
    {
        std::string tempS;
        in >> tempS;

        if(dynamic_cast<IPv4address*>(&b))
        {
            IPv4parser parser;
            b = parser.ipFromString(tempS);
        }
        //else if(dynamic_cast<IPv6address*>(&b))
        else throw NotImplemented{}; //TODO: error handling

        return  in;
    }

    std::string IPaddressBase::asStringDec() const
    {
        boost::asio::ip::address tempAddress;

        if(_IpAddress.size() == 32) tempAddress = boost::asio::ip::make_address_v4(_IpAddress.to_ulong());
        else if(_IpAddress.size() == 128) throw NotImplemented{};
        else throw NotImplemented{}; //TODO: error handling

        return tempAddress.to_string();
    }
}
